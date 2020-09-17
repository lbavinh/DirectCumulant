#ifndef MULTICUMULANTS_RESULT_HH
#define MULTICUMULANTS_RESULT_HH

#include <iostream>
#include "Types.h"

class Result
{
public:
	virtual const char* name() const { return "Result"; }
	virtual const char* classname() const {  return "Result"; }

        //Constructors
        /**
         * Default constructor
         */
	Result() : _sum(0,0), _weights(0) {}
        /**
         * Constructor
         *
         * @param c Complex number
         * @param w Weigth
         */
        Result(const Complex& c, Real w)
          : _sum(), _weights(w)
        {
        	this->_sum = c;
        }
        /**
         * Assignment plus operator
         *
         * @param r Result to add to this
         *
         * @return Reference to this
         */
        Result& operator+=(const Result& r)
        {
          this->_sum  += r._sum;
          this->_weights += r._weights;
          return *this;
        }
        Result& operator=(const Complex& c)
        {
          this->_sum = c;
          return *this;
        }
        /**
         * Evaluate the result
         *
         * @return The scaled result
         */
        Complex eval() const
        {
          return (this->_weights != 0 ? this->_sum / this->_weights : 0);
        }
        void print() const
        {
          std::cout << this->_sum << "\t" << this->_weights << std::endl;
        }

        /**
        * Convert classname to string
        *
        */
	std::string toString(){
		std::string s = "";
		s += classname();
		s += "<>";
		return s;
	}

        protected:
          /** Sum of arguments */
          Complex _sum;
          /** Sum of Weights */
          Real  _weights;
};

/** Vector of results */
typedef std::vector<Result> ResultVector;

#endif
// Local Variables:
//  mode: C++
// End:
