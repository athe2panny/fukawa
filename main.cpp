#include "definition.hpp"

int main(void){

	Sensor sensor[SensorN];
	std::vector<std::vector<int> > array2D;
	std::vector<int> hop_check;

	array2D = std::vector<std::vector<int> >(SensorN, std::vector<int>(SensorN));	//隣接行列の初期化
	hop_check = std::vector<int>(SensorN);

	for (int i = 0; i < SensorN; i++){
		sensor[i].set_id_location(i);	//Sensor の id,x,yの設定
		// sensor[i].disp();
	}
	
	make_adjacency_matrix(sensor, array2D);	//隣接行列の作成

	//隣接行列の表示
	for(int k=0; k<SensorN; k++){
		for(int l=0; l<SensorN; l++){
			std::cout << array2D[k][l] << ' ';
		}
		std::cout << std::endl;
	}

	set_hop(array2D, hop_check, sensor);	//Sensor の hopの設定


	for (int i = 0; i < SensorN; i++){
		// sensor[i].set_id_location(i);
		sensor[i].disp();				//Sensorの中身の表示
	}


	return 0;
}