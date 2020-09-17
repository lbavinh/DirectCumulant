#ifndef MULTICUMULANTS_TOYMCPARTICLE_H
#define MULTICUMULANTS_TOYMCPARTICLE_H

#include <string>

/**
 * Class to define Sets and subsets
 * 
 */
namespace toymc
{

class ToyMCParticle : public TObject
{
public:
	virtual const char* name() const { return "ToyMCParticle"; }
	virtual const char* classname() const { return "toymc::ToyMCParticle"; }
	
	/**
	 * Constructor - 
	 */
	ToyMCParticle()
	{
		reset();
	}

	~ToyMCParticle(){}

	void reset(){
		set( 0.0, 0.0, 0.0 );
	} 

	virtual void copy( ToyMCParticle *that ){
		this->_pt  = that->_pt;
		this->_eta = that->_eta;
		this->_phi = that->_phi;
	}

	void set(double pt, double eta, double phi)
	{
		this->_phi = phi;
		this->_pt  = pt;
		this->_eta = eta;
	}

        double getphi() { return _phi; }
        double getpt( ) { return _pt; }
        double geteta() { return _eta; }

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
	double _phi;
	double _pt;
	double _eta;

	ClassDef( ToyMCParticle, 1 )
};
} // toymc NAMESPACE
#endif

