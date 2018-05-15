#include "definition.hpp"

/*センサの初期設定に関する記述*/
/*センサID:0はシンクノード*/

/*２点間距離の計算*/
double cal_d(double x1, double y1, double x2, double y2){
	return sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
}

double Sensor::Getx(){
	return x;
}

double Sensor::Gety(){
	return y;
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

void Sensor::set_Sensor_hop(int n){
	hop = n;
}

/*センサの内容を表示させる関数*/
void Sensor::disp(){
	std::cout << "センサID:" << id << std::endl;
	std::cout << "x座標:" << x << std::endl;
	std::cout << "y座標:" << y << std::endl;
	std::cout << "ホップ数" << hop << '\n' << std::endl; 
}

/*センサノードの配列と二次元配列を引数として受け取り，隣接行列を作る関数*/
void make_adjacency_matrix(Sensor *s, std::vector<std::vector<int> > &array2D){
	double d;	//２点間距離を保持しておく変数

	for(int i=0;i<SensorN;i++){
		for(int j=0;j<SensorN;j++){
			d = cal_d(s[i].Getx(),s[i].Gety(),s[j].Getx(),s[j].Gety());
			if(d <= Sensorr && d != 0 ){
				array2D[i][j] = 1;
			}
		}
	}
}

//シンクノードからセンサノードまでのホップ数を設定する関数
void set_hop(std::vector<std::vector<int> > &array2D, std::vector<int> &hop_check, Sensor *s){

	int hierarchy = 1;						//シンクノードまでのホップ数をカウントする変数
	int count = 0;							//ループの終わりを管理する変数

	for(int j=0;j<SensorN;j++){
		if(array2D[0][j] == 1 && hop_check[j] == 0){	//hierarchyが登録されていない隣接ノードを対象
			hop_check[j] = hierarchy;
			count++;
		}
	}

 	while(count < SensorN - 1){							//全てのノードで設定するまで
		for(int i=0;i<SensorN;i++){
			if(hop_check[i] == hierarchy){			//階層ごとに隣接ノードの探索

				for(int j=0;j<SensorN;j++){
					if(array2D[i][j] == 1 && hop_check[j] == 0 && j != 0){	//hierarchyが登録されていない隣接ノードを対象
						hop_check[j] = hierarchy + 1;
						count++;
					}
				}

			}
		}
		hierarchy++;
	}

	for (int n = 0; n < SensorN; n++){
		s[n].set_Sensor_hop(hop_check[n]);
	}

}










