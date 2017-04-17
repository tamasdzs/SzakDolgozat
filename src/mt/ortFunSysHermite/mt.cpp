/*
 *                MODULE TEST FOR MODULES SigPrep and EcgSigPrep
*/ 

#include <iostream>
#include <fstream>
#include "Hermite.h"


/* DEFINES FOR TESTCASES */
#define MT_DIM_OF_HERM_SYS1_INT (int)20

/* END DEFINES FOR TESTCASES */

int main() {
	
	/* Set up module test environment */	
	std::ofstream  ofs ("./output/mt_results.txt", std::ofstream::out);
	
	
	/* Clear up module test environment */
	ofs.close();
	
	return 0;
}
