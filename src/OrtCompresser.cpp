#include "OrtCompresser.h"
#include <iostream>
#include <math.h>

OrtCompresser::OrtCompresser(OrtFunSys& H, const int dim) {
			big_ort_sys = &H;
			
			Herm_sys = new Eigen::MatrixXd;
			Herm_sys->resize(H.get_ort_fun_sys()->rows(), dim);
			
			for ( int i = 0; i < dim; ++i ) {
				Herm_sys->col(i) = H.get_ort_fun_sys()->col(i);
			}	
			
			CrisDarb = big_ort_sys->get_ort_fun_lamb()->inverse();			
}

OrtCompresser::~OrtCompresser() {
	delete Herm_sys;
}


/* TODO:
 * - This method should give back a matrix. The method that actually links the compressed
 *   opjects together (MatchingPursuit::CompressBeat()) should create the new OrtCompressed object.
*/
Eigen::MatrixXd OrtCompresser::compressBeat( Eigen::MatrixXd& signal ) {
	return  (Herm_sys->transpose()*(CrisDarb*signal.transpose())); 
}

const Eigen::MatrixXd OrtCompresser::decompress( const OrtCompressed* compr ) {
	
	int trans;
	double dilat = fabs(compr->dilat);
	
	if ( compr->trans < 0 || Herm_sys->rows() < compr->trans ) {
		trans = round(fabs(compr->trans/(compr->trans+1.0))*Herm_sys->rows());
	} else {
		trans = round(compr->trans);
	}
	
	trans = abs(round(Herm_sys->rows()/2.0) - trans);
	
	Eigen::ArrayXd x;
	x = Eigen::ArrayXd::LinSpaced(Herm_sys->rows(), round(-1.0*Herm_sys->rows()/2.0 ), round(Herm_sys->rows() / 2.0) );
	
	x = dilat*(x - trans);
	
	Eigen::MatrixXd H = big_ort_sys->OrtSysGen(x, Herm_sys->cols() );
	
	return (H * compr->compressed_sig).transpose();
}

double OrtCompresser::getPRD( const OrtCompressed* compr, Eigen::MatrixXd & signal, std::ofstream& fout ) {
	Eigen::MatrixXd APR = decompress( compr );
	fout<<APR.transpose();
	return ((signal - APR).norm() / (signal.array() - signal.mean()).matrix().norm());
}

double OrtCompresser::getPRD( const OrtCompressed* compr, Eigen::MatrixXd & signal ) {
	Eigen::MatrixXd APR = decompress( compr );
	return ((signal - APR).norm() / (signal.array() - signal.mean()).matrix().norm());
}

double OrtCompresser::getPRD( Eigen::MatrixXd& APR, Eigen::MatrixXd& signal ) {
	return ((signal - APR).norm() / (signal.array() - signal.mean()).matrix().norm());
}
