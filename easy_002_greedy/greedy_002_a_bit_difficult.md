# 贪心算法

## 大纲

- 题目: [摆动序列](https://leetcode.cn/problems/wiggle-subsequence/description/)
- 题目: [最大子数组和](https://leetcode.cn/problems/maximum-subarray/description/)
- 题目: [买卖股票的最佳时机II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/)
- 题目: [跳跃游戏](https://leetcode.cn/problems/jump-game/description/)
- 题目: [跳跃游戏II](https://leetcode.cn/problems/jump-game-ii/description/)

## [摆动序列](https://leetcode.cn/problems/wiggle-subsequence/description/)

如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列 。

第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。

- 例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3) 是正负交替出现的。
- 相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

子序列 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。

给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。

```
提示：
1 <= nums.length <= 1000
0 <= nums[i] <= 1000

进阶：你能否用 O(n) 时间复杂度完成此题?
```

### 题解

**本题的关键,其实就在于统计山谷和山峰的数量**

```
示例 1：
输入：nums = [1,7,4,9,2,5]
输出：6
解释：整个序列均为摆动序列，各元素之间的差值为 (6, -3, 5, -7, 3) 。

示例 2：
输入：nums = [1,17,5,10,13,15,10,5,16,8]
输出：7
解释：这个序列包含几个长度为 7 摆动序列。
其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3, 6, -8) 。

示例 3：
输入：nums = [1,2,3,4,5,6,7,8,9]
输出：2
```

#### 贪心算法

局部最优：删除单调坡度上的节点, 那么这个坡度就可以有两个局部峰值。
- 如果是单调增或单调减,保留左右两端点;
- 如果是单调不增或单调不减,保留左右两端点之一;

整体最优：整个序列有最多的局部峰值，从而达到最长摆动序列。

局部最优推出全局最优，并举不出反例，那么试试贪心！

**代码详解**

实际操作上，其实连删除的操作都不用做，因为题目要求的是最长摆动子序列的长度，所以只需要统计数组的峰值数量即可.

在计算是否有峰值的时候，计算 prediff（nums[i] - nums[i-1]） 和 curdiff（nums[i+1] - nums[i]），
如果prediff < 0 && curdiff > 0 或者 prediff > 0 && curdiff < 0 此时就有波动就需要统计。

这是思考本题的一个大体思路，但本题要考虑三种情况：

- 情况一：上下坡中有平坡
- 情况二：数组首尾两端
- 情况三：单调坡中有平坡

```python
class Solution:
    def wiggleMaxLength(self, nums: list[int]) -> int:

        n = len( nums )

        if n == 1: return 1

        ans = 1 # 记录峰值个数,序列默认序列最右边有一个峰值

        prediff = 0 # 前一对差值
        curdiff = 0 # 当前一对差值

        for i in range( 0, n - 1 ):
            curdiff = nums[ i + 1 ] - nums[ i ]

            if prediff >= 0 and curdiff < 0 or prediff <= 0 and curdiff > 0:
                ans += 1

                # 注意,只在摆动变化的时候更新prediff
                prediff = curdiff
                
        return ans
```

#### 动态规划

- 分析流程:
  - 确定dp数组的含义
  - 推导状态转移方程
  - 初始化dp数组
  - 确定遍历顺序
  - 实例化模拟dp

**代码详解**

很容易可以发现，对于我们当前考虑的这个数，要么是作为山峰（即 nums[i] > nums[i-1]），要么是作为山谷（即 nums[i] < nums[i - 1]）。

- dp数组的含义:
  - 设 dp 状态dp[i][0]，表示考虑前 i 个数，第 i 个数作为山峰的摆动子序列的最长长度
  - 设 dp 状态dp[i][1]，表示考虑前 i 个数，第 i 个数作为山谷的摆动子序列的最长长度

- 状态转移方程:
  - dp[i][0] = max(dp[i][0], dp[j][1] + 1)，其中0 < j < i且nums[j] < nums[i]，表示将 nums[i]接到前面某个山谷后面，作为山峰。
  - dp[i][1] = max(dp[i][1], dp[j][0] + 1)，其中0 < j < i且nums[j] > nums[i]，表示将 nums[i]接到前面某个山峰后面，作为山谷。

- 初始状态:
  - 由于一个数可以接到前面的某个数后面，也可以以自身为子序列的起点，所以初始状态为：dp[0][0] = dp[0][1] = 1。

```python
class Solution:
    def wiggleMaxLength(self, nums: list[int]) -> int:

        n = len( nums )

        dp = [ [ 1, 1 ] for _ in range( n ) ]

        for i in range( 1, n ):

            for j in range( 0, i ):
                if nums[ j ] < nums[ i ]: dp[ i ][ 0 ] = max( dp[ i ][ 0 ], dp[ j ][ 1 ] + 1 )

            for j in range( 0, i ):
                if nums[ j ] > nums[ i ]: dp[ i ][ 1 ] = max( dp[ i ][ 1 ], dp[ j ][ 0 ] + 1 )
        
        return max( dp[ -1 ][ 0 ], dp[ -1 ][ 1 ] )
```

**进阶**

可以用两棵线段树来维护区间的最大值

每次更新dp[i][0]，则在tree1的nums[i]位置值更新为dp[i][0]

每次更新dp[i][1]，则在tree2的nums[i]位置值更新为dp[i][1]

则 dp 转移方程中就没有必要 j 从 0 遍历到 i-1，可以直接在线段树中查询指定区间的值即可。


## [最大子数组和](https://leetcode.cn/problems/maximum-subarray/description/)

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组是数组中的一个连续部分。

```
提示：
1 <= nums.length <= pow( 10, 5 )
-pow( 10, 4 ) <= nums[i] <= pow( 10, 4 )

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。
```

### 题解

```
示例 1：
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

示例 2：
输入：nums = [1]
输出：1

示例 3：
输入：nums = [5,4,-1,7,8]
输出：23
```

#### 贪心算法

**贪心体现在哪里?**

如果 -2 1 在一起，计算起点的时候，一定是从 1 开始计算，因为负数只会拉低总和，这就是贪心贪的地方！

- 局部最优：当前“连续和”为负数的时候立刻放弃，从下一个元素重新计算“连续和”，因为负数加上下一个元素 “连续和”只会越来越小。
- 全局最优：选取最大“连续和”

局部最优的情况下，并记录最大的“连续和”，可以推出全局最优。

```python
class Solution:
    def maxSubArray(self, nums: list[int]) -> int:

        ans = float( '-inf' )

        acc_sum = 0

        for x in nums:

            if acc_sum < 0:
                acc_sum = x
        
            else:
                acc_sum += x
            
            ans = max( ans, acc_sum )
            
        return ans
```


#### 动态规划

- dp[ i ] 表示到nums[ i ]的最大连续子数组和
  - dp[i][0] 表示不加入nums[i]的最大连续子数组和
  - dp[i][1] 表示要加入nums[i]的最大连续子数组和

- dp[ i ]的状态转移方程 ( ans 记录出现过的最大连续子数组和 )
  - dp[i][0] = max( dp[ i - 1 ][ 0 ], dp[ i - 1 ][ 1 ] ); ans = max( ans, dp[ i ][ 0 ] )
  - dp[i][1] = max( nums[ i ], dp[ i - 1 ][ 1 ] + nums[ i ] ); ans = max( ans, dp[ i ][ 1 ] )

- 初始化: 这里需要特别注意(  )
  - dp[ 0 ][ 1 ] = dp[ 0 ][ 0 ] = nums[ 0 ]
  - ans = nums[ 0 ] # 子数组长度必须大于1

```python
class Solution:
    def maxSubArray(self, nums: list[int]) -> int:

        n = len( nums )

        dp = [ [ 0, 0 ] for _ in range( n ) ]

        dp[ 0 ][ 1 ] = dp[ 0 ][ 0 ] = nums[ 0 ]
        ans = nums[ 0 ] # 子数组长度必须大于1

        for i in range( 1, n ):
            dp[ i ][ 0 ] = max( dp[ i - 1 ][ 0 ], dp[ i - 1 ][ 1 ] )
            dp[ i ][ 1 ] = max( nums[ i ], dp[ i - 1 ][ 1 ] + nums[ i ] )
            ans = max( ans, dp[ i ][ 0 ], dp[ i ][ 1 ] )
        
        return ans
```

**注意:上面代码,其实不需要dp[i][0]这一项来记录**

**因为,如果不选择nums[i],此时已经不是连续序列了,需要从nums[i]开始重新计数, 有ans记录过程中的最大值,所以dp[i][0]无需**

```python
class Solution:
    def maxSubArray(self, nums: list[int]) -> int:

        n = len( nums )

        dp = [ 0 for _ in range( n ) ]

        dp[ 0 ] = ans = nums[ 0 ]
        
        for i in range( 1, n ):
            dp[ i ] = max( nums[ i ], dp[ i - 1 ] + nums[ i ] )
            ans = max( ans, dp[ i ] )
        
        return ans
```


## [买卖股票的最佳时机II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/)

给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。然而，你可以在 同一天 多次买卖该股票，但要确保你持有的股票不超过一股。

返回 你能获得的 最大 利润 。

```
提示：
1 <= prices.length <= 3 * pow( 10, 4 )
0 <= prices[i] <= pow( 10, 4 )
```

### 题解

```
示例 1：
输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3。
最大总利润为 4 + 3 = 7 。

示例 2：
输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
最大总利润为 4 。

示例 3：
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0。
```

#### 动态规划

**本题,dp的状态设置为第i天持有股票和不持有股票的最大利润**
**这样规定比dp的状态设置为第i天卖出/买入/不处理股票的最大利润更容易处理**

**在定义dp含义时,要充分考虑状态转移方程推导的便利性**

- dp[ i ]表示第i天持有/不持有股票的最大利润
  - dp[ i ][ 0 ]表示第i天不持有股票的最大利润
  - dp[ i ][ 1 ]表示第i天持有股票的最大利润

- 状态转移方程:
  - dp[ i ][ 0 ] = max( dp[ i - 1 ][ 0 ], dp[ i - 1 ][ 1 ] + nums[ i ] ) # 前一天不持有;当天卖出;
  - dp[ i ][ 1 ] = max( dp[ i - 1 ][ 1 ], dp[ i - 1 ][ 0 ] - nums[ i ] ) # 前一天不持有;当天买入;

- 初始化:
  - dp[ 0 ][ 0 ] = 0; dp[ 0 ][ 1 ] = -price[ 0 ]

- 遍历顺序:
  - for i in range( 1, n ) [prices] 即可

- 模拟

```python
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        
        n = len( prices )

        dp = [ [ 0, 0 ] for _ in range( n ) ]

        dp[ 0 ][ 0 ] = 0; dp[ 0 ][ 1 ] = -prices[ 0 ]

        for i in range( 1, n ):

            dp[ i ][ 0 ] = max( dp[ i - 1 ][ 0 ], dp[ i - 1 ][ 1 ] + prices[ i ] )
            dp[ i ][ 1 ] = max( dp[ i - 1 ][ 1 ], dp[ i - 1 ][ 0 ] - prices[ i ] )
        
        return max( dp[ -1 ][ 0 ], dp[ -1 ][ 1 ] )
```

#### 贪心算法

这道题目很直观的想法, 选一个低的买入, 再选个高的卖 ... 循环反复。

如果想到其实最终利润是可以分解的，那么本题就很容易了！

**如何分解呢？**
> 分解的依据在于:"在同一天多次买卖该股票"

假如第 0 天买入，第 3 天卖出，那么利润为：prices[3] - prices[0]。

相当于(prices[3] - prices[2]) + (prices[2] - prices[1]) + (prices[1] - prices[0])。

此时就是把利润分解为每天为单位的维度，而不是从 0 天到第 3 天整体去考虑！

那么根据 prices 可以得到每天的利润序列：(prices[i] - prices[i - 1]).....(prices[1] - prices[0])。

注:第一天当然利润，至少要第二天才会有利润，所以利润的序列比股票序列少一天！

**那么只收集正利润就是贪心所贪的地方！**

局部最优：收集每天的正利润，全局最优：求得最大利润。

局部最优可以推出全局最优，找不出反例，试一试贪心！

```python
class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        
        n = len( prices )
        ans = 0

        for i in range( 1, n ):
            if prices[ i ] - prices[ i - 1 ] > 0:
                ans += prices[ i ] - prices[ i - 1 ]
        return ans
```

## [跳跃游戏](https://leetcode.cn/problems/jump-game/description/)

给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

```
提示：
1 <= nums.length <= pow( 10, 4 )
0 <= nums[i] <= pow( 10, 5 )
```

### 题解

```
示例 1：
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。

示例 2：
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
```

**代码详解**

这段代码的想法简单: 就是可达下标是否能够覆盖到整个数组;

- 贪心思想解释

每次移动取最大跳跃步数（得到最大的覆盖范围），每移动一个单位，就更新最大覆盖范围。

**贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点。**

局部最优推出全局最优，找不出反例，试试贪心！



```python
class Solution:
    def canJump(self, nums: list[int]) -> bool:

        maxIndex = 0
        curIndex = 0

        while curIndex <= maxIndex:
            maxIndex = max( maxIndex, curIndex + nums[ curIndex ] )
            curIndex += 1
            if maxIndex >= len( nums ) - 1: return True
        
        return False
```

## [跳跃游戏II](https://leetcode.cn/problems/jump-game-ii/description/)

给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。

每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：

* 0 <= j <= nums[i] 且
* i + j < n

返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。

```
提示：
1 <= nums.length <= pow( 10, 4 )
0 <= nums[i] <= 1000
题目保证可以到达 n - 1
```

### 题解

```
示例 1:
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

示例 2:
输入: nums = [2,3,0,1,4]
输出: 2
```

**代码详解**

- 贪心思想解释

```python

```
