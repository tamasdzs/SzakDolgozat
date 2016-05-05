#include "Hermite.h"
#include <math.h>

/* /////////////////////////////////////////////////////////////////////
 * Hermite::ort_fun_sys_roots()
 * Calculculate the roots of the n-th Hermite function.
 * This will serve as the domain of the Hermite system used 
 * to approximate the ECG signal. The application of this domain
 * enables us to use a Gauss-type quadrature formula.
 */ ////////////////////////////////////////////////////////////////////
void Hermite::ort_fun_sys_roots() {
/*
 * 1. Create Jacobi matrix whose eigenvalues will be the roots of the nth Hermite
 * function.
 */   
	Eigen::MatrixXd J;
	J = Eigen::MatrixXd::Zero(rootNum, rootNum);
	
	for(int i = 0; i < rootNum; ++i) {
		
		if( i == 0 ) {
			J(0, i+1) = sqrt(0.5*double(i+1));
		} 
		else if( i > 0 && i < rootNum-1 ) {
			J(i, i+1) = sqrt(0.5*(i+1));
			J(i, i-1) = sqrt(0.5*(i));
		} 
		else if( i == rootNum-1) {
			J(i, rootNum-2) = sqrt(0.5*i);
		} 
	}
/*
 * 2. Calculate eigenvalues of the Jacobi matrix. Let domain's pointed value
 * be equal to the matrix that stores these.
 */ 	
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(J);
	
	//TODO: error-check if eigensolver was initalized
	
	*domain = eigensolver.eigenvalues();
}

/* /////////////////////////////////////////////////////////////////////
 * Hermite::ort_fun_sys_gen()
 * This function is used to generate the orthonormal Hermite system
 * using the three-term recurrence formula. 
 */ ////////////////////////////////////////////////////////////////////
void Hermite::ort_fun_sys_gen() {	
/*
 * Initalize matrix whose columns will hold the values of the system.
 * Use Eigen::Array for piecewise operations.
 */	
	Eigen::ArrayXXd PHI;
	PHI = Eigen::ArrayXXd::Zero(rootNum, rootNum);
/*
 * Initalize domain (in this case the roots of some Hermite function).
 */
	Eigen::ArrayXXd x = (*domain).array();
/*
 * Weight function.
 */	
	Eigen::ArrayXXd w = (-1*(x*x)/2.0).exp();

/*
 * Zero and First order Hermite functions.
 */	
	PHI.col(0) = w;
	PHI.col(1) = 2*(x*w)/sqrt(2);

/*
 * Recursion for higher order Hermite functions.
 */	
	double ni, ni_1;
	for(int i = 2; i < rootNum; ++i) {
		ni = 1.0/sqrt(2.0*double(i));
		ni_1 = 1.0/sqrt(2.0*(double(i) - 1)) * ni;
		PHI.col(i) = 2.0*(x*PHI.col(i-1)*ni - (double(i)-1)*PHI.col(i-2)*ni_1);
	}

/*
 * Normalize the function system.
 */
	PHI *= pow(4.0*atan(1.0), -1.0/4.0);
	*bigSys = PHI.matrix();	
}

/*
 * Hermite::ort_fun_sys_lamb()
 * This function sets up the lamb matrix, which stores the coefficients
 * for the quadrature formula
 */
void Hermite::ort_fun_sys_lamb() {
	*lambda = (*bigSys)*(*bigSys).transpose();
}

const Eigen::MatrixXd* Hermite::get_ort_fun_roots() {	
	return domain;
}

const Eigen::MatrixXd* Hermite::get_ort_fun_sys() {
	return bigSys;
}

const Eigen::MatrixXd* Hermite::get_ort_fun_lamb() {
	return lambda;
	
}

