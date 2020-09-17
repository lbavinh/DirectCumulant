#ifndef MULTICUMULANTS_QVECTOR_SET_H
#define MULTICUMULANTS_QVECTOR_SET_H


#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <vector>

#include "MultiCumulants/Types.h"
#include "MultiCumulants/Subsets.h"
#include "MultiCumulants/Algorithm.h"
#include "MultiCumulants/QVector.h"

// logging library
#define LOGURU_IMPLEMENTATION 1
#include "vendor/loguru/loguru.hpp"


namespace cumulant{

    typedef std::unordered_map< std::bitset<MAX_SET_SIZE>, QVector > QVectorMap;


    class QVectorSet{
    public:
        virtual const char* name() const { return "QVectorSet"; }
        virtual const char* classname() const { return "QVectorSet"; }

            //Constructors
            QVectorSet()
            : _set(0), _useWeights(false)
            {
            }

            QVectorSet(const HarmonicVector& h, Set set, bool useweights)
            {
                this->_set = set;
                LOG_F( INFO, "Set.size()=%zu == h.size()=%zu", this->_set.size(), h.size() );
                if(this->_set.size() != h.size())  
                {
                    LOG_F( INFO, "Resizing set to be %zu", h.size() );
                    this->_set.resize(h.size());
                }

                this->_useWeights = useweights;
                this->generateBitmasks( h );
            }

            //Destructors
            ~QVectorSet() 
            {
               this->_masks.clear();
               std::vector<QVectorMask>().swap(this->_masks);
            }

            virtual QVectorMap& getQ() { return this->_qvm;}

            virtual void generateBitmasks( const HarmonicVector& h )
            {
                algo::Combinations c;

                size_t n = this->_set.size();

                std::vector<int> ints;
                for (size_t i = 0; i < n; ints.push_back(i++));

                for(size_t k = 1; k <=n; ++k)
                {
                    size_t nC = 0;
                    do
                    {
                        QVectorMask mask;
                        QVector q;
                        mask.i=k-1;
                        mask.j=nC;
                        
                        q._i = k-1;
                        q._j = nC;
                        for (size_t ik = 0; ik < k; ++ik)
                        {
                            mask.bits.set( ints[ik] );
                            q *= QVector( h[ints[ik]] );
                        }
                        // Now save the mask and the q
                        this->_masks.push_back( mask );
                        this->_qvm[ mask.bits ] = q;  

                        ++nC;
                    } while(c.next_combination(ints.begin(), ints.begin() + k, ints.end()));
                }

                LOG_F( INFO, "_masks.size() = %zu", this->_masks.size() );
                LOG_F( INFO, "_qvm.size() = %zu", this->_qvm.size() );
            }

            virtual void fill(std::vector<double> &val, double &phi, double &w)
            {
                Real weight = (!this->_useWeights ? 1 : w);

                std::bitset<MAX_SET_SIZE> setMask = this->_set.setMask(val);
                
                // loop over the q-vectors
                // NB loop by reference or we cannot modify the value!
                for ( auto &kv : this->_qvm ){
                    
                    // only fill the q-vector if the setMask satisfies
                    if ( ( kv.first & setMask ) == kv.first ){
                        kv.second.fill( phi, weight );
                    }
                } // loop on _qvm
            }

            virtual void reset()
            {
                for ( auto &kv : this->_qvm ){
                    kv.second.reset(); 
                }
            }

            virtual std::string print()
            {
                std::string s = "";
                for ( auto kv : this->_qvm ){
                    s+= "index( " + std::to_string( kv.second._i ) + ", " + std::to_string( kv.second._j ) + " ):";
                    s += kv.second.toString();
                    s += "\n";
                }
                return s;
            }

            std::string toString(){
                    std::string s = "";

                    s += this->classname();
                    s += "< Set = " + this->_set.toString();
                    if(this->_useWeights) s += ", Use weights: TRUE ";
                    else                  s += ", Use weights: FALSE ";
                    s += ">";

                    return s;
            }

            std::string maskString(){
                std::string s="size=" + std::to_string( this->_masks.size() ) + "\n";
                for ( size_t i = 0; i < this->_masks.size(); i++){
                    s+= "[" + std::to_string(this->_masks[i].i) + "]" + "[" + std::to_string(this->_masks[i].j) + "]\t" +  this->_masks[i].bits.to_string() + "\n";
                }
                return s;
            }

    protected:
            Set _set;
            bool _useWeights;

            std::vector<QVectorMask> _masks;
            QVectorMap _qvm;
    };
} // napesapce cumulants


#endif
