# 输入和输出

## 基础输入输出方法

1. 基本输入函数

- data = input() # 读取一行输入，返回字符串
- name = input("请输入你的名字: ") # 带提示信息的输入

2. 基本输出函数

- print("Hello, World!")
- print("a =", a, "b =", b) # 输出多个值，默认用空格分隔
- print("2023", "10", "15", sep="-")  # 输出: 2023-10-15  **自定义分隔符**
- print("Hello", end=" ")  # 不换行,用空格结束  **自定义结束符**

## 刷题常用输入模式

模式1：单行单个数据

- n = int(input())  # 整数
- x = float(input()) # 浮点数
- s = input().strip()  # 字符串 ( 推荐使用strip()去除首尾空格 )

模式2：单行多个数据

- a, b, c = map(int, input().split())  # 使用map
- arr = [int(x) for x in input().split()]  # 使用列表推导式
- 已知数量,直接解包
    - a, b = input().split()  # 直接解包（已知数量）
    - a, b = int(a), int(b)

模式3：多行输入（已知行数）

```python
# 方法1：先读第一行获取数据数量, 然后读取n行数据
n = int( input() )
data = [ ]
for i in range( n ):
    data.append( input().strip() )

# 方法2：使用列表推导式
n = int( input() )
data = [ input().strip() for _ in range( n ) ]
```

模式4：多行输入（直到文件结束）

```python
import sys

# 使用sys.stdin.readlines()
lines = sys.stdin.readlines()
for line in lines:
    data = line.strip().split()
```

## 实际刷题示例

示例1：A+B

```python
# 推荐写法
data = input().split()
a, b = int( data[ 0 ] ), int( data[ 1 ] )
print( a + b )

# 更简洁的写法
a, b = map( int, input().split() )
print( a + b )
```

示例2：数组求和

```python
# 输入：第一行是n，第二行是n个整数
# 输出：这n个数的和
n = int( input() )
arr = list( map( int, input().split() ) )
print( sum( arr ) )
```

示例3：矩阵输入

```python
# 输入：第一行是n和m，接下来n行每行m个整数
n, m = map( int, input().split() )
matrix = [ ]
for i in range( n ):
    row = list( map( int, input().split() ) )
    matrix.append( row )

# 输出矩阵
for row in matrix:
    print( ' '.join( map( str, row ) ) )
```

## **⚡ 性能优化技巧**

1. 使用sys.stdin提高读取速度

```python
import sys

# 对于大数据量输入，这比input()快很多
data = sys.stdin.read().splitlines()

# 或者逐行读取
for line in sys.stdin:
    # 处理逻辑
    pass
```

2. 批量输出减少IO操作

```python
result_list = [ ]
n = len( result_list )

# 不推荐的写法（多次输出）
for num in result_list:
    print( num )

# 推荐的写法（一次输出）
print( '\n'.join( map( str, result_list ) ) )

```

## **🛠️ 实用工具函数**

```python
def read_ints():
    """读取一行整数"""
    return list( map( int, input().split() ) )


def read_matrix( rows ):
    """读取矩阵"""
    return [ list( map( int, input().split() ) ) for _ in range( rows ) ]


def print_array( arr, sep = ' ' ):
    """格式化输出数组"""
    print( sep.join( map( str, arr ) ) )


def fast_input():
    """快速输入（适用于大数据量）"""
    import sys
    return sys.stdin.read().splitlines()
```

## **🎯 最佳实践总结**

1. 始终使用 .strip() 处理输入，避免空格问题
2. 明确数据类型，及时使用 int(), float() 转换
3. 对于已知数量的输入，使用解包操作
4. 对于未知数量的输入，使用列表收集
5. 大数据量时，考虑使用 sys.stdin
6. 多次输出时，尽量批量处理减少IO次数
7. 注意空行处理

## ❌ 常见错误避免

```python
# 错误：直接对input()结果进行split
a, b = input().split()  # 如果输入只有一个数会报错

# 正确：先split再判断
data = input().split()
if len( data ) == 2:
    a, b = data[ 0 ], data[ 1 ]

# 错误：忘记类型转换
a, b = input().split()  # a和b还是字符串
result = a + b  # 这是字符串拼接，不是数值相加

# 正确：记得类型转换
a, b = map( int, input().split() )
result = a + b
```

# map()函数

map() 是 Python 中一个非常强大且常用的内置函数，用于对可迭代对象中的所有元素应用指定函数。

**🎯 基本语法**
map( function, iterable, ... )

- function: 要应用的函数
- iterable: 一个或多个可迭代对象（列表、元组、字符串等）

返回值：一个 map 对象（迭代器）

## 📚 基础用法示例

- 基本数据类型转换

