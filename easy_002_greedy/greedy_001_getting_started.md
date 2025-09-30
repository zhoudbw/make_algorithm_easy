
# 贪心算法

## 大纲

- 贪心算法详解
- 题目: [分发饼干](https://leetcode.cn/problems/assign-cookies/description/)
- 题目: [K次取反后最大化的数组和](https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/description/)
- 题目: [柠檬水找零](https://leetcode.cn/problems/lemonade-change/description/)

## 详解

**什么是贪心算法**

**贪心的本质是选择每一阶段的局部最优，从而达到全局最优。**

举个例子:

假设你有一堆钞票，你可以拿走十张，如果想达到最大的金额，怎么拿？
- 每一次都拿走最大数额的钞票，最终结果就是拿走最大数额的钱。
- 每次拿最大的就是局部最优，最后拿走最大数额的钱就是推出全局最优。

**什么时候用贪心算法**

- 问题能够分解成子问题来解决，子问题的最优解能递推到最终问题的最优解。这种子问题最优解称为最优子结构。
- 贪心选择性质: 是指所求问题的整体最优解可以通过一系列局部最优的选择，即贪心选择来达到。这是贪心算法可行的第一个基本要素。
- 最优子结构性质: 当一个问题的最优解包含其子问题的最优解时，称此问题具有最优子结构性质。问题的最优子结构性质是该问题可用贪心算法求解的关键特征。

想要严格的数学证明, 一般数学证明有如下两种方法： 

- 数学归纳法
- 反证法

**贪心算法的一般步骤**

- 将问题分解为若干个子问题
- 找出合适的贪心策略
- 求解每一个子问题的最优解
- 将局部最优解堆叠成全局最优解


## [分发饼干](https://leetcode.cn/problems/assign-cookies/description/)

假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。

如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是满足尽可能多的孩子，并输出这个最大数值。

```
提示：
1 <= g.length <= 3 * pow( 10, 4 )
0 <= s.length <= 3 * pow( 10, 4 )
1 <= g[i], s[j] <= pow( 2, 31 ) - 1
```

### 题解

```
示例:
输入: g = [1,2,3], s = [1,1]
输出: 1
解释: 
你有三个孩子和两块小饼干，3 个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是 1，你只能让胃口值是 1 的孩子满足。
所以你应该输出 1。
```

**代码详解**

- 快速排序模版
  - i,j的初始化, i = left - 1; j = right + 1; 是为了统一操作,交换完元素后,两者应该向中间聚拢.
  - 循环结束的条件是 i < j, 是为了确保最后一次交换后, i, j 指向的元素是相同或交错的.
  - 内部的while循环不应该判断i<j,因为希望i和j是相同或交错的,如果判断了,就可能出现i在j左边,就结束了循环.
  比如 1 2 4 3 此时i在2的位置,而j在4的位置,提前j-=1,此时j在2的位置,判断i<j结束了,但是实际上j的位置并没有更新.

- 贪心思想解释
  - 一块饼干,至多只能满足一个孩子,不管这个饼干有多大.
  - 所以,这里选择先满足胃口小的孩子,如果这个孩子能被满足,就满足,如果不能,就继续满足下一个更大的饼干,尝试满足这个孩子.

```python
class Solution(object):
    def findContentChildren(self, g, s):
        """
        :type g: List[int]
        :type s: List[int]
        :rtype: int
        """

        def qsort( arr, left, right ):
            if left >= right: return

            pivot = arr[ left + ( right - left ) // 2 ]

            i, j = left - 1, right + 1

            while i < j:
                i += 1
                while arr[ i ] < pivot: i += 1
                j -= 1
                while arr[ j ] > pivot: j -= 1

                if i < j: arr[ i ], arr[ j ] = arr[ j ], arr[ i ]

            qsort( arr, left, j )
            qsort( arr, j + 1, right )

        qsort( g, 0, len( g ) - 1 )
        qsort( s, 0, len( s ) - 1 )


        child_index, ans = 0, 0
        
        for v in s:
            if child_index < len( g ) and v >= g[ child_index ]: ans += 1; child_index += 1

        return ans
```

## [K次取反后最大化的数组和](https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/description/)

给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：

- 选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
- 重复这个过程恰好 k 次。可以多次选择同一个下标 i 。

以这种方式修改数组后，返回数组 可能的最大和 。

```
提示：
1 <= nums.length <= pow( 10, 4 )
-100 <= nums[i] <= 100
1 <= k <= pow( 10, 4 )
```

### 题解

```
示例 1：
输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标 1 ，nums 变为 [4,-2,3] 。

示例 2：
输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。

示例 3：
输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。
```

**代码详解**

- 贪心思想解释
> 一定要用贪心的思想去思考,即局部最优->全局最优
  - 每次都选择最小的负数,将其翻转;
  - 如果还剩翻转次数, 取其中的最小值,用来抵消其他翻转次数.

- 代码细节
  - 排序是按照绝对值排序的,所以数值的最小值出现在0号位置.
  - 负数全部翻转了,如果还剩下翻转次数,一定选择最小数,才能使的和最大.

```python
class Solution(object):
  def largestSumAfterKNegations(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """

    # -- 排序,从小到大,将负数翻转,如果还剩翻转次数,取其中的最小值,用来翻转其他次数 --

    def qsort( left, right ):
      if left >= right: return

      pivot = abs( nums[ left + ( right - left ) // 2 ] )

      i, j = left - 1, right + 1

      while i < j:
        i += 1
        while abs( nums[ i ] ) < pivot: i += 1

        j -= 1
        while abs( nums[ j ] ) > pivot: j -= 1

        if i < j: nums[ i ], nums[ j ] = nums[ j ], nums[ i ]

      qsort( left, j )
      qsort( j + 1, right )

    n = len( nums )
    qsort( 0, n - 1 )


    # -- 此时,数组按照绝对值从大到小排序完成 --
    for i in range( n - 1, -1, -1 ):
      if k > 0 and nums[ i ] < 0: nums[ i ] *= -1; k -= 1

    if k > 0: nums[ 0 ] *= pow( -1, k )

    return sum( nums )
```

## [柠檬水找零](https://leetcode.cn/problems/lemonade-change/description/)

在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。

注意，一开始你手头没有任何零钱。

给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。

```
提示：
1 <= bills.length <= pow( 10, 5 )
bills[i] 不是 5 就是 10 或是 20 
```

### 题解

```
示例 1：
输入：bills = [5,5,5,10,20]
输出：true
解释：
前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
由于所有客户都得到了正确的找零，所以我们输出 true。

示例 2：
输入：bills = [5,5,10,10,20]
输出：false
解释：
前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
由于不是每位顾客都得到了正确的找零，所以答案是 false。
```

**代码详解**

- 贪心思想解释
> 一定要用贪心的思想去思考,即局部最优->全局最优,慢慢去分析

  - 找零时,先将手中数额大的找出去. ( 5美元能够组合的可能性更多 )
  - 5美元,直接收下.
  - 10美元,找1张5美元.
  - 20美元,找1张10美元,1张5美元 or 3张5美元.
  
- 代码优化
  - 只需要维护手中的5美元和10美元的数量即可.因为20美元不能用来找零.
  - 因为只需要维护5美元和10美元的数据量,coins字典可以用five,ten两个变量代替.

```python
class Solution(object):
    def lemonadeChange(self, bills):
        """
        :type bills: List[int]
        :rtype: bool
        """

        #-- 找零时,先将手中数额大的找出去 --
        coins = { 10:0, 20:0, 5:0 }

        for v in bills:
            coins[ v ] += 1
            
            if v == 5: # -- 直接收下 --
                continue
            elif v == 10: # -- 1张5美元 --
                if coins[ 5 ] == 0: return False
                else: coins[ 5 ] -= 1

            else: # -- 1张5美元,1张10美元 or 3张5美元 --
                if coins[ 10 ] != 0 and coins[ 5 ] >= 1: coins[ 10 ] -= 1; coins[ 5 ] -= 1
                elif coins[ 10 ] == 0 and coins[ 5 ] >= 3: coins[ 5 ] -= 3
                else: return False

        return True
```
