#ifndef __ORTCOMPRESSER_H__
#define __ORTCOMPRESSER_H__

#include "Compresser.h"
#include "Hermite.h"

/* 
 * CLASS: OrtCompresser
 * Child class of compresser, the puropose of this class is to compress
 * a single signal using some orthonormal function system.
 */
class OrtCompresser: public Compresser {
	protected:
		OrtFunSys* ort_sys;
		unsigned int n;
		
	public:
		OrtCompresser(OrtFunSys& H, const int dim);
		~OrtCompresser();
		
		double get_err( Eigen::MatrixXd& signal );
		Compressed* compressBeat( Eigen::MatrixXd& signal );
		const Eigen::MatrixXd decompress(const Compressed* compr);
};

#endif
