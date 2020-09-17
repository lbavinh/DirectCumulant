#ifndef MULTICUMULANTS_SUBSET_H
#define MULTICUMULANTS_SUBSET_H

#include "MultiCumulants/Types.h"
#include "MultiCumulants/Algorithm.h"

#include <string>

/**
 * Class to define Sets and subsets
 * 
 */
namespace cumulant
{

class ParamSubset
{
public:
	virtual const char* name() const { return "ParamSubset"; }
	virtual const char* classname() const { return "ParamSubset"; }
        
        ParamSubset(){
           setParam("null", -9999., 9999.);
        }

        ParamSubset(std::string name, double min, double max){
           setParam(name, min, max);
        }

        ~ParamSubset(){}

        virtual void setParam(std::string name, double min, double max){
          this->_name = name;
          this->_min  = min;
          this->_max  = max;
        }

        virtual std::string getName() { return this->_name;}
        virtual double getMin() { return this->_min;}
        virtual double getMax() { return this->_max;}

	std::string toString(){
		std::string s = "";

		s += this->classname(); 
		s += "<name: " + getName();
		s += "  min=" + std::to_string( this->getMin() );
		s += ", max=" + std::to_string( this->getMax() );
		s += ">";

		return s; 
	}

protected:
        std::string _name;
        double _min;
        double _max;
};

class Subset
{
public:
	virtual const char* name() const { return "Subset"; }
	virtual const char* classname() const { return "Subset"; }
	
	/**
	 * Constructor - 
	 */
	Subset(){
                set(1);
        }

	Subset(size_t nParam){
                set(nParam);
        }

	Subset(std::vector<ParamSubset> params){
                this->_params.resize(params.size());

                for(size_t ip=0; ip<params.size(); ++ip){                
                  set(ip, params[ip].getName(), params[ip].getMin(), params[ip].getMax());
                }
        }

	~Subset(){
                std::vector<ParamSubset>().swap(this->_params);
        }
	
        virtual void set(size_t nParam){
                this->_params.resize(nParam);
                for(size_t ip=0; ip<this->_params.size(); ++ip)
                {
                   this->_params[ip] = ParamSubset();
                }
        }

	virtual void set(unsigned int pos, std::string name, double min, double max)
        {
                if(pos >= this->_params.size()) 
                  return;
                else{
                  this->_params[pos] = ParamSubset(name,min,max);
                }
        }

        virtual bool isFromSubset(std::vector<double> val)
        {
                bool answer = true;
                for(size_t ip=0; ip<this->_params.size(); ++ip)
                {
                  //std::cout << "subset param name: " << ip << " ~~> " << this->_params[ip].getName() << std::endl;
                  if(val[ip] < this->_params[ip].getMin() || val[ip] > this->_params[ip].getMax()) 
                  {
                     answer = false; 
                  }
                }  
                return answer;
        }

	/**
	 * builds the string representation of the object
	 *
	 * @return String representation of this
	 */
	std::string toString(){
		std::string s = "";

		s += this->classname();
                s += " <";
                for(size_t ip=0; ip<this->_params.size(); ++ip)
                { 
		  s += "  param_" + std::to_string(ip) + ":";
		  s += "  name: " + this->_params[ip].getName();
		  s += ", min =" + std::to_string( this->_params[ip].getMin());
		  s += ", max =" + std::to_string( this->_params[ip].getMax());
                }
		s += ">";

		return s; 
	}

protected:
        std::vector<ParamSubset> _params;
};

class Set
{
public:
	virtual const char* name() const { return "Set"; }
	virtual const char* classname() const { return "Set"; }

        Set(){
                this->_set.resize(2);
        }

        Set(size_t size){
                this->_set.resize(size);
        }

        Set(const Set& set){
                this->_set = set.getSet();
        }

        ~Set() {
                this->_set.clear();
                std::vector<Subset>().swap(this->_set);
        }

        virtual std::vector<bool> isFromSet(std::vector<double> val)
        {
                std::vector<bool> answers(this->_set.size(), true);
                for(size_t isubset=0; isubset<answers.size(); ++isubset)
                {
                  //std::cout << answers.size() << std::endl;
                  answers[isubset] = this->_set[isubset].isFromSubset(val);
                }
                return answers;
        }

        virtual std::bitset<MAX_SET_SIZE> setMask(std::vector<double> val)
        {
                std::bitset<MAX_SET_SIZE> bs;
                for(size_t isubset=0; isubset<this->_set.size(); ++isubset)
                {
                    if (this->_set[isubset].isFromSubset(val))
                        bs.set(isubset);
                  // answers[isubset] = this->_set[isubset].isFromSubset(val);
                }
                return bs;
        }

        virtual void setSubsetParams(unsigned int isubset, Subset subset)
        {
                if(isubset >= this->_set.size()) return;
                else
                {
                  this->_set[isubset] = subset;
                }
        }

        virtual size_t size()
        {
          return this->_set.size();
        }

        virtual void resize(size_t size)
        {
          this->_set.resize(size);
        }

        virtual std::vector<Subset> getSet()       { return _set; }
        virtual std::vector<Subset> getSet() const { return _set; }

	std::string toString(){
		std::string s = "";
		s += this->classname();
                s+= "\n";
                for(size_t isubset = 0; isubset < this->_set.size(); ++isubset)
                {
                    s += "subset_" + std::to_string(isubset) + ":\n";
                    s += this->_set[isubset].toString() + "\n";
                }
		return s; 
	}

protected:
        std::vector<Subset> _set;
};
}
#endif
