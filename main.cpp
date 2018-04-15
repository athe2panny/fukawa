#include "definition.hpp"

int main(void){

	Sensor sensor[SensorN];
	std::vector<std::vector<int> > array2D;

	array2D = std::vector<std::vector<int> >(SensorN, std::vector<int>(SensorN));

	for (int i = 0; i < SensorN; i++){
		sensor[i].set_id_location(i);
		sensor[i].disp();
	}
	
	make_adjacency_matrix(sensor, array2D);

	for(int k=0; k<SensorN; k++){
		for(int l=0; l<SensorN; l++){
			std::cout << array2D[k][l] << ' ';
		}
		std::cout << std::endl;
	}	

	return 0;
}