#ifndef MULTICUMULANTS_TOYMCEVENT_H
#define MULTICUMULANTS_TOYMCEVENT_H

#include <string>
//ROOT include
#include <TH1.h>
//User
#include "ToyMC/ToyMCParticle.h"

#include "TObject.h"

/**
 * Class to define Sets and subsets
 * 
 */
namespace toymc
{
class ToyMCEvent : public TObject
{
public:
	virtual const char* name() const { return "ToyMCEvent"; }
	virtual const char* classname() const { return "ToyMCEvent"; }

	/**
	 * Constructor - 
	 */
	ToyMCEvent()
	{
		// set(500);
	}

	~ToyMCEvent()
	{
		// std::vector<ToyMCParticle>().swap(this->_particles);
	}

	virtual void copy( ToyMCEvent * that ){
		this->_mult = that->_mult;
		this->_noff  = that->_noff;
	}

	void set(UInt_t mult, UInt_t noff )
	{
		// this->_particles.reserve(npart);
		this->_mult = mult;
		this->_noff = noff;
	}

	void add() 
	{
		// this->_particles.push_back(part);
	};

        UInt_t getMult() { return this->_mult; }

	/**
	 * builds the string representation of the object
	 *
	 * @return String representation of this
	 */
	std::string toString(){
		std::string s = "";
		s += this->classname(); 
		return s; 
	}

protected:
	// std::vector<ToyMCParticle> _particles;
	UInt_t  _mult;
	UInt_t  _noff;

	ClassDef( ToyMCEvent, 1 )
};
}	// toymc NAMESPACE
#endif
