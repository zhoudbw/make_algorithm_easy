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

[无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals/description/)

给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。

注意 只在一点上接触的区间是 不重叠的。例如 [1, 2] 和 [2, 3] 是不重叠的。

--提示--
```
1 <= intervals.length <= 10^5
intervals[i].length == 2
-5 * 10^4 <= starti < endi <= 5 * 10^4
```

--示例--
```
示例 1:
输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
输出: 1
解释: 移除 [1,3] 后，剩下的区间没有重叠。

示例 2:
输入: intervals = [ [1,2], [1,2], [1,2] ]
输出: 2
解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

示例 3:
输入: intervals = [ [1,2], [2,3] ]
输出: 0
解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

补充示例4:
输入: intervals = [[0,2],[1,3],[2,4],[3,5],[4,6]]
输出: 2
```

### 题解

* 问题转换能力
  * 题目类比: 射箭问题; 无重叠区间问题;

```python
class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        # 按照左边界排序,计算重叠区间数
        # 注:如果A,B两区间重叠,更新右边界一定是min(Aright,Bright)
        # 比如区间 [1,3],[1,2],[2,3]最小移除数量为1,区间更新就特别重要

        n = len( intervals )

        if n == 1: return 0

        def qsort( low, high ):
            if low >= high: return

            pivot = intervals[ low + ( high - low ) // 2 ][ 0 ]

            i = low - 1; j = high + 1
            while i < j:
                i += 1
                while intervals[ i ][ 0 ] < pivot: i += 1
                j -= 1
                while intervals[ j ][ 0 ] > pivot: j -= 1
                
                if i < j: intervals[ i ], intervals[ j ] = intervals[ j ], intervals[ i ]
            
            qsort( low, j )
            qsort( j + 1, high )
        
        qsort( 0, n - 1 )

        left = intervals[ 0 ][ 0 ]; right = intervals[ 0 ][ 1 ]; overlapCount = 0

        for i in range( 1, n ):
            if left <= intervals[ i ][ 0 ] < right:
                right = min( right, intervals[ i ][ 1 ] )
                overlapCount += 1
            else:
                left = intervals[ i ][ 0 ]
                right = intervals[ i ][ 1 ]

        return overlapCount
        
```

[划分字母区间](https://leetcode.cn/problems/partition-labels/description/)

给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。

例如，字符串 "ababcc" 能够被分为 ["abab", "cc"]，但类似 ["aba", "bcc"] 或 ["ab", "ab", "cc"] 的划分是非法的。

注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。

返回一个表示每个字符串片段的长度的列表。

--提示--
```
1 <= s.length <= 500
s 仅由小写英文字母组成
```

--示例--
```
示例 1：
输入：s = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。 

示例 2：
输入：s = "eccbbbbdec"
输出：[10]
```

### 题解

* 本题的解决和前面区间的题目相同,只是最后统计的是不重叠区间的长度
* **如果单独拎出来这道题,是否能够想到用区间的方法来解决?**

* 举个例子来看,比如字符串"ababcbacadefegdehijhklij",我们可以将其划分为"ababcbaca","defegde","hijhklij"
```
将每个字母的首尾位置作为一个区间
"a"的区间为[0,8], "b"的区间为[1,5], "c"的区间为[2,7], 
"d"的区间为[4,9], "e"的区间为[5,10], "f"的区间为[6,6], 
"g"的区间为[7,7], "h"的区间为[8,14], "i"的区间为[9,11], 
"j"的区间为[10,12], "k"的区间为[11,11], "l"的区间为[12,15]
--
如何能够确定划分出来的每个字符串呢?
由于a的区间为[0,8],b的区间为[1,5],c的区间为[2,7],所以保证统一字母出现在同一个区间内,最终结果为"ababcbaca".
```

* 在处理的过程中,利用keys记录了统计的字母,从而避免了对interval排序的操作

```python
class Solution:
  def partitionLabels(self, s: str) -> List[int]:

    # 统计首尾相同字母的最长区间长度
    # 统计不重叠区间个数,即答案

    interval = {}
    keys = []

    for i in range( len( s ) ):
      if s[ i ] not in interval:
        interval[ s[ i ] ] = [ -1, -1 ]
        interval[ s[ i ] ][ 0 ] = i
        keys.append( s[ i ] )
      else:
        interval[ s[ i ] ][ 1 ] = i

    not_overlap = []
    for key in keys:
      val = interval[ key ]

      if not not_overlap:
        not_overlap.append( val )
        continue

      start, end = val[ 0 ], val[ 1 ]

      if not_overlap[ -1 ][ 0 ] < start < not_overlap[ -1 ][ 1 ]:
        not_overlap[ -1 ][ 1 ] = max( not_overlap[ -1 ][ 1 ], end )
      else:
        not_overlap.append( val )

    ans = []
    for start, end in not_overlap: ans.append( end == -1 and 1 or end - start + 1 )
    return ans
```


[合并区间](https://leetcode.cn/problems/merge-intervals/description/)

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。

请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

--提示--
```
1 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4
```

--示例--
```
示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

示例 3：
输入：intervals = [[4,7],[1,4]]
输出：[[1,7]]
解释：区间 [1,4] 和 [4,7] 可被视为重叠区间。
```

### 题解

* 区间问题:条件反射就想想排序
* 区间比较的条件,根据题目判断

```python
class Solution:
  def merge(self, intervals: List[List[int]]) -> List[List[int]]:

    n = len( intervals )

    def qsort( left, right ):
      if left >= right: return

      pivot = intervals[ left + ( right - left ) // 2 ][ 0 ]

      i = left - 1; j = right + 1
      while i < j:
        i += 1
        while intervals[ i ][ 0 ] < pivot: i += 1
        j -= 1
        while intervals[ j ][ 0 ] > pivot: j -= 1
        if i < j:
          intervals[ i ], intervals[ j ] = intervals[ j ], intervals[ i ]
      qsort( left, j )
      qsort( j + 1, right )

    qsort( 0, n - 1 )

    ans = []

    for start, end in intervals:
      if not ans: ans.append( [ start, end ] ); continue

      if ans[ -1 ][ 0 ] <= start <= ans[ -1 ][ 1 ]:
        ans[ -1 ][ 1 ] = max( ans[ -1 ][ 1 ], end )
      else: ans.append( [ start, end ] )

    return ans
```