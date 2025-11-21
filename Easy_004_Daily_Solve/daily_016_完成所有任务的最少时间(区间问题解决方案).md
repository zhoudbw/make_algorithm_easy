--- Create Time: 2025-11-20 10:00:00
--- @Author: xcyy

# 2589. 完成所有任务的最少时间

[2589. 完成所有任务的最少时间](https://leetcode.cn/problems/minimum-time-to-complete-all-tasks/description/)

--- 题目描述 ---

你有一台电脑，它可以 同时 运行无数个任务。
给你一个二维整数数组 tasks ，其中 tasks[i] = [starti, endi, durationi]
表示第 i 个任务需要在 闭区间 时间段 [starti, endi] 内运行 durationi 个整数时间点（但不需要连续）。

当电脑需要运行任务时，你可以打开电脑，如果空闲时，你可以将电脑关闭。

请你返回完成所有任务的情况下，电脑最少需要运行多少秒。

--- 测试用例 ---

```text
示例 1：
输入：tasks = [[2,3,1],[4,5,1],[1,5,2]]
输出：2
解释：
- 第一个任务在闭区间 [2, 2] 运行。
- 第二个任务在闭区间 [5, 5] 运行。
- 第三个任务在闭区间 [2, 2] 和 [5, 5] 运行。
电脑总共运行 2 个整数时间点。

示例 2：
输入：tasks = [[1,3,2],[2,5,3],[5,6,2]]
输出：4
解释：
- 第一个任务在闭区间 [2, 3] 运行
- 第二个任务在闭区间 [2, 3] 和 [5, 5] 运行。
- 第三个任务在闭区间 [5, 6] 运行。
电脑总共运行 4 个整数时间点。
```

--- 说明提示 ---

```text
1 <= tasks.length <= 2000
tasks[i].length == 3
1 <= starti, endi <= 2000
1 <= durationi <= endi - starti + 1 
```

--- 题目解答 ---

**题目解析**

- 对于一个task,其能运行的时间段位[starti, endi], 可以不连续选择duration个点运行, 每个点的运行时间为1

## 方法1:贪心+暴力

- 按照endi排序 ( 区间问题常用套路, 区间端点排序 )
- 排序后,对于task[i],其右边的任务区间要么和其后缀相交,要么不想交
- 若要使得电脑运行时间最少,应使得运行时间尽可能的相交,所以选择运行时间时,从后endi->starti选择 ( 贪心 )

**详情见代码注释**

```python
from typing import List


class Solution:
    def findMinimumTime( self, tasks: List[ List[ int ] ] ) -> int:

        # 按照endi排序
        tasks.sort( key = lambda x: x[ 1 ] )

        # 记录在运行的数轴点
        # 数轴点做多 task[ -1 ][ 1 ] + 1 个
        running = [ False ] * (tasks[ -1 ][ 1 ] + 1)

        for start, end, duration in tasks:
            # 判断当前区间是否被运行覆盖
            duration -= sum( running[ start: end + 1 ] )
            if duration <= 0: continue

            # 从后往前选择duration个点运行
            # 这样可以保证运行时间尽可能的相交
            # 从而使得电脑运行时间最少
            for i in range( end, start - 1, -1 ):
                if running[ i ]: continue
                running[ i ] = True
                duration -= 1
                if duration == 0: break

        return sum( running )
```

- 时间复杂度: `O( nlogn + nT )`, 其中n=len(tasks), T=max(endi)
    - `nlogn` 为排序的时间复杂度
    - `nT` 为遍历tasks的时间复杂度, 每次遍历需要O(T)的时间判断是否运行过, 并O(T)的时间更新running数组
- 空间复杂度: `O( T )`, 其中T为任务的最大运行时间即endi的最大值

## 线段树优化

详情见 [daily_016_线段树.md](daily_016_线段树.md)

## 方法3: 栈+二分

根据方法1,有如下发现:

对于每个tasks[i]都是从后往前添加时间点, 将这些点当做一个闭区间时, 每个tasks[i]都会有一个闭区间[ endi-duration+1, endi ]

求tasks运行的最短时间,实际就是将这些区间合并.

维护一个有序结构,这里用栈维护, 栈内元素为 闭区间的左右端点，以及从栈底到栈顶的区间长度之和（类似前缀和）.

由于一旦发现区间相交就立即合并，所以栈中保存的都是不相交的区间。

合并前，先尝试在栈中二分查找包含左端点 start 的区间。
由于栈中还保存了区间长度之和，所以可以快速得到 [start,end] 范围内的运行中的时间点个数。

如果还需要新增时间点，那么就从右到左合并，具体细节见代码。

```python
from typing import List
import bisect


class Solution:
    def findMinimumTime( self, tasks: List[ List[ int ] ] ) -> int:
        tasks.sort( key = lambda t: t[ 1 ] )
        # 栈中保存闭区间左右端点，栈底到栈顶的区间长度的和
        st = [ (-2, -2, 0) ]  # 哨兵，保证不和任何区间相交
        for start, end, d in tasks:
            _, r, s = st[ bisect.bisect_left( st, (start,) ) - 1 ]
            d -= st[ -1 ][ 2 ] - s  # 去掉运行中的时间点
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

**示例**：tasks = [[1,3,2], [2,5,3], [5,6,2]]

- 步骤1：排序后 [[1,3,2], [2,5,3], [5,6,2]]
- 步骤2：处理任务1 [1,3,2]
    - st = [(-2,-2,0)]
    - 需要2个单位时间
    - 添加区间 [2,3]（靠近结束时间）
    - st = [(-2,-2,0), (2,3,2)]
- 步骤3：处理任务2 [2,5,3]
    - 检查已有覆盖：区间 [2,3] 覆盖了时间点2,3
    - 剩余需要：3 - 2 = 1个单位时间
    - 添加区间 [5,5]
    - st = [(-2,-2,0), (2,3,2), (5,5,3)]
- 步骤4：处理任务3 [5,6,2]
    - 检查已有覆盖：时间点5已被覆盖
    - 剩余需要：2 - 1 = 1个单位时间
    - 添加区间 [6,6]
    - st = [(-2,-2,0), (2,3,2), (5,5,3), (6,6,4)]

结果：总时间 = 4


