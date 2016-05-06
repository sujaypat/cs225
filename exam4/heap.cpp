#include <cmath>
using namespace std;
#include <vector>
using namespace std;




vector<int> buildMinHeap(vector<int> partialMinHeap){
    // Your code here
  for(size_t i = partialMinHeap.size() - 1; i > 0; i--){
    //cout << i << endl;
    if(partialMinHeap[i] == -1){
      int maxPriorityChild;
      if(partialMinHeap[2 * i] < partialMinHeap[2 * i + 1]){
	maxPriorityChild = 2 * i;
      }
      else maxPriorityChild = 2 * i + 1;
      partialMinHeap[i] = partialMinHeap[maxPriorityChild] - 1;
    }

  }
  return partialMinHeap;
}
