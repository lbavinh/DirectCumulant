#ifndef MULTICUMULANTS_QTERMS_H
#define MULTICUMULANTS_QTERMS_H

#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <vector>

#include "MultiCumulants/Types.h"
#include "MultiCumulants/Subsets.h"
#include "MultiCumulants/Algorithm.h"
#include "MultiCumulants/NativeMaskLUT.h"

using std::vector;
namespace cumulant{

    class QTerms {

    public:
        void init_partition(std::vector<int> &s, std::vector<int> &m, int n, std::vector< std::bitset<MAX_SET_SIZE> > &bm, int &np ){

            s.resize( n );
            m.resize( n );
            bm.resize( n );

            for ( int i = 0; i < n; i++ ){
                s[i] = 1;
                m[i] = 1;
                bm[0].set( i );
            }

            np = 1;

        }

        int next_partition(std::vector<int> &s, std::vector<int> &m, int n, std::vector< std::bitset<MAX_SET_SIZE> > &bm, int &np ) {
            /* Update s: 1 1 1 1 -> 2 1 1 1 -> 1 2 1 1 -> 2 2 1 1 -> 3 2 1 1 -> 1 1 2 1 ... */
            int i = 0;
            ++s[i];
            while ((i < n - 1) && (s[i] > m[i] + 1)) {
                s[i] = 1;
                ++i;
                ++s[i];
            }

            /* If i has reached the n-1 element, then the last unique partitiong has been found*/
            if (i == n - 1)
                return 0;

            /* Because all the first i elements are now 1, s[i] (i + 1 element) is the largest. 
            So we update max by copying it to all the first i positions in m.*/
            int max = s[i];
            for (i = i - 1; i >= 0; --i)
                m[i] = max;


            for ( int i = 0; i < n; i++ ) {
                bm[i].reset();
            }

            np = 0;
            // converts [s] to bitmask
            for ( int i = 0; i < n; i++){
                bm[ s[i]-1 ].set( i );
                if ( s[i] > np )
                    np = s[i];
            }

            // np = max;

            return 1;
        }

        int factorial( int n ){
            if ( n <= 1 ) return 1;
            return n * factorial( n - 1 );
        }

        int coeff( int n ){
            return pow( -1, n-1 ) * factorial( n - 1 );
        }

        int kcoeff( std::vector<int> &s, int np ){
            std::vector<int> occupancy( np );
            for ( size_t i = 0; i < s.size(); i++ ){
                occupancy[ s[i]-1 ]++;
            }

            int c = 1;
            for ( int i = 0; i < np; i++ ){
                c *= coeff( occupancy[i] );
            }
            return c;

        }


        void generate( size_t n, bool cpp14 = false ){
            LOG_F( INFO, "test(%zu)", n );
            std::vector<int> s;
            std::vector<int> m;
            std::vector< std::bitset<MAX_SET_SIZE> > bm;
            int np = 0;
            init_partition( s, m, n, bm, np );

            size_t iTerm = 0;
            std::string msg = "\n{";
            std::string kmsg = "{";
            std::string nmsg = "{";

            int kco = kcoeff( s, np );
            
            LOG_F( INFO, "np=%d [%zu]", np, iTerm );
            LOG_F( INFO, "k( %d ) %d *\n%s", kco, coeff(np), maskString( bm, np ).c_str() );
            // LOG_F( INFO, "TERMS_%lu_MAP[%lu] = %s;", n, iTerm, cppString(  s, bm, np ).c_str() );

            msg += "\n\t" + cppString( bm, np, cpp14 );
            kmsg += std::to_string( kcoeff( s, np ) );
            nmsg += std::to_string( coeff( np ) );

            while( next_partition( s, m, n, bm, np ) ){
                iTerm++;
                LOG_F( INFO, "np=%d [%zu]", np, iTerm );
                LOG_F( INFO, "k( %d ) %d *\n%ss=%sm=%s", kcoeff( s, np ),coeff(np), maskString( bm, np ).c_str(), sString( s, n ).c_str(), sString( m, n ).c_str() );
                // LOG_F( INFO, "TERMS_%lu_MAP[%lu] = %s;", n, iTerm, cppString( s, bm, np ).c_str() );
                msg = msg + ",\n\t" + cppString( bm, np, cpp14 );
                kmsg += ", " + std::to_string( kcoeff( s, np ) );
                nmsg += ", " + std::to_string( coeff( np ) );
            }

            msg += "\n};";
            kmsg += "};";
            nmsg += "};";

            LOG_F( INFO, "\nNativeMaskLUT QTERMS_h%lu = %s", n, msg.c_str() );
            LOG_F( INFO, "\nCoefficient QTERMS_h%lu_KCOEFF[%lu] = %s", n, iTerm+1, kmsg.c_str() );
            LOG_F( INFO, "\nCoefficient QTERMS_h%lu_NCOEFF[%lu] = %s", n, iTerm+1, nmsg.c_str() );

            LOG_F( INFO, "test(%zu) complete", n );
        }

        std::string sString( std::vector<int> &s, size_t np ){
            std::string m="";
            for ( size_t i = 0; i < np; i++){
                m+= "[" + std::to_string(s[i]) + "]";
            }
            return m + "\n";
        }

        std::string maskString( std::vector< std::bitset<MAX_SET_SIZE> > bm, size_t np ){
            std::string s="";
            for ( size_t i = 0; i < np; i++){
                s+= "[" + bm[i].to_string() + "] \n";
            }
            return s;
        }

        std::string cppString( std::vector< std::bitset<MAX_SET_SIZE> > bm, size_t np, bool cpp14 = false ){
            std::string msg = "";
            msg += "{";
            // char buff[100];
            std::string delim = "";
            for ( size_t i = 0; i < np; i++){
                
                // snprintf( buff, sizeof(buff), "%llu", bm[i].to_ullong() );
                if ( true == cpp14 )
                    msg += ( delim + "0b" + bm[i].to_string() );
                else 
                    msg += (delim + std::to_string( bm[i].to_ullong() ) );
                delim = ", ";
            }
            return msg + "}";
        }

    };
} // namespace cumulant
#endif
