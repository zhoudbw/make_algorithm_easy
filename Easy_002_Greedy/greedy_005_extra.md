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
  * **首先让strNum[i - 1]--，然后strNum[i]赋值为9**，这样这个整数就是89，即小于98的最大的单调递增整数。

* 遍历顺序,从后往前,这样讲最后一位赋值为9,不会让前面数字的相对大小发生变化.

* 特别注意:flag的设置很重要!!!

* 思考方式很重要!!!

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

* 一个摄像头能够监控上中下三层
  * 可以选择从叶子结点的父节点开始,从下往上安装摄像头;摄像头之间相隔两层;
  * 也可选择从根节点的子节点开始,从上往下安装摄像头;摄像头之间相隔两层;
  * **综合上述两种情况,应选择从下往上安装摄像头**, 很明显:
    * 如果从上往下安装摄像头,最后时可能无法监控叶子节点,这就要求叶子结点都要单独安装摄像头;(指数级)
    * 如果从下往上安装摄像头,最后时可能无法监控根节点,这就要求根节点单独安装摄像头,也仅仅是安装1个摄像头;
    * 综合上述两种情况,应选择从下往上安装摄像头;

* 贪心:从下往上看，局部最优：让叶子节点的父节点安摄像头，所用摄像头最少，整体最优：全部摄像头数量所用最少.

* 操作:
  * 二叉树遍历 ( 后序遍历'左右中',回溯时就是从下往上 )
  * **间隔两个节点安装摄像头**
    * 一个节点的三种状态:
      * 0: 无覆盖
      * 1: 有摄像头
      * 2: 有覆盖
      * 有没有第四种状态：本节点无摄像头，其实无摄像头就是 无覆盖 或者 有覆盖的状态，所以一共还是三个状态。
```text

在遍历树的过程中，会遇到空节点，那么空节点究竟是哪一种状态呢？ 空节点表示无覆盖？ 表示有摄像头？还是有覆盖呢？

**回归本质，为了让摄像头数量最少，要尽量让叶子节点的父节点安装摄像头，这样才能摄像头的数量最少。**

如果空节点是无覆盖的状态，就会给叶子节点的父节点放摄像头，摄像头数量就多了一个。
如果空节点是有摄像头的状态,那么叶子节点父节点就没有必要放摄像头了,因为有摄像头的话,叶子节点就有覆盖了.
所以空节点的状态只能是有覆盖，这样就可以在叶子节点的父节点放摄像头了

接下来就是递推关系。递归的终止条件应该是遇到了空节点，此时应该返回2（有覆盖），原因上面已经解释过了。
---

**单层逻辑:**
情况1：左右节点都有覆盖，
    那么本节点就是无覆盖的状态0。( 由于左右节点都有覆盖,所以本节点没有必要安装摄像头,本节点的状态就是无覆盖 )
情况2：左右节点至少有一个无覆盖的情况，
    那么本节点就是有摄像头的状态1。( 由于左右节点有一个不处于监控状态,所以为了让整棵树都处于监控状态,所以本节点必须安装摄像头 )
情况3：左右节点至少有一个有摄像头，
    那么本节点就是有覆盖的状态2。 ( 由于左右节点有一个摄像头,所以本节点就有覆盖了,本节点的状态就是有覆盖 )
情况4：头结点没有覆盖，
    递归结束，需要增加一个摄像头。
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def minCameraCover(self, root: Optional[TreeNode]) -> int:

        # * 0:表示无覆盖
        # * 1:表示有摄像头
        # * 2:表示有覆盖
        # ******
        # * 叶子结点的父节点安装摄像头,间隔两层再次安装
        ans = [ 0 ]

        def getNodeType( node ):
            if not node: return 2
            
            leftType = getNodeType( node.left )
            rightType = getNodeType( node.right )
        
            # * 当前节点的3种情况,即0,1,2
            if leftType == 2 and rightType == 2: return 0
            if leftType == 0 or rightType == 0: ans[ 0 ] += 1; return 1
            if leftType == 1 or rightType == 1: return 2

        rootType = getNodeType( root )
        if rootType == 0: ans[ 0 ] += 1

        return ans[ 0 ]
```