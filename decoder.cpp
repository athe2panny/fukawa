//デコーダーの記述
#include "definition.hpp"

//ある値numberがvector内の要素に含まれているか否か判定する関数
int vector_finder(std::vector<int> vec, int number) {
  auto result = std::find(vec.begin(), vec.end(), number);
  if(result == vec.end()){
  	return 0;	//発見できなかった時
  }else{
  	return 1;	//発見できた時
  }
}

//ノード番号領域のサイズが1のパケット番号を専用の配列に格納する関数
void decoded_packet(Packet *packet, std::vector<int> &decp){

	std::vector<int> node;	//ノード番号領域
	int pid;

	for(pid = 0;pid<SensorN*Sensorb;pid++){
		node = packet[pid].GetnodeNumber();
		if(node.size() == 1 && vector_finder(decp, pid) == 0 && packet[pid].Getat_sink() == 1){		//ノード番号領域サイズが1で，かつ，size1配列の中にないノード番号
			decp.push_back(pid);
		}
	}
}

//ノード番号領域サイズ1のパケットと同じデータを持つパケットの探索と復号
void decoding(Packet *packet, std::vector<int> &decp){

	int n,pid,i;		//カウント変数

	for(n = 0;n<decp.size();n++){											//すべての復号済みのパケットnに対して
		for(pid = 0;pid<SensorN*Sensorb;pid++){								//全パケットに対して
			if(packet[pid].Getat_sink() == 1){
				std::vector<int>& node = packet[pid].GetnodeNumber();			//あるパケットのノード番号領域nodeにおいて
				
				for(i=0;i<node.size();i++){								
					if(decp[n] == node[i] && node.size() != 1){		//復号済みパケットnと同じ番号をノード番号領域nodeのi番目に見つける この時自分自身は除く
						
						int *data = packet[pid].Getbit();
						int *data1 = packet[decp[n]].Getbit();

						for(n=0;n<BITN;n++){
							data[n] = (data[n] + data1[n]) % 2;						//データの排他的論理和
						}

						node.erase(node.begin() + i);				//ノード番号領域から加算したパケットを除く
							// for(int n = 0;n<node.size();n++){
							// 	std::cout << node[n] << ' ';
							// }
							// std::cout <<std::endl;
					}
				}
			}
		}
	}
}

void decode(Packet *packet, int& decpn){

	std::vector<int> decp;
	size_t now,next;

	do{
		now = decp.size();	
		decoded_packet(packet, decp);

		// for(int i=0;i<decp.size();i++){
		// 	std::cout << decp[i] << ' ';
		// }
		// std::cout << std::endl;

		decoding(packet, decp);
		next = decp.size();
	}while(now != next);				//新しく復号されなければ終了

	decpn = (int) now;	
}

						


