//LT符号化に伴うパケットのノード間移動について定義する
#include "definition.hpp"

/***********************************Packetクラスのメンバ関数　以下*********************************************/


//データ部分の配列の先頭アドレスを取ってくる関数
int* Packet::Getbit(){return bit;}

int Packet::Getdegree(){return degree;}

int Packet::GetMix(){return MixingTime;}

//ノード番号を取得する関数
std::vector<int>& Packet::GetnodeNumber(){return nodeNumber;}

//ノード番号を末尾に追加する関数
void Packet::pushnodeNumber(int now_id){nodeNumber.push_back(now_id);}

int Packet::Getnowid(){
	int& now_id = nodeNumber.back();
	return now_id;
}

void Packet::set_at_sink(){at_sink = 1;}

int Packet::Getat_sink(){return at_sink;}

//パケットの内容を表示する関数
void Packet::disp(){

	int n;		//カウント変数

	std::cout << "シンクノード到達" << at_sink << std::endl;
	std::cout << "パケットID:" << Pid << std::endl;
	std::cout << "次数:" << degree << std::endl;
	std::cout << "ミキシングタイム:" << MixingTime << std::endl;
	std::cout << "ノード番号:";
	for(n=0;n<nodeNumber.size();n++){
		std::cout << nodeNumber[n] << ' ';
	}
	std::cout << std::endl; 
	std::cout << "データ:" ;
	for(n=0;n<BITN;n++){
		std::cout << bit[n] << ' ';
	}
	std::cout << '\n' << std::endl; 
}

//パケット生成
void Packet::set_Packet(int n, int id, int *p, int MIX){

	Pid = n;									//パケットid
	degree = degree_init(deg);					//次数
	MixingTime = MIX;								//ミキシングタイム
	nodeNumber.push_back(id);					//ノード番号の追加		
	for(int n=0;n<BITN;n++){
		bit[n] = p[n];							//ビットシーケンスデータのコピー
	}
}	

//コンストラクタ
Packet::Packet(){
	bit = new int[BITN];
	at_sink = 0;
}

//ディストラクタ
Packet::~Packet(){
	delete [] bit;
	std::vector<int>().swap(nodeNumber);
}			
/***********************************Packetクラスのメンバ関数　以上*********************************************/


//遷移先の決定
//自分自身のノードには遷移しない
//今まで訪問したノードのデータを加算しない
//引数:現在いるノードID, 隣接行列 出力:遷移先ノードID となる関数
int transition_id(int now_id, std::vector<std::vector<int> > &array2D, Sensor *s){

	int count_adjacent_node = -1;	//隣接ノード数の合計
	std::vector<int> adjacent_node; //隣接ノード番号を保持するベクタ
	int j;

	std::random_device rnd;
	std::mt19937_64 mt(rnd());

	for(j=0;j<SensorN;j++){
		if(array2D[now_id][j] == 1){
			count_adjacent_node++;
			adjacent_node.push_back(j);
		}
	}
	std::uniform_int_distribution<> rand(0, count_adjacent_node);
	return adjacent_node[rand(mt)];
}


//引数:ビットシーケンス 出力:ビットシーケンス 
//ビットシーケンスから通信路を通した時のビットシーケンスを返す関数
//ついでにhop数もカウントする
double h[PATH][SYMBOLN][2];	/*チャネル*/
void transmitter_to_receiver(int& hop_count, int *transmitted_bit, int *received_bit){

	double transmitted_signal[SYMBOLN][2], received_signal[SYMBOLN][2];


	transmitter(transmitted_bit, transmitted_signal);
	multipath_propagation(transmitted_signal, received_signal);
	awgn(transmitted_signal, received_signal);
	receiver(received_signal, received_bit);
	hop_count++;	//ホップ数カウント
}

//誤り検出する関数
//引数：送信ビット，受信ビット 出力：誤りがある場合=>1 誤りがない場合=>0
int bed(int *tbit, int *rbit){

	int error = 0;		//エラーありの場合:1 なし:0

	for(int n=0;n<BITN;n++){
		if(tbit[n] != rbit[n]){
			error = 1;
			break;
		}
	}
	return error;
}



