#include <iostream>
#include <algorithm>

#include <vector>
#include <set>

using namespace std; 

class Solution {
public:
	int findRepeatNumber(vector<int>& nums) {
		if (nums.empty()) return -1;
		
		set<int> s;
		for (int i = 0, len = nums.size(); i < len; i++) {
			if (s.count(nums[i])) return nums[i]; // 重复了，返回 
			s.insert(nums[i]); // 没重复，插入 
		} 
	
		// 没有重复元素 
		return -1;
	}
};

int main() {
	Solution solu;
	vector<int> nums = {2, 3, 1, 0, 2, 5, 3}; // c++11支持 
	
	int res = solu.findRepeatNumber(nums);
	cout << res << endl;
	
	return 0;
} 
