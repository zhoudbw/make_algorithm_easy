--- Create Time: 2025-11-07 10:00:00
--- @Author: xcyy

# 最大化城市的最小电量

[2528. 最大化城市的最小电量](https://leetcode.cn/problems/maximize-the-minimum-powered-city/description/)

--- 题目描述 ---

给你一个下标从 0 开始长度为 n 的整数数组 stations ，其中 stations[i] 表示第 i 座城市的供电站数目。

每个供电站可以在一定 范围 内给所有城市提供电力。
换句话说，如果给定的范围是 r ，在城市 i 处的供电站可以给所有满足 |i - j| <= r 且 0 <= i, j <= n - 1 的城市 j 供电。

|x| 表示 x 的 绝对值 。比方说，|7 - 5| = 2 ，|3 - 10| = 7 。
一座城市的 电量 是所有能给它供电的供电站数目。

政府批准了可以额外建造 k 座供电站，你需要决定这些供电站分别应该建在哪里，这些供电站与已经存在的供电站有相同的供电范围。

给你两个整数 r 和 k ，如果以最优策略建造额外的发电站，返回所有城市中，最小电量的最大值是多少。

这 k 座供电站可以建在多个城市。

--- 测试用例 ---

```text
示例 1：
输入：stations = [1,2,4,5,0], r = 1, k = 2
输出：5
解释：
最优方案之一是把 2 座供电站都建在城市 1 。
每座城市的供电站数目分别为 [1,4,4,5,0] 。
- 城市 0 的供电站数目为 1 + 4 = 5 。
- 城市 1 的供电站数目为 1 + 4 + 4 = 9 。
- 城市 2 的供电站数目为 4 + 4 + 5 = 13 。
- 城市 3 的供电站数目为 5 + 4 = 9 。
- 城市 4 的供电站数目为 5 + 0 = 5 。
供电站数目最少是 5 。
无法得到更优解，所以我们返回 5 。

示例 2：
输入：stations = [4,4,4,4], r = 0, k = 3
输出：4
解释：
无论如何安排，总有一座城市的供电站数目是 4 ，所以最优解是 4 。
```

--- 说明提示 ---

```text
n == stations.length
1 <= n <= 10^5
0 <= stations[i] <= 10^5
0 <= r <= n - 1
0 <= k <= 10^9
```

--- 题目解答 ---

## 二分答案

**转化**

- 如果存在一种方案，可以让所有城市的电量都 ≥low，那么也可以 ≥low−1 或者更小的值（要求更宽松）。
- 如果不存在让所有城市的电量都 ≥low 的方案，那么也不存在 ≥low+1 或者更大的方案（要求更苛刻）。

据此，可以二分猜答案。

**现在问题转化成一个判定性问题：**

**给定 low，是否存在建造 k 座额外电站的方案，使得所有城市的电量都 ≥low？ 如果存在，说明答案 ≥low，否则答案 <low。**

---

由于已经建造的电站是可以发电的，我们需要在二分之前，用 stations 计算每个城市的初始电量 power。这可以用前缀和或者滑动窗口做.

然后从左到右遍历 power，挨个处理。
如果 power[i]<low，就需要建造电站，额外提供 low−power[i] 的电力。

**在哪建造电站最好呢？**

由于我们是从左到右遍历的，在 i 左侧的城市已经处理好了，所以建造的电站越靠右越好，尽可能多地覆盖没遍历到的城市。
具体地，i 应当恰好在电站供电范围的边缘上，也就是把电站建在 i+r 的位置，使得电站覆盖范围为 [i,i+2r]。

我们要建 m=low−power[i] 个供电站，也就是把下标在 [i,i+2r] 中的城市的电量都增加 m。
这里有一个「区间增加 m」的需求，用差分数组实现。
我们要一边做差分更新，一边计算差分数组的前缀和，以得到当前城市的实际电量。
遍历的同时，累计额外建造的电站数量，如果超过 k，不满足要求，可以提前跳出循环。

---
**细节**

下面代码采用开区间二分，这仅仅是二分的一种写法，使用闭区间或者半闭半开区间都是可以的，喜欢哪种写法就用哪种。

**确定二分left和right**

**开区间左端点初始值：min(power)+⌊n / k⌋。**
把 k 均摊，即使 r=0，每个城市都能至少分到 ⌊n / k⌋ 的额外电量，所以 low=min(power)+⌊n / k⌋ 时一定满足要求。

开区间右端点初始值：min(power)+k+1。即使把所有额外电站都建给电量最小的城市，也无法满足要求。

> 对于开区间写法，简单来说 check(mid) == true 时更新的是谁，最后就返回谁。
> 相比其他二分写法，开区间写法不需要思考加一减一等细节，更简单。推荐使用开区间写二分。

最大化最小值 = 有单调性，二分查找
离线单点修改区间求和 = 差分数组
在线单点修改区间求和 = 线段树/树状数组
这些模板都好说，二分查找的关键还在于快速出一个合理的上下界(left & right)来减少二分次数，这个是本题格外值得思考的地方

### 前缀和

能覆盖城市 i 的电站下标范围是 [i−r,i+r]。注意下标不能越界，所以实际范围是 [max(i−r,0),min(i+r,n−1)]。

我们需要计算 stations 的这个范围（子数组）的和。

计算 stations 的 前缀和 数组后，可以 O(1) 计算 stations 的任意子数组的和。

```python
class Solution:
    def maxPower( self, stations: List[ int ], r: int, k: int ) -> int:
        n = len( stations )
        # 前缀和
        s = list( accumulate( stations, initial = 0 ) )
        # 初始电量
        power = [ s[ min( i + r + 1, n ) ] - s[ max( i - r, 0 ) ] for i in range( n ) ]

        def check( low: int ) -> bool:
            diff = [ 0 ] * n  # 差分数组
            sum_d = built = 0
            for i, p in enumerate( power ):
                sum_d += diff[ i ]  # 累加差分值
                m = low - (p + sum_d)
                if m <= 0:
                    continue
                # 需要在 i+r 额外建造 m 个供电站
                built += m
                if built > k:  # 不满足要求
                    return False
                # 把区间 [i, i+2r] 加一
                sum_d += m  # 由于 diff[i] 后面不会再访问，我们直接加到 sum_d 中
                if (right := i + r * 2 + 1) < n:
                    diff[ right ] -= m
            return True

        # 开区间二分
        mn = min( power )
        left, right = mn + k // n, mn + k + 1
        while left + 1 < right:
            mid = (left + right) // 2
            if check( mid ):
                left = mid
            else:
                right = mid
        return left
```

### 滑动窗口

```python
class Solution:
    def maxPower( self, stations: List[ int ], r: int, k: int ) -> int:
        n = len( stations )
        # 滑动窗口
        s = sum( stations[ :r ] )  # 先计算 [0, r-1] 的发电量，为第一个窗口做准备
        power = [ 0 ] * n
        for i in range( n ):
            # 右边进
            if (right := i + r) < n:
                s += stations[ right ]
            # 左边出
            if (left := i - r - 1) >= 0:
                s -= stations[ left ]
            power[ i ] = s

        def check( low: int ) -> bool:
            diff = [ 0 ] * n  # 差分数组
            sum_d = built = 0
            for i, p in enumerate( power ):
                sum_d += diff[ i ]  # 累加差分值
                m = low - (p + sum_d)
                if m <= 0:
                    continue
                # 需要在 i+r 额外建造 m 个供电站
                built += m
                if built > k:  # 不满足要求
                    return False
                # 把区间 [i, i+2r] 加一
                sum_d += m  # 由于 diff[i] 后面不会再访问，我们直接加到 sum_d 中
                if (right := i + r * 2 + 1) < n:
                    diff[ right ] -= m
            return True

        # 开区间二分
        mn = min( power )
        left, right = mn + k // n, mn + k + 1
        while left + 1 < right:
            mid = (left + right) // 2
            if check( mid ):
                left = mid
            else:
                right = mid
        return left
```