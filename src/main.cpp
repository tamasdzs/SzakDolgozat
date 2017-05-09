#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>

#include "MatchingPursuit.h"

/* CONSTANTS */

const int ANIMATION_MODE     = 1;
const int COMPRESSION_MODE   = 2;
const int DECOMPRESSION_MODE = 3;
const int MANUAL_MODE 		 = 4;

const unsigned int NUM_OF_LEADS = 2;
const unsigned int NUM_OF_SAMPS = 3000;

const unsigned int NUM_OF_BEATS_TO_COMPRESS = 3;

const int QRS_DEG = 7;
const int T_DEG   = 6;
const int P_DEG   = 2;


/* DEFINES */
#define ANIMATION_SIGNAL_ID "signals/119/119"

/* METHODS */
void showAnimation(unsigned int num_of_leads, unsigned int num_of_samples);
void compressSignal( char* signal_id, char* output_dir, unsigned int num_of_leads, unsigned int num_of_samples, unsigned int num_of_beats );
void compressSignalManually( char* signal_id, char* output_dir, unsigned int num_of_leads, unsigned int num_of_beats );
void decompressSignal(char* input_path, char* output_path);

int main( int argc, char* argv[] ) {

	int mode = -1;
	int beats_to_cmpr;
	char* output_dir;
	char* input_dir;
	
	/* Parse command line parameters and decide usecase */
	
	if ( argc < 2 ) {
		return -1;
	}
	else if ( argc == 2 ) {
		mode = 1;
	}
	else if ( argc == 4 ) {
		mode = atoi(argv[1]);
		input_dir = argv[2];
		output_dir = argv[3];
	}
	else {
		mode = atoi(argv[1]);
		input_dir = argv[2];
		output_dir = argv[3];
		beats_to_cmpr = atoi(argv[4]);
	}
	
	switch(mode) {
		case ANIMATION_MODE:
			showAnimation(NUM_OF_LEADS, NUM_OF_SAMPS);
			break;
		
		case COMPRESSION_MODE:
			compressSignal(input_dir, output_dir, NUM_OF_LEADS, NUM_OF_SAMPS, NUM_OF_BEATS_TO_COMPRESS);
			break;
			
		case DECOMPRESSION_MODE:
			decompressSignal(input_dir, output_dir);
			break;
		
		case MANUAL_MODE:
			compressSignalManually(input_dir, output_dir, NUM_OF_LEADS, beats_to_cmpr);
			break;
		default:
			std::cout<<"Not a valid mode"<<std::endl;
			return 1;
			break;
	}
	
	return 0;
}

void compressSignalManually( char* signal_id, char* output_dir, unsigned int num_of_leads, unsigned int num_of_beats ) {
	
	unsigned int num_of_samples = num_of_beats * 350;
	bool segment_ok = true;
	
	EcgSigPrep* signal_handler = new EcgSigPrep(signal_id, num_of_leads, num_of_samples);
	
	MatchingPursuit MP(signal_handler);
		
	std::ofstream cmp_ofs (output_dir);
	
	std::vector<int> rounds_deg;
	rounds_deg.push_back(7);
	rounds_deg.push_back(6);
	rounds_deg.push_back(2);
	
	for ( unsigned int i = 0; (i < num_of_beats) && (segment_ok != false); ++i ) {
		
		signal_handler->getNextSegment();
		
		if (  (*(signal_handler->getSignal()))(0,0) != -1 ) {
			
			OrtCompressed* res;
			res = MP.CompressBeat(rounds_deg, false);
			
			OrtCompressed* del_res = 0;
			for (int j = 0; j < 3; ++j) {
				
				cmp_ofs<<res->dilat<<" "<<res->trans<<" "<<signal_handler->getSignal()->cols()<<" "<<res->compressed_sig.rows()<<" "<<res->compressed_sig.transpose()<<std::endl;
				
				if ( del_res == 0 ) {
					del_res = res;
				} 
				else 
				{
					delete del_res;
					del_res = res;
				}
				
				res = res->next;
			}
			delete del_res;
		}
		else {
			segment_ok = false;
		}
	}
	cmp_ofs.close();
}

void showAnimation(unsigned int num_of_leads, unsigned int num_of_samples ) {
	
	EcgSigPrep signal_handler(ANIMATION_SIGNAL_ID, num_of_leads, num_of_samples);
	signal_handler.getNextSegment();
	signal_handler.getNextSegment();
	std::vector<int> rounds_deg = { QRS_DEG, T_DEG, P_DEG };
	
	MatchingPursuit MP( &signal_handler );
	
	OrtCompressed* res;
	
	res = MP.CompressBeat(rounds_deg, true);
	OrtCompressed* del_res = 0;
	for ( ; res != 0; res = res->next) {
		
		if ( del_res == 0 ) {
			del_res = res;
		} 
		else {
			delete del_res;
			del_res = res;
		}
	}
	delete del_res;
}

void compressSignal ( char* signal_id, char* output_dir, unsigned int num_of_leads, unsigned int num_of_samples, unsigned int num_of_beats ) {
		
	EcgSigPrep* signal_handler = new EcgSigPrep(signal_id, num_of_leads, num_of_samples);
	MatchingPursuit MP(signal_handler);
		
	std::ofstream cmp_ofs (output_dir);
	
	std::vector<int> rounds_deg;
	rounds_deg.push_back(7);
	rounds_deg.push_back(6);
	rounds_deg.push_back(2);
	
	for ( unsigned int i = 0; i < NUM_OF_BEATS_TO_COMPRESS; ++i ) {
	
		signal_handler->getNextSegment();
		
		OrtCompressed* res;
		res = MP.CompressBeat(rounds_deg, false);
		
		OrtCompressed* del_res = 0;
		for (int j = 0; j < 3; ++j) {
			
			cmp_ofs<<res->dilat<<" "<<res->trans<<" "<<signal_handler->getSignal()->cols()<<" "<<res->compressed_sig.rows()<<" "<<res->compressed_sig.transpose()<<std::endl;
			
			if ( del_res == 0 ) {
				del_res = res;
			} 
			else 
			{
				delete del_res;
				del_res = res;
			}
			
			res = res->next;
		}
		delete del_res;
	}
	cmp_ofs.close();
}

void decompressSignal(char* input_path, char* output_path) {
	
	std::ofstream ofs(output_path);
	
	std::ifstream preproc(input_path);
	std::string line;
	int beatno = 0;
	
	while (std::getline(preproc, line)) {
		beatno++;
	}
	beatno = beatno/3;
	
	preproc.close();
	
	std::ifstream ifs;
	ifs.open(input_path);
	if (ifs.is_open()){
		ofs<<"The signal's values:"<<std::endl;
	}
	else {
		ofs<<"Input could not be opened"<<std::endl;
		return;
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
}
