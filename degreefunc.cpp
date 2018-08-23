//次数関数の定義
#include	"definition.hpp"

//次数を決定する関数
//出力：次数	引数：分布の種類番号
int degree_init(int deg){

	if(deg == 0){
		return uni_dis(D_MAX);
	}else if(deg == 1){
		return soliton(D_MAX);
	}else{
		return robust_soliton(delta, D_MAX, M);
	} 

}

//一様分布
//uniform_int_distributionクラスを使用
int uni_dis(int d_max){

	std::random_device seed_gen;
	std::default_random_engine engine(seed_gen());

	// 0以上d_max以下の値を等確率で発生させる
  	std::uniform_int_distribution<> dist(1, d_max);

  	return dist(engine);
}

//ソリトン分布　O_s(d)
int soliton(int d_max){
	
	int d;

 	std::random_device seed_gen;
  	std::default_random_engine engine(seed_gen());

  	// 0.000以上1.000未満の値を等確率で発生させる
  	std::uniform_real_distribution<> dist(0.0, 1.0);
  	double r = dist(engine);

  	double cdf = 1.0/(double)d_max; 

	if(r < cdf){
		return 1;		
	}else{
		for(d=2;d<=d_max;d++){
			cdf += 1.0/(double)(d*(d-1));
			if(r < cdf){
				return d;
			}
		}
	}
	return 0;
}

//ロバストソリトン分布　O_RS(d)
int robust_soliton(double delta, int d_max, int M){

	int i;
  	double R = d_max/M;
	double beta = 0;
	std::vector<double> O_rs(d_max, 0);
	std::vector<double> O_s(d_max, 0);
	std::vector<double> mu(d_max, 0);


	//O_s
	O_s[0] = 1.0 / (double)d_max;
	for(i=1;i<d_max;i++){
		O_s[i] = 1.0 / (double) ((i+1) * ( (i+1) - 1 ));
	}

	//mu
	for(i=0;i<M-1;i++){
  		mu[i] = (double)1/((i+1)*M);
  	}
  	mu[M-1] = std::log(R/delta)/M;

  	//beta
	for(i=0;i<d_max;i++){
		beta += O_s[i] + mu[i];
	}

	//O_rs
	for(i=0;i<d_max;i++){
		O_rs[i] = (O_s[i] + mu[i]) / beta;
	}

	//累積分布関数
	for(i=1;i<d_max;i++){
		O_rs[i] += O_rs[i-1];
	}


	std::random_device seed_gen;
  	std::default_random_engine engine(seed_gen());

  	// 0.000以上1.000未満の値を等確率で発生させる
  	std::uniform_real_distribution<> dist(0.0, 1.0);
  	double r = dist(engine);

  	for(i=0;i<d_max;i++){
  		if(r<O_rs[i]){
  			return i+1;
  		}
  	}
  	return 0;
}











