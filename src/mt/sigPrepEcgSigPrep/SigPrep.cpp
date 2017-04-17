#include "SigPrep.h"

/*/////////////////////////////////////////////////////////////////////
 * SigPrep::SigPrep(args)
 * This is the constructor for the abstract class SigPrep. It copies the
 * sample values from a database signal (specified in args) to the matrices
 * entire_signal, and signal. Signal will be a desired part of entire_signal
 * we wish to operate on. By deafult its the first lead of entire_signal. In
 * addition the constructor is responsible for setting up the annotations vector.
 * This vector stores WFDB_Annotations, but for this implementation only the
 * ones which mark the beginning of a QRS complex. 
*//////////////////////////////////////////////////////////////////////
SigPrep::SigPrep(): sig_first_val(0.0), sig_last_val(0.0), sig_max_val(0.0){

	entire_signal = new Eigen::MatrixXd;
	signal = new Eigen::MatrixXd;
	
}

/* Destructor
 * Deletes all dynamically allocated members.
*/
SigPrep::~SigPrep() {
	delete entire_signal;
	delete signal; 
}

/*//////////////////////////////////////////////////////////////////////
 * const Eigen::MatrixXd* SigPrep::getSignal()
 * This function returns the part of the signal we work with in a matrix
 * pointer format. If you wish to get the entire recording, please refer
 * to Eigen::MatriXxd* SigPrep::getEntireSignal()
*///////////////////////////////////////////////////////////////////////
const Eigen::MatrixXd* SigPrep::getSignal() {
	return signal;
}

/*//////////////////////////////////////////////////////////////////////
 * const Eigen::MatrixXd* SigPrep::getEntireSignal()
 * This function returns the entire signal, all leads included.
*///////////////////////////////////////////////////////////////////////
const Eigen::MatrixXd* SigPrep::getEntireSignal() {
	return entire_signal;
}

const double SigPrep::getSigFirstVal() {
	return sig_first_val;
}

const double SigPrep::getSigLastVal() {
	return sig_last_val;
}

const double SigPrep::getSigMaxVal() {
	return sig_max_val;
}
/* /////////////////////////////////////////////////////////////////////
 * void SigPrep::setSignal()
 * This function readies to signal for compression. It first 'pulls' the
 * edges to zero, then normalizes the signal by its maximum. The original
 * values (for later restoration) are stored in sig_first_val, sig_last_val
 * and sig_max_val
*/ /////////////////////////////////////////////////////////////////////
void SigPrep::setSignal() {
	
	sig_first_val = (*signal)(0,0);
	sig_last_val = (*signal)(0, signal->cols() - 1);
	Eigen::MatrixXd::Index maxRow, maxCol;
	sig_max_val = signal->maxCoeff(&maxRow, &maxCol);
	
	Eigen::VectorXd temp = Eigen::VectorXd::LinSpaced(signal->cols(),1.0,(double)signal->cols());
	Eigen::MatrixXd base = Eigen::MatrixXd::Constant(1, signal->cols(), (*signal)(0,0));
	
	temp *= (((*signal)(0, signal->cols()-1) - (*signal)(0,0)) /
						   ((double)(signal->cols()-1)));
	base += temp;
	
	*signal = (*signal) - base.transpose();
	*signal = (*signal)/sig_max_val; 
	
}

