--- Create Time: 2025-11-06 10:00:00
--- @Author: xcyy

# 并查集

## 基础知识

1. 并查集解决的问题
    - 并查集常用来解决连通性问题。
    - 即,判断两个元素是否在同一个集合里的时候，就要想到用并查集。

2. 并查集主要有两个功能：
    - 将两个元素添加到一个集合中。
    - 判断两个元素在不在同一个集合。

**并查集原理**

1. 如何将两个元素添加到同一个集合中呢?

方案1: 直接将两个元素添加到同一map/set/数组中?

很多个集合时,会有多个数组(或二维数组)/map/set来维护这些集合。
加入一个元素时,需要遍历全部数组/set/map; 判断是否是一个集合时,也需要遍历全部数组/set/map。
如果沿着这个思路去实现代码，非常复杂，因为管理集合还需要很多逻辑。

方案2:

将三个元素A，B，C (均为数字)放在同一个集合，其实就是将三个元素连通在一起，如何连通呢。
只需要用一个一维数组来表示，即：father[A] = B，father[B] = C 这样就表述 A 与 B 与 C连通了（有向连通图）。

代码:

```c++
// 将v，u 这条边加入并查集
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根
    if (u == v) return; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
    father[v] = u;
}
```

寻根思路，只要 A ，B，C 在同一个根下就是同一个集合。
给出A元素，就可以通过 father[A] = B，father[B] = C，找到根为 C。
给出B元素，就可以通过 father[B] = C，找到根也为为 C，说明 A 和 B 是在同一个集合里。
find函数其实就是通过数组下标找到数组元素，一层一层寻根过程。

代码:

```c++
// 并查集里寻根的过程
int find(int u) {
    if (u == father[u]) return u; // 如果根就是自己，直接返回
    else return find(father[u]); // 如果根不是自己，就根据数组下标一层一层向下找
}
```

如何表示 C 也在同一个集合里呢？
需要 father[C] = C，即C的根也为C，这样就方便表示 A，B，C 都在同一个集合里了。
所以father数组初始化的时候要 father[i] = i，默认自己指向自己。

代码:

```c++
// 并查集初始化
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}
```

最后如何判断两个元素是否在同一个集合里，
如果通过 find函数 找到 两个元素属于同一个根的话，那么这两个元素就是同一个集合里的元素。

代码:

```c++
// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}¬
```

## 路径压缩

路径压缩的核心思想：在查找过程中，将路径上的所有节点直接连接到根节点，从而将树的高度压平，大幅提高后续操作的效率。

在实现 find 函数的过程中，通过递归的方式，不断获取father数组下标对应的数值，最终找到这个集合的根。

搜索过程像是一个多叉树中从叶子到根节点的过程，
如果每次搜索都从叶子节点向根节点搜索，那么搜索路径就会很长，
而路径压缩的作用就是在搜索的过程中，将搜索路径上的所有节点都指向根节点，
这样就可以减少后续搜索的时间复杂度。

代码:

```c++
// 并查集里寻根的过程
int find(int u) {
    if (u == father[u]) return u; // 如果根就是自己，直接返回
    else return father[u] = find(father[u]); // 如果根不是自己，就根据数组下标一层一层向下找，同时压缩路径
}
```

图示:

![路径压缩](Assets/daily_006_path_compression.png)

## 补充:按秩合并

关键点:

- 在 find() 操作中递归压缩路径
- 配合按秩合并避免树过高
- 将时间复杂度从 O(n) 优化到 O(α(n)), 其中 α(n) 是反阿克曼函数，对于所有实际应用场景，α(n) ≤ 5。

```python
class UnionFind:
    def __init__( self, n ):
        self.parent = list( range( n ) )
        self.rank = [ 0 ] * n

    def find( self, x ):
        """带路径压缩的查找"""
        if self.parent[ x ] != x:
            # 递归进行路径压缩
            self.parent[ x ] = self.find( self.parent[ x ] )
        return self.parent[ x ]

    def union( self, x, y ):
        """按秩合并"""
        root_x = self.find( x )
        root_y = self.find( y )

        if root_x != root_y:
            if self.rank[ root_x ] < self.rank[ root_y ]:
                self.parent[ root_x ] = root_y
            elif self.rank[ root_x ] > self.rank[ root_y ]:
                self.parent[ root_y ] = root_x
            else:
                self.parent[ root_y ] = root_x
                self.rank[ root_x ] += 1
            return True
        return False
```

## 应用:电网维护

