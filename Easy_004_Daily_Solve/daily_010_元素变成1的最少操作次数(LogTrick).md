--- Create Time: 2025-11-12 10:00:00
--- @Author: xcyy

# 一和零

[2654. 使数组所有元素变成 1 的最少操作次数](https://leetcode.cn/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/description/)

--- 题目描述 ---

给你一个下标从 0 开始的 正 整数数组 nums 。你可以对数组执行以下操作 任意 次：

选择一个满足 0 <= i < n - 1 的下标 i ，将 nums[i] 或者 nums[i+1] 两者之一替换成它们的最大公约数。
请你返回使数组 nums 中所有元素都等于 1 的 最少 操作次数。如果无法让数组全部变成 1 ，请你返回 -1 。

两个正整数的最大公约数指的是能整除这两个数的最大正整数。

--- 测试用例 ---

```text
示例 1：
输入：nums = [2,6,3,4]
输出：4
解释：我们可以执行以下操作：
- 选择下标 i = 2 ，将 nums[2] 替换为 gcd(3,4) = 1 ，得到 nums = [2,6,1,4] 。
- 选择下标 i = 1 ，将 nums[1] 替换为 gcd(6,1) = 1 ，得到 nums = [2,1,1,4] 。
- 选择下标 i = 0 ，将 nums[0] 替换为 gcd(2,1) = 1 ，得到 nums = [1,1,1,4] 。
- 选择下标 i = 2 ，将 nums[3] 替换为 gcd(1,4) = 1 ，得到 nums = [1,1,1,1] 。

示例 2：
输入：nums = [2,10,6,14]
输出：-1
解释：无法将所有元素都变成 1 。
```

--- 说明提示 ---

```text
2 <= nums.length <= 50
1 <= nums[i] <= 10^6
```

--- 题目解答 ---

## 计算GCD=1的最短连续子数组

- if nums中所有数的最大公约数 != 1: 无法让数组全部变成1, return -1
- if nums中包含1: 最小操作数 = nums中非1的个数 ( 从1向左向右不断替换就能把所有数变成1)
- if nums中不包含1:
    - 和1操作,只需要1次,即可将非1的数变为1
    - **所以如何用最少的操作数,造出1:**
        - 关键点: 由于只能操作相邻的数，所以这个1必然是一个连续子数组的GCD
        - 例如: a1, a2, a3, ..., ai, ...,其中 GCD( a2, ai ) = 1
        - 若GCD( a2, a3 ) = 1, 操作数 1
        - 若GCD( a2, a4 ) = 1, 说明GCD( a2, a3 ) = x, GCD( x, a4 ) = 1, 传递过去操作数 2
        - 所以对于[a2, ai]的连续子数组,**操作数=连续子数组长度-1**, 故应当使得 连续子数组长度尽可能小
        - 设其长度为 minSize，那么我们需要操作 minSize−1 次得到 1

- 语法糖:
    - 函数定义中的 *args（收集参数）:在函数定义时使用 *，它会将多余的位置参数收集到一个元组中。常见的用法是 *args
    - 函数调用中的 *（解包参数）:解包一个可迭代对象（如列表或元组），将其元素作为位置参数传递给函数。

```python
from math import gcd
from typing import List


class Solution:
    def minOperations( self, nums: List[ int ] ) -> int:

        if gcd( *nums ) != 1: return -1

        cnt = nums.count( 1 )
        n = len( nums )

        if cnt > 0: return n - cnt

        min_size = n

        # 找到GCD(x,y)=1
        # 确定min_size
        for i in range( n ):
            g = 0
            for j in range( i, n ):
                # 过程中GCD要传递
                # gcd( 0, nums[ j ] ) = nums[ j ]
                g = gcd( g, nums[ j ] )
                if g == 1: min_size = min( min_size, j - i + 1 )

        return min_size - 1 + (n - 1)
```

## LogTrick

给你一个数组 nums 和一个整数 k 。
你需要找到 nums 的一个 子数组 ，满足子数组中所有元素按位或运算 OR 的值与 k 的 绝对差 尽可能 小 。
换言之，你需要选择一个子数组 nums[l..r] 满足 |k - (nums[l] OR nums[l + 1] ... OR nums[r])| 最小。

请你返回 最小 的绝对差值。

子数组 是数组中连续的 非空 元素序列。

---

怎么计算子数组的或值？

从暴力算法开始。枚举所有 O(n^2) 个子数组，计算每个子数组的或值。

有如下O(n^2) 暴力算法：
- 外循环,从 i=0 开始,从左向右遍历
  - 内循环,从 j=i-1 开始,从右向左遍历,更新 nums[ j ] = nums[ j ] | nums[ i ]

- 当i=1时, 会把nums0到nums1的值存储在nums0中
- 当i=2时, 会把nums1到nums2的值存储到nums1中;nums0到nums2的值存储到nums0中
- 依次类推
- 对于每个i,会算出以i为右端点,以j为左端点的子数组的或值.此时nums[j]存储的就是nums[i~j]的或值

```python
from math import inf
from typing import List


class Solution:
    def minimumDifference( self, nums: List[ int ], k: int ) -> int:

        min_diff = inf

        for i, x in enumerate( nums ):
            min_diff = min( min_diff, abs( nums[ i ] - k ) )

            for j in range( i - 1, -1, -1 ):
                nums[ j ] |= x
                min_diff = min( min_diff, abs( nums[ j ] - k ) )
        return min_diff
```

### 从集合论到位运算，常见位运算技巧分类总结

[ 集合论到位运算 ]( ./daily_010_集合论到位运算.md )





