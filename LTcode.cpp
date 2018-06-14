//LT符号化に伴うパケットのノード間移動について定義する
#include "definition.hpp"

//データ部分の配列の先頭アドレスを取ってくる関数
int* Packet::Getbit(){
	return bit;
}

int Packet::Getdegree(){
	return degree;
}

int Packet::GetMix(){
	return MixingTime;
}

int Packet::Getnowid(){
	int& now_id = nodeNumber.back();
	return now_id;
}

//パケットの内容を表示する関数
void Packet::disp(){
	std::cout << "パケットID:" << Pid << std::endl;
	std::cout << "次数:" << degree << std::endl;
	std::cout << "ミキシングタイム:" << MixingTime << std::endl;
	std::cout << "ノード番号:" ;
	for(int n=0;n<SensorN;n++){
		std::cout << nodeNumber[n] << ' ';
	}
	std::cout << std::endl; 
	std::cout << "データ:" ;
	for(int n=0;n<BITN;n++){
		std::cout << bit[n] << ' ';
	}
	std::cout << '\n' << std::endl; 
}

//パケット生成
void Packet::set_Packet(int n, int id, int *p){

	Pid = n;									//パケットid
	degree = 3;									//次数
	MixingTime = 3;								//ミキシングタイム
	nodeNumber = std::vector<int>(1);			//ノード番号
	nodeNumber[0] = id;				
	for(int n=0;n<BITN;n++){
		bit[n] = p[n];							//ビットシーケンスデータのコピー
	}
}



std::vector<int> Packet::GetnodeNumber(){
	return nodeNumber;
}

//パケットコピー
void Packet::copy_Packet(int n, int id,int *p){

	Pid = n;									//パケットid
	degree = 3;									//次数
	MixingTime = 3;								//ミキシングタイム
	nodeNumber = std::vector<int>(SensorN);		//ノード番号
	nodeNumber[0] = id;				
	
	for(int n=0;n<BITN;n++){
		bit[n] = p[n];							//ビットシーケンスデータのコピー
	}
}					


//次数決定


//ミキシングタイム決定


//ノード遷移

//遷移先の決定
//引数:現在いるノードID, 隣接行列 出力:遷移先ノードID となる関数
int transition_id(int now_id, std::vector<std::vector<int> > &array2D){

	int count_adjacent_node = 0;

	for(int j=0;j<SensorN;j++){			//隣接ノードの数をカウント
		if(array2D[now_id][j] == 1){
			count_adjacent_node++;
		}
	}


	std::random_device rnd;     										// 非決定的な乱数生成器
    std::mt19937_64 mt(rnd());											// 乱数生成
    std::uniform_int_distribution<> rand3(0, count_adjacent_node);		// [0, 隣接ノード数] 範囲の一様乱数

    int next_adjacent_node = rand3(mt);
    int next_id;

    for(int j=0;j<SensorN;j++){
    	if(array2D[now_id][j] == 1){
    		next_adjacent_node--;
    		if(next_adjacent_node == 0){
    			next_id = j;
    			break;
    		}
    	}
    }

    return next_id;

}

//引数:ビットシーケンス 出力:ビットシーケンス 
//ビットシーケンスから通信路を通した時のビットシーケンスを返す関数
void transmitter_to_receiver(int *transmitted_bit, int *received_bit){

	double transmitted_signal[SYMBOLN][2], received_signal[SYMBOLN][2];

	transmitter(transmitted_bit, transmitted_signal);
	awgn(transmitted_signal, received_signal);
	receiver(received_signal, received_bit);
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


//パケット更新
//引数:パケット，現在のノードID 出力:なし

//センサノード

//シンクノードに到着

