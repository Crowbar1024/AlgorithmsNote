#include <myheader.h>

// 现在要让所有人在夜晚从A跑到B，花费时间cost，路上必须有蜡烛亮着，只有一根蜡烛。
// 规则是，每次让两个人过去，然后让对岸的一个人拿蜡烛回来。过去的时间取决于最慢的人，问最短让所有人到B点的时间
// 需要让每次回来的时间短，所以让最快的搭配最慢的两个，1 2 ... 10 12
// 但如果是 1 2 ... 100 102，可不可以让最慢的一起走，这样可以节省一半的时间。所以引入次快的
// 1 最快搭配最慢，最快回来，然后最快搭配次慢，最快回来：cost[0]*2+cost[n-1]+cost[n-2]
// 2 最快搭配次快，最快回来，然后最慢搭配次慢，次快回来：cost[1]*2+cost[0]+cost[n-1]
int carriage(vector<int> cost) {
	sort(cost.begin(), cost.end());
	int n = cost.size();
	int sum = 0;
	while(n) {
		if (n == 1) {  // 只剩一匹马，过去就行
			sum += cost[0];
			break;
		} else if (n == 2) {  // 两匹马
			sum += cost[1];
			break;
		} else if (n == 3) {  // 三匹马，无论什么顺序，花费时间都一样
			sum += cost[0]+cost[1]+cost[2];
			break;
		} else {
			if (2*cost[1] < cost[0]+cost[n-2])  // 方案2
				sum += cost[1]*2+cost[0]+cost[n-1];
			else sum += cost[0]*2+cost[n-1]+cost[n-2];  // 方案1
			n -= 2;
		}
	}
	return sum;
}



