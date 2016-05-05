#ifndef __ORTFUNSYS_H_INCLUDED__
#define __ORTFUNSYS_H_INCLUDED__

#include <Eigen/Dense>

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
		
		const virtual Eigen::MatrixXd* get_ort_fun_lamb() = 0;
		const virtual Eigen::MatrixXd* get_ort_fun_sys() = 0;
		const virtual Eigen::MatrixXd* get_ort_fun_roots() = 0;
};

#endif
