#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int> nums) {
		vector<int> res; 
		for (int i = 0, len = nums.size(); i < len; i++) {
			// 取原数组中的数据
			int rawNum = abs(nums[i]);
			// 确定该元素应该用哪个索引表示
			int idx = rawNum - 1;
			// 将该索引位置的元素置为其相反数：
			// 1. 如果已经是负数了，说明这个位置的数已经出现过了
			// 不予处理（注意，之后遍历的过程中，这个位置元素可能被置换） 
			// 2. 如果不是负数，那么置换为其相反数 
			if (nums[idx] > 0) nums[idx] = -1 * nums[idx];
		}
		
		// 将置换后的数组中还是正数的索引位置对应的元素放入结果集中 
		for (int i = 0; i < nums.size(); i++)
			if (nums[i] > 0) res.push_back(i + 1);
			 
		return res;
	}
};

int main() {
	Solution solu;
	vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
	vector<int> res = solu.findDisappearedNumbers(nums);
	
	for (int x : res) cout << x << ',';
	cout << endl;
	
	return 0;
} 
