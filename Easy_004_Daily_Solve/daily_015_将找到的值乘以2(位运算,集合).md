--- Create Time: 2025-11-19 10:00:00
--- @Author: xcyy

# 2154. 将找到的值乘以 2

[2154. 将找到的值乘以 2](https://leetcode.cn/problems/keep-multiplying-found-values-by-two/description/)

--- 题目描述 ---

给你一个整数数组 nums ，另给你一个整数 original ，这是需要在 nums 中搜索的第一个数字。

接下来，你需要按下述步骤操作：

- 如果在 nums 中找到 original ，将 original 乘以 2 ，得到新 original（即，令 original = 2 * original）。
- 否则，停止这一过程。
- 只要能在数组中找到新 original ，就对新 original 继续 重复 这一过程。

返回 original 的 最终 值。

--- 测试用例 ---

```text
示例 1：
输入：nums = [5,3,6,1,12], original = 3
输出：24
解释： 
- 3 能在 nums 中找到。3 * 2 = 6 。
- 6 能在 nums 中找到。6 * 2 = 12 。
- 12 能在 nums 中找到。12 * 2 = 24 。
- 24 不能在 nums 中找到。因此，返回 24 。

示例 2：
输入：nums = [2,7,9], original = 4
输出：4
解释：
- 4 不能在 nums 中找到。因此，返回 4 。
```

--- 说明提示 ---

```text
1 <= nums.length <= 1000
1 <= nums[i], original <= 1000
```

--- 题目解答 ---

**题意**

返回不在 nums 中的最小的 original * 2^k, 其中 k 是非负整数。

## 方法1:排序+遍历

```python
from typing import List


class Solution:
    def findFinalValue( self, nums: List[ int ], original: int ) -> int:

        def qsort( left, right ):
            if left >= right: return

            pivot = nums[ left + (right - left) // 2 ]

            i, j = left - 1, right + 1

            while i < j:
                i += 1
                while nums[ i ] < pivot: i += 1
                j -= 1
                while nums[ j ] > pivot: j -= 1
                if i < j: nums[ i ], nums[ j ] = nums[ j ], nums[ i ]

            qsort( left, j )
            qsort( j + 1, right )

        qsort( 0, len( nums ) - 1 )

        for v in nums:
            if v == original: original *= 2

        return original
```

## 方法2:集合+枚举

枚举 k=0,1,2,… 判断 original * 2^k 是否在 nums 中。
用哈希集合记录 nums 的每个元素可以加快判断。

```python
from typing import List


class Solution:
    def findFinalValue( self, nums: List[ int ], original: int ) -> int:
        st = set( nums )
        while original in st:
            original *= 2
        return original
```

- 时间复杂度：O(n+log( U/original ))，其中 n 是 nums 的长度，U=max(nums)。循环次数为 O(log( U/original ))。
- 空间复杂度：O(n)。

## 方法3:只记录所有可能值

哈希集合记录的元素可以更少，只需要记录符合 original*2^k 的元素。

设 x=nums[i]，如果 x=original*2^k，那么：

- x 是 original 的倍数。
- original / x 是 2 的幂.

```python
from typing import List


class Solution:
    def findFinalValue( self, nums: List[ int ], original: int ) -> int:
        st = set()
        for x in nums:
            k, r = divmod( x, original )
            if r == 0 and k & (k - 1) == 0:
                st.add( x )

        while original in st:
            original *= 2
        return original
```

- 时间复杂度：O(n+log( U/original ))，其中 n 是 nums 的长度，U=max(nums)。循环次数为 O(log( U/original ))。
- 空间复杂度：O(log( U/original ))。

## 方法4:位运算

改成记录 original*2^k中的 k。 由于 k 很小，可以把 k 保存到一个二进制数 mask 中.
答案中的 k 就是 mask 的最低 0 的位置。

这可以通过位运算 O(1) 地计算出来：把 mask 取反，找最低位的 1，其对应的二进制数 lowbit 即为答案中的 2^k。
再乘以 original，得到最终答案。

> 注：找最低 0 对应的 2^k，也可以直接计算 (mask + 1) & ~mask。

```python
from typing import List


class Solution:
    def findFinalValue( self, nums: List[ int ], original: int ) -> int:
        mask = 0
        for x in nums:
            k, r = divmod( x, original )
            if r == 0 and k & (k - 1) == 0:
                mask |= k

        # 找最低的 0，等价于取反后，找最低的 1（lowbit）
        mask = ~mask
        return original * (mask & -mask)
```

- 时间复杂度：O(n)，其中 n 是 nums 的长度。
- 空间复杂度：O(1)。

