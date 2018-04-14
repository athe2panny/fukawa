#include "definition.hpp"

int main(void){

	Sensor sensor[Sensor_N];

	for (int i = 0; i < Sensor_N; i++){
		sensor[i].set_id_location(i);
		sensor[i].disp();
	}
	


	return 0;
}