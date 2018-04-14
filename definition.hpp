#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

/**************変数の定義*************************************/

const int Sensor_N = 1000;		//センサの数
const int Sensor_b = 3;			//センサー複製数
const double Sensor_r = 0.05;	//センサが通信できる距離
const int Sensor_P = 1;			//各センサのパケット数
const int PacketSize = 80;		//送信パケット長

/**************センサクラスの宣言******************************/
class Sensor{
	private:
		int id;
		int hop;				// シンクノードまでのホップ数
		double x;				// x座標
		double y;				// y座標

	public:
		void set_id_location(int id);		//id,x,yを設定する関数
		void set_near_sensor(Sensor *p);	//近くのセンサの設定
		void disp();						//内容を出力するメンバ関数宣言
	};

/***************計算のための関数*******************************/

double cal_d(double x1, double y1, double x2, double y2);	//2点間距離を導出する関数
