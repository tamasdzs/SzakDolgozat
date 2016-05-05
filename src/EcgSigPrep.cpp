#include "EcgSigPrep.h"
#include "spline.h"
#include <vector>
#include <iostream>
#include <cmath>

EcgSigPrep::EcgSigPrep(char* sig_name, const int n_of_leads, const int n_of_samples):
													SigPrep(sig_name, n_of_leads, n_of_samples),
													curr_pos(0) {
					getNextSegment();
			}

const Eigen::MatrixXd* EcgSigPrep::getNextSegment() {
	
	if( annotations.empty() || curr_pos >= entire_signal->cols()) {
			//Hibakezeles
			std::cout<<"Nincs tobb QRS! "<<std::endl;
			return signal;
	} 
	
	
	
	WFDB_Annotation Curr_annot = annotations.front();
	annotations.pop();
	
	int end_of_segment = Curr_annot.time + 150;
	
	if(end_of_segment >= entire_signal->cols()) end_of_segment = entire_signal->cols()-1;
	
	*signal = entire_signal->block(0, curr_pos, 1, abs(end_of_segment-curr_pos));
	
	curr_pos += end_of_segment;
	
	setSignal();
	
	return signal;
	
}

void EcgSigPrep::setDilatTrans(const double l, const double t, const Eigen::MatrixXd* alpha, Eigen::MatrixXd& sig) {
	
	dilat = l;
	trans = t;
	
	std::vector<double> X(signal->cols()), Y(signal->cols());
	
	Eigen::MatrixXd domain = dilat*(*alpha);
	
	for(int i = 0; i < signal->cols(); ++i) {
		X[i] = domain(i, 0) - trans;
		Y[i] = sig(0, i);
	}
	
	tk::spline s;
	s.set_points(X,Y);
	
	
	for(int j = 0; j < signal->cols(); ++j) {
		
		if ((*alpha)(j, 0) < X[0] ||
			(*alpha)(j, 0) > X[signal->cols()-1] ) {
			sig(0,j) = 0.0;
		}
		else {
			sig(0,j) = s((*alpha)(j, 0));
		}
		
	}
} 
