# [2466. 统计构造好字符串的方案数](https://leetcode.cn/problems/count-ways-to-build-good-strings/description/

[ -- 题目描述 -- ]

给你整数 zero ，one ，low 和 high ，我们从空字符串开始构造一个字符串，每一步执行下面操作中的一种：

- 将 '0' 在字符串末尾添加 zero 次。
- 将 '1' 在字符串末尾添加 one 次。
- 以上操作可以执行任意次。

如果通过以上过程得到一个 长度 在 low 和 high 之间（包含上下边界）的字符串，那么这个字符串我们称为 好 字符串。

请你返回满足以上要求的 不同 好字符串数目。由于答案可能很大，请将结果对 109 + 7 取余 后返回。

[ -- 测试用例 -- ]

```text
示例 1：
输入：low = 3, high = 3, zero = 1, one = 1
输出：8
解释：
一个可能的好字符串是 "011" 。
可以这样构造得到："" -> "0" -> "01" -> "011" 。
从 "000" 到 "111" 之间所有的二进制字符串都是好字符串。

示例 2：
输入：low = 2, high = 3, zero = 1, one = 2
输出：5
解释：好字符串为 "00" ，"11" ，"000" ，"110" 和 "011" 。
```

![测试用例1图示](Assets/daily_002_01_eg.png)

[ -- 提示说明 -- ]

```
1 <= low <= high <= 10^5
1 <= zero, one <= low
```

[ -- 题目解答 -- ]

* 方法1: 背包问题

```
# -- 背包问题 --
# 任取若干个zero和one,装满容量为low~high容量的背包

# dp[ v ][ i ]表示0~i装满v的组装数 -- 排列问题
# dp[ v ][ i ] = dp[ v ][ i - 1 ] + dp[ v - nums[ i ] ][ n ]
# 需要保证dp[ v - nums[ i ] ][ n ]: 外循环容量;内循环物品
```

```python
class Solution:
    def countGoodStrings( self, low: int, high: int, zero: int, one: int ) -> int:

        nums = [ zero, one ]
        n = len( nums )
        MOD = 10 ** 9 + 7

        dp = [ [ 0 for _ in range( n ) ] for _ in range( high + 1 ) ]

        for i in range( n ): dp[ 0 ][ i ] = 1

        for v in range( 1, high + 1 ):
            for i in range( n ):
                if i > 0: dp[ v ][ i ] = dp[ v ][ i - 1 ] % MOD
                if v >= nums[ i ]: dp[ v ][ i ] += dp[ v - nums[ i ] ][ n - 1 ] % MOD

        kinds = 0
        for i in range( low, high + 1 ):
            kinds = (kinds + dp[ i ][ n - 1 ]) % MOD

        return kinds
```

背包问题中排列,其实用一维数组更容易写;

```python
class Solution:
    def countGoodStrings( self, low: int, high: int, zero: int, one: int ) -> int:
        MOD = 10 ** 9 + 7

        # dp[i] 表示构造长度为i的字符串的方法数
        dp = [ 0 ] * (high + 1)
        dp[ 0 ] = 1  # 空字符串有1种方法

        for i in range( 1, high + 1 ):
            # 可以在末尾添加 '0' * zero
            if i >= zero:
                dp[ i ] = (dp[ i ] + dp[ i - zero ]) % MOD
            # 可以在末尾添加 '1' * one  
            if i >= one:
                dp[ i ] = (dp[ i ] + dp[ i - one ]) % MOD

        # 累加 low 到 high 的结果
        result = 0
        for i in range( low, high + 1 ):
            result = (result + dp[ i ]) % MOD

        return result

```

* 方法2: 爬楼梯

利用背包模型,反而是复杂了,**爬楼梯**更直接;

```
这实际上是一个爬楼梯问题的变种：

每次可以爬 zero 阶或 one 阶

求爬到 low 到 high 阶的方案数
```

```python
class Solution:
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:

        MOD = 10 ** 9 + 7

        # dp[ i ]表示跳到i阶的种类数

        dp = [ 0 for _ in range( high + 1 ) ]

        dp[ 0 ] = 1

        kinds = 0
        for i in range( 1, high + 1 ):

            if i >= zero: dp[ i ] = ( dp[ i ] + dp[ i - zero ] ) % MOD
            if i >= one: dp[ i ] = ( dp[ i ] +  dp[ i - one ] ) % MOD
            if i >= low: kinds = ( kinds + dp[ i ] ) % MOD
        return kinds
```

