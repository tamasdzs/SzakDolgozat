/*
 *                MODULE TEST FOR MODULES OrtFunSys and Hermite
*/ 

#include <vector>
#include <fstream>
#include "NelderMead.h"

/* DEFINES FOR TESTCASES */
#define MT_NUM_OF_MAX_GENERATIONS_INT (int)100
#define MT_MAXIMUM_TOLARABLE_FVAL_DOUBLE (double)0.00001

#define MT_SIZE_OF_INPUT_VECTOR_INT (int)3

#define MT_X_0_0_DOUBLE (double)10.0
#define MT_X_0_1_DOUBLE (double)1.0
#define MT_X_1_0_DOUBLE (double)2.0
#define MT_X_1_1_DOUBLE (double)3.0
#define MT_X_2_0_DOUBLE (double)2.0
#define MT_X_2_1_DOUBLE (double)1.0
/* END DEFINES FOR TESTCASES */

int main() {
	
	/* Set up module test environment */	
	std::ofstream  ofs ("./output/mt_results.txt", std::ofstream::out);
	
	/* TC_1:  Create an instance of a NelderMead type object*/
	ofs<<"**************** MT TC 1 ****************"<<std::endl;
	ofs<<"testcase 1: Create an instance of a NelderMead type object"<<std::endl;
	
	std::vector<Coord> X;
	X.resize(MT_SIZE_OF_INPUT_VECTOR_INT);
	X[0][0] = MT_X_0_0_DOUBLE;
	X[0][1] = MT_X_0_1_DOUBLE;
	X[1][0] = MT_X_1_0_DOUBLE;
	X[1][1] = MT_X_1_1_DOUBLE;
	X[2][0] = MT_X_2_0_DOUBLE;
	X[2][1] = MT_X_2_1_DOUBLE;
	
	NelderMead NM(MT_NUM_OF_MAX_GENERATIONS_INT, MT_MAXIMUM_TOLARABLE_FVAL_DOUBLE, X);
	ofs<<"testcase 1: DONE"<<std::endl<<std::endl;
	
	/* TC_2:  Find minimum place of a test function*/
	ofs<<"**************** MT TC 2 ****************"<<std::endl;
	ofs<<"testcase 2: Find minimum place of a test function"<<std::endl;
	
	auto test_func = [] (Coord &m) { return (m[0]*m[0]) + (m[1]*m[1]);};
	Coord minimum_place = NM.Optimize(test_func);
	
	ofs<<"Minimum place of f(x,y) := x^2+y^2"<<std::endl;
	ofs<<"X: "<<minimum_place[0]<<" Y: "<<minimum_place[1]<<std::endl;
	
	ofs<<"testcase 2: DONE"<<std::endl<<std::endl;
	
	/* Clear up module test environment */
	ofs.close();
	
	return 0;
}
