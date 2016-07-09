#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit( EcgSigPrep *SH): sig_handler(SH) {
	
}

MatchingPursuit::~MatchingPursuit() {
	
}

void MatchingPursuit::set_costfun(std::function<double (Coord &)> cfun) {
	costfun = cfun;
}

OrtCompressed* MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	OrtCompressed* ret;
	
	Eigen::MatrixXd sig = *(sig_handler->getNextSegment());
	Hermite Herm(sig.cols());
	std::cout<<"HERM INIT DONE"<<std::endl;
	
	for (unsigned int i = 0; i < rounds_deg.size(); ++i) {
		
		OrtCompresser OC(Herm, rounds_deg[i]);
		OrtCompressed* p = new OrtCompressed;
		
		//OPTIMIZATION
		// 1. Set anonymus function
		
		set_costfun( 
			[&sig, &OC, &Herm, this ] (Coord & pos) -> double {
				double dilat = pos[0];
				double trans = pos[1];
				Eigen::MatrixXd s = sig;
				s = sig_handler->setDilatTrans( dilat, trans, Herm.get_ort_fun_roots(), s );
				OrtCompressed* a_compression = OC.compressBeat( s );
				return OC.getPRD( a_compression, s ); 
			}
		);
		
		//2. NelderMead (vagy mas) -->o legyen jo -> harmadik kor
		
		//Initial values for NM optimization
		std::vector<Coord> pop;
		pop[0][0] = 1; pop[0][1] = sig.cols()/2.0;
		pop[1][0] = 0.5; pop[1][1] = 100.0;
		pop[2][0] = 1.0/4.5; 
		
		Eigen::MatrixXd::Index maxRow;
		Eigen::MatrixXd::Index maxCol; 
		
		Eigen::MatrixXd absSig = sig;
		for( unsigned int i = 0; i < absSig.cols(); ++i ) {
				absSig(0, i) = abs(absSig(0, i));
		}
		
		absSig.maxCoeff(&maxRow, &maxCol);
		
		pop[2][2] = (double)(maxCol);
		
		Coord optimized_coords;
		
		NelderMead opter(20, 0.2, pop);
		optimized_coords = opter.Optimize(costfun);
		
		sig = sig_handler->setDilatTrans(optimized_coords[0], optimized_coords[1], Herm.get_ort_fun_roots(), sig);
		
		
		//3. Csinald meg a jokkal
		
		p = OC.compressBeat(sig);
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		std::cout<<"sig round "<<i<<":"<<std::endl;
		std::cout<<sig.transpose()<<std::endl;
		std::cout<<"***************"<<std::endl;
		
		char c; std::cin>>c;
		
		std::cout<<"apr:"<<std::endl;
		std::cout<<apr.transpose()<<std::endl;
		std::cout<<"****************"<<std::endl;
		
		std::cin>>c;
		
		sig = sig - apr;
		ret = p;
	}
	
	return ret;
}

