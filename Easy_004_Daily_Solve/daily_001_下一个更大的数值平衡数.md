# [2048. 下一个更大的数值平衡数](https://leetcode.cn/problems/next-greater-numerically-balanced-number/)

[ -- 题目描述 -- ]

如果整数 x 满足：对于每个数位 d ，这个数位 恰好 在 x 中出现 d 次。那么整数 x 就是一个 数值平衡数 。

[ -- 测试用例 -- ]

```text
示例 1：
输入：n = 1
输出：22
解释：
22 是一个数值平衡数，因为：
- 数字 2 出现 2 次 
这也是严格大于 1 的最小数值平衡数。

示例 2：
输入：n = 1000
输出：1333
解释：
1333 是一个数值平衡数，因为：
- 数字 1 出现 1 次。
- 数字 3 出现 3 次。 
这也是严格大于 1000 的最小数值平衡数。
注意，1022 不能作为本输入的答案，因为数字 0 的出现次数超过了 0 。

示例 3：
输入：n = 3000
输出：3133
解释：
3133 是一个数值平衡数，因为：
- 数字 1 出现 1 次。
- 数字 3 出现 3 次。 
这也是严格大于 3000 的最小数值平衡数。
```

[ -- 提示说明 -- ]

0 <= n <= 106

[ -- 题目解答 -- ]

* 枚举法:
    * 从n+1开始枚举,判断每个数是否是数值平衡数;
    * 如果是,则返回该数;
    * 如果不是,则继续枚举;
* 关键点:
    * 枚举到哪个数?
        * 因为n的范围是[0, 10^6],所以枚举到10^7.

```python
class Solution:

  def isBalance( self, x ):
    # * 数据范围0~9
    times = [ 0 for _ in range( 10 ) ]

    while x > 0:
      times[ x % 10 ] += 1
      x //= 10

    for i, v in enumerate( times ):
      if 0 < v != i: return False
    return True

  def nextBeautifulNumber( self, n: int ) -> int:
    # * 对于本题的数据范围，一定存在十进制长为 len(n)+1 的数值平衡数。
    for i in range( n + 1, 10 ** 7 ):
      if self.isBalance( i ): return i
    return -1
```

* 如果数据范围变大( 数据范围扩大到 n≤10^18 ),怎么处理,才能不超时?

```python

    """
    待补充
    """
```



