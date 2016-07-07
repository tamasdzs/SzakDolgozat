#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit(char* REC, OrtFunSys& OS, EcgSigPrep &SH) {
	 signal_handler = SH;
	 ort_sys = OS;
}

MatchingPursuit::~MatchingPursuit() {
	
}

void MatchingPursuit::set_costfun(std::function<double (Coord &)> cfun) {
	costfun = cfun;
}

Compressed* MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	Compressed* ret;
	
	Eigen::MatrixXd sig = sig_handler.getNextSegment();
	Hermite Herm(sig.cols());
	std::cout<<"HERM INIT DONE"<<std::endl;
	
	for (unsigned int i = 0; i < rounds_deg.size(); ++i) {
		
		OrtCompresser OC(Herm, rounds_deg[i]);
		Compressed* p;
		
		//OPTIMIZATION
		// 1. Set anonymus function
		
		set_costfun( //-> o legyen jo -> masodik kor
			[] (Coord & pos) {
				Eigen::MatrixXd s = sig;
				s = sig_handler.SetDilatTrans( pos[0], pos[1], Herm.get_ort_fun_roots(), s );
				a_compression = OC.compressBeat( s );
				return OC.getPRD( a_compression ); //o legyen jo ->elso kor
			}
		);
		
		//2. NelderMead (vagy mas) -->o legyen jo -> harmadik kor
		
		
		
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
	
	}
	
	return ret;
}

