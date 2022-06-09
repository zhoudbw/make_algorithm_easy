#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int> &nums) {
		vector<int> res;
		set<int> appeared;
		
		// 对于set集合而言：有序无重复。 
		// 当添加重复元素时，直接覆盖。 
		for (int x : nums) appeared.insert(x);
		
		// 数组下标+1，即范围 1 ~ n，就是数据范围。 
		for (int i = 0, len = nums.size(); i < len; i++)
			// i + 1没有出现 
			if (!appeared.count(i + 1)) res.push_back(i + 1);
			
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
