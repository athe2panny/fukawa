//LT符号化に伴うパケットのノード間移動について定義する
#include "definition.hpp"

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
void Packet::set_Packet(int n, int id){

	Pid = n;									//パケットid
	degree = 3;									//次数
	MixingTime = 3;								//ミキシングタイム
	nodeNumber = std::vector<int>(SensorN);		//ノード番号
	nodeNumber[0] = id;
	bit = std::vector<int>(BITN);				//ビットシーケンスデータ
	bit_generator(bit);


}

//データシーケンス生成
void bit_generator(std::vector<int> &bit){
	
	std::random_device rnd;     						// 非決定的な乱数生成器
    std::mt19937_64 mt(rnd());							// 乱数生成
    std::uniform_int_distribution<> rand2(0, 1);		// [0, 1] 範囲の一様乱数
	int n;

	for(n=0; n<BITN; n++){
    	bit[n] = rand2(mt);	
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

//transmitter

//noise

//receiver


//パケット更新
//引数:パケット，現在のノードID 出力:なし

//センサノード

//シンクノードに到着
