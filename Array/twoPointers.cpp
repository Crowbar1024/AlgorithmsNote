#include <myheader.h>

// 我认为双指针问题有很多适用场景
// A 若干个有序数组，这种情况有点像滑动窗口
// B 无序数组，进行排列


// 167 升序数组元素唯一，一定可以找到两个数的和是target，那么返回任意的两个
vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0, r = numbers.size() - 1;
    while (l < r && numbers[l] + numbers[r] != target) {
        if (numbers[l] + numbers[r] > target) r--;
        else l++;
    }
    return vector<int>{l + 1, r + 1};
}

// 977 非降序排列的数组，使其平方后再排序
// 当然可以先平方消耗On，再排序消耗Onlogn
// 但显然会有更好的解，只能是On，那么只能是双指针 A场景
// 虽然这不是纯粹的双指针，左边的不动而已
vector<int> sortedSquares(vector<int>& A) {
    int tail = A.size() - 1;
    while (tail > 0) {
        if (abs(A[tail]) > abs(A[0])) A[tail] = A[tail] * A[tail];
        else A[tail - 1] = exchange(A[tail], A[0] * A[0]);
        tail--;
    }
    A[0] = A[0] * A[0];
    return A;
}


// 11 medium 数组存水 C场景
// 很细的棍子表示数组数的高度，棍子间可以容纳的水
// 比如 1 5 3 2 4 可以存4*3=12
// 两个棍子l和r能装多少水，显然取决于最短的
int maxArea(vector<int>& height) {
	int l = 0, r = height.size()-1;
	int res = 0;
	while (l < r) {
		int minh = min(height[l], height[r]);
		res = max(res, minh*(r-l));
		// 如果下一个或者前一个比最短的还短，自然可以无视这些
		while (height[l] <= minh && l < r) ++l;
		while (height[r] <= minh && l < r) --r;
	}
	return res;
}

// 42 hard 和11很像，也是存水，但是棍子很粗，占满了格子
// 比如 1 5 3 2 4 可以存1+2=3
// [l,r]，lmax为[0,l]最高，rmax为[r,len]最高
// 只要lmax>rmax，那么在r位置上一定可以存下水
int trap(vector<int>& height) {
	int l = 0, r = height.size()-1;
	int lmax = 0, rmax = 0, res = 0;
	while (l < r) {
		lmax = max(lmax, height[l]);
		rmax = max(rmax, height[r]);
		// 只要左边最高大于右边最高，那么在r位置上一定可以存下水
		if (lmax > rmax) res += rmax-height[r--];
		else res += lmax-height[l++];
	}
	return res;
}


// 1089 easy 给你一个长度固定的整数数组 arr，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。
// 双指针，分别指向旧数组和新数组的末尾，用新指针去重写数组，注意只有新指针指向原来数组时才有写操作
// 新指针每次往前跳时，需要判断是否进入了原数组长度，这样就能重写了
void duplicateZeros(vector<int>& arr) {
    int l1 = arr.size();
    int l2 = l1 + count(arr.begin(), arr.end(), 0);
    for (int i = l1 - 1, j = l2 - 1; i >= 0, j >= 0; i--, j--) {
        if (j < l1) {
            arr[j] = arr[i];  // 任何数都要重写一次
        }
        if (arr[i] == 0) {
            j--;  // 新指针指0时，往向前多跳一下
            if (j < l1) {
                arr[j] = arr[i];  // 是0且进入范围后多重写一次
            }
        }
    }
}

// 905 easy 将 nums 中的的所有偶数元素移动到数组的前面，后跟所有奇数元素。
// 首尾不断交换元素就行