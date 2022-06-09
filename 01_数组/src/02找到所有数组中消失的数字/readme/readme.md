## 448. 找到所有数组中消失的数字

> 来源：https://leetcode.cn/problems/find-all-numbers-disappeared-in-an-array/

### 题目描述

```text
给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。
```

### 题目示例

```
输入：nums = [4,3,2,7,8,2,3,1]
输出：[5,6]
```

```
输入：nums = [1,1]
输出：[2]
```

### 题目限制

```
n == nums.length
1 <= n <= 105
1 <= nums[i] <= n
```

### 题目进阶

```
你能在不使用额外空间且时间复杂度为 O(n) 的情况下解决这个问题吗? 你可以假定返回的数组不算在额外空间内。
```

### 代码模板

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {

    }
};
```

---

> **参考解答一般仅是提供思路上的参考，解答不一定是最简单的，或者最好的，并且有时候可能还有些许小错误。希望在对照完以后，不管是题目有问题，还是参考解答过程有问题，希望能不吝指出！**
>
> **如果有更好的解题思路与过程，也欢迎提交分享。**

---

### 题目解答

**解法1：集合法**

> 统计数组中已经出现的元素，存储到set集合中；按照数据的特点，挨个比对，得到最终没有出现的元素。

```cpp
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
```

![image-20220609091840707](image-20220609091840707.png)



**解法2：利用原数组索引来记录已经出现过的数字(不使用额外空间)**

> 原数组:       [1, 2, 4, 5, 2] 
> 索引:            0  1  2  3  4
> 索引+1:        1  2  3  4  5
>
> **通过索引+1，就将数据范围对应上了，那么怎么说明该数字是否已经出现过呢？**
> **这里的做法非常的巧妙：已经出现过的元素，对到索引上，即：该元素-1==索引。将该索引位置上的数置为负数。最后统计正数对应的索引，然后索引+1就是消失的数字。**
>
> **示例如下：**
>
> 元素  索引`i`   第`i`位的值进行变化       说明
>   1        0          [-1, 2, 4, 5, 2]                1变为-1
>   2        1          [-1, -2, 4, 5, 2]               2变为-2
>   4        3          [-1, -2, 4, -5, 2]              5变为-5
>   5        4          [-1, -2, 4, -5, -2]             倒数的2变为-2
>   2        1          [-1, -2, -4, -5, -2]            已经是负数了，不做处理
>
> **从上面的示例，可以很清晰的看出：**
>
> - 索引 + 1 == 该索引表示的数字；
> - 某个元素x出现，那么将 x - 1位置上的数字置为对应的相反数；
> - 对于元素的变换，从0~n-1逐个比对变换，也就是n次；
> - 每次变换之后，都是元素组的数据变化，但是从示例可以看出，每次取的是原数组的数据，这就体现了置为相反数的好处了，只要取个绝对值，就还原成原数组的数据了。

```cpp
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
```

![image-20220609101335030](image-20220609101335030.png)

---

**end**