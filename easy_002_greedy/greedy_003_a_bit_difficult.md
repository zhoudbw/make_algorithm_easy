# 贪心算法

## 大纲

- 题目: [加油站](https://leetcode.cn/problems/gas-station/description/)
- 题目: [分发糖果](https://leetcode.cn/problems/candy/description/)
- 题目: [根据身高重建队列](https://leetcode.cn/problems/queue-reconstruction-by-height/description/)

## [加油站](https://leetcode.cn/problems/gas-station/description/)

在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。

--提示--
```
n == gas.length == cost.length
1 <= n <= pow( 10, 5 )
0 <= gas[i], cost[i] <= pow( 10, 4 )
输入保证答案唯一。
```

--示例--
```
示例 1:
输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。

示例 2:
输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。
```

## 题解

暴力方法很明显就是O(n^2)的，遍历每一个加油站为起点的情况，模拟一圈。

> for循环适合模拟从头到尾的遍历，而while循环适合模拟环形遍历.

* 如果总油量大于等于总消耗，那么一定可以跑完一圈。
* 如果总油量小于总消耗，那么一定不能跑完一圈。
* 计算每站的剩余油量rest:
  * 从0开始累加rest[i]，和记为curSum，一旦curSum小于0，说明[0, i]区间都不能作为起始位置，
  * 因为这个区间选择任何一个位置作为起点，到i这里都会断油，那么起始位置从i+1算起，再从0计算curSum。

- 贪心思想解释 
  * 局部最优：当前累加rest[i]的和curSum一旦小于0，起始位置至少要是i+1，因为从i之前开始一定不行。
  * 全局最优：找到可以跑一圈的起始位置。

局部最优可以推出全局最优，找不出反例，试试贪心！

```python
class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:

        if sum( cost ) > sum( gas ): return -1

        n = len( gas )
        rest = [ ( gas[ i ] - cost[ i ] ) for i in range( n ) ]

        start_index = 0

        while start_index < n:

            transfer_count = 0
            left_gas = 0
            while transfer_count == 0 or ( start_index + transfer_count ) % n != start_index:
                left_gas += rest[ ( start_index + transfer_count ) % n ]
                transfer_count += 1
                if left_gas < 0: 
                    start_index = start_index + transfer_count
                    break

            else: return start_index
        else: return -1
```


## [分发糖果](https://leetcode.cn/problems/candy/description/)


## [根据身高重建队列](https://leetcode.cn/problems/queue-reconstruction-by-height/description/)