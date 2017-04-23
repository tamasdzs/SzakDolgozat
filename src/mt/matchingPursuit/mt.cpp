/*
 *                MODULE TEST FOR MODULES OrtFunSys and Hermite
*/ 

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "EcgSigPrep.h"
#include "Hermite.h"
#include "OrtCompresser.h"
#include "MatchingPursuit.h"

/* DEFINES FOR TESTCASES */

#define MT_MIT_BIH_MEASUREMENT_NAME_1_STR "./input/103/103"
#define MT_NUM_OF_LEADS_INT 	(int)2
#define MT_NUM_OF_SAMPLES_1_INT (int)2500

#define MT_NUM_OF_BEATS_TO_COMP_INT (int)2

/* END DEFINES FOR TESTCASES */

int main() {
	 
	 
	// Set up module test environment 	
	std::ofstream  ofs ("./output/mt_results.txt", std::ofstream::out);
	
	
	// TC_1:  Create an instance of a MatchingPursuit type object
	ofs<<"**************** MT TC 1 ****************"<<std::endl;
	ofs<<"testcase 1: Create an instance of a MatchingPursuit type object"<<std::endl;
	
	EcgSigPrep* signal_handler = new EcgSigPrep(MT_MIT_BIH_MEASUREMENT_NAME_1_STR, MT_NUM_OF_LEADS_INT, MT_NUM_OF_SAMPLES_1_INT);
	MatchingPursuit MP(signal_handler);
	
	// TC_2:  Compress a heartbeat. Write result to output and input/decomp.cmp
	ofs<<"**************** MT TC 2 ****************"<<std::endl;
	ofs<<"testcase 2: Compress two consecutive heartbeats. Write result to output and input/decomp.cmp"<<std::endl;
	
	std::ofstream cmp_ofs ("input/decomp.cmp");
	
	std::vector<int> rounds_deg;
	rounds_deg.push_back(7);
	rounds_deg.push_back(6);
	rounds_deg.push_back(2);
	
	for ( int i = 0; i < MT_NUM_OF_BEATS_TO_COMP_INT; ++i ) {
	
		signal_handler->getNextSegment();
		
		OrtCompressed* res;
		res = MP.CompressBeat(rounds_deg, false);
		
		OrtCompressed* del_res = 0;
		for (int j = 0; j < 3; ++j) {
			
			
			ofs<<"Dilat: "<<res->dilat<<" Trans: "<<res->trans<<std::endl;
			ofs<<"coefss: "<<res->compressed_sig<<std::endl;
			cmp_ofs<<res->dilat<<" "<<res->trans<<" "<<signal_handler->getSignal()->cols()<<" "<<res->compressed_sig.rows()<<" "<<res->compressed_sig.transpose()<<std::endl;
			
			res = res->next;
			delete del_res;
		}
	}
	cmp_ofs.close();
	
	
	/* TC_3: Decompress the compressed heartbeat*/
	ofs<<"**************** MT TC 3 ****************"<<std::endl;
	ofs<<"testcase 3: Decompress the compressed heartbeats"<<std::endl;
	
	
	std::ifstream preproc("./input/decomp.cmp");
	std::string line;
	int beatno = 0;
	
	while (std::getline(preproc, line)) {
		beatno++;
	}
	beatno = beatno/3;
	
	preproc.close();
	
	std::ifstream ifs;
	ifs.open("./input/decomp.cmp");
	if (ifs.is_open()){
		ofs<<"input file opened"<<std::endl;
	}
	else {
		ofs<<"file wasnt opened"<<std::endl;
		return -1;
	}
	for ( int i = 0; i < beatno; ++i ) {	
			
		std::string line;
		std::stringstream line_stream;
		
		OrtCompressed single_segment;
		int N;
		int CoeffsN;
		
		Eigen::MatrixXd finalApr;
		
		for ( int j = 0; j < 3; ++j ) {
			
			line_stream.clear();
			line.clear();
			getline(ifs, line);
			line_stream.str(line);
			
			line_stream>>single_segment.dilat;
			
			line_stream>>single_segment.trans;
			
			line_stream>>N;
			
			line_stream>>CoeffsN;
			
			single_segment.compressed_sig = Eigen::MatrixXd::Zero( CoeffsN, 1 );
			
			for ( int i = 0; i < CoeffsN; ++i ) {
				line_stream>>single_segment.compressed_sig(i, 0);
			}
			
			std::cout<<std::endl;
			
			Hermite H(N);
			OrtCompresser OC(H, CoeffsN);
			Eigen::MatrixXd apr_segment = OC.decompress( &single_segment );
				
			if ( j == 0 ) {
				finalApr = apr_segment;
			} 
			else {
				finalApr += apr_segment;
			}
		
		}
		
		ofs<<finalApr.transpose()<<std::endl;
	}
			
	ifs.close();
	ofs<<"testcase 3: DONE"<<std::endl<<std::endl;
	
	
	/* Clear up module test environment */
	//delete signal_handler;
	ofs.close();
	
	return 0;
}
