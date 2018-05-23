#include "definition.hpp"

int main(void){

	Sensor sensor[SensorN];						//SensorN個のSensorの生成
	std::vector<std::vector<int> > array2D;		//隣接行列の生成
	std::vector<int> hop_check;					//シンクノードまでのホップ数を管理するvector
	Packet packet[SensorN*Sensorb];				//Packetの生成

	array2D = std::vector<std::vector<int> >(SensorN, std::vector<int>(SensorN));	//隣接行列の初期化
	hop_check = std::vector<int>(SensorN);

	for (int i = 0; i < SensorN; i++){
		sensor[i].set_id_location(i);	//Sensor の id,x,yの設定
		// sensor[i].disp();
	}
	
	make_adjacency_matrix(sensor, array2D);	//隣接行列の作成

	set_hop(array2D, hop_check, sensor);	//Sensor の hopの設定

	for (int i = 0; i < SensorN; i++){
		// sensor[i].set_id_location(i);
		sensor[i].disp();				//Sensorの中身の表示
	}

	// //隣接行列の表示
	// for(int k=0; k<SensorN; k++){
	// 	for(int l=0; l<SensorN; l++){
	// 		std::cout << array2D[k][l] << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }
	int now_id = 0;
	std::cout << transition_id(now_id, array2D) << std::endl;
	packet[0].set_Packet(0,0);
	packet[0].disp();
	



	
	return 0;
}