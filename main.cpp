#include "definition.hpp"

double CNR;

int main(void){

	//シミュレーションループ関連の変数
	int loop, Eb_N0, MIX=4;

	//センサ，パケット，隣接行列関連の初期定義
	// Sensor *sensor;						//SensorN個のSensorの生成
	// Packet *packet;						//Packetの生成
	std::vector<std::vector<int> > array2D;		//隣接行列の生成
	std::vector<int> hop_check;					//シンクノードまでのホップ数を管理するvector

	int hop_count;							//合計ホップ数を管理するカウンタ
	int decpn;								//復号済みパケットの総数	decoded_packet_number

	//カウンタ変数
	int pid;								//パケット専用カウンタ変数
	int id;									//ノード専用カウンタ変数
	int mix;								//ミキシングタイム専用カウンタ変数
	int degree; 							//次数専用カウンタ変数

	//フラグ関連
	int error; 		//エラー
	
	//送受信関連の変数
	int now_id;				//現在いるノード番号を保持する変数
	int transition = 0;		//遷移先idを保持する変数
	int received_bit[BITN];		//受信bitを保持する配列

	int *pdata, *ndata;		//パケットデータとノードデータの先頭ポインタを保持する関数

/****************************************************************************************************/
// for(MIX=1; MIX<=10; MIX++){		//ミキシングタイムのグラフを作るとき
// 	Eb_N0=10;

for(Eb_N0=0; Eb_N0<=20; Eb_N0++) {
		CNR = (double)Eb_N0 + 3.0;

		for(loop=0; loop<LOOPN; loop++) {
/******************************シミュレーションループ内**************************************************/
	Sensor sensor[SensorN];						//SensorN個のSensorの生成
	Packet packet[SensorN*Sensorb];				//Packetの生成

	array2D = std::vector<std::vector<int> >(SensorN, std::vector<int>(SensorN));	//隣接行列の初期化
	hop_check = std::vector<int>(SensorN);

	hop_count = 0;							//合計ホップ数を管理するカウンタ
	decpn = 0;								//復号済みパケットの総数

	do{							
		for (int i = 0; i < SensorN; i++){
			sensor[i].set_Sensor(i);				//Sensor の id,x,yの設定
		}

		make_adjacency_matrix(sensor, array2D);		//隣接行列の作成
	}while(check(array2D));							//ネットワークが閉じているか検査

	set_hop(array2D, hop_check, sensor);			//Sensor の hopの設定

	// //隣接行列の表示
	// for(int k=0; k<SensorN; k++){
	// 	for(int l=0; l<SensorN; l++){
	// 		std::cout << array2D[k][l] << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;

	for(int id=0;id<SensorN;id++){		
		packet[id].set_Packet(id,id,sensor[id].Getbit(),MIX);		//パケットの生成
		for(int b=1;b<Sensorb;b++){
			packet[b*SensorN+id].copy_Packet(b*SensorN+id,id,packet[id].Getbit(),MIX);	//パケットのコピー
		}
	}
	// for(int n=0;n<SensorN;n++){
	// 	packet[n].disp();
	// }

	//パケットの送受信
	for(int pid = 0;pid<SensorN*Sensorb;pid++){										//全パケットのループ

		now_id = packet[pid].Getnowid();											//現在いるノードidの初期化
		// received_bit = new int[BITN];

			for(int degree = 1;degree<packet[pid].Getdegree();degree++){				//次数が1になるまで
				for(int mix = 0;mix<packet[pid].GetMix();mix++){						//ミキシングタイムが0になるまで

					now_id = transition_id(now_id, array2D);						//遷移先ノードの決定
					transmitter_to_receiver(hop_count, packet[pid].Getbit(), received_bit);	//ノード間送受信
					error = bed(packet[pid].Getbit(), received_bit);
					if(error == 1){continue;}
				}

				//パケットのノード番号追加,データの合成
				packet[pid].pushnodeNumber(now_id);					//ノード番号の追加
				// //ノード番号領域の中身表示
				// std::vector<int> test = packet[pid].GetnodeNumber();
				// std::size_t size = test.size();
				// for(int i=0;i<size;i++){
				// 	std::cout << test[i];
				// }
				// std::cout << std::endl;

				pdata = packet[pid].Getbit();
				ndata = sensor[now_id].Getbit();
				
				for(int n=0;n<BITN;n++){
					pdata[n] = (pdata[n] + ndata[n]) % 2;						//データの排他的論理和
				}
			}

			while(now_id != 0 && error == 0){											//シンクノードに到達するまで
			
				now_id = transition_id(now_id, array2D);						//遷移先ノードの決定
				transmitter_to_receiver(hop_count, packet[pid].Getbit(), received_bit);	//ノード間送受信
				error = bed(packet[pid].Getbit(), received_bit);
				if(error == 1){break;}
			}

			if(now_id == 0){
				packet[pid].set_at_sink();		//シンクノードに到達しているかのフラグを追加
			}
			// delete[] received_bit;
		}

	decode(packet, decpn);
	make_graph(loop, decpn, hop_count, MIX);
/******************************メモリ解放**************************************************/
std::vector<std::vector<int> >().swap(array2D);
std::vector<int>().swap(hop_check);
// delete[] sensor;
// delete[] packet;
/******************************シミュレーションループ内**************************************************/
	}
}
	
	return 0;
}