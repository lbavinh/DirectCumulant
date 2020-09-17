#ifndef MULTICUMULANTS_ALGORITHM_H
#define MULTICUMULANTS_ALGORITHM_H

#include <iostream>
#include <algorithm>
#include <string>

/**
 * Class with useful algo
 * 
 */

namespace algo{

class Algorithm
{
public:
	virtual const char* name() const { return "Algorithm"; }
	virtual const char* classname() const { return "Algorithm"; }

        Algorithm() {};

        virtual void algo(int N, int K) = 0;

protected:

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

};

class Combinations : public Algorithm
{
public:
	virtual const char* name() const { return "Combinations"; }
	virtual const char* classname() const { return "Combinations"; }

        Combinations() 
        {
        }

        ~Combinations()
        {
           std::vector< std::vector<unsigned short> >().swap( this->_combi );
        }

        void algo(int N, int K)
        {
            std::string bitmask(K, 1); // K leading 1's
            bitmask.resize(N, 0); // N-K trailing 0's
        
            // print integers and permute bitmask
            do {
                std::vector<unsigned short> oneCombination;
                for (int i = 0; i < N; ++i) // [0..N-1] integers
                {
                    if (bitmask[i]) 
                    {
                      oneCombination.push_back(i);
                    }
                }
                this->_combi.push_back(oneCombination);
            } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
        }

        //std::vector< std::vector<unsigned short> > getCombinations() { return this->_combi; }
        //unsigned int getNCombinations() { return this->_combi.size(); }

        template <typename Iterator>
        inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
        {
          /* Credits: Thomas Draper */
          if ((first == last) || (first == k) || (last == k))
             return false;
          Iterator itr1 = first;
          Iterator itr2 = last;
          ++itr1;
          if (last == itr1)
             return false;
          itr1 = last;
          --itr1;
          itr1 = k;
          --itr2;
          while (first != itr1)
          {
             if (*--itr1 < *itr2)
             {
                Iterator j = k;
                while (!(*itr1 < *j)) ++j;
                std::iter_swap(itr1,j);
                ++itr1;
                ++j;
                itr2 = k;
                std::rotate(itr1,j,last);
                while (last != j)
                {
                   ++j;
                   ++itr2;
                }
                std::rotate(k,itr2,last);
                return true;
             }
          }
          std::rotate(first,k,last);
          return false;
        } 

        unsigned int getCombinations(size_t n, size_t k) 
        { 
          if(n == 0 || n == 1) return 1;
          else if(k >= n)      return 1;
          else                 return getCombinations(n-1,k)*n/(n-k); 
        }

protected:
        std::vector< std::vector<unsigned short> > _combi; 
};

}

#endif
