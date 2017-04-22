#ifndef __ECGSIGPREP_H__
#define __ECGSIGPREP_H__

#include <Eigen/Dense>
#include <wfdb/wfdb.h>
#include <wfdb/ecgmap.h>
#include <queue>
#include "SigPrep.h"
	
/*
 *	CLASS: EcgSigPrep 
 * 	Class responsible for handling database records, we wish to compress
 * 	using the approach relying on orthonormal systems. It is able to dissect
 *  the record into independent heartbeats, and set the dilatation and translation
 *  parameters of the signal.
*/

class EcgSigPrep: public SigPrep {
	protected:
		
		std::queue<WFDB_Annotation> annotations;
		double dilat;
		int trans;
		
		int curr_pos;
	public:
		
		EcgSigPrep(char* sig_name, const int n_of_leads, const int n_of_samples);
		~EcgSigPrep() {}
		
		const Eigen::MatrixXd* getNextSegment();
		Eigen::MatrixXd setDilatTrans(const double &l, const double &t, const Eigen::MatrixXd* alpha, Eigen::MatrixXd& sig);
		
		
		const double getDilat();
		const double getTrans();
};

#endif
