#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
	int majorityElement(vector<int> &nums) {
		map<int, int> res;
		// 遍历数组，构造<元素值, 元素个数>形式的存储  
		for (int i = 0, len = nums.size(); i < len; i++) {
			map<int, int>::iterator iter = res.find(nums[i]); // 记录key所在位置的迭代器 
			int count; // 记录元素出现的次数 
			
			if (iter != res.end()) {
				count = iter->second;
				count++;
				
				// 清除已经已经存在的pair，否则insert(pair)无法插入	
				res.erase(iter); 
			}
			else count = 1;

			// 判断count是否已经大于了len / 2 
			if (count > len / 2) return nums[i];
			// 不满足条件，放到集合中，继续迭代 
			else {
				// 特别注意：insert(pair<>)只有在插入的pair不存在时才会插入 
				// 所以需要先删除，然后再插入
				res.insert(make_pair(nums[i], count)); 
			}
		}
		
		// 无解返回-1 
		return -1; 
	}
}; 


int main() {
	/*===== 测试map*/
//	map<int, int> test;
//	test.insert(make_pair(2, 1));
//	test.insert(make_pair(3, 2));
//	// 遍历map 
//	for (map<int, int>::iterator i = test.begin(); i != test.end(); ++i) {
//		cout << i->first << ',';
//		cout << i->second << endl;
//	}

	// 测试用例
	Solution solu;
	vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
	int manyNum = solu.majorityElement(nums);
	
	cout << manyNum << endl;

	return 0;
} 

