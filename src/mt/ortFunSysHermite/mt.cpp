/*
 *                MODULE TEST FOR MODULES OrtFunSys and Hermite
*/ 

#include <iostream>
#include <fstream>
#include "Hermite.h"


/* DEFINES FOR TESTCASES */
#define MT_DIM_OF_HERM_SYS1_INT (int)20
#define MT_DIM_OF_HERM_SYS2_INT (int)15

#define MT_NUMBER_OF_POINTS_IN_EQUIDISTANT_INTERVAL_INT (int)100
#define MT_LOWER_BOUND_FOR_INTERVAL_DOUBLE (double)-10.0
#define MT_UPPER_BOUND_FOR_INTERVAL_DOUBLE (double)10.0

/* END DEFINES FOR TESTCASES */

int main() {
	
	/* Set up module test environment */	
	std::ofstream  ofs ("./output/mt_results.txt", std::ofstream::out);
	
	
	/* TC_1:  Create an instance of a Hermite type object*/
	ofs<<"**************** MT TC 1 ****************"<<std::endl;
	ofs<<"testcase 1: Create an instance of a Hermite type object"<<std::endl;
	Hermite H(MT_DIM_OF_HERM_SYS1_INT);
	ofs<<"testcase 1: DONE"<<std::endl<<std::endl;
	
	/* TC_2:  Retrieve roots of 20th degree Hermite function via getter*/
	ofs<<"**************** MT TC 2 ****************"<<std::endl;
	ofs<<"testcase 2: Retrieve roots of 20th degree Hermite function via getter"<<std::endl;
	ofs<<*(H.get_ort_fun_roots())<<std::endl;
	ofs<<"testcase 2: DONE"<<std::endl<<std::endl;
	
	/* TC_3:  Retrieve Hermite functions via getter*/
	ofs<<"**************** MT TC 3 ****************"<<std::endl;
	ofs<<"testcase 3: Retrieve Hermite functions via getter"<<std::endl;
	ofs<<*(H.get_ort_fun_sys())<<std::endl;
	ofs<<"testcase 3: DONE"<<std::endl<<std::endl;
	
	/* TC_4:  Retrieve matrix containing the Cristoffel-Darboux numbers via getter*/
	ofs<<"**************** MT TC 4 ****************"<<std::endl;
	ofs<<"testcase 4: Retrieve matrix containing the Cristoffel-Darboux numbers via getter"<<std::endl;
	ofs<<*(H.get_ort_fun_lamb())<<std::endl;
	ofs<<"testcase 4: DONE"<<std::endl<<std::endl;
	
	/* TC_5:  Generate an Hermite system on an equidistant interval using Hermite::OrtSysGen(...)*/
	ofs<<"**************** MT TC 5 ****************"<<std::endl;
	ofs<<"testcase 5: Generate an Hermite system on an equidistant interval using Hermite::OrtSysGen(...)"<<std::endl;
	
	Eigen::ArrayXd domain;
	domain = Eigen::ArrayXd::LinSpaced(MT_NUMBER_OF_POINTS_IN_EQUIDISTANT_INTERVAL_INT, MT_LOWER_BOUND_FOR_INTERVAL_DOUBLE, MT_UPPER_BOUND_FOR_INTERVAL_DOUBLE);
	Eigen::MatrixXd generated_hermite = H.OrtSysGen(domain, MT_DIM_OF_HERM_SYS2_INT);
	ofs<<generated_hermite<<std::endl;
	ofs<<"testcase 5: DONE"<<std::endl<<std::endl;
	
	/* Clear up module test environment */
	ofs.close();
	
	return 0;
}
