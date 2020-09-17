#ifndef MULTICUMULANTS_QVECTOR_H
#define MULTICUMULANTS_QVECTOR_H

#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <vector>

#include "MultiCumulants/Types.h"
#include "MultiCumulants/Subsets.h"
#include "MultiCumulants/Algorithm.h"

// logging library
#define LOGURU_IMPLEMENTATION 1
#include "vendor/loguru/loguru.hpp"

namespace cumulant{

	class QVector {
	public:
                virtual const char* name() const { return "QVector"; }
                virtual const char* classname() const {  return "QVector"; }

                //Constructors
                QVector()
                : _qvector(0), _weights(0), _harm(0)
                {
                }
                
                QVector(Harmonic harm)
                : _qvector(0), _weights(0), _harm(harm)
                {
                }
                
                //Destructors
                ~QVector()
                {
                    
                }
                
                virtual QVector& operator*=(const QVector& qv)
                {
                		this->_harm += qv._harm;
                		this->_qvector *= qv.getQV();
                		this->_weights *= qv.getW();
                		return *this;
                }
                
                virtual void setHarm(Harmonic harm) 
                {
                		this->_harm = harm;
                }
                
                virtual Harmonic getHarm() 
                {
                		return this->_harm;
                }
                
                virtual const Complex getQV() const
                {
                	return this->_qvector;
                }
                
                virtual Real getW() const
                {
                	return this->_weights;
                }
                
                virtual Complex getQV()
                {
                	return this->_qvector;
                }
                
                virtual Real getW()
                {
                	return this->_weights;
                }
                
                virtual void fill(double phi, double w )
                {
                	size_t power = this->_i;
                	this->_qvector += Complex(pow(w, power+1) * cos(static_cast<double>(this->_harm) * phi), 
                				  pow(w, power+1) * sin(static_cast<double>(this->_harm) * phi));
                	this->_weights += pow(w, power+1);
                        LOG_IF_F( INFO, DEBUG, "power = %zu, qvector = %f + i.%f", 
                                                power+1, 
                                                this->_qvector.real(), 
                                                this->_qvector.imag() );
                }
                
                virtual void reset(const Complex& q=Complex(0,0))
                {
                		this->_qvector = q;
                		this->_weights = q.real();
                }
                
                std::string toString(){
                		std::string s = "";
                
                		s += this->classname();
                		s += "<harmonic =  " + std::to_string( this->_harm );
                		s += "  qvector =  " + std::to_string( this->getQV().real() ) + " + " 
                				     + std::to_string( this->getQV().imag() ) + ".i";
                		s += ", weights =  " + std::to_string( this->getW() ); 
                		s += ">";
                
                		return s;
                }
                
                size_t _i;
                size_t _j;
	protected:
                bool DEBUG = true;
	        Complex _qvector;
	        Real _weights;
	        Harmonic _harm;
	};

	class QVectorMask {
	public:
		std::bitset<MAX_SET_SIZE> bits;
		size_t i=0;
		size_t j=0;
	};
} // namespace cumulant
#endif
// Local Variables:
//  mode: C++
// End:
