#include <myheader.h>



// 21/4/25字节笔试1 easy 但没做出来
// 一组数，他们的平均数满足整数的条件。问最少多少次把一个数通过减自己给相邻的数，使得所有数一样
// 比如 9 11 9 11，2次；1 10 10 19，3次
// 不用关注问题中的减，直接从头遍历，大了放到下一个，小了从下一个拿，遍历到n-1

// PAT 0~n-1这n个数乱序排列。 Sort with Swap(0, i)
// 通过交换0与任意一个数的位置，问至少交换多少次才能使之有序；
// 1.如果0不在自己的位置，那么本应该出现在当前0的位置的数和0交换；
// 2.如果0在自己的位置，找到第一个不在自己位置上的数与0交换
// 根据这个策略，需要新建一个数组，使a[s[i]]=i，s为给定的数组，即用额外空间获取i的位置





// 1033 To Fill or Not to Fill
// 加油站加油问题
// 已知汽车的油箱最大容量cmax，当前位置到终点距离d，每升汽油行驶距离davg，加油站数量n
// 并且有路上每个加油站的油价和与起点的距离
// 问如何设计加油策略，使得油钱最少，能到终点
// 如果无法到终点，输出最远可以到达的距离
// 怎么贪心:
// 1.选当前到离到当前最大距离的这一段,加油直到能恰好开到比现在油价还少的地方.
// 2.这段如果没有那个加油站,就加满,开到这段中最便宜的加油站，开到剩也没关系，反正比之前贵
// TODO 871
struct station {
	double price, dis;
	bool operator<(const station& b) {
		return dis < b.dis;
	}
};
void gasStation(double cmax, double d, double davg, int n, vector<double> sPrice, vector<double> sDist) {
	vector<station> sta(n+1);
	sta[0] = {0.0, d};  //很关键，如果当前的油直接可以开到终点时，可以作为end节点。
	for (int i = 1; i <= n; i++) {
		sta[i].price = sPrice[i-1];
		sta[i].dis = sDist[i-1];
	}
	sort(sta.begin(), sta.end());
	// leftdis是剩余的油能开的距离.
	double currentDist = 0.0, maxdis = 0.0, currentPrice = 0.0, totalPrice = 0.0, leftDist = 0.0;
	if (sta[0].dis != 0) {
		printf("The maximum travel distance = 0.00");
		return;
	} else {
		currentPrice = sta[0].price;  // 用第一个站点的油价
	}
	while (currentDist < d) {
		maxdis = currentDist + cmax*davg;  // 从当前位置，把邮箱用完的最远距离
		// minPrice为[currentDist,maxdis]中价格比当前高最少的加油站价格，minPriceDis是对应的位置
		double minPriceDis = 0, minPrice = INF;
		int flag = 0;  // 等于1说明选择了策略1
		for (int i = 1; i <= n && sta[i].dis <= maxdis; i++) {  // 选择一个加油站
			if (sta[i].dis <= currentDist) continue;  // 加油站得是当前节点以后的
			// 注意下面包括了终点的情况,因为终点的price为0
			if (sta[i].price < currentPrice) {  // 加油到能恰好开到比现在油价低的加油站的量
				totalPrice += (sta[i].dis-currentDist-leftDist)*currentPrice/davg;
				currentPrice = sta[i].price;
				currentDist = sta[i].dis;
				leftDist = 0.0;  // 现在到了那个恰好比当前油价低的加油站，用完油了
				flag = 1;
				break;
			}
			if (sta[i].price < minPrice) {  // 找到策略2的那个加油站
				minPrice = sta[i].price;
				minPriceDis = sta[i].dis;
			}
		}
		if (flag == 0 && minPrice != INF) {  // 进行策略2
			totalPrice += currentPrice*(cmax-leftDist/davg);  // 在currentDist处加满
			leftDist = cmax*davg - (minPriceDis - currentDist);  // 到策略2的那个加油站时剩下的油能开的距离
			currentDist = minPriceDis;  // 然后开到策略2的那个加油站
			currentPrice = minPrice;
		}
		if (flag == 0 && minPrice == INF) {  // 说明[currentDist,maxdis]中最近的一个加油站都到不了
			currentDist += cmax*davg;  // 只能直接加满，能跑多远是多远
			printf("The maximum travel distance = %.2f", currentDist);
			return;
		}
	}
	printf("%.2f", totalPrice);
}

// 21/5/9 美团笔试3
// 小明弹吉他，当前状态x，每天可以选择两件事，休息，没有奖励，状态x加b；弹吉他，奖励当前的状态x，然后状态x减a
// 如果弹吉他时当前的状态x<a，依然可以奖励x，然后状态归0
// 问n天后可以获得最高的奖励
// 贪心，最好的策略就是先休息够，再不断练习，由于x小于a时，会变为0，可以构建等差数列求和：
// 比如当前状态8，休息+6，弹琴消耗-7，问5天后的最大奖励，随便给个解（不一定为最优）：
// +0 14 / +0 20 / +20 13 / +13 6 / +6 0
// f(i) =[(x+b*i)+((x+b*i)-a*(n-i-1))]* (n-i)/2
// (x+b*i)就是开始弹琴第一天的奖励，(x+b*i)-a*(n-i-1)是最后一天的奖励，然后利用二次函数的极值点
// i = (2*b*n+2*a*n-2*x-a)/(4*b+2*a)
// 由于int向下取整，所以取max(f(i),f(i+1))


// 平面填充 POJ 1017
// 1*1、2*2、3*3、4*4、5*5、6*6，填充6*6的框，a是不同小正方形的数量，求最少需要多少个框装满小正方形
// 6*6：1个产品放在1个箱子里
// 5*5：1个产品要占用1个箱子，用1*1的箱子可以填充（11个填满1箱）
// 4*4：1个产品要占用1个箱子，剩余空间用2*2和1*1的箱子填充（先填充2*2（最多5个填满），再填充1*1）
// 3*3：4个产品可以填满1个箱子，假如有不满1个箱子的，分情况用1*1和2*2的产品填满（突破口）
// 2*2：9个产品可以填满1个箱子，假如有不满1个箱子的，用1*1的产品填充
// 1*1：36个产品可填满一个箱子

int roundUp(int m, int n) {
	return (m - (m/n)*n) > 0 ? m/n+1 : m/n;
}
int filling(vector<int> a) {
	int res = a[5] + a[4] + a[3] + roundUp(a[2], 4);  // 先装大的，前三个只要一个就可以新开一个框
	// 接下来由于3*3对4向上取整，所以余数需要用2*2和1*1填充
	int b[4] = {0, 5, 3, 1};  // 3*3的箱子装满后框后剩下的还可以放入的2*2数量
	int left2 = 5*a[3] + b[a[2]%4];		//装4*4,3*3后空出来的可以装2*2的数量
	if (a[1] > left2)  // 4*4和3*3剩下的可以用2*2填满
		res += roundUp(a[1]-left2, 9);  // 剩余的2*2用来填框
	int left1 = res*36 - a[5]*36 - a[4]*25 - a[3]*16 -a[2]*9 - a[1]*4;
	if (a[0] > left1)
		res += roundUp(a[0]-left1, 36);  // 作为补充的1*1用完后填空框
	return res;
}

