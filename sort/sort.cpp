#include <myheader.h>


void printArray(vector<int> arr) {
	for (int i = 0; i<arr.size(); i++) {
		printf("%d%c", arr[i], i<arr.size() - 1 ? ' ' : '\n');
	}
}

// 冒泡排序
// 空间复杂度O(1)
// 和插入顺序相反
void bubbleSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) return;
	for (int end = arr.size() - 1; end > 0; end--)
		for (int i = 0; i < end; i++)
			if (arr[i] > arr[i + 1])    // 可以稳定
				swap(arr[i], arr[i + 1]);
}

// 插入排序
// 空间复杂度O(1)
void insertionSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) return;
	for (int i = 1; i < arr.size(); i++) {
		// 下面这个过程就是插入
		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] > arr[j + 1]) {    // 可以稳定
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

// 选择排序
// 空间复杂度O(1)
void selectionSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) return;
	// 边界值判断，因为最后一次判断了数组最后两个数的最小值，最后一次不用判定
	for (int i = 0; i < arr.size() - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < arr.size(); j++) {
			// 破坏了稳定性，所以这个算法实现不了稳定性
			minIndex = (arr[minIndex]>arr[j]) ? j : minIndex;
		}
		swap(arr[i], arr[minIndex]); 
	}
}




// 归并排序 三个部分
// 由于需要一个临时数组存放，再merge，所以空间On
void merge(vector<int> &arr, int l, int r, int mid) {
	vector<int> tmp(r - l + 1, 0);
	int i = 0, p1 = l, p2 = mid + 1;
	while (p1 <= mid && p2 <= r) {
		tmp[i++] = (arr[p1] <= arr[p2]) ? arr[p1++] : arr[p2++];    // 可以稳定，如果<就变成了不稳定
	}
	while (p1 <= mid) {
		tmp[i++] = arr[p1++];
	}
	while (p2 <= r) {
		tmp[i++] = arr[p2++];
	}
	for (i = l; i <= r; i++) {
		arr[i] = tmp[i - l];
	}
}

void mergeSortProcess(vector<int> &arr, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = l + ((r - l) >> 1);
	mergeSortProcess(arr, l, mid);
	mergeSortProcess(arr, mid + 1, r);
	merge(arr, l, r, mid);
}

void mergeSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) {
		return;
	}
	mergeSortProcess(arr, 0, arr.size() - 1);
}


// 非递归的归并排序
void mergeSortWithoutRecursion(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) {
		return;
	}
	int len = arr.size();
	int bar = 1;
	while (bar < len) {
		for (int i = 0; i<len; i += bar * 2) {
			int l = i, r = i + 2 * bar - 1;
			int mid = l + ((r - l) >> 1);
			if ((len - i) <= bar) {    // 那块已经招不到与之匹配了，一直保留到最后一步
				break;
			}
			if ((len - i) < 2 * bar) {    // 很大一块与一小块
				r = len - 1;
				mid = i + bar - 1;
			}
			vector<int> tmp(r - l + 1, 0);
			int j = 0, p1 = l, p2 = mid + 1;
			while (p1 <= mid && p2 <= r) {
				tmp[j++] = (arr[p1] < arr[p2]) ? arr[p1++] : arr[p2++];
			}
			while (p1 <= mid) {
				tmp[j++] = arr[p1++];
			}
			while (p2 <= r) {
				tmp[j++] = arr[p2++];
			}
			for (j = l; j <= r; j++) {
				arr[j] = tmp[j - l];
			}
		}
		bar <<= 1;
	}
}

// 快速排序（改成非递归不会有好处，空间复杂度省不下去）（不能稳定，但论文级别可以做到01-stable）
// 经典快排：划分值的两边有序
// 随机快排：无序 （每次划分时间On，空间O1）(同理，也可以分奇偶)

// 时间复杂度分析
// 差的情况：Tn = Tn-1 + On; 好的情况：Tn = 2Tn/2 + On
// 快排常数项低，所以工业常用

// 空间复杂度分析（断点的深度就是空间复杂度，因为递归的断点变量可以复用，同一层树的一个断点释放了，另一个可以复用）
// 好的情况：每次递归展开的断点记录的是中间的位置（与上面一致）

vector<int> paritition(vector<int> &arr, int l, int r) {
	int less = l - 1;  // 小于划分数的数组右边界
	int more = r;  // 大于划分数的数组左边界，注意此时arr[r]就是划分数，所以这是[l,r-1]，即less和more都是取不到的
	// 所以便利的顺序只能从左往右，下标为l
	while(l < more) {
		if (arr[l] < arr[r]) swap(arr[l++], arr[++less]);    // 如果l之前有与划分数相同的数，那么这样做就会让这个数成为新的less
		else if (arr[l] > arr[r]) swap(arr[l], arr[--more]);  // l不动是因为不知道换过来的数与划分数的大小关系
		else l++;  // 让l跑到一堆划分数之后
	}
	swap(arr[more], arr[r]);    // 处理划分数
	// 这样数组从[less + 1, more]开始，左右都是小于等于和大于划分数的数，乱序
	return vector<int>{less+1, more};    // [less+1, more]是等于划分数arr[r]的部分
}

void quickSortProcess(vector<int> &arr, int l, int r) {
	if (l < r) {
		int randomIndex = l + rand()%(r-l+1);
		swap(arr[r], arr[randomIndex]);  // 让这个随机数成为划分值，并把它放到数组末尾
		vector<int> bound = paritition(arr, l, r);
		quickSortProcess(arr, l, bound[0] - 1);
		quickSortProcess(arr, bound[1] + 1, r);
	}
}

void QuickSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) return;
	quickSortProcess(arr, 0, arr.size() - 1);
}


