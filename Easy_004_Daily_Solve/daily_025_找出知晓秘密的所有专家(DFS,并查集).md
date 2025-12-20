--- Create Time: 2025-12-19 10:00:00
--- @Author: xcyy

# 2092. 找出知晓秘密的所有专家

[2092. 找出知晓秘密的所有专家](https://leetcode.cn/problems/find-all-people-with-secret/description/)

--- 题目描述 ---

给你一个整数 n ，表示有 n 个专家从 0 到 n - 1 编号。
另外给你一个下标从 0 开始的二维整数数组 meetings ，其中 meetings[i] = [xi, yi, timei] 表示专家 xi 和专家 yi 在时间 timei
要开一场会。
一个专家可以同时参加 多场会议 。最后，给你一个整数 firstPerson 。

专家 0 有一个 秘密 ，最初，他在时间 0 将这个秘密分享给了专家 firstPerson 。
接着，这个秘密会在每次有知晓这个秘密的专家参加会议时进行传播。
更正式的表达是，每次会议，如果专家 xi 在时间 timei 时知晓这个秘密，那么他将会与专家 yi 分享这个秘密，反之亦然。

秘密共享是 瞬时发生 的。也就是说，在同一时间，一个专家不光可以接收到秘密，还能在其他会议上与其他专家分享。

在所有会议都结束之后，返回所有知晓这个秘密的专家列表。你可以按 任何顺序 返回答案。

--- 测试用例 ---

```
示例 1：
输入：n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
输出：[0,1,2,3,5]
解释：
时间 0 ，专家 0 将秘密与专家 1 共享。
时间 5 ，专家 1 将秘密与专家 2 共享。
时间 8 ，专家 2 将秘密与专家 3 共享。
时间 10 ，专家 1 将秘密与专家 5 共享。
因此，在所有会议结束后，专家 0、1、2、3 和 5 都将知晓这个秘密。

示例 2：
输入：n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
输出：[0,1,3]
解释：
时间 0 ，专家 0 将秘密与专家 3 共享。
时间 2 ，专家 1 与专家 2 都不知晓这个秘密。
时间 3 ，专家 3 将秘密与专家 0 和专家 1 共享。
因此，在所有会议结束后，专家 0、1 和 3 都将知晓这个秘密。

示例 3：
输入：n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
输出：[0,1,2,3,4]
解释：
时间 0 ，专家 0 将秘密与专家 1 共享。
时间 1 ，专家 1 将秘密与专家 2 共享，专家 2 将秘密与专家 3 共享。
注意，专家 2 可以在收到秘密的同一时间分享此秘密。
时间 2 ，专家 3 将秘密与专家 4 共享。
因此，在所有会议结束后，专家 0、1、2、3 和 4 都将知晓这个秘密。
```

--- 说明提示 ---

```
2 <= n <= 10^5
1 <= meetings.length <= 10^5
meetings[i].length == 3
0 <= xi, yi <= n - 1
xi != yi
1 <= timei <= 10^5
1 <= firstPerson <= n - 1
```

--- 题目解答 ---

~~**错误思路**~~

```python
from typing import List


class Solution:
    def findAllPeople( self, n: int, meetings: List[ List[ int ] ], firstPerson: int ) -> List[ int ]:

        # meetings 按照 time 排序
        # 排序由 若 meetings[ i ] 内无人知晓秘密, 则这两人都不知道秘密

        # 排序后, 检测是否 meetings[ i ] 内存在知晓秘密的人即可
        def qsort( l, r ):
            if l >= r: return

            pivot = meetings[ (l + r) // 2 ][ 2 ]

            i, j = l - 1, r + 1

            while i < j:
                i += 1
                while meetings[ i ][ 2 ] < pivot: i += 1
                j -= 1
                while meetings[ j ][ 2 ] > pivot: j -= 1
                if i < j: meetings[ i ], meetings[ j ] = meetings[ j ], meetings[ i ]

            qsort( l, j )
            qsort( j + 1, r )

        qsort( 0, len( meetings ) - 1 )
        print()

        known = set()
        known.add( 0 )
        known.add( firstPerson )

        for x, y, d in meetings:
            if x in known or y in known:
                known.add( x )
                known.add( y )

        return list( known )
```

未满足:在同一时间,一个专家不光可以接收到秘密,还能在其他会议上与其他专家分享。

## 分析

假设一开始 0 和 1 知道秘密。对比如下两种情况：

- 时间 1，1 和 2 开会。时间 2，2 和 3 开会。秘密会传播给 2 和 3，最终 0,1,2,3 都知道秘密。
- 时间 1，2 和 3 开会。时间 2，1 和 2 开会。第一场会议，参加会议的人都不知道秘密，所以秘密不会传播。秘密只会在第二场会议传播给
  2，最终 0,1,2 都知道秘密。

所以要按照开会的先后顺序传播秘密，模拟这个过程。

注意题目的这段话：

- 秘密共享是瞬时发生的。也就是说，在同一时间，一个专家不光可以接收到秘密，还能在其他会议上与其他专家分享。

解读：在同一时间发生的所有会议，可以视作一个无向图。专家是图中的节点，meetings[i] 是图的边，连接 xi 和 yi。

**这个图可能有多个连通块。对于一个连通块，如果其中有知道秘密的专家，那么这个专家会把秘密分享给这个连通块中的其他专家。**

---

从题目给定的数据结构,直觉就感觉和并查集相关。

## 方法一: 并查集

如何遍历 time 相同的会议？**分组循环。**

适用场景：按照题目要求，数组会被分割成若干组，每一组的判断/处理逻辑是相同的。

核心思想：

- 外层循环负责遍历组之前的准备工作（记录开始位置等），和遍历组之后的工作（传播秘密）。
- **内层循环负责遍历组，找出这一组最远在哪结束，同时建图。**

```python

# 并查集规定模版

class UnionFind:
  def __init__( self, n ):
    # 初始化n个集合,每个集合的代表元是自己
    self.fa = list( range( n ) )

  def find( self, x:int ) -> int:
    fa = self.fa
    if fa[ x ] != x:
      fa[ x ] = self.find( fa[ x ] )
    return fa[ x ]

  def connected( self, x:int, y:int ) -> bool:
    return self.find( x ) == self.find( y )

  def merge( self, from_:int, to_:int ) -> None:
    x, y = self.find( from_ ), self.find( to_ )
    self.fa[ x ] = y

from typing import List

class Solution:
  def findAllPeople(self, n: int, meetings: List[List[int]], firstPerson: int) -> List[int]:

    uf = UnionFind( n )
    
    # 初始时,0和firstPerson知道秘密
    uf.merge( 0, firstPerson )

    # 模拟:按照时间排序,模拟会议过程
    meetings.sort( key=lambda x: x[ 2 ] )
    
    # 分组循环
    m = len( meetings )
    i = 0
    while i < m:

      # 若存在多个time相等的会议,则这些会议可以视作一个连通块
      # 模拟:在这个连通块中,若专家x知道秘密,则专家x会把秘密分享给专家y
      # 若不存在多个相同时间会议,则模拟当前会议
      start = i
      time = meetings[ i ][ 2 ]
      while i < m and  meetings[ i ][ 2 ] == time:
        uf.merge( meetings[ i ][ 0 ], meetings[ i ][ 1 ] )
        i += 1

      # 对于不知道秘密的专家,还原其代表元,方便最终统计
      for x, y, _ in meetings[ start: i ]:
        if not uf.connected( x, 0 ): uf.fa[ x ] = x
        if not uf.connected( y, 0 ): uf.fa[ y ] = y

    return [ i for i in range( n ) if uf.connected( i, 0 ) ]
```

- 时间复杂度：O(n+mlogm)，其中 m 是 meetings 的长度。
  - 分组循环是 O(m) 的，每个 meetings[i] 恰好遍历两次。
  - mlogm 是排序的时间复杂度。
- 空间复杂度：O(n)。忽略排序的栈开销。

## 方法二: DFS

```python
from typing import List
from collections import defaultdict


class Solution:
  def findAllPeople( self, n: int, meetings: List[List[int]], firstPerson: int) -> List[int]:

        # 按照time 从小到大排序
        meetings.sort( key=lambda x: x[ 2 ] )

        # 一开始 0 和 firstPerson 知道秘密
        known = { 0, firstPerson }

        # 分组循环
        m = len( meetings )
        i = 0
        
        while i < m:
            # 同一时间发生的会议: 建图
            g = defaultdict( list )
            time = meetings[ i ][ 2 ]
            while i < m and meetings[ i ][ 2 ] == time:
                x, y, _ = meetings[ i ]
                g[ x ].append( y )
                g[ y ].append( x )
                i += 1
            
            # 每个连通块 只要有人知道秘密 整个连通块都知道秘密
            vis = set()

            def dfs( x:int ) -> None:
                # x: 已知秘密
                vis.add( x )
                known.add( x )
                for y in g[ x ]:
                    # 边连通: y 已知秘密
                    if y not in vis: dfs( y )
            
            # time 时间点参加会议的专家 从知道秘密的专家开始标记
            for x in g:
                if x in known and x not in vis: dfs( x )
        
        return list( known )
```



