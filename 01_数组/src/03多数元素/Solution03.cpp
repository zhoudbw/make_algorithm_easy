#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int majorityElement(vector<int> &nums) {
		int candidate = -1, count = 0; // 候选人, 票数 
		for (int i = 0, len = nums.size(); i < len; i++) {
			// count == 0重置候选人 
			if (count == 0) candidate = nums[i];
			// 根据新元素是否等于候选人，进行次数的加减 
			if (nums[i] == candidate) count++;
			if (nums[i] != candidate) count--; 
		} 
		return candidate;
	}
};

int main() {
	Solution solu;
	vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
	int manyNum = solu.majorityElement(nums);
	
	cout << manyNum << endl;
	
	return 0;
} 
