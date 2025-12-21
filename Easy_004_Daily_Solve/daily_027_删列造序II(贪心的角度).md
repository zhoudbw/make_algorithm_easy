--- Create Time: 2025-12-20 12:00:00
--- @Author: xcyy

# 955. 删列造序II

[955. 删列造序II](https://leetcode.cn/problems/delete-columns-to-make-sorted-ii/description/)

--- 题目描述 ---

给定由 n 个字符串组成的数组 strs，其中每个字符串长度相等。

选取一个删除索引序列，对于 strs 中的每--- Create Time: 2025-12-20 12:00:00
--- @Author: xcyy

# 955. 删列造序II

[955. 删列造序II](https://leetcode.cn/problems/delete-columns-to-make-sorted-ii/description/)

--- 题目描述 ---

给定由 n 个字符串组成的数组 strs，其中每个字符串长度相等。

选取一个删除索引序列，对于 strs 中的每个字符串，删除对应每个索引处的字符。

比如，有 strs = ["abcdef", "uvwxyz"]，删除索引序列 {0, 2, 3}，删除后 strs 为["bef", "vyz"]。

假设，我们选择了一组删除索引 answer，那么在执行删除操作之后，
最终得到的数组的元素是按 字典序（strs[0] <= strs[1] <= strs[2] ... <= strs[n - 1]）排列的，
然后请你返回 answer.length 的最小可能值。

--- 测试用例 ---

```
示例 1：
输入：strs = ["ca","bb","ac"]
输出：1
解释： 
删除第一列后，strs = ["a", "b", "c"]。
现在 strs 中元素是按字典排列的 (即，strs[0] <= strs[1] <= strs[2])。
我们至少需要进行 1 次删除，因为最初 strs 不是按字典序排列的，所以答案是 1。

示例 2：
输入：strs = ["xc","yb","za"]
输出：0
解释：
strs 的列已经是按字典序排列了，所以我们不需要删除任何东西。
注意 strs 的行不需要按字典序排列。
也就是说，strs[0][0] <= strs[0][1] <= ... 不一定成立。

示例 3：
输入：strs = ["zyx","wvu","tsr"]
输出：3
解释：
我们必须删掉每一列。
```

--- 说明提示 ---

```
n == strs.length
1 <= n <= 100
1 <= strs[i].length <= 100
strs[i] 由小写英文字母组成
```

--- 题目解答 ---

**分析**

举例: strs = [ "ada", "acc", "bad", "bba""], 竖着看,

```
    ada
    acc
    bad
    bba
```

第1列是有序的,可以不删. 讨论:

- 若删除第1列: 需要完整比较第2列所有元素,保证其有序;
- 若不删第1列: 对于第二列，
    - 由于d和a前面的字母不同,只看第1列的字母就能确定ad<ba，所以不需要比较d和a大小。
    - 此时第2列分成了两组 [c,d] 和 [a,b]，只需判断组内字母是不是升序，而不是完整地比较第2列的四个字母。

综上, 当列已经是升序时,不删除更好,后面需要比较的字母更少,更容易满足要求,最终删的列更少.
如果列不是升序，那么一定要删（否则最终得到的数组不是字典序排列）。

* 注: 字符串的字典序: 即每位按照字母表顺序排列的先后 a < b, ad < bb, acg < adf

```python
from typing import List


class Solution:
    def minDeletionSize( self, strs: List[ str ] ) -> int:

        m, n = len( strs ), len( strs[ 0 ] )

        a = [ '' for _ in range( m ) ]  # 最终得到的字符串数组

        ans = 0

        for j in range( n ):
            for i in range( m - 1 ):
                # + 字符串拼接
                if a[ i ] + strs[ i ][ j ] > a[ i + 1 ] + strs[ i + 1 ][ j ]:
                    # j 列 不是升序, 删除
                    ans += 1
                    break
            else:
                # j 列 是升序, 不删更好
                for i, s in enumerate( strs ): a[ i ] += s[ j ]

        return ans
```

- 时间复杂度：O(nm^2)，其中 n 是 strs 的长度，m 是 strs[i] 的长度。比较 O(nm) 次大小，每次 O(m)。
- 空间复杂度：O(nm)。

**优化**

```
    ada
    acc
    bad
    bba
```

第1列升序，不删。

由于 strs[1][0]<strs[2][0]，后续 a[1]<a[2] 必定成立，所以不需要比较这两个字符串。

对于其余相邻字符串来说，**由于第1列的字母都一样，所以只需比较第2列的字母**，无需比较整个字符串。

怎么维护需要比较的下标（行号）呢？

- 可以用哈希集合，或者布尔数组，或者创建一个下标列表，删除列表中的无需比较的下标 。
- 最后一种方法最高效，我们可以用 27. 移除元素 的方法，原地删除无需比较的下标, 见代码.

```python
from typing import List


class Solution:
    def minDeletionSize( self, strs: List[ str ] ) -> int:

        # m 行 n 列
        m, n = len( strs ), len( strs[ 0 ] )

        # 需要比较的行号
        check_rows = list( range( m - 1 ) )

        ans = 0
        for j in range( n ):
            for i in check_rows:
                if strs[ i ][ j ] > strs[ i + 1 ][ j ]:
                    # j 列 无序
                    ans += 1
                    break
            else:
                # j 列有序
                new_size = 0
                # 列元素相同的行, 需要再次比较
                for i in check_rows:
                    if strs[ i ][ j ] == strs[ i + 1 ][ j ]:
                        check_rows[ new_size ] = i
                        new_size += 1
                del check_rows[ new_size: ]

        return ans

```






