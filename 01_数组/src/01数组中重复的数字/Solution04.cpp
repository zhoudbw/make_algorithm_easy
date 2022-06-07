#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int findRepeatNumber(vector<int> &nums) {
		if (nums.empty()) return -1;
		
		// 就在vector这个原数组上进行变换
		// 从0号位置开始，
		// 将0号变成匹配的，才能再变1号；
		// 将1号变成匹配的，才能再变2号；... 
		for (int i = 0, len = nums.size(); i < len; i++) {
			/* 索引和元素值相等，即匹配，直接下一个 */ 
			if (nums[i] == i) continue;
			/* 索引和元素值不等，即nums[i] != i */ 
			else {
				// 索引和元素值不相等，需要考虑：可以变换 / 不可以变换
				// 可以变换就交换位置，不可以变换就是重复元素。
				/*不可以变换：交换的位置的值和索引值相等*/
				if (nums[nums[i]] == nums[i]) return nums[i];
				/*可以交换*/
				else { 
					// i位置元素和nums[i]位置元素交换 	
					int tmp = nums[nums[i]]; // 1
		            nums[nums[i]] = nums[i];
		            nums[i] = tmp;
					
//					for (int i = 0; i < nums.size(); i++) cout << nums[i] << ' ';
//					cout << endl;

					// 交换过后，只有当前位置的索引==元素值才能下一个
					// 所以需要先判断一下是否已经满足该条件
					// 所以这里应当抵消一下for循环里面的i++
					i--; 
				} 
			}
		} 
		return -1;
	}
};

int main() {
	Solution solu;
	vector<int> nums = {2, 3, 1, 0, 2, 5, 3};
	
	int res = solu.findRepeatNumber(nums);
	cout << res << endl;
	
	return 0;
} 
