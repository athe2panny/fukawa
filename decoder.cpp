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

	int pid;

	for(pid = 0;pid<SensorN*Sensorb;pid++){
		std::vector<int>&node = packet[pid].GetnodeNumber();
		if(node.size() == 1 && vector_finder(decp, node[0]) == 0 && packet[pid].Getat_sink() == 1){		//ノード番号領域サイズが1で，かつ，size1配列の中にないノード番号
			decp.push_back(node[0]);
		}
	}
}

//ノード番号領域サイズ1のパケットと同じデータを持つパケットの探索と復号
void decoding(Packet *packet, std::vector<int> &decp){

	int n,pid,i,m;		//カウント変数

	for(n = 0;n<decp.size();n++){											//すべての復号済みのパケットnに対して
		for(pid = 0;pid<SensorN*Sensorb;pid++){								//全パケットに対して
			if(packet[pid].Getat_sink() == 1){								//シンクノードに到達しているしている時
				std::vector<int>& node = packet[pid].GetnodeNumber();			//あるパケットのノード番号領域nodeにおいて

				for(i=0;i<node.size();i++){								
					if(decp[n]%SensorN == node[i] && node.size() != 1){		//復号済みパケットnと同じ番号をノード番号領域nodeのi番目に見つける この時自分自身は除く
						// std::cout << node.size() << "ノードサイズ" << std::endl;
						// std::cout << n << "<-復号済みパケットn" << std::endl;
						int *data = packet[pid].Getbit();
						int *data1 = packet[decp[n]].Getbit();

						for(m=0;m<BITN;m++){
							data[m] = data[m] xor data1[m];						//データの排他的論理和
						}
							
							std::cout << pid << "パケットid" <<  std::endl;
							for(m = 0;m<node.size();m++){
								std::cout << node[m] << ' ';
							}
							std::cout << std::endl;



						node.erase(node.begin() + i);				//ノード番号領域から加算したパケットを除く
						std::cout << i << std::endl;
							for(m = 0;m<node.size();m++){
								std::cout << node[m] << ' ';
							}
							std::cout << std::endl;
					}
				}
			}
		}
	}
}

void decode(Packet *packet, int& decpn){

	std::vector<int> decp;
	size_t now,next;
	int i;

	do{
		now = decp.size();	
		decoded_packet(packet, decp);

		for(int i=0;i<decp.size();i++){
			std::cout << decp[i] << ' ';
		}
		std::cout << std::endl;

		decoding(packet, decp);
		next = decp.size();
		std::cout << now << ' ' << next << "<- 復号されたノードの数" << std::endl;
	}while(now != next);				//新しく復号されなければ終了

	for(i=0;i<decp.size();i++){
		if(decp[i] >=SensorN && vector_finder(decp, decp[i]%SensorN) == 1){
			now--;
		}
	}
	decpn = now;
	std::cout << decpn << std::endl;
}

						


