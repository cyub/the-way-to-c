在C语言中，**数组** 是一种数据结构，是**具有一定顺序关系的若干相同类型数据的集合**, 是基本数据类型的推广，用于存储相同类型的多个元素。数组可以是一维的（线性结构）或二维的（表格结构）。

## 一维数组

一维数组是线性结构，是**相同类型元素的有序集合**，用于存储相同类型的多个元素。数组中的每个元素可以通过索引访问，索引从`0`开始。

### 声明和初始化

语法：

```c
数据类型 数组名[长度];        // 声明未初始化（值为随机）
数据类型 数组名[长度] = {初始值列表};  // 声明并初始化
```

示例：
```c
int arr[5];                   // 声明长度为5的int数组（元素未初始化）
int nums[3] = {10, 20, 30};  // 完全初始化
int data[] = {1, 2, 3};       // 自动推断长度为3

double balance[5] = {1} // 第一个元素是1， 后面默认是0 
double balance[5] = {0} // 全部为0 
double balance[5] = {1000.0, 2.0} // 头两个元素值为1000，和2，后面值为0 
double balance[] = {1000.0, 2.0} // 省略掉了数组的大小，数组的大小则为初始化时元素的个数，balance数组大小为2 
int x[] = { 1, 2, [6] = 10, 11 }; // 显示将第7个元素指定为10
```

`{}`叫做初始化器。初始化规则如下: 

- 如果数组为静态⽣生存周期，那么初始化器必须是常量表达式。 
- 如果提供初始化器，那么可以不提供数组⻓长度，由初始化器的最后⼀一个元素决定。 
- 如果同时提供⻓长度和初始化器，那么没有提供初始值的元素都被初始化为 0 或 NULL。

