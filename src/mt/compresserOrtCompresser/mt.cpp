/*
 *                MODULE TEST FOR MODULES OrtFunSys and Hermite
*/ 

#include <vector>
#include <iostream>
#include <fstream>
#include "EcgSigPrep.h"
#include "Hermite.h"
#include "OrtCompresser.h"

/* DEFINES FOR TESTCASES */

#define MT_MIT_BIH_MEASUREMENT_NAME_1_STR "./input/103/103"
#define MT_NUM_OF_LEADS_INT 	(int)2
#define MT_NUM_OF_SAMPLES_1_INT (int)1000

#define MT_SAMPLE_DILATATION_DOUBLE  (double)0.15
#define MT_SAMPLE_TRANSLATION_DOUBLE (double)100.0

#define MT_DIM_OF_APR_INT		(int)25

/* END DEFINES FOR TESTCASES */

int main() {
	
	/* Set up module test environment */	
	std::ofstream  ofs ("./output/mt_results.txt", std::ofstream::out);
	
	
	/* TC_1:  Create an instance of an OrtCOmpresser with both costructors type object*/
	ofs<<"**************** MT TC 1 ****************"<<std::endl;
	ofs<<"testcase 1: Create an instance of an OrtCOmpresser with both costructors"<<std::endl;
	
	OrtCompresser l_compresserWithoutHermSys_oc;
	
	EcgSigPrep l_sigHandler_esp(MT_MIT_BIH_MEASUREMENT_NAME_1_STR, MT_NUM_OF_LEADS_INT, MT_NUM_OF_SAMPLES_1_INT);
	l_sigHandler_esp.getNextSegment();
	Hermite l_HermiteSystem_h(l_sigHandler_esp.getSignal()->cols());
	
	OrtCompresser l_compresserWithHermSys_oc(l_HermiteSystem_h, MT_DIM_OF_APR_INT);
	ofs<<"testcase 1: DONE"<<std::endl<<std::endl;
	
	/* TC_2:  Compress a heartbeat. Write result to output and input/decomp.cmp*/
	ofs<<"**************** MT TC 2 ****************"<<std::endl;
	ofs<<"testcase 2: Compress a heartbeat. Write result to output and input/decomp.cmp"<<std::endl;
	
	Eigen::MatrixXd t_sig_md = *(l_sigHandler_esp.getSignal());
	Eigen::MatrixXd t_dilatTransSig_md = t_sig_md;
	t_dilatTransSig_md = l_sigHandler_esp.setDilatTrans(MT_SAMPLE_DILATATION_DOUBLE, MT_SAMPLE_TRANSLATION_DOUBLE, l_HermiteSystem_h.get_ort_fun_roots(), t_dilatTransSig_md);
	
	OrtCompressed t_compr_c;
	t_compr_c.compressed_sig = l_compresserWithHermSys_oc.compressBeat( t_dilatTransSig_md );
	t_compr_c.dilat = MT_SAMPLE_DILATATION_DOUBLE;
	t_compr_c.trans = MT_SAMPLE_TRANSLATION_DOUBLE;
	
	ofs<<"dilatation: "<<t_compr_c.dilat<<" translation: "<<t_compr_c.trans<<std::endl;
	ofs<<"Fourier coeffs: "<<std::endl<<t_compr_c.compressed_sig<<std::endl;
	
	
	std::ofstream cmp_ofs;
	cmp_ofs.open("./input/decomp.cmp");
	
	cmp_ofs<<t_compr_c.dilat<<" "<<t_compr_c.trans<<" "<<t_compr_c.compressed_sig.rows()<<" "<<t_compr_c.compressed_sig.transpose()<<std::endl;
			
	ofs<<"testcase 2: DONE"<<std::endl<<std::endl;
	
	/* TC_3: Decompress the compressed heartbeat*/
	ofs<<"**************** MT TC 3 ****************"<<std::endl;
	ofs<<"testcase 3: Decompress the compressed heartbeat"<<std::endl;
	
	std::ifstream ifs;
	
	ifs.open("./input/decomp.cmp");
	
	OrtCompressed t_compressedHeartbeat_oc;
	unsigned int t_numOfCoeffs_ui;
	
	ifs>>t_compressedHeartbeat_oc.dilat;
	ifs>>t_compressedHeartbeat_oc.trans;
	ifs>>t_numOfCoeffs_ui;
	
	t_compressedHeartbeat_oc.compressed_sig = Eigen::MatrixXd::Zero(t_numOfCoeffs_ui, 1);
	
	for ( unsigned int i = 0; i < t_numOfCoeffs_ui; ++i ) {
		ifs>>t_compressedHeartbeat_oc.compressed_sig(i, 0);
	}
	
	Eigen::MatrixXd t_apr_md = l_compresserWithHermSys_oc.decompress( &t_compressedHeartbeat_oc );
	
	ofs<<t_apr_md.transpose()<<std::endl;
	
	ifs.close();
	
	ofs<<"testcase 3: DONE"<<std::endl<<std::endl;
	
	/* TC_4: Test getPRD methods*/
	ofs<<"**************** MT TC 4 ****************"<<std::endl;
	ofs<<"testcase 4: Test getPRD methods"<<std::endl;
	
	std::ofstream test_ofs("./output/test_ofs.txt");
	
	ofs<<l_compresserWithHermSys_oc.getPRD( &t_compressedHeartbeat_oc, t_sig_md, test_ofs);
	ofs<<std::endl<<l_compresserWithHermSys_oc.getPRD( &t_compressedHeartbeat_oc, t_sig_md)<<std::endl;
	ofs<<l_compresserWithHermSys_oc.getPRD( t_apr_md, t_sig_md )<<std::endl;
	
	test_ofs.close();
	
	ofs<<"testcase 4: DONE"<<std::endl<<std::endl;
	
	/* Clear up module test environment */
	ofs.close();
	
	return 0;
}
