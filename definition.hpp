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

//送信電力関連
const double Eb_N0 = 11;
const double CNR = Eb_N0 + 3.0;

/**************変数の定義*************************************/

const int SensorN = 30;		//センサの数
const int Sensorb = 3;			//センサーのパケット複製数
const double Sensorr = 0.3;	//センサが通信できる距離
const int PacketSize = 80;		//送信パケット長

/**************センサクラスの宣言******************************/
class Sensor{
	private:
		int id;
		int hop;				// シンクノードまでのホップ数
		double x;				// x座標
		double y;				// y座標
		int bit[BITN];			// ビットシーケンスデータ

	public:
		double Getx();	//xの取得
		double Gety();	//yの取得
		int* Getbit();	//データの先頭アドレスの取得
		void set_Sensor(int id);			//id,x,y,ビットシーケンスデータを設定する関数
		void set_Sensor_hop(int hop);	    //hopを設定する関数
		void disp();						//内容を出力するメンバ関数宣言		

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
		int bit[BITN];					//ビットシーケンスデータ

	public:
		int Getdegree();
		int GetMix();
		int* Getbit();								//ビットシーケンスデータを取得する関数

		void set_Packet(int Pid, int id, int *p);	//id,次数,ミキシングタイム,ノード番号,データを設定する関数
		void copy_Packet(int n, int id, int *p);	//パケットの内容をコピーする関数
		int Getnowid();	

		void disp();								//内容を出力するメンバ関数宣言
		void pushnodeNumber(int now_id);			//ノード番号を末尾に追加する関数
	 	std::vector<int> GetnodeNumber();			//nodeNumberの先頭アドレスを返す関数
};

/***************計算のための関数*******************************/

double cal_d(double x1, double y1, double x2, double y2);	//2点間距離を導出する関数

/***********************隣接行列******************************/

void make_adjacency_matrix(Sensor *s, std::vector<std::vector<int> > &array2D);						/*隣接行列を作る関数*/
void set_hop(std::vector<std::vector<int> > &array2D, std::vector<int> &hop_check, Sensor *s);		//隣接行列からホップ数配列を設定する関数

/***********************パケット生成******************************/

void bit_generator(int *bit);															//ビット生成
int transition_id(int id, std::vector<std::vector<int> > &array2D);						//遷移先idを決定する関数
void transmitter_to_receiver(int *transmitted_bit, int *received_bit);					//送信機>通信路>受信機の部分をまとめた関数
int bed(int *tbit, int *rbit);															//bit error detection 誤り検出　出力:0or1

/***********************transmitter******************************/
void transmitter(int (*bit), double (*signal)[2]);
void QPSK_modulator(int (*bit), double (*signal)[2]);



/***********************noise******************************/
void awgn(double (*transmitted_signal)[2], double (*received_signal)[2]);


/***********************receiver******************************/
void receiver(double (*signal)[2], int (*bit));
void QPSK_demodulator_cd(double (*signal)[2], int (*bit));

/*************************ber********************************/
void ber(int loop, int (*tbit), int (*rbit));






