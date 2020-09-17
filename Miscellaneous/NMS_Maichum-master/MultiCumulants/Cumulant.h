#ifndef MULTICUMULANTS_CUMULANT_H
#define MULTICUMULANTS_CUMULANT_H

#include "MultiCumulants/QVectorSet.h"
#include "MultiCumulants/QTerms.h"
#include "MultiCumulants/Correlator.h"

#include "vendor/loguru/loguru.hpp"

#include <set>
#include <utility> 
#include <sstream>
#include <iomanip>

namespace cumulant{

	class Cumulant{
		typedef std::unordered_map< std::bitset<MAX_SET_SIZE>, cumulant::Correlator > CorrelatorMap;

	protected:
		// std::vector<cumulant::Correlator> C( 58, q );
		Complex _v;
		Complex _w;

		CorrelatorMap _cm;
		NativeMask _m;
		size_t _nevents = 0;
	public:
		bool DEBUG = true;

		Cumulant( NativeMask m ) {
			this->_m = m;
		}

		void buildCorrelators( QVectorMap &qvm){
			LOG_SCOPE_FUNCTION(INFO);
			this->_nevents ++;
			auto bm = std::bitset<MAX_SET_SIZE>( this->_m );
			size_t maskBitsSet = Correlator::countSetBits( this->_m );
			LOG_IF_F( INFO, DEBUG, "nSetBits(mask) = %lu", maskBitsSet );

			// TODO: optimize maskBitsSet == 1 case: i.e. return bare Q vector
			auto lut = NativeMaskLUTs[ maskBitsSet-1 ];

			size_t nTerms = lut.size();

			for ( size_t i = 0; i < nTerms; i++ ){
				LOG_IF_F( INFO, DEBUG, "\n\nTERM %lu", i );
				
				double totalN = 1.0;

				for ( size_t j = 0; j < lut[ i ].size(); j++ ){
					NativeMask tm = lut[ i ][ j ];
					NativeMask em = Correlator::expandMask( tm, this->_m );
					
					if ( true == DEBUG ){
						auto btm = std::bitset<MAX_SET_SIZE>( tm );
						auto bem = std::bitset<MAX_SET_SIZE>( em );
						
						LOG_IF_F( INFO, DEBUG, "NativeMask=%s", std::bitset<8>( tm ).to_string().c_str() );
						LOG_IF_F( INFO, DEBUG, "expandMask( im=%s, mm=%s ) = %s", btm.to_string().c_str(), bm.to_string().c_str(), bem.to_string().c_str() );
					}

					Correlator c( em, qvm );
					if ( this->_cm.count( em ) == 0 ){
						this->_cm[em] = c;
					} else { 
						this->_cm[em] += c;
					}
				} // loop on lut[i]
			} // loop on nTerms
		}



		void buildCumulant(){
			LOG_SCOPE_FUNCTION(INFO);
			auto bm = std::bitset<MAX_SET_SIZE>( this->_m );
			size_t maskBitsSet = Correlator::countSetBits( this->_m );
			LOG_IF_F( INFO, DEBUG, "nSetBits(mask) = %lu", maskBitsSet );

			// TODO: optimize maskBitsSet == 1 case: i.e. return bare Q vector
			auto lut = NativeMaskLUTs[ maskBitsSet-1 ];

			size_t nTerms = lut.size();


			Complex n(0, 0);
			this->_v = n;
			this->_w = n;
			for ( size_t i = 0; i < nTerms; i++ ){
				size_t lut_size = lut[ i ].size();
				LOG_IF_F( INFO, DEBUG, "\n\nTERM %lu, with lut_size=%lu", i, lut_size );
				
				double ncoeff = (pow(-1, lut_size-1) * Correlator::factorial(lut_size-1));
				Complex tv(0,0);
				Complex tw(0,0);

				for ( size_t j = 0; j < lut_size; j++ ){
					NativeMask tm = lut[ i ][ j ];
					NativeMask em = Correlator::expandMask( tm, this->_m );

					LOG_IF_F( INFO, DEBUG, "adding correlator: %llu", em  );
					Correlator &c = this->_cm[ em ];
					if ( 0 == j ){
						tv = c.v;
						tw = c.w;
					} else {
						tv *= c.v;
						tw *= c.w;
					}
				} // loop on lut[i]

				LOG_IF_F( INFO, DEBUG, "N = %f", ncoeff );
				this->_v += tv * ncoeff;
				this->_w += tw * ncoeff;

			} // loop on nTerms
		}

	};
}


#endif