```python
# 字符串列表转整数列表
str_list = [ '1', '2', '3', '4', '5' ]
int_list = list( map( int, str_list ) )
print( int_list )  # [1, 2, 3, 4, 5]

# 整数列表转字符串列表
num_list = [ 1, 2, 3, 4, 5 ]
str_list = list( map( str, num_list ) )
print( str_list )  # ['1', '2', '3', '4', '5']

# 浮点数转整数
float_list = [ 1.5, 2.7, 3.1, 4.9 ]
int_list = list( map( int, float_list ) )
print( int_list )  # [1, 2, 3, 4] 注意：直接截断小数部分
```

- 自定义函数应用

```python
# 定义自定义函数
def square( x ):
    return x ** 2


numbers = [ 1, 2, 3, 4, 5 ]
squared = list( map( square, numbers ) )
print( squared )  # [1, 4, 9, 16, 25]

# 使用 lambda 表达式（更简洁）
numbers = [ 1, 2, 3, 4, 5 ]
squared = list( map( lambda x: x ** 2, numbers ) )
print( squared )  # [1, 4, 9, 16, 25]
```

- 多迭代对象操作

```python
# 两个列表对应元素相加
list1 = [ 1, 2, 3, 4 ]
list2 = [ 10, 20, 30, 40 ]
result = list( map( lambda x, y: x + y, list1, list2 ) )
print( result )  # [11, 22, 33, 44]

# 三个列表操作
a = [ 1, 2, 3 ]
b = [ 4, 5, 6 ]
c = [ 7, 8, 9 ]
result = list( map( lambda x, y, z: x + y + z, a, b, c ) )
print( result )  # [12, 15, 18]
```

```python
# map 会以最短的迭代对象为准
list1 = [ 1, 2, 3, 4, 5 ]  # 长度5
list2 = [ 10, 20, 30 ]  # 长度3
result = list( map( lambda x, y: x + y, list1, list2 ) )
print( result )  # [11, 22, 33] 只计算前3个元素
```

## 刷题实战应用

- 输入输出

```python
# 读取一行整数输入
# 输入: "1 2 3 4 5"
data = list( map( int, input().split() ) )
print( data )  # [1, 2, 3, 4, 5]

# 读取多行数据
n = int( input() )
matrix = [ ]
for i in range( n ):
    row = list( map( int, input().split() ) )
    matrix.append( row )
```

- 数据处理和转换

```python
# 字符串处理
words = [ 'hello', 'world', 'python' ]
upper_words = list( map( str.upper, words ) )
print( upper_words )  # ['HELLO', 'WORLD', 'PYTHON']


# 提取对象属性
class Student:
    def __init__( self, name, score ):
        self.name = name
        self.score = score


students = [
        Student( 'Alice', 85 ),
        Student( 'Bob', 92 ),
        Student( 'Charlie', 78 )
]

# 提取所有学生的分数
scores = list( map( lambda s: s.score, students ) )
print( scores )  # [85, 92, 78]
```

- 与其他函数结合使用

```python
# 与 filter 结合
numbers = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]
# 先过滤偶数，再平方
result = list( map( lambda x: x ** 2, filter( lambda x: x % 2 == 0, numbers ) ) )
print( result )  # [4, 16, 36, 64, 100]

# 与 zip 结合
names = [ 'Alice', 'Bob', 'Charlie' ]
scores = [ 85, 92, 78 ]
# 创建字典列表
data = list( map( lambda x: { 'name': x[ 0 ], 'score': x[ 1 ] }, zip( names, scores ) ) )
print( data )
# [{'name': 'Alice', 'score': 85}, {'name': 'Bob', 'score': 92}, ...]
```

- 惰性求值特性

```python
# map 返回的是迭代器，不是列表（节省内存）
numbers = [ 1, 2, 3, 4, 5 ]
map_obj = map( lambda x: x * 2, numbers )
print( map_obj )  # <map object at 0x...>

# 需要时才计算
for item in map_obj:
    print( item, end = ' ' )  # 2 4 6 8 10

# 注意：map对象只能遍历一次
print( list( map_obj ) )  # [] 因为已经遍历过了
```

## 🛠️ 实用工具函数

```python
def process_input():
    """处理多种输入格式"""
    # 单行多个整数
    nums = list( map( int, input().split() ) )

    # 多行字符串
    n = int( input() )
    lines = [ input().strip() for _ in range( n ) ]

    return nums, lines


def transform_data( data ):
    """数据转换工具"""
    # 批量类型转换
    int_data = list( map( int, data ) )

    # 批量运算
    squared = list( map( lambda x: x ** 2, int_data ) )

    return squared


# 使用示例
if __name__ == "__main__":
    # 测试输入处理
    print( "请输入数字，空格分隔:" )
    input_str = "1 2 3 4 5"  # 模拟输入
    numbers = list( map( int, input_str.split() ) )
    print( "转换结果:", numbers )
```

⚠️ 注意事项

1. map对象一次性: map返回的是迭代器，只能遍历一次
2. 内存考虑: 对于大数据集，map比列表推导式更节省内存
3. 可读性: 复杂的lambda表达式可能降低代码可读性
4. 错误处理: map本身不处理异常，需要在函数中处理