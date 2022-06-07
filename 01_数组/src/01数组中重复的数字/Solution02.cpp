#include <iostream>
#include <algorithm>

#include <vector>

using namespace std;

class Solution {
public:
	int findRepeatNumber(vector<int> &nums) {
		if (nums.empty()) return -1;
		
		// sort：排序nums的[*begin, *end)之间的数
		// 特别注意的是：begin()和end()返回的都是迭代器 
		sort(nums.begin(), nums.end());
		
		for (int i = 1, len = nums.size(); i < len; i++) {
			if (nums[i] == nums[i - 1]) return nums[i];
			continue;
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
