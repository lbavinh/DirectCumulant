#ifndef MULTICUMULANTS_CORRELATOR_H
#define MULTICUMULANTS_CORRELATOR_H

#include "MultiCumulants/QVectorSet.h"
#include "MultiCumulants/QTerms.h"

#include "vendor/loguru/loguru.hpp"

#include <set>
#include <utility> 
#include <sstream>
#include <iomanip>

namespace cumulant{

    class Correlator{

    public:
        bool DEBUG = false;
        Complex v;
        Real w;

        std::string repr;
        NativeMask _m;

        Correlator() : v(0, 0), w(0) {

        }

        Correlator( NativeMask m, QVectorMap &qvm) : v(0, 0), w(0) {
            build( m, qvm );
        }

        ~Correlator()
        {

        }

        Correlator& operator+=(const Correlator& rhs){
            assert( this->_m == rhs._m && "Cannot add Correlators of different terms" );
            this->v += rhs.v;
            this->w += rhs.w;

            return *this;
        }

        Correlator& operator*=(const Correlator& rhs){
            assert( this->_m == rhs._m && "Cannot operate on Correlators of different terms" );
            this->v *= rhs.v;
            this->w *= rhs.w;

            return *this;
        }

        static int factorial( int n ){
            if ( n <= 1 ) return 1;
            return n * Correlator::factorial( n - 1 );
        }

        static size_t countSetBits(NativeMask m){
            size_t count = 0;
            while (m){
                m &= (m-1) ;
                count++;
            }
            return count;
        }

        // im is the one in the compressed space
        // mm is the mask in the full space
        // example :
        // given im=0101, and mm=00110101
        // returns rm = 00010001, ie 1st and 3rd set bits in mask
        static NativeMask expandMask( NativeMask im, NativeMask mm, size_t start = 0, size_t stop = 8 ){

            vector<size_t> mlut;
            size_t n = 0;
            NativeMask rm = 0;
            for ( size_t i = start; i <stop; i++ ){
                NativeMask ithbit = (1 << i);
                NativeMask nthbit = (1 << n);
                if ( ithbit & mm ){
                    if ( nthbit & im )
                        rm |= ithbit;
                    n++; 
                }
            }
            return rm;
        }


        void build( NativeMask m, QVectorMap &qvm){
            //LOG_SCOPE_FUNCTION(INFO);
            // just save for printing
            // these are needed only for verbose printing
            this->_m = m;
            std::string cmsg = "";
            std::string cdelim = "";
            std::stringstream sstr;

            auto bm = std::bitset<MAX_SET_SIZE>( m );
            size_t maskBitsSet = Correlator::countSetBits( m );
            LOG_IF_F( INFO, DEBUG, "nSetBits(mask) = %lu", maskBitsSet );

            auto lut = NativeMaskLUTs[ maskBitsSet-1 ];    

            size_t nTerms = lut.size();
            
            Complex qv(0, 0);
            Real qw(0);

            for ( size_t i = 0; i < nTerms; i++ ){
                LOG_IF_F( INFO, DEBUG, "\n\nTERM %lu", i );
                
                double totalK = 1.0;
                Complex tv(0,0);
                Real tw(0);

                // only used for DEBUG printout
                std::string msg = "";
                std::string qmsg = "";
                std::string qvmsg = "";


                for ( size_t j = 0; j < lut[ i ].size(); j++ ){
                    NativeMask tm = lut[ i ][ j ];
                    NativeMask em = Correlator::expandMask( tm, m );
                    
                    auto btm = std::bitset<MAX_SET_SIZE>( tm );
                    auto bem = std::bitset<MAX_SET_SIZE>( em );
                    
                    LOG_IF_F( INFO, DEBUG, "NativeMask=%s", std::bitset<8>( tm ).to_string().c_str() );
                    LOG_IF_F( INFO, DEBUG, "expandMask( im=%s, mm=%s ) = %s", btm.to_string().c_str(), bm.to_string().c_str(), bem.to_string().c_str() );

                    if ( qvm.count( bem ) == 0 ){
                        LOG_F( WARNING, "QVector not found! mask=%s", bem.to_string().c_str() );
                    }
                    
                    auto q = qvm[ bem ];
                    double ck = (pow(-1, q._i) * factorial(q._i));
                    totalK *= ck;
                    if ( true == DEBUG ){
                        qmsg += "" + maskString( em );
                        msg += "*" + bem.to_string();
    
                        sstr.str("");
                        sstr << std::setprecision(3) << "Q(" <<q.getQV().real() << "+" << q.getQV().imag() << "i)";
                        qvmsg += sstr.str();
                    }


                    if ( 0 == j ){
                        tv = q.getQV();
                        tw = q.getW();
                    } else {
                        tv *= q.getQV();
                        tw *= q.getW();
                    }
                    

                } // loop on j

                if ( true == DEBUG ){
                    LOG_IF_F( INFO, DEBUG, "%ld * %s", (Coefficient)totalK, qmsg.c_str() );
                    if ( i == 0 || ( i > 0 && totalK < 0 ) )
                        cmsg += "\n" + std::to_string( (Coefficient)totalK ) + "*" + qmsg + "\t\t = " + qvmsg;
                    else if ( i > 0 && totalK > 0)
                        cmsg += "\n+" + std::to_string( (Coefficient)totalK ) + "*" + qmsg + "\t\t = " + qvmsg;
                }

                qv += tv * totalK;
                qw += tw * totalK;

            } // loop on i terms
    
            LOG_IF_F( INFO, DEBUG, "Correlator = %s", cmsg.c_str() );

            this->repr = cmsg;

            this->v = qv;
            this->w = qw;

            return;

        }

        Complex calculate(  ){
            if(this->w != 0. ) 
               return (this->v / this->w);
            else
               return 0;
        }


        inline NativeMask maskAndCompactify( NativeMask &im, NativeMask &mm, size_t start = 0, size_t stop = 8 ){

            // first do a quick check for validity
            
            NativeMask rm = im & mm;
            // require at least one bit to be 1
            if ( 0 == rm ) return 0;
            // then require that bits outside of mask are falsy
            if ( (im & (!mm)) > 0 ) return 0;

            NativeMask frm = 0;
            size_t n = 0;
            for ( size_t i = start; i < stop; i++ ){
                NativeMask ithbit = (1 << i);
                NativeMask nthbit = (1 << n);
                if ( ithbit & mm ){
                    // LOG_F( INFO, "Setting %luth bit", n );
                    if ( rm & ithbit )
                        frm |= (nthbit);
                    n++;
                }
            }

            // LOG_IF_F( INFO, DEBUG, "%s = (im=%s, mm=%s, rm=%s)", std::bitset<8>( frm ).to_string().c_str(), std::bitset<8>(im).to_string().c_str(), std::bitset<8>(mm).to_string().c_str(), std::bitset<8>(rm).to_string().c_str() );
            
            return frm;
        } // maskAndCompactify
    
        std::string toString(){
            std::string s = "";
            s += "Correlator( m=" + std::bitset<8>( _m ).to_string() + " )[ ";
            s += "v=" + std::to_string( v.real() ) + " + " + std::to_string( v.imag() ) + "i, ";
            s += "w=" + std::to_string( w );
            s += " ]";
            return s;

        }

        std::string maskString( NativeMask m){
            std::string msg = "Q(";
            std::string delim = "";
            for ( size_t i = 0; i < 8; i++ ){
                NativeMask ithbit = (1 << i);
                if ( ithbit & m ){
                    msg += delim + "A" + std::to_string( i+1 );
                    delim=",";
                }
            }
            msg += ")";
            return msg;
        }
        
    };
}


#endif
