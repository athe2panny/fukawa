//ランダムに生成されたネットワークが1つのネットワークとして閉じているかチェックする
#include "definition.hpp"

//Depth-first search
void Depth_firsh_search(std::vector<std::vector<int> > &array2D, int i, std::vector<int> &visit){

	int j;
	visit[i] = 1;				//シンクノードを始点に探索

	for(j=0;j<SensorN;j++){
		if(array2D[i][j] == 1 && visit[j] == 0){
			Depth_firsh_search(array2D, j, visit);
		}
	}
}

//ネットワークが複数に分断されている時:1 そうでない時:0 
int check(std::vector<std::vector<int> > &array2D){

	std::vector<int> visit(SensorN,0);

	Depth_firsh_search(array2D, 0, visit);

	return vector_finder(visit, 0);

}