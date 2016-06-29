#ifndef __ORTFUNSYS_H_INCLUDED__
#define __ORTFUNSYS_H_INCLUDED__

#include <Eigen/Dense>

/*
 * CLASS: OrtFunSys
 * This class defines orthonormal function systems used for signal compression.
 * The class is abstract and makes use of only pure virtual functions. Different
 * orthonormal specialised systems can be derived from it. For further use, refer
 * to OrtCompresser.h
*/

class OrtFunSys {
	protected:
		int rootNum;
		Eigen::MatrixXd* domain;
		Eigen::MatrixXd* bigSys;
		Eigen::MatrixXd* lambda;
		
		virtual void ort_fun_sys_roots() = 0;
		virtual void ort_fun_sys_gen() = 0;
		virtual void ort_fun_sys_lamb() = 0;
		
	public:
		OrtFunSys(int N);
		virtual ~OrtFunSys();
		
		const virtual Eigen::MatrixXd OrtSysGen(const Eigen::ArrayXd& x, int deg) = 0;
		const virtual Eigen::MatrixXd* get_ort_fun_lamb() = 0;
		const virtual Eigen::MatrixXd* get_ort_fun_sys() = 0;
		const virtual Eigen::MatrixXd* get_ort_fun_roots() = 0;
};

#endif
