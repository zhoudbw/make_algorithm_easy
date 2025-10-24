# P1303 A*B Problem

## 题目描述

-- 题目描述 --

高精度乘法模板题。

给出两个非负整数，求它们的乘积。

-- 输入格式 --

输入共两行，每行一个非负整数。

-- 输出格式 --

输出一个非负整数表示乘积。

-- 测试用例 --

```
测试用例1输入
1
2
测试用例1输出
2
```

-- 提示 --
每个非负整数不超过 10^2000。

## 题目解答

* strip()作用是 去除字符串两端（前后）的指定字符，默认为空格字符。
    * 如果你没有传递任何参数，strip() 会删除字符串开头和结尾的所有空白字符，包括空格、换行符、制表符等。

* 解决问题,最好写成函数的形式,这样方便在想要停止的地方return停止;
  * 在本题的测试用例中,需要判断a或b是否为0,如果是0,则直接输出0,不需要进行乘法运算;
  * 如果没有及时return,则会超时;

* 模拟乘法:
    * 从后往前,模拟乘法,记录每一位的结果,最后再处理进位;
    * 输出结果时,需要去除前导0;

```python
import sys

def main():

    data = sys.stdin.read().split()
    if not data: return

    a = data[ 0 ]; b = data[ 1 ]
    if a == "0" or b == "0": print( "0" ); return

    a_size = len( a ); b_size = len( b )

    # * 乘积不会超过两个乘数的长度
    ans = [ 0 for _ in range( a_size + b_size ) ]

    # * 模拟乘法
    for i in range( a_size - 1, -1, -1 ):
        a_val = int( a[ i ] )

        for j in range( b_size - 1, -1, -1 ):
            b_val = int( b[ j ] )
            mul_val = a_val * b_val

            # * 数位和进位
            bit_index = i + j + 1; carry_index = i + j

            total = ans[ bit_index ] + mul_val
            ans[ bit_index ] = total % 10
            ans[ carry_index ] += total // 10

    # * 去除前导0
    print( "".join( str( x ) for x in ans ).lstrip( "0" ) or "0" )

main()
```