[3607. 电网维护](https://leetcode.cn/problems/power-grid-maintenance/description/)

给你一个整数 c，表示 c 个电站，每个电站有一个唯一标识符 id，从 1 到 c 编号。

这些电站通过 n 条 双向 电缆互相连接，表示为一个二维数组 connections，
其中每个元素 connections[i] = [ui, vi] 表示电站 ui 和电站 vi 之间的连接。
直接或间接连接的电站组成了一个 电网 。

最初，所有 电站均处于在线（正常运行）状态。

另给你一个二维数组 queries，其中每个查询属于以下 两种类型之一 ：

[1, x]：请求对电站 x 进行维护检查。如果电站 x 在线，则它自行解决检查。
如果电站 x 已离线，则检查由与 x 同一 电网 中 编号最小的在线电站解决。
如果该电网中 不存在 任何 在线 电站，则返回 -1。

[2, x]：电站 x 离线（即变为非运行状态）。

返回一个整数数组，表示按照查询中出现的顺序，所有类型为 [1, x] 的查询结果。

注意：电网的结构是固定的；离线（非运行）的节点仍然属于其所在的电网，且离线操作不会改变电网的连接性。

--- 测试用例 ---

```text
示例 1：
输入： c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]
输出： [3,2,3]
解释：
最初，所有电站 {1, 2, 3, 4, 5} 都在线，并组成一个电网。
查询 [1,3]：电站 3 在线，因此维护检查由电站 3 自行解决。
查询 [2,1]：电站 1 离线。剩余在线电站为 {2, 3, 4, 5}。
查询 [1,1]：电站 1 离线，因此检查由电网中编号最小的在线电站解决，即电站 2。
查询 [2,2]：电站 2 离线。剩余在线电站为 {3, 4, 5}。
查询 [1,2]：电站 2 离线，因此检查由电网中编号最小的在线电站解决，即电站 3。

示例 2：
输入： c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]
输出： [1,-1]
解释：
没有连接，因此每个电站是一个独立的电网。
查询 [1,1]：电站 1 在线，且属于其独立电网，因此维护检查由电站 1 自行解决。
查询 [2,1]：电站 1 离线。
查询 [1,1]：电站 1 离线，且其电网中没有其他电站，因此结果为 -1。
```

--- 说明提示 ---

```text
1 <= c <= 10^5
0 <= n == connections.length <= min(10^5, c * (c - 1) / 2)
connections[i].length == 2
1 <= ui, vi <= c
ui != vi
1 <= queries.length <= 2 * 10^5
queries[i].length == 2
queries[i][0] 为 1 或 2。
1 <= queries[i][1] <= c
```

--- 题目解答 ---

思路:

- 维护一个并查集，记录每个电站所属的电网
- 维护一个Map< Key, SortedSet< Integer > >，记录每个电网中在线的电站
    - Key 为电网的根节点
    - SortedSet 中存储该电网中在线的电站的编号 ( 有序, 方便查询编号最小的在线电站 )

- 对于每个查询 [1, x]，如果 x 在线，则直接返回 x；否则，返回该电网中编号最小的在线电站; 如果电网中没有在线电站，则返回 -1;
- 对于每个查询 [2, x]，将 x 从其电网的 SortedSet 中移除.

```python
from sortedcontainers import SortedSet
from typing import List


class Solution:
    def processQueries( self, c: int, connections: List[ List[ int ] ], queries: List[ List[ int ] ] ) -> List[ int ]:

        parent = [ x for x in range( 0, c + 1 ) ]

        def find( x_ ):
            if x_ != parent[ x_ ]:
                parent[ x_ ] = find( parent[ x_ ] )
            return parent[ x_ ]

        def join( x_, y_ ):
            root_x = find( x_ );
            root_y = find( y_ )
            if root_x != root_y: parent[ root_x ] = root_y

        # -- 构建并查集 --
        for x, y in connections:
            join( x, y )

        online = { }

        for i in range( 1, c + 1 ):
            key = find( i )
            if key not in online:
                online[ key ] = SortedSet()
            online[ key ].add( i )
        ans = [ ]
        for opt, x in queries:
            online_set = online[ find( x ) ]
            if opt == 1:
                if x in online_set:
                    ans.append( x )
                else:
                    ans.append( -1 if len( online_set ) == 0 else online_set[ 0 ] )
            else:
                if x in online_set: online_set.remove( x )
        return ans
```

和上述类似的做法:

首先，建图 + DFS，把每个连通块中的节点加到各自的最小堆中。每个最小堆维护对应连通块的节点编号。

然后处理询问。

对于类型二，用一个 offline 布尔数组表示离线的电站。这一步不修改堆。

对于类型一：

如果电站 x 在线，那么答案为 x。
否则检查 x 所处堆的堆顶是否在线。若离线，则弹出堆顶，重复该过程。如果堆为不空，那么答案为堆顶，否则为 −1。
为了找到 x 所属的堆，还需要一个数组 belong 记录每个节点在哪个堆中。

```python
import heapq
from typing import List


class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:

        g = [ [] for _ in range( c + 1 ) ]

        for x, y in connections:
            g[ x ].append( y )
            g[ y ].append( x )

        # -- 记录元素所处的堆index --
        belong = [ -1 for _ in range( c + 1 ) ]
        heaps = []

        def dfs( x_, h_ ):
            belong[ x_ ] = len( heaps )
            h_.append( x_ )
            for y in g[ x_ ]:
                if belong[ y ] < 0: dfs( y, h_ )

        for i in range( 1, c + 1 ):
            if belong[ i ] >= 0: continue

            h = []
            dfs( i, h )
            heapq.heapify( h )
            heaps.append( h )

        offline = [ False for _ in range( c + 1 ) ]

        ans = []
        for op, x in queries:
            if op == 2:
                offline[ x ] = True
                continue

            if not offline[ x ]: ans.append( x )
            else:
                h = heaps[ belong[ x ] ]
                while h and offline[ h[ 0 ] ]:
                    heapq.heappop( h )
                ans.append( h and h[ 0 ] or -1 )
        return ans
```
