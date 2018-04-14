#include "definition.hpp"

/*センサの初期設定に関する記述*/
/*センサID:0はシンクノード*/

/*２点間距離の計算*/
double cal_d(double x1, double y1, double x2, double y2){
	return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}

/*ノードを1*1エリアにばらまく関数*/
void Sensor::set_id_location(int n){

	std::random_device rnd;     						// 非決定的な乱数生成器
    std::mt19937_64 mt(rnd());							//乱数生成
    std::uniform_real_distribution<> rand1(-0.5, 0.5);	// [-0.5, 0.5] 範囲の一様乱数

	id = n;
	if(n == 0){
		x = 0;
		y = 0;
	}else{
		x = rand1(mt);
		y = rand1(mt);
	}
	
}

/*センサの内容を表示させる関数*/
void Sensor::disp(){
	std::cout << "センサID:" << id << '\n';
	std::cout << "x座標:" << x << '\n';
	std::cout << "y座標:" << y << "\n\n";
}

/*隣接ノードの登録をする関数*/
void Sensor::set_near_sensor(Sensor *p){
	
}





//シンクノードからセンサノードの番号決定