#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit( EcgSigPrep *SH, std::map<std::string, std::string> fdirs): sig_handler(SH) {
	file_dirs = fdirs;
}

MatchingPursuit::MatchingPursuit( EcgSigPrep*SH ) {
	
}

MatchingPursuit::~MatchingPursuit() {
	
}

void MatchingPursuit::set_costfun(std::function<double (Coord &)> cfun) {
	costfun = cfun;
}

OrtCompressed* MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	OrtCompressed* ret;
	
	Eigen::MatrixXd sig = *(sig_handler->getNextSegment());
	Eigen::MatrixXd osig = sig;
	Hermite Herm(sig.cols());
	
	for (unsigned int i = 0; i < rounds_deg.size(); ++i) {
		
		std::ofstream sigout;
		sigout.clear();
		switch(i) {
			case 0:
				//sigout.open(file_dirs["QRS_sig"]);
				sigout.open(CN_MATCHING_PURSUIT_QRS_SIG_STR);
				sigout<<osig.transpose();
				sigout.close();
				sigout.clear();
				sigout.open(CN_MATHCING_PURSUIT_COMBINED_SIG_STR);
				sigout<<osig.transpose();
				sigout.close();
				break;
			case 1:	
				sigout.open(CN_MATCHING_PURSUIT_T_SIG_STR);
				sigout<<osig.transpose();
				sigout.close();
				break;
			case 2:
				sigout.open(CN_MATHCING_PURSUIT_P_SIG_STR);
				sigout<<osig.transpose();
				sigout.close();
				break;
		}
		
		
		//Fileokat egyszer nyissuk meg es zarjuk be
		std::ofstream fout; 
		fout.open(file_dirs["in_action_sig"]);
		fout<<osig.transpose();
		fout.close();
		
		OrtCompresser OC(Herm, rounds_deg[i]);
		
		OrtCompressed* p = new OrtCompressed;
		
		//OPTIMIZATION
		// 1. Set anonymus function
		
		
		//TODO: FILE MEGNYITAS MENJEN A MAINBEN, itt mar csak FD-kbe irjunk (FIGYELNI A FLUSH-ra)
		
		set_costfun( 
			[&osig, &OC, &Herm, this ] (Coord & pos) -> double {
				double dilat = pos[0];
				double trans = pos[1];
				OrtCompressed a_compression;
				Eigen::MatrixXd s = osig;
				s = sig_handler->setDilatTrans( dilat, trans, Herm.get_ort_fun_roots(), s );
				a_compression.compressed_sig = OC.compressBeat( s );
				a_compression.dilat = dilat; a_compression.trans = trans;
				double ret = OC.getPRD( &a_compression, osig, this->file_dirs["in_action_apr"] );  
				return ret;
			}
		);
		//2. NelderMead (vagy mas) -->o legyen jo -> harmadik kor
		
		//Initial values for NM optimization -->> TODO: constant or define, dont shit the code here.
		std::vector<Coord> pop;
		pop.resize(3);
	
		pop[0][0] = 0.16; 
		pop[1][0] = 0.14; 
		pop[2][0] = 0.154; 
		
		Eigen::MatrixXd::Index maxRow;
		Eigen::MatrixXd::Index maxCol; 
		
		Eigen::MatrixXd absSig = osig;
		for( unsigned int i = 0; i < absSig.cols(); ++i ) {
				absSig(0, i) = fabs(absSig(0, i));
		}
		
		absSig.maxCoeff(&maxRow, &maxCol);
		
		pop[0][1] = maxCol - 5;
		pop[1][1] = maxCol + 5;
		pop[2][1] = (double)(maxCol);
				
		Coord optimized_coords;
		
		NelderMead opter(20, 0.2, pop);
		
		optimized_coords = opter.Optimize(costfun);
		
		sig = sig_handler->setDilatTrans(optimized_coords[0], optimized_coords[1], Herm.get_ort_fun_roots(), sig);
			
		p->compressed_sig = OC.compressBeat(sig);
		p->dilat = optimized_coords[0];
		p->trans = optimized_coords[1];
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		fout.clear();
		fout.open(file_dirs["in_action_apr"]);
		fout<<apr.transpose();
		fout.close();
		
		std::ofstream aprout;
		aprout.clear();
		
		switch(i) {
			case 0:
				aprout.open(file_dirs["QRS_apr"]);
				aprout<<apr.transpose();
				aprout.close();
				break;
			case 1:	
				aprout.open(file_dirs["T_apr"]);
				aprout<<apr.transpose();
				aprout.close();
				break;
			case 2:
				aprout.open(file_dirs["P_apr"]);
				aprout<<apr.transpose();
				aprout.close();
				break;
		}
				
		osig = osig - apr;
		ret = p;
		delete p;
		sig = osig;
	}
	
	return ret;
}
