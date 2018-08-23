#include <cstdio>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

/**************変数の定義*************************************/

#define sqr(x) ((x)*(x))
#define DIFF 1
#define PI 3.141592654	/* acos(-1.0) */
#define PHI (PI / 2.0)
#define OneBySqrt2 0.707106781	/* 1.0/sqrt(2.0) */
#define SYMBOL_RATE 42.0e3
#define Ts (1.0/SYMBOL_RATE)
#define BITN 128
#define SYMBOLN (BITN/2 + DIFF)

const int SensorN = 100;			//センサの数
const int Sensorb = 3;			//センサーのパケット複製数
const double Sensorr = 0.1;		//センサが通信できる距離
const int PacketSize = 80;		//送信パケット長
const double delta = 0.01;		//LT符号誤り率delta
const int D_MAX = 20;			//最大次数
const int M = 2;				//Robast Soliton distribution M
const int deg = 2;				//次数を決定する番号
/*---------------------------------------------------------*/
/* Multipath                                               */
/*---------------------------------------------------------*/
#define BURST			(SYMBOLN + PATH-1)
#define COMPONENT		8
#define PATH			2
#define FD				0.0

/**************結果データ関連*************************************/
const int GRAPH = 0;								//0:x軸が電力雑音比　1:x軸がmixing time
const int LOOPN = 1;						//ループ回数
#define FILENAME 	"./data/Eb_N0_PER2322.dat"		//出力ファイル名
#define FILENAME2	"./data/Eb_N0_HOP2322.dat"		//出力ファイル名
#define FILENAME3	"./data/MIXT_PER.dat"		//出力ファイル名
#define FILENAME4	"./data/MIXT_HOP.dat"		//出力ファイル名

/**************センサクラスの宣言******************************/
class Sensor{
	private:
		//メンバ変数
		int id;
		int hop;				// シンクノードまでのホップ数
		double x;				// x座標
		double y;				// y座標
		int *bit;				// ビットシーケンスデータ　動的確保

	public:
		//メンバのアクセス関数
		double Getx();	//xの取得
		double Gety();	//yの取得
		int Gethop();	//hopの取得
		int* Getbit();	//データの先頭アドレスの取得
		void set_Sensor(int id);			//id,x,y,ビットシーケンスデータを設定する関数
		void set_Sensor_hop(int hop);	    //hopを設定する関数
		void disp();						//内容を出力するメンバ関数宣言		

	public:
		//コンストラクタ，デストラクタ
		Sensor();
		~Sensor();
	};

/*************パケットクラスの宣言******************************/
class Packet{
	private:
		//メンバ変数
		int Pid;						//パケットid
		int degree;						//次数
		int MixingTime;					//ミキシングタイム
		std::vector<int> nodeNumber;	//ノード番号
		int* bit;						//ビットシーケンスデータ
		int at_sink;				//シンクノードに到達した:1 途中で破棄された:0

	public:
		//メンバへのアクセス関数
		int Getdegree();
		int GetMix();
		int* Getbit();								//ビットシーケンスデータを取得する関数
		int Getat_sink();
	 	std::vector<int>& GetnodeNumber();			//nodeNumberの先頭アドレスを返す関数

		void set_Packet(int Pid, int id, int *p, int MIX);	//id,次数,ミキシングタイム,ノード番号,データを設定する関数
		int Getnowid();	
		void set_at_sink();

		void disp();								//内容を出力するメンバ関数宣言
		void pushnodeNumber(int now_id);			//ノード番号を末尾に追加する関数

	public:
		//コンストラクタ，デストラクタ
		Packet();
		~Packet();

};


//プロトタイプ宣言
/***************計算のための関数*******************************/

double cal_d(double x1, double y1, double x2, double y2);	//2点間距離を導出する関数

/***********************隣接行列******************************/

void make_adjacency_matrix(Sensor *s, std::vector<std::vector<int> > &array2D);						/*隣接行列を作る関数*/
void set_hop(std::vector<std::vector<int> > &array2D, std::vector<int> &hop_check, Sensor *s);		//隣接行列からホップ数配列を設定する関数
void Depth_firsh_search(std::vector<std::vector<int> > &array2D, int i, std::vector<int> &visit);	//深さ優先探索
int check(std::vector<std::vector<int> > &array2D);													//ネットワークの状態の検査

/***********************パケット生成******************************/

void bit_generator(int *bit);															//ビット生成
int transition_id(int id, std::vector<std::vector<int> > &array2D, Sensor *s);						//遷移先idを決定する関数
void transmitter_to_receiver(int& hop_count, int *transmitted_bit, int *received_bit);	//送信機>通信路>受信機の部分をまとめた関数
int bed(int *tbit, int *rbit);															//bit error detection 誤り検出　出力:0or1

/***********************degreefunc******************************/
int degree_init(int n);																	//次数の設定を行う関数
int uni_dis(int d_max);																	//一様分布
int soliton(int d_max);																	//soliton分布
int robust_soliton(double delta, int d_max, int M);											//robast soliton分布
/***********************transmitter******************************/
void transmitter(int (*bit), double (*signal)[2]);
void QPSK_modulator(int (*bit), double (*signal)[2]);
void QPSK_modulator_de(int (*bit), double (*signal)[2]);

/***********************noise******************************/
void awgn(double (*transmitted_signal)[2], double (*received_signal)[2]);
void multipath_propagation(double (*transmit_signal)[2], double (*received_signal)[2]);
/***********************receiver******************************/
void receiver(double (*signal)[2], int (*bit));
void QPSK_demodulator_cd(double (*signal)[2], int (*bit));
void QPSK_demodulator_dd(double (*signal)[2], int (*bit));
/*************************ber********************************/
void ber(int loop, int (*tbit), int (*rbit));

/*************************decoder********************************/
void decode(Packet *packet, int& decpn);
int vector_finder(std::vector<int> vec, int number);
void decoded_packet(Packet *packet, std::vector<int> &decp);
void decoding(Packet *packet, std::vector<int> &decp);

/*************************graph********************************/
void make_graph(int loop, size_t decpn, int hop, int MIX);



