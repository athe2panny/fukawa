#include "definition.hpp"

int main(void){

	Sensor sensor[SensorN];

	for (int i = 0; i < Sensor_N; i++){
		sensor[i].set_id_location(i);
		sensor[i].disp();
	}
	


	return 0;
}