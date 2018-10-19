/*再送を行うバージョン*/
#include "definition.hpp"


//遷移先の決定(シンクノードに直行する)
//hop数が−1のノードに遷移する8
//自分自身のノードには遷移しない
//引数:現在いるノードID, 隣接行列 出力:遷移先ノードID となる関数
int transition_id_tosink(int now_id, std::vector<std::vector<int> > &array2D, Sensor *s){

	int j;									/*カウンタ変数*/
	int now_hop = s[now_id].Gethop();		/*現在いるノードのシンクノードからのホップ数*/
	int count_adjacent_node = -1;			/*隣接ノード数の合計*/
	std::vector<int> adjacent_node; 		/*隣接ノード番号を保持するベクタ*/

	for(j=0;j<SensorN;j++){
		if(array2D[now_id][j] == 1){
			if(s[j].Gethop() == now_hop - 1){
				return j;					/*隣接ノード内にシンクノードからの距離が−1のノードが存在した場合*/
			}
		}
	}
	return 0;								/*存在しなかった場合*/
}