// 堆排序（系统上的堆：递归堆栈的大小；数据结构上的堆是棵完全二叉树，小根堆和大根堆）
// 用处，建堆之后就可以获得最大值，不拿它排序依然很有用。但如果要弹出它，就可以用heapify
// 工程上不常用：不稳定，常数项比较大

// 往数组末尾添加一个元素（arr[0,i-1]是存放堆的数组，现在再增加一个，下标从0开始），让这个元素往上走
// Ologn 假设i是节点，那么(i-1)/2向下取整是父亲节点（堆是完全二叉树）
void heapAdd(vector<int> &arr, int i) {
	while (arr[i] > arr[(i-1)/2]) {
		swap(arr[i], arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

// Ologn 由于将堆顶即最大的值与末尾交换（末尾是小的），所以需要从堆顶重新往下不断交换
void heapify(vector<int> &arr, int i, int heapSize) {
	int left = i * 2 + 1;
	while (left < heapSize) {
		// 取到左右儿子中最大的节点，若大于父亲则与其交换
		int largest = (left + 1 < heapSize) && (arr[left + 1] > arr[left]) ? left + 1 : left;
		largest = arr[largest] > arr[i] ? largest : i;
		if (largest == i) {   // i节点是以i为堆顶的堆的最大值
			break;
		}
		swap(arr[i], arr[largest]);
		i = largest;
		left = i * 2 + 1;
	}
}

// 建立小顶堆（堆头最大）
void heapSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) {
		return;
	}
	int heapSize = arr.size();
	// 建堆，让每个节点是自己所有子节点的最大值 （On = Ologi的求和）
	for (int i = 0; i < heapSize; i++) {
		heapAdd(arr, i);
	}
	// 下面的过程是让最大值放到数组最后，再调整堆，往复，得到了一个递增的数组 （Onlogn）
	swap(arr[0], arr[--heapSize]);
	while (heapSize > 0) {
		heapify(arr, 0, heapSize);
		swap(arr[0], arr[--heapSize]);
	}
}


// 桶排序分为2种
// 计数排序
// 限正数
void bucketSort(vector<int> &arr) {
	if (arr.empty() || arr.size() == 1) {
		return;
	}
	int bucketSize = arr[0];
	for (int i = 1; i < arr.size(); i++) {
		bucketSize = max(bucketSize, arr[i]);
	}
	vector<int> bucket(bucketSize + 1, 0);
	for (int i = 0; i < arr.size(); i++) {
		bucket[arr[i]]++;
	}
	int i = 0;
	for (int j = 0; j <= bucketSize; j++) {
		while (bucket[j]--) {
			arr[i++] = j;
		}
	}
}

int maxGap(vector<int> arr) {
	if (arr.empty() || arr.size() == 1) {
		return 0;
	}
	int maxNum = INT_MIN;
	int minNum = INT_MAX;
	int len = arr.size();
	for (int i = 0; i < len; i++) {
		maxNum = max(maxNum, arr[i]);
		minNum = min(minNum, arr[i]);
	}
	if (maxNum == minNum) {
		return 0;
	}
	vector<int> haveNum(len + 1, 0), maxBucket(len + 1, 0), minBucket(len + 1, 0);
	int bid = 0;
	for (int i = 0; i < len; i++) {
		bid = (int)((arr[i] - minNum) * len / (maxNum - minNum));
		maxBucket[bid] = haveNum[bid] ? max(maxBucket[bid], arr[i]) : arr[i];
		minBucket[bid] = haveNum[bid] ? min(minBucket[bid], arr[i]) : arr[i];
		haveNum[bid] = 1;
	}
	int lastMax = maxBucket[0];
	int res = 0;
	for (int i = 1; i <= len; i++) {
		if (haveNum[i]) {
			res = max(res, minBucket[i] - lastMax);
			lastMax = maxBucket[i];
		}
	}
	return res;
}

// 同理可以生成随机字符串
// rand() % (b-a) + a: [a,b)
vector<int> generateRandomArray(int size, int bound) {
	int trueSize = rand() % (size + 1);    // [0, size]
	vector<int> res(trueSize);
	for (int i = 0; i<trueSize; i++) {
		// res[i] = rand() % (bound * 2 + 1) - bound;    // [-bound, bound]
		res[i] = rand() % (bound + 1);    // [0, bound]
	}
	return res;
}

bool judgeEqual(vector<int> a, vector<int> b) {
	if ((a.empty() && !b.empty()) || (!a.empty() && b.empty())) {
		return false;
	}
	else if (a.empty() && b.empty()) {
		return true;
	}
	else if (a.size() != b.size()) {
		return false;
	}
	else {
		for (int i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
	}
	return true;
}



int main() {
	srand((unsigned)time(NULL));
	int testTimes = 10, size = 20, bound = 20;
	bool isEqual = false;
	for (int i = 0; i<testTimes; i++) {
		vector<int> arr1 = generateRandomArray(size, bound);
		// int len = arr1.size();
		// vector<int> arr2 = arr1, arr3 = arr1;    // 没涉及指针和引用时浅拷贝和深拷贝没区别
		// bucketSort(arr1);
		int gap = maxGap(arr1);
		printArray(arr1);
		sort(arr1.begin(), arr1.end());
		printArray(arr1);
		printf("%d\n", gap);
		// sort(arr2.begin(), arr2.end());
		// isEqual = judgeEqual(arr1, arr2);
		// if (!isEqual) {
		// 	printArray(arr3);
		// 	printArray(arr1);
		// 	printArray(arr2);
		// 	break;
		// })
	}
	printf("%s\n", isEqual ? "testRight" : "Wrong");
	system("PAUSE");
	return 0;
}