> [!note] 笔记
> - 这里面的介绍声明注意和[[数据类型与变量#^600532|变量的声明]]不是一个观念，这里面的声明其实是[[数据类型与变量#^cb3d83|变量的定义]]。
> - 在C语言和C++语言中，如果没有显式初始化，数组的值将是未定义的，即其内容是不确定的。 在这种情况下，上面中的`arr`数组中的值可能是任何值，这取决于它所分配的内存的状态。

声明数组时, 若长度中含有变量, 则不能初始化！

```c
const int n=3; ✅
int x[n]; // OK
int y[n]={1,2,3}; // ERROR 
```

### 访问与修改

一维数组的访问和修改的语法格式如下：
```c
数组名[索引];
数组名[索引] = 值;
```

 访问超出范围的索引会导致未定义行为（可能崩溃或数据错误）。**数组名是首元素地址的指针常量**，我们也可以通过数组名进行指针运算来访问元素。

```c
int arr[5] = {1, 2, 3, 4, 5};

// 访问第三个元素
printf("%d\n", arr[2]);  // 输出：3
arr[2] = 1; // 修改第三个元素

// 通过数组指针访问数组元素
printf("%d\n", *(arr+2)); // 访问第三个元素，输出1

// 数组名是指针常量，不能被修改
arr = {1,2,3,4,5}; // ERROR

// 下面两个是等效的
int *ptr = arr;
int *ptr = &arr[0];
```
> [!note] 笔记
> 上面`arr`值的值是内存地址，指向数组首个元素地址，`arr+2`并不是只是加上2，而是加上两个数组元素的size

### 获取数组大小

我们可以使用[[表达式与运算符#^1a3f41|sizeof运算符]]来获取数组大小。

```c
int arr[5];
printf("arr size: %d\n", sizeof(arr)/sizeof(arr[0])); // 输出5

int arr2[] = {1,2,3,4,5};
printf("arr2 size: %d\n", sizeof(arr)/sizeof(arr[0])); // 输出5
```

需要注意，当忽略数组大小数组变量作为函数参数传递时候，是不能用上面的方法的，需要显示传递数组大小，或者以特定标志结尾的数组（比如NULL结尾的字符串数组）：

```c
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // 数组名arr被当作指针使用
    }
}

void printArray2(int arr[]) {
	  int size = sizeof(arr)/sizeof(arr[0]) // 这种获取的size是错误的，此时sizeof(arr)是sizeof(int *)的大小。
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // 数组名arr被当作指针使用
    }
}

// 以NULL结尾的指针数组
vod printArray3( int** x) { // 等效于int* x[]
	int *p;
	while((p = *x) != NULL) {
		printf("%d", *p);
		x++;
	}
}


int main() {
    int myArray[] = {10, 20, 30, 40, 50};
		printf("%d\n", sizeof(myArray)/sizeof(myArray[0])); // 这个是正确的，因为编译器可以根据myArray初始化信息推断出正确的sizeof(myArray)
    printArray(myArray, 5); // 将数组名传递给函数
		printArray2(myArray); 
    return 0;
}
```

### 遍历

我们可以通过[[控制结构#^edb94d|for循环]]来遍历数组。

```c
int myArray[5] = {10, 20, 30, 40, 50};
int size = sizeof(myArray)/sizeof(myArray[0])
for (int i = 0; i < size; i++) {
        printf("%d ", myArray[i]); // 通过索引下标访问
}

for (int i = 0; i < size; i++) {
        printf("%d ", *(myArray+i); // 数组名arr被当作指针使用
}
```

> [!warning] 注意
>  `myArray++`以及`myArray+1` 并不是将数组开始地址+1，而是加上数组元素的大小。`myArray+i`的计算公式是：
>```c
>myArray + i * sizeof(int)
>```

### 数组作为参数传递给函数

#### 形参是一个数组指针

此时需要传递数组大小，或者最后一个元素是`NULL`。

```c
void myFunction(int *param, int arraySize) 
{ }
```

#### 形参是一个已定义大小的数组

```c
void myFunction(int param[5]) { }
```

#### 形参是一个未定义大小的数组

此时需要传递数组大小，或者最后一个元素是`NULL`。

```c
void myFunction(int param[], int arraySize) { }
```

### 数组作为函数返回值

在C语言中不允许返回完整数组，但我们可以返回一个指向数组的指针。

```c
int * getRandom( )
{
  static int  r[10]; // C 不支持在函数外返回局部变量的地址，除非定义局部变量为 static 变量。
  int i;
 
  /* 设置种子 */
  srand( (unsigned)time( NULL ) );
  for ( i = 0; i < 10; ++i)
  {
     r[i] = rand();
     printf( "r[%d] = %d\n", i, r[i]);
 
  }
 
  return r;
}
```

## 二维数组

二维数组是**由行和列组成的表格结构**，本质是一维数组的数组（每个元素是一维数组），用于存储多行多列的数据。每个元素可以通过行索引和列索引访问。

二维数组中的元素按行优先顺序连续存储。对于`int[3][5]`类型数组其内存空间布局使用如下图所示：

![](https://static.cyub.vip/images/202104/array_memory_alloc.png)

二维数组通常也被称为"矩阵(matrix)"，相当于一个`row*column`的表格。

### 声明与初始化

语法：

```c
数据类型 数组名[行数][列数];                // 声明未初始化
数据类型 数组名[行数][列数] = {初始值列表};    // 声明并初始化
```

示例：

```c
int matrix[2][3];                   // 声明2行3列的数组
int table[2][3] = {{1, 2, 3}, {4, 5, 6}};  // 完全初始化
int grid[][3] = {{7, 8}, {9}};      // 自动推断行数（第二行第三列默认填充0）
```

> [!warning] 注意
> 二维数组中只有第一维长度可以省略。

### 访问与遍历

二维数组可以通过`数组名[行索引][列索引]` 进行访问。

```c
int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

// 访问第二行第三列元素
printf("%d\n", matrix[1][2]);  // 输出：6

// 遍历所有元素
for (int i = 0; i < 2; i++) {        // 遍历行
    for (int j = 0; j < 3; j++) {    // 遍历列
        printf("%d ", matrix[i][j]); // 输出：1 2 3 4 5 6
    }
    printf("\n");
}
```

二维数组当然也可以通过`数组名[列索引][行索引]`的形式进行访问，但由于空间局部性的关系，其访问效果不高，不推荐这种方式访问。

> [!note] 笔记
> **空间局部性**是指程序在运行时，如果访问了某个存储位置，那么它附近的存储位置很可能在不久的将来也会被访问。这种原理通常用于缓存和内存管理中，以提高数据访问的效率。

### 矩阵加法

```c
int a[2][2] = {{1, 2}, {3, 4}};
int b[2][2] = {{5, 6}, {7, 8}};
int result[2][2];

for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
        result[i][j] = a[i][j] + b[i][j];
        printf("%d ", result[i][j]); // 输出：6 8 10 12
    }
    printf("\n");
}
```

### 字符数组

**字符数组**是用于存储字符序列的数组，每个元素为 `char` 类型，通过下标访问单个字符。

```c
// 声明未初始化（值为随机）
char arr1[5];    

// 声明并逐个初始化（手动填充）
char arr2[3] = {'A', 'B', 'C'}; 

// 部分初始化（剩余元素自动填充0或空）
char arr3[5] = {'H', 'i'}; 

// 自动推断长度（长度为3）
char arr4[] = {'X', 'Y', 'Z'}; 

char arr[] = {'H', 'e', 'l', 'l', 'o'};
for (int i = 0; i < 5; i++) {
    printf("%c", arr[i]); // 输出：Hello
}
```

### 字符串

**字符串**是以空字符 `\0` 结尾(`\0`称为字符串结束标志)的字符数组，是字符数组的一种特殊形式。

```c
// 字符串字面量初始化（自动添加\0）
char str1[] = "Hello";  // 等效于 {'H','e','l','l','o','\0'}

// 显式指定长度（需预留\0位置）
char str2[6] = "World"; // 正确：长度6足够（5字符+\0）
char str3[5] = "Test";  // 正确：长度5足够（4字符+\0）
char str4[4] = "Oops";  // 错误！长度不足（需至少5字节）
char str5[20] = "Hello"; // 字符数组长度为20，但仅包含5个字符

// 字符指针（指向字符串字面量）
char *str5 = "Hello";   // 字符串字面量存储在只读区
```

下图展示了数组、字符串的内促布局情况[^1]。
![](https://static.cyub.vip/images/202509/c_string.png)

当字符串字面量很长时候，可以拆成多个相邻的字符串，C编译器会相邻的字符串字面量自动拼接成一个字符串：

```c
const char *text =
    "这是一个很长的字符串，"
    "可以分成多行写，"
    "编译器会自动拼接成一行。\n";
```

#### 输入与输出

```c
char name[20];
printf("输入名字：");
scanf("%s", name);    // 输入到name数组（自动补\0，但需注意溢出风险）
printf("名字：%s\n", name);
```

> [!note] 笔记
> - `printf` 是整体输出, 系统自动逐个输出字符, 直到遇见字符串结束标志符。
> - `printf` 输出字符串中不含 字符串结束标志符 `\0`。

#### "\0" vs '\0'

在 C 语言中，`"\0"` 和 `'\0'` 是两种表示空字符（null character）的方式，但它们有一些不同之处：

1. `"\0"`：
    - `"\0"` 是一个包含两个字符的字符串字面量（string literal）。其中，`\0` 表示空字符（null character），ASCII 值为 0。
    - 在 C 语言中，字符串字面量是用双引号括起来的字符序列，末尾会自动添加一个空字符 `'\0'` 作为字符串的终止符。因此，`"\0"` 实际上表示的是包含一个空字符的字符串，长度为 1。
2. `'\0'`：
    - `'\0'` 是一个字符常量（character constant）或者叫做字符字面量（character literal）。表示单个字符的空字符（null character），ASCII 值为 0。
    - 在 C 语言中，字符常量用单引号括起来，表示一个字符。
    - `'\0'` 是一种特殊的字符，通常用作字符串的终止符，表示字符串的结束。
    - 当我们用 `'\0'` 来初始化字符数组时，这个字符数组将会被视为一个空字符串。

```c
#include <stdio.h>

int main() {
    char str1[] = "\0";  // 包含一个空字符的字符串，长度为 1
    char str2[] = {'\0'};  // 包含一个空字符的字符数组，长度为 1

    printf("Length of str1: %zu\n", sizeof(str1));  // 输出字符串长度，包括终止符，输出2
    printf("Length of str2: %zu\n", sizeof(str2));  // 输出字符数组长度，输出1

    printf("str1: %s\n", str1);  // 输出 str1 的内容
    printf("str2: %s\n", str2);  // 输出 str2 的内容

    return 0;
}
```

#### 相关函数

字符串相关函数（头文件 string.h 和 stdlib.h）

函数 | 含义
--- | ---
strlen(str) | 求字符串长度
strcat(dest,src) | 字符串连接
strcpy(dest,src) | 字符串复制
strcmp(str1,str2) | 字符串比较
atoi(str) | 将字符串转换为整数
atol(str) | 将字符串转换为 long
atof(str) | 将字符串转换为 double

字符检测函数（头文件 cctype）

函数 | 含义 | 示例
--- |--- | ---
isdigit | 是否为数字 | isdigit('3')
isalpha | 是否为字母 | isalpha('a')
isalnum | 是否为字母或数字 | isalnum('c')
islower | 是否为小写 | islower('b')
isupper | 是否为大写 | isupper('B')
isspace | 是否为空格 | isspace(' ')
isprint | 是否为可打印字符, 包含空格 | isprint('A')
isgraph  |是否为可打印字符, 不含空格 | isgraph('a')
ispunct | 除字母数字空格外的可打印字符 | ispunct('*')
iscntrl | 是否为控制符 | iscntrl('\n')
tolower | 将大写转换为小写 | tolower('A')
toupper | 将小写转换为大写|  toupper('a')

[^1]: https://pythontutor.com/c.html#
