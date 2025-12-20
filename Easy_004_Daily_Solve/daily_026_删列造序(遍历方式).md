--- Create Time: 2025-12-20 14:00:00
--- @Author: xcyy

# 944. 删列造序

[944. 删列造序](https://leetcode.cn/problems/delete-columns-to-make-sorted/description/)

--- 题目描述 ---

给你由 n 个小写字母字符串组成的数组 strs，其中每个字符串长度相等。

这些字符串可以每个一行，排成一个网格。例如，strs = ["abc", "bce", "cae"] 可以排列为：
abc
bce
cae

你需要找出并删除 不是按字典序非严格递增排列的 列。
在上面的例子（下标从 0 开始）中，列 0（'a', 'b', 'c'）和列 2（'c', 'e', 'e'）都是按字典序非严格递增排列的，
而列 1（'b', 'c', 'a'）不是，所以要删除列 1 。

返回你需要删除的列数。

--- 测试用例 ---

```
示例 1：
输入：strs = ["cba","daf","ghi"]
输出：1
解释：网格示意如下：
  cba
  daf
  ghi
列 0 和列 2 按升序排列，但列 1 不是，所以只需要删除列 1 。

示例 2：
输入：strs = ["a","b"]
输出：0
解释：网格示意如下：
  a
  b
只有列 0 这一列，且已经按升序排列，所以不用删除任何列。
```

--- 说明提示 ---

```
n == strs.length
1 <= n <= 100
1 <= strs[i].length <= 1000
strs[i] 由小写英文字母组成
```

--- 题目解答 ---

**写法1**

```python
from typing import List


class Solution:
    def minDeletionSize( self, strs: List[ str ] ) -> int:
        row, col = len( strs ), len( strs[ 0 ] )

        ans = 0
        for i in range( 0, col ):
            for j in range( 1, row ):
                if strs[ j - 1 ][ i ] > strs[ j ][ i ]:
                    ans += 1
                    break
        return ans
```

**写法2**

```python
from typing import List
from itertools import pairwise


class Solution:
    def minDeletionSize( self, strs: List[ str ] ) -> int:
        ans = 0
        for col in zip( *strs ):
            if any( x > y for x, y in pairwise( col ) ):
                ans += 1
        return ans
```

工作原理:

使用 zip(*strs) 对输入数组进行转置：例如，若 strs = ["abc", "bce", "cae"]，
则 zip(*strs) 会生成 ('a','b','c'), ('b','c','a'), ('c','e','e')，每个元组对应原数组的一列。

使用 **pairwise(col)生成列中连续的字符对**（如 (col[0], col[1]), (col[1], col[2]), ...）。

any(x > y for x, y in pairwise(col)) 检查该列是否存在任意一对字符无序（即 x > y）：
若存在，则该列需删除，ans 加 1。

**注**

- *strs 是一个解包操作，将 strs 中的每个元素（这里是字符串）解包为单独的参数传递给 zip 函数。

```
strs = ["abc", "bce", "cae"]
那么对应的*strs 就等价于 "abc", "bce", "cae"
```

- zip 示例:

```
>>> a = [1,2,3]
>>> b = [4,5,6]
>>> c = [4,5,6,7,8]
>>> zipped = zip(a,b)     # 返回一个对象
>>> zipped
<zip object at 0x103abc288>
>>> list(zipped)  # list() 转换为列表
[(1, 4), (2, 5), (3, 6)]
>>> list(zip(a,c))              # 元素个数与最短的列表一致
[(1, 4), (2, 5), (3, 6)]

>>> a1, a2 = zip(*zip(a,b))          # 与 zip 相反，zip(*) 可理解为解压，返回二维矩阵式
>>> list(a1)
[1, 2, 3]
>>> list(a2)
[4, 5, 6]
>>>
```

**写法3**

```python
from typing import List


class Solution:
    def minDeletionSize( self, strs: List[ str ] ) -> int:
        ans = 0
        for col in zip( *strs ):
            if list( col ) != sorted( col ):
                ans += 1
        return ans
```

- 时间复杂度：O(n * m)，其中 n 是数组 strs 的长度，m 是每个字符串的长度。
- 空间复杂度：O(1)

