# 计算子数组的 x-sum II

[3321. 计算子数组的 x-sum II](https://leetcode.cn/problems/find-x-sum-of-all-k-long-subarrays-ii/description/)

给你一个由 n 个整数组成的数组 nums，以及两个整数 k 和 x。

数组的 x-sum 计算按照以下步骤进行：

- 统计数组中所有元素的出现次数。
- 仅保留出现次数最多的前 x 个元素的出现次数。如果两个元素的出现次数相同，则数值较大的元素被认为出现次数更多。
- 计算结果数组的和。

注意，如果数组中的不同元素少于 x 个，则其 x-sum 是数组的元素总和。

返回一个长度为 n - k + 1 的整数数组 answer，其中 answer[i] 是 子数组 nums[i..i + k - 1] 的 x-sum。

子数组 是数组内的一个连续 非空 的元素序列。

--- 测试用例 ---

```text
示例 1：
输入：nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
输出：[6,10,12]
解释：
对于子数组 [1, 1, 2, 2, 3, 4]，只保留元素 1 和 2。因此，answer[0] = 1 + 1 + 2 + 2。
对于子数组 [1, 2, 2, 3, 4, 2]，只保留元素 2 和 4。因此，answer[1] = 2 + 2 + 2 + 4。注意 4 被保留是因为其数值大于出现其他出现次数相同的元素（3 和 1）。
对于子数组 [2, 2, 3, 4, 2, 3]，只保留元素 2 和 3。因此，answer[2] = 2 + 2 + 2 + 3 + 3。

示例 2：
输入：nums = [3,8,7,8,7,5], k = 2, x = 2
输出：[11,15,15,15,12]
解释：
由于 k == x，answer[i] 等于子数组 nums[i..i + k - 1] 的总和。
```

--- 说明提示 ---

```text
nums.length == n
1 <= n <= 10^5
1 <= nums[i] <= 10^9
1 <= x <= k <= nums.length
```

--- 题目解答 ---

使用两个有序集合来维护窗口元素：一个存储频率最高的前x个元素，另一个存储剩余元素。

初始化时，统计前k个元素的频率，将所有元素按频率和元素值排序后，将前x个放入高频集合，其余放入剩余集合，并计算初始窗口的X和。

窗口滑动时：

1. 移除左边界元素：减少其频率，如果该元素仍在窗口中，根据新频率重新插入到合适的集合
2. 添加右边界元素：增加其频率，根据新频率插入到合适的集合
3. 平衡集合：确保高频集合始终保持x个元素。如果不足，从剩余集合取出频率最高的元素加入；如果超出，将高频集合中频率最低的元素移出
4. 计算当前X和：累加高频集合中所有元素的"值×频率"

[注]

- defaultdict的特点是，当访问一个不存在的键时，会返回一个默认值，而不是抛出 KeyError 异常。

```python
from collections import defaultdict
from typing import List

from sortedcontainers import SortedList


class Solution:
    def findXSum( self, nums: List[ int ], k: int, x: int ) -> List[ int ]:
        cnt = defaultdict( int )
        L = SortedList()  # 保存 tuple (出现次数，元素值)
        R = SortedList()
        sum_l = 0  # L 的元素和

        def add( val: int ) -> None:
            if cnt[ val ] == 0:
                return
            p = (cnt[ val ], val)
            if L and p > L[ 0 ]:  # p 比 L 中最小的还大
                nonlocal sum_l
                sum_l += p[ 0 ] * p[ 1 ]
                L.add( p )
            else:
                R.add( p )

        def remove( val: int ) -> None:
            if cnt[ val ] == 0:
                return
            p = (cnt[ val ], val)
            if p in L:
                nonlocal sum_l
                sum_l -= p[ 0 ] * p[ 1 ]
                L.remove( p )
            else:
                R.remove( p )

        def l2r() -> None:
            nonlocal sum_l
            p = L[ 0 ]
            sum_l -= p[ 0 ] * p[ 1 ]
            L.remove( p )
            R.add( p )

        def r2l() -> None:
            nonlocal sum_l
            p = R[ -1 ]
            sum_l += p[ 0 ] * p[ 1 ]
            R.remove( p )
            L.add( p )

        ans = [ 0 ] * (len( nums ) - k + 1)
        for r, in_ in enumerate( nums ):
            # 添加 in_
            remove( in_ )
            cnt[ in_ ] += 1
            add( in_ )

            l = r + 1 - k
            if l < 0:
                continue

            # 维护大小
            while R and len( L ) < x:
                r2l()
            while len( L ) > x:
                l2r()
            ans[ l ] = sum_l

            # 移除 out
            out = nums[ l ]
            remove( out )
            cnt[ out ] -= 1
            add( out )
        return ans
```

