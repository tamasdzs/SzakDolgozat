#ifndef __SIGPREP_H__
#define __SIGPREP_H__

#include <Eigen/Dense>
#include <wfdb/wfdb.h>
#include <wfdb/ecgmap.h>
#include <queue>

/*
 * CLASS: SigPrep
 * Class loads a signal (record) from wfdb database). It records
 * important attributes of the record, (and also partial signals) which
 * will be needed for reconstruction of the compressed signals.  
*/

class SigPrep {
	protected:
		Eigen::MatrixXd* entire_signal;
		Eigen::MatrixXd* signal;
		
		double sig_first_val;
		double sig_last_val;
		double sig_max_val;
		
		virtual void setSignal();
	public:
		SigPrep();
		virtual ~SigPrep();
		
		const Eigen::MatrixXd* getSignal();
		const Eigen::MatrixXd* getEntireSignal();
		
		const double getSigFirstVal();
		const double getSigLastVal();
		const double getSigMaxVal();
};

#endif
