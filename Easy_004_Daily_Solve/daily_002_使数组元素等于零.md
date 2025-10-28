# [3354. 使数组元素等于零](https://leetcode.cn/problems/number-of-laser-beams-in-a-bank/description/)

[ -- 题目描述 -- ]

给你一个整数数组 nums 。

开始时，选择一个满足 nums[curr] == 0 的起始位置 curr ，并选择一个移动 方向 ：向左或者向右。

此后，你需要重复下面的过程：

* 如果 curr 超过范围 [0, n - 1] ，过程结束。
* 如果 nums[curr] == 0 ，沿当前方向继续移动：如果向右移，则 递增 curr ；如果向左移，则 递减 curr 。
* 如果 nums[curr] > 0:
    * 将 nums[curr] 减 1 。
    * 反转 移动方向（向左变向右，反之亦然）。
    * 沿新方向移动一步。

如果在结束整个过程后，nums 中的所有元素都变为 0 ，则认为选出的初始位置和移动方向 有效 。

返回可能的有效选择方案数目。

[ -- 测试用例 -- ]

```text

示例 1：
输入：nums = [1,0,2,0,3]
输出：2
解释：
可能的有效选择方案如下：
选择 curr = 3 并向左移动。
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] -> 
[1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] -> 
[1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> 
[0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,0].
选择 curr = 3 并向右移动。
[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] -> 
[1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] -> 
[1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].

示例 2：
输入：nums = [2,3,4,0,4,1,0]
输出：0
解释：
不存在有效的选择方案。
```

[ -- 提示说明 -- ]

```
1 <= nums.length <= 100
0 <= nums[i] <= 100
至少存在一个元素 i 满足 nums[i] == 0 。
```

[ -- 题目解答 -- ]

* 模拟

```python
class Solution:
    def countValidSelections( self, nums: List[ int ] ) -> int:

        def simulation( bak_nums, curr, direction ):
            n = len( bak_nums )
            # ** 注意数组边界:判断完边界后,
            # ** 内部尽量不要做下标操作后应用新的下标
            while 0 <= curr < n:
                if bak_nums[ curr ] > 0:
                    bak_nums[ curr ] -= 1
                    direction *= -1
                curr += direction
            return sum( bak_nums ) == 0 and 1 or 0

        kinds = 0

        for i, v in enumerate( nums ):
            if v == 0:
                kinds += simulation( nums[ :: ], i, 1 )
                kinds += simulation( nums[ :: ], i, -1 )

        return kinds
```

* 前缀和

本题可以视作一个「小球打砖块」游戏，

每打掉一个砖块，小球的移动方向就要反向，所以要想打掉所有砖块，**起始位置左右的砖块个数之差不能超过 1。**

设整个数组的元素和为 total。遍历数组的同时，维护前缀和 pre。

如果 nums[i]=0，那么这个位置可以是起始位置吗？分类讨论：

- 如果前缀和 pre 等于后缀和 total−pre，那么小球初始方向可以向左，也可以向右，答案加 2。
- 如果前缀和比后缀和多 1，那么小球初始方向必须向左，才能打掉所有砖块，答案加 1。
- 如果前缀和比后缀和少 1，那么小球初始方向必须向右，才能打掉所有砖块，答案加 1。
- 其余情况，不能是起始位置。

```python
class Solution:
    def countValidSelections( self, nums: List[ int ] ) -> int:

        kinds = 0

        pre = 0;
        total = sum( nums )

        for v in nums:
            if v:
                pre += v
            else:
                if pre == total - pre: kinds += 2
                if abs( total - 2 * pre ) == 1: kinds += 1

        return kinds
```

