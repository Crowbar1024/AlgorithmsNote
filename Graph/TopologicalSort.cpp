#include <myheader.h>

// 拓扑排序定义
// 举个例子，一个工程编译，需要编译ABCDE...等文件
// 每个文件可能会依赖于其他文件，所以编译顺序需要先编译没有依赖的文件，然后……，同级的不要求顺序
// 作用在图，就是先遍历出所有入度为0的节点
// 然后删除，继续遍历图中剩余的入度为0的节点，依次往复。
// 一般要求有向且无环


// medium 207
// numCourses课程数量，prerequisites一组pair{ai,bi}先修bi才能修ai（反过来的）
// 问是否可以修完全部课程
// 显然是拓扑排序，从结果来看是判定有向图是否有环，那么可以转换为拓扑排序后剩余的点的数量是否为0
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> inDegree(numCourses, 0);  // 入度
    vector<vector<int>> adjL(numCourses);  // 邻接表adjacencyList
    for (int i = 0; i < prerequisites.size(); ++i) {
        adjL[prerequisites[i][1]].push_back(prerequisites[i][0]);
        inDegree[prerequisites[i][0]] += 1;
    }
    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        numCourses -= 1;
        for (int next : adjL[cur]) {
            if (--inDegree[next] == 0) {  // 这一步是拓扑排序的关键
                q.push(next);
            }
        }
    }
    return numCourses == 0;
}
// 衍生210，输出任意修习的顺序
// medium，只要创建一个数组保存每次的对头就行
// 注意没满足条件时的输出 if (numCourses != 0) return vector<int>{};