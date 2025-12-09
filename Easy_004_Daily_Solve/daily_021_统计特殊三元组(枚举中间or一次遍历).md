--- Create Time: 2025-12-09 10:00:00
--- @Author: xcyy

# 3583. 统计特殊三元组

[3583. 统计特殊三元组](https://leetcode.cn/problems/count-special-triplets/description/)

--- 题目描述 ---

给你一个整数数组 nums。

特殊三元组 定义为满足以下条件的下标三元组 (i, j, k)：

* 0 <= i < j < k < n，其中 n = nums.length
* nums[i] == nums[j] * 2
* nums[k] == nums[j] * 2

返回数组中 特殊三元组 的总数。

由于答案可能非常大，请返回结果对 10^9 + 7 取余数后的值。

--- 测试用例 ---

```text
示例 1：
输入： nums = [6,3,6]
输出： 1
解释：
唯一的特殊三元组是 (i, j, k) = (0, 1, 2)，其中：
nums[0] = 6, nums[1] = 3, nums[2] = 6
nums[0] = nums[1] * 2 = 3 * 2 = 6
nums[2] = nums[1] * 2 = 3 * 2 = 6

示例 2：
输入： nums = [0,1,0,0]
输出： 1
解释：
唯一的特殊三元组是 (i, j, k) = (0, 2, 3)，其中：
nums[0] = 0, nums[2] = 0, nums[3] = 0
nums[0] = nums[2] * 2 = 0 * 2 = 0
nums[3] = nums[2] * 2 = 0 * 2 = 0

示例 3：
输入： nums = [8,4,2,8,4]
输出： 2
解释：
共有两个特殊三元组：
(i, j, k) = (0, 1, 3)
nums[0] = 8, nums[1] = 4, nums[3] = 8
nums[0] = nums[1] * 2 = 4 * 2 = 8
nums[3] = nums[1] * 2 = 4 * 2 = 8
(i, j, k) = (1, 2, 4)
nums[1] = 4, nums[2] = 2, nums[4] = 4
nums[1] = nums[2] * 2 = 2 * 2 = 4
nums[4] = nums[2] * 2 = 2 * 2 = 4
```

--- 说明提示 ---

```text
3 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^5
```

--- 题目解答 ---

## 方法一：枚举中间

三变量问题，一般枚举中间的变量最简单。为什么？对比一下：

- 枚举 i，后续计算中还需保证 j < k。
- 枚举 j，那么 i 和 k 自动被 j 隔开，互相独立，后续计算中无需关心 i 和 k 的位置关系。

枚举中间的 j，问题变成：

- 在 [0,j−1] 中，nums[j]⋅2 的出现次数。
- 在 [j+1,n−1] 中，nums[j]⋅2 的出现次数。
- 在这些出现次数中，左右两边各选一个。根据乘法原理，把这两个出现次数相乘，加到答案中。

用哈希表（或者数组）统计 j 左右每个数的出现次数。

- 右边的元素出现次数，可以先统计整个数组，然后再次遍历数组，撤销 [0,j] 中统计的元素出现次数，即为 [j+1,n−1] 中的元素出现次数。
- 左边的元素出现次数，可以一边遍历 nums，一边统计。

```python
from typing import List


class Solution:
    def specialTriplets( self, nums: List[ int ] ) -> int:

        # 枚举中间

        rig_counts = { }
        lef_counts = { }
        MOD = 1_000_000_007

        for v in nums:
            if v not in rig_counts:
                rig_counts[ v ] = 0
            rig_counts[ v ] += 1

        count = 0
        for v in nums:
            rig_counts[ v ] -= 1

            target = v * 2
            if target in lef_counts and target in rig_counts:
                count += lef_counts[ target ] * rig_counts[ target ] % MOD

            if v not in lef_counts:
                lef_counts[ v ] = 0
            lef_counts[ v ] += 1

        return count % MOD
```

* 时间复杂度：O(n), 其中 n 是 nums 的长度。
* 空间复杂度：O(n)

> 注1: 由于答案不超过 n⋅10^5 ⋅10^5 ≤10^15, 也可以只在返回时取模。

> 注2: 简化代码可以使用 defaultdict 来避免判断 key 是否存在。

## 方法二：枚举右，维护左（一次遍历）

枚举 k，设 x=nums[k]，问题变成：

- 有多少个二元组,满足i < j < k 且 nums[ i ] = x 且 nums[ j ] = x / 2. 用哈希表 cnt12 记录这样的二元组个数。

再次**分解**,上述问题也可以枚举右维护左，即枚举 j，问题变成：

- 在 j 左边有多少个数等于 nums[j]⋅2. 用哈希表 cnt1 记录。

```python
from typing import List
from collections import defaultdict


class Solution:
    def specialTriplets( self, nums: List[ int ] ) -> int:

        # 一次遍历 枚举右 维护左
        MOD = 1_000_000_007
        cnt1 = defaultdict( int )
        cnt12 = defaultdict( int )
        cnt123 = 0

        for x in nums:
            # 1. x作为nums[k]：需要找nums[j] = x/2
            if x % 2 == 0:
                cnt123 += cnt12[ x // 2 ]  # 把x当作nums[ k ]

            # 2. x作为nums[j]：需要找nums[i] = x/2
            cnt12[ x ] += cnt1[ x * 2 ]  # 把x当作nums[ j ]

            # 3. x作为nums[i]
            cnt1[ x ] += 1  # 把x当作nums[ i ]

        return cnt123 % MOD
```

- 时间复杂度：O(n), 其中 n 是 nums 的长度。
- 空间复杂度：O(n)

**代码的详细解释**

- 数据结构定义

```
cnt1 = defaultdict(int)      # 记录每个数字作为 nums[i] 出现的次数
cnt12 = defaultdict(int)    # 记录每个数字作为 (nums[i], nums[j]) 对的数量
cnt123 = 0                  # 统计完整三元组的数量
```

- 算法核心思路

对于每个数字 x，考虑它能扮演的三个角色：

**当 x 作为 nums[k] (第三个数) 时：**

```
if x % 2 == 0:
    cnt123 += cnt12[ x // 2 ]  # 把x当作nums[ k ]
    
逻辑：如果 x 是 nums[k]，那么 nums[j] 应该是 x/2。
cnt12[x // 2] 表示前面已经有多少个 (nums[i], nums[j]) 对满足 nums[j] = x//2。
```

**当 x 作为 nums[j] (第二个数) 时：**

```
cnt12[ x ] += cnt1[ x * 2 ]  # 把x当作nums[ j ]

逻辑：如果 x 是 nums[j]，那么 nums[i] 应该是 x*2。
cnt1[x * 2] 表示前面已经有多少个 nums[i] 等于 x*2。
```

**当 x 作为 nums[i] (第一个数) 时：**

```
cnt1[ x ] += 1  # 把x当作nums[ i ]

逻辑：简单的计数，记录 x 出现的次数。
```
