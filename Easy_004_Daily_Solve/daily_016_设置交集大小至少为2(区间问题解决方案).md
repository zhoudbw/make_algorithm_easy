--- Create Time: 2025-11-20 10:00:00
--- @Author: xcyy

# 757. 设置交集大小至少为2

[757. 设置交集大小至少为2](https://leetcode.cn/problems/set-intersection-size-at-least-two/description/)

--- 题目描述 ---

给你一个二维整数数组 intervals ，
其中 intervals[i] = [starti, endi] 表示从 starti 到 endi 的所有整数，包括 starti 和 endi 。

包含集合 是一个名为 nums 的数组，并满足 intervals 中的每个区间都 至少 有 两个 整数在 nums 中。

例如，如果 intervals = [[1,3], [3,7], [8,9]] ，那么 [1,2,4,7,8,9] 和 [2,3,4,8,9] 都符合 包含集合 的定义。
返回包含集合可能的最小大小。

--- 测试用例 ---

```text
示例 1：
输入：intervals = [[1,3],[3,7],[8,9]]
输出：5
解释：nums = [2, 3, 4, 8, 9].
可以证明不存在元素数量为 4 的包含集合。

示例 2：
输入：intervals = [[1,3],[1,4],[2,5],[3,5]]
输出：3
解释：nums = [2, 3, 4].
可以证明不存在元素数量为 2 的包含集合。 

示例 3：
输入：intervals = [[1,2],[2,3],[2,4],[4,5]]
输出：5
解释：nums = [1, 2, 3, 4, 5].
可以证明不存在元素数量为 4 的包含集合。 
```

--- 说明提示 ---

```text
1 <= intervals.length <= 3000
intervals[i].length == 2
0 <= starti < endi <= 10^8
```

--- 题目解答 ---

详情见 [daily_016_完成所有任务的最少时间(区间问题解决方案).md](daily_016_完成所有任务的最少时间(区间问题解决方案).md)

## 方法1: 贪心+暴力

题意转换: 对于intervals等价为tasks,每个interval可在区间[starti, endi]中选择2个点运行,问选择最少点的数量

- 排序右端点
- 排序后,对于interval的右边区间,要么与其后缀相交,要么与其不想交
- 从后往前选择,使得后缀相交的点尽可能多,从而使得选择的点最少

**细节见代码**
<pre><del>
from typing import List

class Solution:
    def intersectionSizeTwo( self, intervals: List[ List[ int ] ] ) -> int:
        # 排序右端点
        intervals.sort( key = lambda x: x[ 1 ] )

        # 记录已选择点
        running = [ False for _ in range( intervals[ -1 ][ 1 ] + 1 ) ]

        for start, end in intervals:
            duration = 2 - sum( running[ start: end + 1 ] )
            if duration <= 0: continue

            # 从后往前选择
            for i in range( end, start - 1, - 1 ):
                if running[ i ]: continue
                running[ i ] = True
                duration -= 1
                if duration == 0: break
        return sum( running )
</del></pre>

- 时间复杂度: O( nlogn + n * m ), 其中n为intervals的长度, m为intervals中最大的右端点
- 空间复杂度: O( m ), 其中m为intervals中最大的右端点

和明显上述代码不可行, 超时且空间复杂度较高.

## 方法2: 栈+二分

```python
from typing import List
import bisect


class Solution:
    def intersectionSizeTwo( self, intervals: List[ List[ int ] ] ) -> int:
        intervals.sort( key = lambda interval: interval[ 1 ] )
        # 栈中保存闭区间左右端点，栈底到栈顶的区间长度的和
        st = [ (-2, -2, 0) ]  # 哨兵，保证不和任何区间相交
        for start, end in intervals:
            _, r, s = st[ bisect.bisect_left( st, (start,) ) - 1 ]
            d = 2 - (st[ -1 ][ 2 ] - s)  # 去掉运行中的时间点
            if start <= r:  # start 在区间 st[i] 内
                d -= r - start + 1  # 去掉运行中的时间点
            if d <= 0:
                continue
            while end - st[ -1 ][ 1 ] <= d:  # 剩余的 d 填充区间后缀
                l, r, _ = st.pop()
                d += r - l + 1  # 合并区间
            st.append( (end - d + 1, end, st[ -1 ][ 2 ] + d) )
        return st[ -1 ][ 2 ]
```


