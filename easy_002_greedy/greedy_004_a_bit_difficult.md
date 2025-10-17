# 贪心算法

## 大纲

- 题目: [用最少数量的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/)
- 题目: [无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals/description/)
- 题目: [划分字母区间](https://leetcode.cn/problems/partition-labels/description/)
- 题目: [合并区间](https://leetcode.cn/problems/merge-intervals/description/)

## [用最少数量的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/)

有一些球形气球贴在一堵用 XY 平面表示的墙面上。

墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。

在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。

可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。

--提示--
```
1 <= points.length <= 10^5
points[i].length == 2
-2^31 <= xstart < xend <= 2^31 - 1
```

--示例--
```
示例 1：
输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用2支箭来爆破:
-在x = 6处射出箭，击破气球[2,8]和[1,6]。
-在x = 11处发射箭，击破气球[10,16]和[7,12]。

示例 2：
输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要4支箭。

示例 3：
输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在x = 2处发射箭，击破气球[1,2]和[2,3]。
- 在x = 4处射出箭，击破气球[3,4]和[4,5]。
```

### 题解

* 直觉上来看,射出位置重叠气球越多,用的弓箭越少;

* 按照points[i][0]从小到大排序,然后统计不重叠区间的个数,即弓箭数;
* 通过不重叠区间的过程中:
  * 如何更新no_repeats[ i ]的左右边界,特别注意:
  * 如果points[i]和points[j]重叠,那么重叠区间[ points[j][0], min( points[i][1], points[j][1] ) ]
  * 要时刻记住,points已经按照points[i][0]排序的了,这是更新重叠区间左右边界的依据.


* 经验: **区间类问题,很大概率需要排序,这样方便处理杂乱的一堆区间.**

```python
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        
        def qsort( left, right ):
            if left >= right: return

            pivot = points[ left + ( right - left ) // 2 ]

            i = left - 1; j = right + 1
            while i < j:
                i += 1
                while points[ i ][ 0 ] < pivot[ 0 ]: i += 1
                j -= 1
                while points[ j ][ 0 ] > pivot[ 0 ]: j -= 1

                if i < j: points[ i ], points[ j ] = points[ j ], points[ i ]
            qsort( left, j )
            qsort( j + 1, right )

        n = len( points )
        qsort( 0, n - 1 )

        no_repeats = [ points[ 0 ] ]

        for i in range( 1, n ):
            ball = points[ i ]
            if no_repeats[ -1 ][ 0 ] <= ball[ 0 ] <= no_repeats[ -1 ][ 1 ]:
                no_repeats[ -1 ][ 0 ] = ball[ 0 ]
                no_repeats[ -1 ][ 1 ] = min( no_repeats[ -1 ][ 1 ], ball[ 1 ] )
            else:
                no_repeats.append( ball )
        
        return len( no_repeats )
```

--优化--
* 从上面代码其实可以看出来,每次都是在更新no_repeats[-1],所以可以用left,right,count来取代no_repeats.