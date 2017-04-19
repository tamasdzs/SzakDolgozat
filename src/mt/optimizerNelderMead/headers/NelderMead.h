#ifndef __NELDER_MEAD_H__
#define __NELDER_MEAD_H__  

#include <map>
#include <vector>
#include <limits>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include "Optimizer.h"

/* 
 * TEMPLATE CLASS: NelderMead
 * This class implements the standardized nelder mead algorithm. As an
 * input it expects an anonymus function to be minimized, 
 * the maximum number of rounds, the maximum margin of error and the nodes of the 
 * initial simplex.  
 */

class NelderMead: public Optimizer {
	protected:
		std::multimap<double, Coord> population;
		
		std::vector<std::multimap<double, Coord>::reverse_iterator> set_pointers();
		
	public:
		NelderMead( const unsigned int gen, const double merr, std::vector<Coord> pop);
		~NelderMead() {}
		Coord Optimize( std::function<double (Coord &)> costfun );
};



#endif

