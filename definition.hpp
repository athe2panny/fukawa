#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

/**************変数の定義(transmitter,noise,receiver関連)*************************************/

#define sqr(x) ((x)*(x))
const double PI = 3.141592654;	/* acos(-1.0) */
const double OneBySqrt2 = 0.707106781;	/* 1.0/sqrt(2.0) */
const double SYMBOL_RATE = 42.0e3;
const double Ts = (1.0/SYMBOL_RATE);
const int SYMBOLN = 64;
const int BITN = (SYMBOLN*2);


/**************変数の定義*************************************/

const int SensorN = 30;		//センサの数
const int Sensorb = 3;			//センサーのパケット複製数
const double Sensorr = 0.3;	//センサが通信できる距離
const int SensorP = 1;			//各センサのパケット数
const int PacketSize = 80;		//送信パケット長

/**************センサクラスの宣言******************************/
class Sensor{
	private:
		int id;
		int hop;				// シンクノードまでのホップ数
		double x;				// x座標
		double y;				// y座標

	public:
		double Getx();	//xの取得
		double Gety();	//yの取得
		void set_id_location(int id);		//id,x,yを設定する関数
		void disp();						//内容を出力するメンバ関数宣言
		void set_Sensor_hop(int hop);			//hopを設定する関数
		

		Sensor():
			hop(0){}
	};

/*************パケットクラスの宣言******************************/
class Packet{
	private:
		int Pid;						//パケットid
		int degree;						//次数
		int MixingTime;					//ミキシングタイム
		std::vector<int> nodeNumber;	//ノード番号
		int bit[BITN];			//ビットシーケンスデータ

	public:
		void set_Packet(int Pid, int id);		//id,次数,ミキシングタイム,ノード番号,データ
		void disp();							//内容を出力するメンバ関数宣言
};

/***************計算のための関数*******************************/

double cal_d(double x1, double y1, double x2, double y2);	//2点間距離を導出する関数

/***********************隣接行列******************************/

void make_adjacency_matrix(Sensor *s, std::vector<std::vector<int> > &array2D);		/*隣接行列を作る関数*/
void set_hop(std::vector<std::vector<int> > &array2D, std::vector<int> &hop_check, Sensor *s);						//隣接行列からホップ数配列を設定する関数

/***********************パケット生成******************************/

void bit_generator(int *bit);		//ビット生成
int transition_id(int id, std::vector<std::vector<int> > &array2D);						//遷移先idを決定する関数ゆ

/***********************transmitter******************************/
void transmitter(int (*bit), double (*signal)[2]);
void BPSK_modulator(int (*bit), double (*signal)[2]);



/***********************noise******************************/
void awgn(double (*transmitted_signal)[2], double (*received_signal)[2]);


/***********************receiver******************************/
void receiver(double (*signal)[2], int (*bit));
void QPSK_demodulator_cd(double (*signal)[2], int (*bit));







