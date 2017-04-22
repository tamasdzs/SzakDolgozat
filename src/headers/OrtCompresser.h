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
 * 
 * 
 *  - TODO: Function compressBeat should return compressed*, the dilat and trans values should be private and returned separetaly. 
 * 			This way class Compresser can get rid of OrtCOmpressed*s in virtual methods.
 */
class OrtCompresser: public Compresser {
	protected:
		OrtFunSys* big_ort_sys;
		Eigen::MatrixXd* Herm_sys;
		
	public:
		OrtCompresser(OrtFunSys& H, const int dim);
		~OrtCompresser();
		
		double getPRD( const OrtCompressed* compr, Eigen::MatrixXd& signal, std::string fout );
		double getPRD( const OrtCompressed* compr, Eigen::MatrixXd& signal );
		Eigen::MatrixXd compressBeat( Eigen::MatrixXd& signal );
		const Eigen::MatrixXd decompress(const OrtCompressed* compr);
};

#endif
