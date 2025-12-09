--- Create Time: 2025-11-21 10:00:00
--- @Author: xcyy

# 1930. 长度为 3 的不同回文子序列

[1930. 长度为 3 的不同回文子序列](https://leetcode.cn/problems/unique-length-3-palindromic-subsequences/description/)

--- 题目描述 ---

给你一个字符串 s ，返回 s 中 长度为 3 的不同回文子序列 的个数。

即便存在多种方法来构建相同的子序列，但相同的子序列只计数一次。

回文 是正着读和反着读一样的字符串。

子序列 是由原字符串删除其中部分字符（也可以不删除）且不改变剩余字符之间相对顺序形成的一个新字符串。

例如，"ace" 是 "abcde" 的一个子序列。

--- 测试用例 ---

```text
示例 1：
输入：s = "aabca"
输出：3
解释：长度为 3 的 3 个回文子序列分别是：
- "aba" ("aabca" 的子序列)
- "aaa" ("aabca" 的子序列)
- "aca" ("aabca" 的子序列)

示例 2：
输入：s = "adc"
输出：0
解释："adc" 不存在长度为 3 的回文子序列。

示例 3：
输入：s = "bbcbaba"
输出：4
解释：长度为 3 的 4 个回文子序列分别是：
- "bbb" ("bbcbaba" 的子序列)
- "bcb" ("bbcbaba" 的子序列)
- "bab" ("bbcbaba" 的子序列)
- "aba" ("bbcbaba" 的子序列)
```

--- 说明提示 ---

```text
3 <= s.length <= 10^5
s 仅由小写英文字母组成
```

--- 题目解答 ---

本题要找长为 3 的回文子序列，这要求子序列的第一个字母等于第三个字母。

换句话说，确定了子序列的前两个字母，就确定了子序列。

这引出了两类做法：

- 先枚举两侧的字母，再枚举中间的字母。
- 先枚举中间的字母，再枚举两侧的字母。

## 方法1: 枚举两侧

算法：

- 枚举 alpha = { a, b, …, z } ;

- 找 alpha元素 在 s 中首次出现的下标 i 和最后一次出现的下标 j。
    - 如果没有这样的下标，回到第一步继续枚举。

- 下标在 [i+1,j−1] 中的字母，可以作为回文子序列的中间字母。

- 相同的子序列只计数一次。可以用哈希集合去重，也可以用长为 26 的布尔数组记录遇到过的中间字母，避免重复统计。

```python
from string import ascii_lowercase


class Solution:
    def countPalindromicSubsequence( self, s: str ) -> int:

        count = 0

        for x in ascii_lowercase:
            i = s.find( x )
            if i < 0: continue

            j = s.rfind( x )
            count += len( set( s[ i + 1: j ] ) )

        return count
```

## 方法2: 枚举中间

枚举 i = 1, 2, …, n−2，把 s[i] 当作子序列的第二个字母，那么对于第一、三个字母要判断：

- s 的前缀 [0,i−1] 中有没有 α？
- s 的后缀 [i+1,n−1] 中有没有 α？

可以先遍历 s，统计 s 中每个字母的个数，然后再从左到右遍历 s，把 s[i] 的个数减一，就得到了后缀 [i+1,n−1] 每个字母的个数。

对于前缀 [0,i−1]，在从左到右遍历 s 的同时，记录遇到了哪些字母。

```python
from collections import defaultdict
from string import ascii_lowercase


class Solution:
    def countPalindromicSubsequence( self, s: str ) -> int:

        rig_counts = defaultdict( int )
        lef_counts = defaultdict( int )

        n = len( s )

        for i in range( 1, n ):
            rig_counts[ s[ i ] ] += 1

        st = set()
        for i in range( 1, n - 1 ):
            rig_counts[ s[ i ] ] -= 1
            lef_counts[ s[ i - 1 ] ] += 1

            # 判断 i 左右两侧是否存在相同字母
            for x in ascii_lowercase:
                if rig_counts[ x ] > 0 and lef_counts[ x ] > 0: st.add( x + s[ i ] )

        return len( st )
```
