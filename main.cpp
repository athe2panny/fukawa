#include "definition.hpp"

int main(void){

	Sensor sensor[SensorN];						//SensorN個のSensorの生成
	std::vector<std::vector<int> > array2D;		//隣接行列の生成
	std::vector<int> hop_check;					//シンクノードまでのホップ数を管理するvector
	Packet packet[SensorN*Sensorb];				//Packetの生成

	array2D = std::vector<std::vector<int> >(SensorN, std::vector<int>(SensorN));	//隣接行列の初期化
	hop_check = std::vector<int>(SensorN);

	for (int i = 0; i < SensorN; i++){
		sensor[i].set_Sensor(i);	//Sensor の id,x,yの設定
		// sensor[i].disp();
	}
	
	make_adjacency_matrix(sensor, array2D);	//隣接行列の作成

	set_hop(array2D, hop_check, sensor);	//Sensor の hopの設定

	// for (int i = 0; i < SensorN; i++){
	// 	// sensor[i].set_id_location(i);
	// 	sensor[i].disp();				//Sensorの中身の表示
	// }

	// //隣接行列の表示
	// for(int k=0; k<SensorN; k++){
	// 	for(int l=0; l<SensorN; l++){
	// 		std::cout << array2D[k][l] << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }

	// int now_id = 0;
	// std::cout << transition_id(now_id, array2D) << std::endl;

	for(int id=0;id<SensorN;id++){		
		packet[id].set_Packet(id,id,sensor[id].Getbit());		//パケットの生成
		for(int b=1;b<Sensorb;b++){
			packet[b*SensorN+id].copy_Packet(b*SensorN+id,id,packet[id].Getbit());	//パケットのコピー
		}
	}
	
	// //生成したパケットの表示
	// for(int n=0;n<35 ;n++){
	// 	packet[n].disp();
	// }

	//フラグ関連
	int mix;		//ミキシングタイムを管理する変数
	int degree; 	//次数を管理する変数
	int end = 1;	//一つのパケットに対する送信の終わりを示すフラグ
	
	//
	int now_id;				//現在いるノード番号を保持する変数
	int transition = 0;		//遷移先idを保持する変数
	int received_bit[BITN];		//受信bitを保持する配列

	int *pdata, *ndata;		//パケットデータとノードデータの先頭ポインタを保持する関数

	//パケットの送受信
	for(int pid = 0;pid<SensorN*Sensorb;pid++){										//全パケットのループ

		now_id = packet[pid].Getnowid();											//現在いるノードidの初期化

			for(int degree = 0;degree<packet[pid].Getdegree();degree++){				//次数が0になるまで
				for(int mix = 0;mix<packet[pid].GetMix();mix++){						//ミキシングタイムが0になるまで

					now_id = transition_id(now_id, array2D);						//遷移先ノードの決定
					transmitter_to_receiver(packet[pid].Getbit(), received_bit);	//ノード間送受信
					end = bed(packet[pid].Getbit(), received_bit);					//誤り検出
					if(end == 1){
						break;	//誤りあり
					}

				}
				
				if(end == 1){
					break;	//誤りあり
				}

				//パケットのノード番号追加,データの合成
				packet[pid].pushnodeNumber(now_id);					//ノード番号の追加

				//ノード番号領域の中身表示
				std::vector<int> test = packet[pid].GetnodeNumber();
				std::size_t size = test.size();
				for(int i=0;i<size;i++){
					std::cout << test[i];
				}
				std::cout << std::endl;

				pdata = packet[pid].Getbit();
				ndata = sensor[now_id].Getbit();
				
				for(int n=0;n<BITN;n++){
					pdata[n] = (pdata[n] + ndata[n]) % 2;						//データの排他的論理和
				}
			}
			
			while(now_id != 0 && end == 0){											//シンクノードに到達するまで
			
				now_id = transition_id(now_id, array2D);						//遷移先ノードの決定
				transmitter_to_receiver(packet[pid].Getbit(), received_bit);	//ノード間送受信
				end = bed(packet[pid].Getbit(), received_bit);					//誤り検出

				if(end == 1){
					break;	//誤りあり
				}
			}
		}

	for(int n=0;n<SensorN ;n++){
		packet[n].disp();
	}
	
	return 0;
}