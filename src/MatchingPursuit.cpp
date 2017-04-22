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

std::vector<Coord> MatchingPursuit::set_optimizer_init_values(Eigen::MatrixXd curr_sig) {
	std::vector<Coord> ret;
	ret.resize(CN_MATCHING_PURSUIT_POPULATION_SIZE_INT);
	
	ret[0][0] = CN_MATCHING_PURSUIT_INIT_SIMPLEX_HIGH_DILAT_DB; 
	ret[1][0] = CN_MATCHING_PURSUIT_INIT_SIMPLEX_LOW_DILAT_DB; 
	ret[2][0] = CN_MATCHING_PURSUIT_INIT_SIMPLEX_MID_DILAT_DB;
	
	Eigen::MatrixXd::Index maxRow;
	Eigen::MatrixXd::Index maxCol; 
		
	Eigen::MatrixXd absSig = curr_sig;
	for( unsigned int i = 0; i < absSig.cols(); ++i ) {
			absSig(0, i) = fabs(absSig(0, i));
	}
		
	absSig.maxCoeff(&maxRow, &maxCol);
	
	ret[0][1] = maxCol - 5;
	ret[1][1] = maxCol + 5;
	ret[2][1] = (double)(maxCol);
	
	return ret; 
}

OrtCompressed* MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	OrtCompressed* ret = 0;
	
	Eigen::MatrixXd sig = *(sig_handler->getNextSegment());
	Eigen::MatrixXd osig = sig;
	Eigen::MatrixXd original_signal = sig;
	Hermite Herm(sig.cols());
	
	std::ofstream t_inActionSig_ofs;
	std::ofstream t_inActionApr_ofs;
	
	std::ofstream t_qrsSig_ofs;
	std::ofstream t_qrsApr_ofs;
	
	std::ofstream t_tSig_ofs;
	std::ofstream t_tApr_ofs;
	
	std::ofstream t_pSig_ofs;
	std::ofstream t_pApr_ofs;
	
	std::ofstream t_combinedSig_ofs;
	std::ofstream t_combinedApr_ofs;
	
	for (unsigned int i = 0; i < rounds_deg.size(); ++i) {
		
		switch(i) {
			case 0:
				t_qrsSig_ofs.open(CN_MATCHING_PURSUIT_QRS_SIG_STR);
				t_qrsSig_ofs.clear();
				t_qrsSig_ofs<<osig.transpose();
				t_qrsSig_ofs.close();
				
				t_combinedSig_ofs.open(CN_MATHCING_PURSUIT_COMBINED_SIG_STR);
				t_combinedSig_ofs.clear();
				t_combinedSig_ofs<<osig.transpose();
				t_combinedSig_ofs.close();
				break;
			case 1:	
				t_tSig_ofs.open(CN_MATCHING_PURSUIT_T_SIG_STR);
				t_tSig_ofs.clear();
				t_tSig_ofs<<osig.transpose();
				t_tSig_ofs.close();
				break;
			case 2:
				t_pSig_ofs.open(CN_MATHCING_PURSUIT_P_SIG_STR);
				t_pSig_ofs.clear();
				t_pSig_ofs<<osig.transpose();
				t_pSig_ofs.flush();
				break;
		}
		
		t_inActionSig_ofs.open(CN_MATCHING_PURSUIT_IN_ACTION_SIG_STR);
		t_inActionSig_ofs.clear();
		t_inActionSig_ofs<<osig.transpose();
		t_inActionSig_ofs.close();
		
		OrtCompresser OC(Herm, rounds_deg[i]);
		
		OrtCompressed* p = new OrtCompressed;
		
		set_costfun( 
			[&osig, &OC, &Herm, &t_inActionApr_ofs, this ] (Coord & pos) -> double {
				double dilat = pos[0];
				double trans = pos[1];
				OrtCompressed a_compression;
				Eigen::MatrixXd s = osig;
				s = sig_handler->setDilatTrans( dilat, trans, Herm.get_ort_fun_roots(), s );
				a_compression.compressed_sig = OC.compressBeat( s );
				a_compression.dilat = dilat; a_compression.trans = trans;
				
				t_inActionApr_ofs.open(CN_MATCHING_PURSUIT_IN_ACTION_APR_STR);	
				t_inActionApr_ofs.clear();
				double ret = OC.getPRD( &a_compression, osig, t_inActionApr_ofs );
				t_inActionApr_ofs.close();  
				return ret;
			}
		);
		
		std::vector<Coord> pop = set_optimizer_init_values(osig);
		
		Coord optimized_coords;
		
		NelderMead opter(CN_MATCHING_PURSUIT_NELDER_ROUNDS_INT, CN_MATCHING_PURSUIT_NELDER_MAXERR_DB, pop);
		
		optimized_coords = opter.Optimize(costfun);
	
		sig = sig_handler->setDilatTrans(optimized_coords[0], optimized_coords[1], Herm.get_ort_fun_roots(), sig);
			
		p->compressed_sig = OC.compressBeat(sig);
		p->dilat = optimized_coords[0];
		p->trans = optimized_coords[1];
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		t_inActionApr_ofs.open(CN_MATCHING_PURSUIT_IN_ACTION_APR_STR);
		t_inActionApr_ofs.clear();
		t_inActionApr_ofs<<apr.transpose();
		t_inActionApr_ofs.close();
		
		switch(i) {
			case 0:
				t_qrsApr_ofs.open(CN_MATCHING_PURSUIT_QRS_APR_STR);
				t_qrsApr_ofs.clear();
				t_qrsApr_ofs<<apr.transpose();
				t_qrsApr_ofs.close();
				break;
			case 1:	
				t_tApr_ofs.open(CN_MATCHING_PURSUIT_T_APR_STR);
				t_tApr_ofs.clear();
				t_tApr_ofs<<apr.transpose();
				t_tApr_ofs.close();
				break;
			case 2:
				t_pApr_ofs.open(CN_MATHCING_PURSUIT_P_APR_STR);
				t_pApr_ofs.clear();
				t_pApr_ofs<<apr.transpose();
				t_pApr_ofs.close();
				break;
		}
				
		osig = osig - apr;
		p->next = ret;
		ret = p;
		sig = osig;
	}
	
	return ret;
}
