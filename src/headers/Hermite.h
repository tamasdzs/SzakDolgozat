#ifndef __HERMITE_H_INCLUDED__
#define __HERMITE_H_INCLUDED__

#include "OrtFunSys.h"

/*
 *	CLASS: Hermite
 * 	This class generates an orthonormal Hermite function system. The roots of the 
 * 	functions can also be accessed in order to make use of Gauss type quadrature 
 * 	formulae.  
*/
 
class Hermite : public OrtFunSys {
	protected:
		
		void ort_fun_sys_roots();
		void ort_fun_sys_gen();
		void ort_fun_sys_lamb();
		
	public:
		Hermite(int N, int M) : OrtFunSys(N) {
			ort_fun_sys_roots();
			ort_fun_sys_gen();
			ort_fun_sys_lamb();
		};
		
		~Hermite() {};
		
		const Eigen::MatrixXd* get_ort_fun_lamb();
		const Eigen::MatrixXd* get_ort_fun_sys();
		const Eigen::MatrixXd* get_ort_fun_roots();
};


#endif
