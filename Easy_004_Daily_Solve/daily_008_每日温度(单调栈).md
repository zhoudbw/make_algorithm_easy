--- Create Time: 2025-11-09 10:00:00
--- @Author: xcyy

# 每日温度

[739. 每日温度](https://leetcode.cn/problems/daily-temperatures/description/)

--- 题目描述 ---

给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i
天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

--- 测试用例 ---

```text
示例 1:
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]

示例 2:
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]

示例 3:
输入: temperatures = [30,60,90]
输出: [1,1,0]
```

--- 说明提示 ---

```text
1 <= temperatures.length <= 10^5
30 <= temperatures[i] <= 100
```

--- 题目解答 ---

```python
class Solution:
    def dailyTemperatures( self, temperatures: List[ int ] ) -> List[ int ]:
        # -- 单调栈 --
        # -- 求下一个更高温度,要保证栈内温度是是按照从栈头到栈顶递减的 --

        n = len( temperatures )

        mono_stk = [ ]

        answer = [ 0 for _ in range( n ) ]

        for i, v in enumerate( temperatures ):
            if not mono_stk or v <= temperatures[ mono_stk[ -1 ] ]:
                mono_stk.append( i )
            else:
                while mono_stk and v > temperatures[ mono_stk[ -1 ] ]:
                    day = mono_stk.pop()
                    answer[ day ] = i - day
                mono_stk.append( i )
        return answer
```