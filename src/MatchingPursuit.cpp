#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit( EcgSigPrep *SH, std::string s, std::string nm, std::string apr): sig_handler(SH) {
	sig_out = s;
	nm_out = nm;
	apr_out = apr;
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
		
		std::ofstream fout; 
		fout.open(sig_out);
		fout<<osig.transpose();
		fout.close();
		
		OrtCompresser OC(Herm, rounds_deg[i]);
		
		OrtCompressed* p = new OrtCompressed;
		
		//OPTIMIZATION
		// 1. Set anonymus function
		
		set_costfun( 
			[&osig, &OC, &Herm, this ] (Coord & pos) -> double {
				double dilat = pos[0];
				double trans = pos[1];
				
				//std::cout<<"COSTFUN: dilat: "<<dilat<<" trans: "<<trans<<std::endl;
				
				Eigen::MatrixXd s = osig;
				s = sig_handler->setDilatTrans( dilat, trans, Herm.get_ort_fun_roots(), s );
				OrtCompressed* a_compression = OC.compressBeat( s );
				a_compression->dilat = dilat; a_compression->trans = trans;
				double ret = OC.getPRD( a_compression, osig, nm_out );  
				delete a_compression;
				return ret;
			}
		);
		
		//std::cout<<"costfun set \n";
		
		//2. NelderMead (vagy mas) -->o legyen jo -> harmadik kor
		
		//Initial values for NM optimization
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
				
		//std::cout<<"Starting positions for population initaliazed \n";
		
		Coord optimized_coords;
		
		NelderMead opter(20, 0.2, pop);
		
		//std::cout<<"Nelder Mead optimizer init done \n";
		
		optimized_coords = opter.Optimize(costfun);
		
		
		sig = sig_handler->setDilatTrans(optimized_coords[0], optimized_coords[1], Herm.get_ort_fun_roots(), sig);
		
		//std::cout<<"signal set up \n";
			
		p = OC.compressBeat(sig);
		p->dilat = optimized_coords[0];
		p->trans = optimized_coords[1];
		//std::cout<<"Final compression done \n";
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		//std::cout<<"Apprixmation acquired \n";
		
		fout.clear();
		fout.open(apr_out);
		fout<<apr.transpose();
		fout.close();
				
		osig = osig - apr;
		ret = p;
		delete p;
		sig = osig;
	}
	
	return ret;
}
