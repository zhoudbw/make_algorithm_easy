--- Create Time: 2025-12-15 10:00:00
--- @Author: xcyy

# 2110. 股票平滑下跌阶段的数目

[2110. 股票平滑下跌阶段的数目](https://leetcode.cn/problems/number-of-smooth-descent-periods-of-a-stock/description/)

--- 题目描述 ---

给你一个整数数组 prices ，表示一支股票的历史每日股价，其中 prices[i] 是这支股票第 i 天的价格。

一个 平滑下降的阶段 定义为：对于 连续一天或者多天 ，每日股价都比 前一日股价恰好少 1 ，这个阶段第一天的股价没有限制。

请你返回 平滑下降阶段 的数目。

--- 测试用例 ---

```
示例 1：
输入：prices = [3,2,1,4]
输出：7
解释：总共有 7 个平滑下降阶段：
[3], [2], [1], [4], [3,2], [2,1] 和 [3,2,1]
注意，仅一天按照定义也是平滑下降阶段。

示例 2：
输入：prices = [8,6,7,7]
输出：4
解释：总共有 4 个连续平滑下降阶段：[8], [6], [7] 和 [7]
由于 8 - 6 ≠ 1 ，所以 [8,6] 不是平滑下降阶段。

示例 3：
输入：prices = [1]
输出：1
解释：总共有 1 个平滑下降阶段：[1]
```

--- 说明提示 ---

```
1 <= prices.length <= 10^5
1 <= prices[i] <= 10^5
```

--- 题目解答 ---

## 动态规划

```python
from typing import List


class Solution:
    def getDescentPeriods( self, prices: List[ int ] ) -> int:

        # dp[ i ] 表示 第 i 天平滑下降阶段的数目
        n = len( prices )
        dp = [ 1 for _ in range( n ) ]

        for i in range( 1, n ):
            # 显然,若前后两天非平滑下降,那么阶段数目为1
            # 若前后两天形成平滑下降,那么当前天可以和dp[i-1]组合形成连续下降阶段
            if prices[ i - 1 ] - prices[ i ] == 1:
                dp[ i ] += dp[ i - 1 ]
        return sum( dp )
```

- 时间复杂度: O(n), 其中n是price的长度.
- 空间复杂度: O(n)

**空间优化**

题意：计算 prices 有多少个连续子数组是连续递减的。

示例 1 的 prices=[3,2,1,4]，按照子数组的右端点下标分组，有这些连续递减子数组：

右端点 i=0：[3]。
右端点 i=1：[3,2],[2]。
右端点 i=2：[3,2,1],[2,1],[1]。
右端点 i=3：[4]。

在遍历 prices 的同时，统计当前这段连续递减的长度 dec，那么右端点为 i 的连续递减子数组个数就是 dec，加到答案中。

- 如果 prices[i]=prices[i−1]−1，连续递减，dec 增加 1。
- 否则，连续递减中断，重新统计，dec=1。

```python
from typing import List


class Solution:
    def getDescentPeriods( self, prices: List[ int ] ) -> int:
        count = dec = 0

        for i, v in enumerate( prices ):
            if i > 0 and prices[ i - 1 ] - 1 == v:
                # 连续递增
                dec += 1
            else:
                # 重新计数
                dec = 1
            count += dec
        return count
```

- 时间复杂度: O(n)
- 空间复杂度: O(1)