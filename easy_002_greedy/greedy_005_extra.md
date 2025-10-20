# 贪心算法

## 大纲

- 题目: [单调递增的数字](https://leetcode.cn/problems/monotone-increasing-digits/description/)
- 题目: [监控二叉树](https://leetcode.cn/problems/binary-tree-cameras/description/)


## [单调递增的数字](https://leetcode.cn/problems/monotone-increasing-digits/description/)

当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。

给定一个整数 n ，返回 小于或等于 n 的最大数字，且数字呈 单调递增 。

--提示--
```
0 <= n <= 10^9
```

--示例--
```
示例 1:
输入: n = 10
输出: 9

示例 2:
输入: n = 1234
输出: 1234

示例 3:
输入: n = 332
输出: 299

补充示例 4:
输入: n = 100
输出: 99
```

### 题解

**贪心的体现:**

* 题目要求小于等于N的最大单调递增的整数 ( 当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。 )
  * 例如：98，一旦出现strNum[i - 1] > strNum[i]的情况（非单调递增），
  * 首先想让strNum[i - 1]--，然后strNum[i]给为9，这样这个整数就是89，即小于98的最大的单调递增整数。

* 遍历顺序,从后往前,这样讲最后一位赋值为9,不会让前面数字的相对大小发生变化.

* 特别注意:flag的设置很重要!!!

```python
class Solution:
    def monotoneIncreasingDigits(self, n: int) -> int:

        nlist = list( str( n ) )

        llen = len( nlist )

        flag = llen #标识从flag位开始,后面所有数都是9,针对100这样的测试用例

        for i in range( llen - 1, 0, -1 ):
            pre = int( nlist[ i - 1 ] )
            cur = int( nlist[ i ] )
            if pre > cur: 
                nlist[ i - 1 ] = str( pre - 1 )
                flag = i

        for i in range( flag, llen ): nlist[ i ] = "9"

        return int( "".join( nlist ) )
```


[监控二叉树](https://leetcode.cn/problems/binary-tree-cameras/description/)

给定一个二叉树，我们在树的节点上安装摄像头。

节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。

计算监控树的所有节点所需的最小摄像头数量。

--提示--
```
给定树的节点数的范围是 [1, 1000]。
每个节点的值都是 0。
```

--示例--
```
示例 1：
输入：[0,0,null,0,0]
输出：1
解释：如图所示，一台摄像头足以监控所有节点。

示例 2：
输入：[0,0,null,0,null,0,null,null,0]
输出：2
解释：需要至少两个摄像头来监视树的所有节点。 上图显示了摄像头放置的有效位置之一。
```

### 题解

```python

```