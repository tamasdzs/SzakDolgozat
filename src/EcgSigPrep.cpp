#include "EcgSigPrep.h"
#include "spline.h"
#include <vector>
#include <iostream>
#include <cmath>

EcgSigPrep::EcgSigPrep(char* sig_name, const int n_of_leads, const int n_of_samples):
													dilat(1.0), trans(0.0),curr_pos(0) {
					
	WFDB_Sample v[n_of_leads];
	WFDB_Siginfo s[n_of_leads];

	WFDB_Anninfo an[n_of_leads];
	WFDB_Annotation annot; 
	
	an[0].name = "atr"; an[0].stat = WFDB_READ;
    an[1].name = "aha"; an[1].stat = WFDB_AHA_WRITE;

	
	*entire_signal = Eigen::MatrixXd::Zero(n_of_leads, n_of_samples);
	*signal = Eigen::MatrixXd::Zero(1, n_of_samples);
	
	if( isigopen(sig_name, s, n_of_leads) < n_of_leads) {
		//std::cout<<"could not open record!"<<std::endl;
	}
	
	for( int i = 0; i < n_of_samples; ++i ) {
		if(getvec(v) < n_of_leads) break;
		
		(*signal)(0, i) = v[0];
		for(int j = 0; j < n_of_leads; ++j) {
			(*entire_signal)(j, i) = v[j];
		} 
		
	}
	
	if (annopen(sig_name, an, n_of_leads) < 0) {
		//std::cout<< annopen(sig_name, an, n_of_leads) <<" could not open annotation file"<<std::endl;
	}
	
	while (getann(0, &annot) == 0) {
		if (isqrs(annot.anntyp)) {
			annotations.push(annot);
		}
	} 
					
					
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
	
	if(end_of_segment >= entire_signal->cols()) {
		(*signal)(0,0) = -1;
		return signal;
	}
	*signal = entire_signal->block(0, curr_pos, 1, abs(end_of_segment-curr_pos));
	
	
	int diff = end_of_segment - curr_pos;
	curr_pos += diff;
	
	setSignal();
	
	return signal;
	
}

Eigen::MatrixXd EcgSigPrep::setDilatTrans(const double &l, const double &t, const Eigen::MatrixXd* alpha, Eigen::MatrixXd& sig) {
	if ( l != 0 ) {
		dilat = fabs(l);
	} else {
		dilat = 1.0;
	}
	
	//MAP THE TRANSLATION
	if ( t < 0 || sig.cols() < t ) {
		trans = round(fabs(t/(t+1.0))*sig.cols());
	} else {
		trans = round(t);
	}
	
	trans = abs(round(sig.cols()/2.0) - trans);
	
	std::vector<double> X(sig.cols()), Y(sig.cols());
	
	Eigen::ArrayXd domain;
	domain = Eigen::ArrayXd::LinSpaced(sig.cols(), round(-1.0*sig.cols()/2.0 ), round(sig.cols() / 2.0) );
	
	//Set up dilatation
	for(int i = 0; i < sig.cols(); ++i) {
		X[i] = domain(i)*dilat; 
		Y[i] = sig(0, i);
	}
	
	//Circshift translation
	std::rotate(Y.begin(), Y.begin()+trans, Y.end());
		
	//Subsample
	
	tk::spline s;
	s.set_points(X,Y);

	for(int j = 0; j < sig.cols(); ++j) {
		
		if ((*alpha)(0, 0) <= X[j] &&
			(*alpha)(sig.cols()-1, 0) >= X[j] &&
			(*alpha)(j, 0) >= X[0] &&
			(*alpha)(j,0) <= X[sig.cols()-1]
			 ) {
			sig(0,j) = s((*alpha)(j, 0));
		}
		else {
			sig(0,j) = 0.0;
		}
		
	}
	
	return sig;
} 


const double EcgSigPrep::getDilat() {
	return dilat;
}

const double EcgSigPrep::getTrans() {
	return trans;
}
