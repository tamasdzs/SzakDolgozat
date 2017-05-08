#ifndef __ORTCOMPRESSER_H__
#define __ORTCOMPRESSER_H__

#include "Compresser.h"
#include "Hermite.h"
#include <fstream>
#include <string>

/* 
 * CLASS: OrtCompresser
 * Child class of compresser, the puropose of this class is to compress
 * a single signal using some orthonormal function system.
 */
class OrtCompresser: public Compresser {
	protected:
		OrtFunSys* big_ort_sys;
		Eigen::MatrixXd* Herm_sys;
		Eigen::MatrixXd CrisDarb;
		
	public:
		OrtCompresser(OrtFunSys& H, const int dim);
		OrtCompresser() : big_ort_sys(0), Herm_sys(0) {}
		~OrtCompresser();
		
		double getPRD( const OrtCompressed* compr, Eigen::MatrixXd& signal, std::ofstream& fout );
		double getPRD( const OrtCompressed* compr, Eigen::MatrixXd& signal );
		double getPRD( Eigen::MatrixXd& APR, Eigen::MatrixXd& signal );
		Eigen::MatrixXd compressBeat( Eigen::MatrixXd& signal );
		const Eigen::MatrixXd decompress(const OrtCompressed* compr);
};

#endif
