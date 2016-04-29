/* Your code here! */
#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num){
	for (int i = 0; i < num; i++){
		lmao.push_back(-1);
	}
}

int DisjointSets::find(int elem){
	if(lmao[elem] < 0) return elem;
	else{
		lmao[elem] = find(lmao[elem]);
		return lmao[elem];
	}
}

void DisjointSets::setunion(int a, int b){
	int af = find(a);
	int bf = find(b);

	if(lmao[af] <= lmao[bf]){
		lmao[af] += lmao[bf];
		lmao[bf] = af;
	}
	else{
		lmao[bf] += lmao[af];
		lmao[af] = bf;
	}
}
