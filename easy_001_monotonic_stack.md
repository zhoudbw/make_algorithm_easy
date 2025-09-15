
# 单调栈

## [每日温度](https://leetcode.cn/problems/daily-temperatures/description/)

> 给定一个整数数组 temperatures，表示每天的温度，返回一个数组 answer，      </br>
> 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

> 提示：</br>
> 1 <= temperatures.length <= pow( 10, 5 ) </br>
> 30 <= temperatures[i] <= 100

暴力解法: 两层for循环，把至少需要等待的天数搜出来。时间复杂度是O(n^2)

**单调栈: 栈内元素保持单调递增或递减的栈**
* 栈头到栈底的元素，对应的温度从栈头到栈底递减，我们就可以保持栈的递减性，
* 当遇到温度更高的元素时，就可以弹出栈头的元素，计算弹出元素的下标差，就是至少需要等待的天数。

```
示例:
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
```
```python
##--- python ---##
class Solution(object):
    def dailyTemperatures(self, temperatures):
        """
        :type temperatures: List[int]
        :rtype: List[int]
        """
        n = len( temperatures )
        ans = [ 0 for _ in range( n ) ]

        stk = []
        for i in range( n ):
            while stk and temperatures[ i ] > temperatures[ stk[ -1 ] ]: 
                x = stk.pop(); ans[ x ] = i - x
            stk.append( i )
        return ans
```
