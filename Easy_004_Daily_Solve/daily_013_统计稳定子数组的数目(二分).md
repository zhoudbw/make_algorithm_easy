--- Create Time: 2025-11-17 10:00:00
--- @Author: xcyy

# 3748. 统计稳定子数组的数目

[3748. 统计稳定子数组的数目](https://leetcode.cn/problems/count-stable-subarrays/description/)

--- 题目描述 ---

给你一个整数数组 nums。

如果 nums 的一个 子数组 中 没有逆序对 ，即不存在满足 i < j 且 nums[i] > nums[j] 的下标对，则该子数组被称为 稳定 子数组。

同时给你一个长度为 q 的 二维整数数组 queries，其中每个 queries[i] = [li, ri] 表示一个查询。
对于每个查询 [li, ri]，请你计算完全包含在 nums[li..ri] 内的 稳定子数组 的数量。

返回一个长度为 q 的整数数组 ans，其中 ans[i] 是第 i 个查询的答案。

注意：

- 子数组 是数组中一个连续且 非空 的元素序列。
- 单个元素的子数组被认为是稳定的。

--- 测试用例 ---

```text
示例 1：
输入：nums = [3,1,2], queries = [[0,1],[1,2],[0,2]]
输出：[2,3,4]
解释：
对于 queries[0] = [0, 1]，子数组为 [nums[0], nums[1]] = [3, 1]。
稳定子数组包括 [3] 和 [1]。稳定子数组的总数为 2。
对于 queries[1] = [1, 2]，子数组为 [nums[1], nums[2]] = [1, 2]。
稳定子数组包括 [1]、[2] 和 [1, 2]。稳定子数组的总数为 3。
对于 queries[2] = [0, 2]，子数组为 [nums[0], nums[1], nums[2]] = [3, 1, 2]。
稳定子数组包括 [3]、[1]、[2] 和 [1, 2]。稳定子数组的总数为 4。
因此，ans = [2, 3, 4]。

示例 2：
输入：nums = [2,2], queries = [[0,1],[0,0]]
输出：[3,1]
解释：
对于 queries[0] = [0, 1]，子数组为 [nums[0], nums[1]] = [2, 2]。
稳定子数组包括 [2]、[2] 和 [2, 2]。稳定子数组的总数为 3。
对于 queries[1] = [0, 0]，子数组为 [nums[0]] = [2]。
稳定子数组包括 [2]。稳定子数组的总数为 1。
因此，ans = [3, 1]。


```

--- 说明提示 ---

```text
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^5
1 <= queries.length <= 10^5
queries[i] = [li, ri]
0 <= li <= ri <= nums.length - 1
```

--- 题目解答 ---

没有逆序对: 子数组递增(允许元素相等)

**思路**

将nums划分成若干个递增段

- 如果l,r落在某个递增段内:
  [l,r]内任意子数组都是递增的,则有:
  设m=r-l+1 => m + ( m - 1 ) + ( m - 2 ) + ... + 1 = m*(m+1)/2

- 如果l,r落在不同递增段内:
  将[ l, r ]分成三部分: [ l, left1 ), [ left1, left2 ), [ left2, r ]
  其中,left1是下一个递增段的左端点,left2是r所在递增段的左端点,则有:
    - [l,left1): 设m=left1-l => m*(m+1)/2
    - [left1, left2): 预处理前缀和,O(1)算出
    - [left2, r ]: 设m=r-left2+1 => m*(m+1)/2

**本题中,边界处理,需要特别注意**

**补充**

- bisect_right
    - 用于在有序列表中查找插入位置
    - bisect.bisect_right(a, x, lo=0, hi=len(a) )
        - a: 有序列表（必须已排序）
        - x: 要查找的值
        - lo, hi: 查找范围 [lo, hi)
        - 返回值: 插入位置，使得 x 插入后仍保持有序，且位于所有等于 x 的元素的右侧
    - bisect_left: 找到第一个 ≥ x 的位置
    - bisect_right: 找到第一个 > x 的位置

```python
import bisect
from typing import List


class Solution:
    def countStableSubarrays( self, nums: List[ int ], queries: List[ List[ int ] ] ) -> List[ int ]:

        # 递增段的左端点
        left_list = [ ]
        curr_left = 0
        # 稳定数前缀和
        prefix_sum = [ 0 ]

        n = len( nums )
        for i, x in enumerate( nums ):
            if i == n - 1 or x > nums[ i + 1 ]:
                # 发现递增段[curr_left,i]
                # 当n-1时,递增段[curr_left,n-1]
                # 有多少个递增段,append多少次
                left_list.append( curr_left )

                # 计算前缀和
                m = i + 1 - curr_left
                prefix_sum.append( m * (m + 1) // 2 + prefix_sum[ -1 ] )
                curr_left = i + 1

        print( left_list, prefix_sum )
        ans = [ ]

        for l, r in queries:
            # 左端点严格大于l的第一个区间端点
            i = bisect.bisect_right( left_list, l )
            # 左端点严格大于r的第一个区间端点
            j = bisect.bisect_right( left_list, r )

            # 在同一个区间内
            if i == j:
                m = r - l + 1
                ans.append( m * (m + 1) // 2 )
                continue

            # 不在一个区间内 拆分三部分
            # [ l, left1 )
            m1 = left_list[ i ] - l
            # [ left2, r ]
            m2 = r - left_list[ j - 1 ] + 1
            ans.append( m1 * (m1 + 1) // 2 + (prefix_sum[ j - 1 ] - prefix_sum[ i ]) + m2 * (m2 + 1) // 2 )

        return ans
```