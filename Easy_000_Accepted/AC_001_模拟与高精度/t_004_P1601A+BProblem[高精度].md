# P1601 A+B Problem（高精）

## 题目描述

-- 题目描述 --

高精度加法，相当于 a+b problem，不用考虑负数。

-- 输入格式 --

分两行输入。a,b≤10^500 。

-- 输出格式 --

输出只有一行，代表 a+b 的值。

-- 测试用例 --

```
测试用例1输入
1
1
测试用例1输出
2
------
测试用例2输入
1001
9099
测试用例2输出
10100
```

## 题目解答

- 模板题:高精度都按照这个方式来写
- 代码中设置了carry表示进位;cur_index表示当前相加位;
    - 如果cur_index在某个数字中已经越界,则默认该数字该位位0;
    - 最后如果carry>0,则需要在结果前添加carry;
- 方法二补充: 位数较少的数字,补充前导0,使两个数字位数相同,然后再逐位进行加法运算;

```python

a = list( input()[ ::-1 ] )
b = list( input()[ ::-1 ] )
a_size = len( a ); b_size = len( b )

ans = ""
carry = 0
cur_index = 0

while cur_index < a_size or cur_index < b_size:
    a_bit, b_bit = 0, 0
    if cur_index < a_size: a_bit = int( a[ cur_index ] )
    if cur_index < b_size: b_bit = int( b[ cur_index ] )

    bit_sum = a_bit + b_bit + carry

    ans = str( bit_sum % 10 ) + ans
    carry = bit_sum // 10
    cur_index += 1

if carry > 0:
    ans = str( carry ) + ans
    carry = 0

print( ans )
```
