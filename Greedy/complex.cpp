#include <myheader.h>

/*
    一些较为复杂的题目，基本都是hard
    除了贪心之外，还涉及动态规划，大小顶堆……
    但本质还是通过局部最优找到全局最优，所以归到贪心方法中去。
*/


// PAT 有n个机器，m个任务。每个机器至多能完成一个任务。
// 给定每个机器的runTime1和level1，以及每个每个任务的runTime2和level2。（level<=100）
// 当且仅当runTime1[i]>=runTime2[j]和level1[i]>=level2[j]时，机器i才能完成任务j，
// 并获得500*runTime2[j]+2*level2[j]的利润。问最多能完成几个任务。当出现多种情况时，输出获得金钱最多的情况。
// 因为500>>2，并且奖励只与任务有关，所以首先匹配能完成该任务runTime的机器。从中优先挑选满足等级要求的等级最小的。
// 所以需要一个额外的数据结构来统计满足条件的机器的数量。因为level上限不大，建立数组就行。
// 第2种方法，建两个堆
class Solution {
public:
    struct eva {
        int runTime;
        int level;
        bool operator<(const eva& x) {
            if (runTime == x.runTime) {
                return level > x.level;
            } else {
                return runTime > x.runTime;
            }
        }
    };
    pair<int,ll> machineTask(vector<int> runTime1, vector<int> level1, vector<int> runTime2, vector<int> level2) {
        int n = runTime1.size(), m = runTime2.size();
        vector<eva> machine(n), task(m);
        for (int i = 0; i < n; i++) {
            machine[i].runTime = runTime1[i];
            machine[i].level = level1[i];
        }
        for (int i = 0; i < m; i++) {
            task[i].runTime = runTime2[i];
            task[i].level = level2[i];
        }
        sort(machine.begin(), machine.end());
        sort(task.begin(), task.end());
        vector<int> cnt(105, 0);  // 统计能完成level对应的机器数量
        int res = 0;  // 完成的任务数
        ll profit = 0;  // 最大回报
        for (int i = 0, j = 0; i < m; i++) {  // 完成任务i
            while (j < n && task[i].runTime <= machine[j].runTime) {  // 统计可以完成任务i的机器
                cnt[machine[j].level]++;  // 统计可以完成任务j的机器个数
                j++;
            }
            for (int k = task[i].level; k <= 100; k++) {  // 寻找能完成任务i的最小level的机器
                if (cnt[k]) {
                    res++;
                    profit += 500*task[i].runTime + 2*task[i].level;
                    cnt[k]--;
                    break;
                }
            }
        }
        return pair<int,ll>{res, profit};
    }
};