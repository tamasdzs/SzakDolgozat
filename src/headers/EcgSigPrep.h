#ifndef __ECGSIGPREP_H__
#define __ECGSIGPREP_H__

#include <Eigen/Dense>
#include <wfdb/wfdb.h>
#include "SigPrep.h"
	
class EcgSigPrep: public SigPrep {
	protected:
		
		int curr_pos;
	public:
		
		EcgSigPrep(char* sig_name, const int n_of_leads, const int n_of_samples);
		~EcgSigPrep() {}
		
		const Eigen::MatrixXd* getNextSegment();
		void setDilatTrans(const double l, const double t, const Eigen::MatrixXd* alpha, Eigen::MatrixXd& sig);
};

#endif
