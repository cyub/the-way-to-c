在C语言中，函数是一段独立的代码块，用于执行特定任务，可以接受参数、返回值，并支持代码复用和模块化编程。

C 语言程序是由一个或多个函数构成的, 且必须有一个 **main** 函数, 通常称为 **主函数**。

## 函数定义

函数由两部分组成, 分别是函数头和函数体。

```c
类型标识符 函数名(形式参数列表) // 函数头
{
 // 函数体
}
```

1. **类型标识符**指明了函数的类型, 即函数返回值的类型, 若没有返回值, 则使用 `void`
2. **形式参数列表**: 可以有多个形式参数, 也可以没有, 格式如下:
1. **类型标识符 变量1, 类型标识符 变量2, ... ...**
2. 形式参数 (通常简称形参) 需要指定数据类型
 (形参在函数定义时不会分配任何存储空间, 也没有具体的值, 因此称为形式参数)
3. 有多个形参时, 用逗号隔开, 每个形参需单独指定数据类型。
4. 如果函数不带参数, 则形参可以省略, 但括号不能省。
5. 形参只在函数内部有效/可见。

```c
int my_max(int x, int y) // OK
int my_max(int x, y) // ERROR
```

## 函数返回值

函数返回值通过 `return` 语句给出。若没有返回值, 可以不写 `return`, 也可以写不带任何表达式的 `return`。

```c
int my_max(int x, int y)
{
 if (x > y) return x;
 else return y;
}
```

## 函数调用

函数调用语法如下：

```c
函数名(实际参数列表)
```

实际参数 (通常简称实参) 必须是实际存在的变量或表达式, 即有具体的值.

### 主调函数与被调函数

为了描述方面, 如果在函数 A 中调用函数 B, 我们称 A 是主调函数(caller), B 是被调
函数(callee)。

1. 如果被调函数在主调函数之前已经定义, 则可直接调用.
2. 如果被调函数是在主调函数后面才定义, 则需要在调用前事先声明.
函数声明: 函数头加分号, 比如 `int my_max(int x, int y);`
3. 被调函数的声明: 可以在主调函数中声明, 也可以在所有函数之前声明。
4. 被调函数可以出现在表达式中, 此时必须要有返回值。
5. 被调函数执行过程中遇到 return 语句时, 就返回主调函数, 如果 return 后面带有表达式, 则
将该表达式的值带回到主调函数, 如果 return 后面没有表达式, 则表示直接返回到主调函数。

### 调用约定

C语言函数的调用约定（或更广义的 C 调用约定）定义了在 C 语言程序中函数的调用规则，而这些规则的底层实现依赖于系统的 ABI（Application Binary Interface）。在 Linux 上，C 调用约定遵循 System V AMD64 ABI 的规范， Linux C 调用约定相当于System V AMD64 ABI 的规范的子集。

> [!note] 笔记
> **ABI（Application Binary Interface）**是硬件平台和操作系统上的一种标准，它定义了以下内容：
>
> - 函数调用约定：参数如何传递、返回值如何传递、寄存器如何使用等。
> - 二进制格式：比如可执行文件的格式（ELF 在 Linux 上常见）。
> - 栈布局：如何管理函数调用栈。
> - 数据类型布局：结构体、数组等数据类型的内存布局和对齐方式。

#### 参数传递

- 传递参数时，按照从左到右的顺序，将尽可能多的参数依次保存在寄存器中
  - 整数或指针类型参数通过寄存器 `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9` 传递
  - 浮点类型参数通过寄存器 `xmm0`，`xmm1`，`xmm2`，`xmm3`，`xmm4`，`xmm5`，`xmm6`，`xmm7`
- 超出寄存器数量的参数通过栈传递，按照从右到左的顺序压入栈中，并在调用之后 由调用函数推出栈
  - 栈上的参数以 8 字节对齐

寄存器/栈位置 | 参数
--- | ---
rdi | 第一个参数
rsi   |  第二个参数
rdx   |  第三个参数
rcx   |  第四个参数
r8   |  第五个参数
r9 | 第六个参数
rsp + 0x00   |  第七个参数
rsp + 0x08   |  第八个参数
…   |  剩余参数

示例：C代码：

```c
#include <stdio.h>

int add(int a, int b, int c, int d, int e, int f, int g, int h) {
    return a+b + c + d + e + f + g + h;
}

int main() {
   printf("%d\n", add(1,2, 3, 4, 5, 6, 7, 8));
}
```

汇编调用：

```armasm
; @see https://godbolt.org/z/qhYjKh5z5
add:
        pushq   %rbp
        movq    %rsp, %rbp ; 保存基址
        movl    24(%rbp), %eax ; 无效代码
        movl    16(%rbp), %eax ; 无效代码
        movl    %edi, -4(%rbp) ; 将传入参数保存到栈中
        movl    %esi, -8(%rbp)
        movl    %edx, -12(%rbp)
        movl    %ecx, -16(%rbp)
        movl    %r8d, -20(%rbp)
        movl    %r9d, -24(%rbp)
        movl    -4(%rbp), %eax
        addl    -8(%rbp), %eax
        addl    -12(%rbp), %eax
        addl    -16(%rbp), %eax
        addl    -20(%rbp), %eax
        addl    -24(%rbp), %eax
        addl    16(%rbp), %eax
        addl    24(%rbp), %eax
        popq    %rbp
        retq

main:
        pushq   %rbp
        movq    %rsp, %rbp ; 保存基址
        subq    $16, %rsp ; 预留栈空间，用来存放参数7,8
        movl    $1, %edi ; 第一个参数
        movl    $2, %esi ; 第二个参数
        movl    $3, %edx ; 第三个参数
        movl    $4, %ecx ; 第四个参数
        movl    $5, %r8d ; 第五个参数
        movl    $6, %r9d ; 第六个参数
        movl    $7, (%rsp) ; 第七个参数
        movl    $8, 8(%rsp); 第八个参数
        callq   add ; 调用add函数
        movl    %eax, %esi ; 将add函数返回值（保存在eax中）拷贝到esi中，作为printf函数的第一个参数
        leaq    .L.str(%rip), %rdi ; printf 函数的第二个参数
        movb    $0, %al
        callq   printf@PLT
        xorl    %eax, %eax
        addq    $16, %rsp
        popq    %rbp
        retq

.L.str:
        .asciz  "%d\n"
```

#### 返回值

- 整数（或者指针）返回值存放在 rax 或者 rdx:rax 中
  - 如果返回的是结构体或数组
    - 小结构体（≤ 16 字节）分拆到 rax 和 rdx
    - 大结构体通过调用者提供的指针返回
- 浮点数返回值存放在 xmm0 或者 xmm1:xmm0 中

#### 函数调用栈布局

- **调用函数时，栈指针（rsp）必须保持 16 字节对齐**
- 栈上的返回地址和参数按 ABI 规则存储

如果通过栈传递参数（超出 6 个参数），栈布局如下：

栈地址偏移 | 内容
--- | ---
rsp+16 | 第 9 个参数
rsp+8 | 第 8 个参数
rsp  | 第 7 个参数

示例：

```armasm
; -----------------------------------------------------------------------------
; @see https://godbolt.org/z/q7r6vj9TP
; 一个显示命令行参数的 64 位程序。一行一个地输出。
;
; 在函数入口处,rdi 保存 argc 的值,rsi 保存 argv 的值。
; nasm -felf64 echo.asm && gcc echo.o && ./a.out hello world
; -----------------------------------------------------------------------------

        global  main
        extern  puts
        section .text
main:
        push    rdi                     ; 保存 puts 函数需要用到的寄存器 
        push    rsi
        sub     rsp, 8                  ; 调用函数前让栈顶对齐, 注意此处需要是将rsp减8

        mov     rdi, [rsi]              ; 需要输出的字符串参数 
        call    puts                    ; 调用 puts 输出

        add     rsp, 8                  ; 恢复 %rsp 到未对齐前的值 
        pop     rsi                     ; 恢复 puts 用到的寄存器 
        pop     rdi

        add     rsi, 8                  ; 指向下一个参数 
        dec     rdi                     ; 递减 
        jnz     main                    ; 如果未读完参数则继续 

        ret
```

上面示例中`push rdi` 和 `push rsi` 操作之后，rsp一定是16字节对齐的，为啥还要手动`sub rsp, 8` 操作？

这是因为调用 `puts` 时候，会将返回地址压入栈中（占用8字节），如果没有`sub rsp, 8`，那么调用 `puts` 时候，`rsp` 是非对齐状态，不符合栈布局要求的第一条（调用函数时，栈指针（rsp）必须保持 16 字节对齐）。为了避免这种情况，提前执行 `sub rsp, 8`，让栈在 `call puts` 前处于非对齐状态，这样 `call` 之后栈就重新回到 16 字节对齐 状态。

#### 调用方与被调用方职责

调用方职责：

- 按照 ABI 规则准备参数
- 确保栈指针对齐
- 保存调用者保存寄存器（rax, rcx, r8-r11 等）中需要保留的值

被调用方职责：

- 保存被调用者保存寄存器（rbx, rbp, r12-r15）。
- 管理自己的栈帧
- 按规则返回结果

示例: C代码：

```c
int add(int a, int b) {
    return a + b;
}
```

示例：汇编调用：

```assembly
add:
    push rbp              ; 保存调用者的栈基址
    mov rbp, rsp          ; 设置新的栈基址
    mov eax, edi          ; 获取第 1 个参数
    add eax, esi          ; 加上第 2 个参数
    pop rbp               ; 恢复调用者的栈基址
    ret                   ; 返回
```

**注意**：对于Window平台上，遵循的是 `Windows x64 ABI` 规范。

#### 调用者保存寄存器（caller-saved registers）和 被调用者保存寄存器（callee-saved registers）

System V AMD64 ABI 中明确定义了 调用者保存寄存器（caller-saved registers）和 被调用者保存寄存器（callee-saved registers）的概念。这种分类是为了在函数调用中分配寄存器保存责任，从而优化寄存器使用和性能。

##### 调用者保存寄存器

调用者保存寄存器 是那些在函数调用时，由调用函数（caller）负责保存和恢复的寄存器。如果调用者需要在调用函数后继续使用这些寄存器中的值，它必须在调用前手动保存（比如推到栈上），并在调用后手动恢复。

###### 调用者保存寄存器列表

寄存器  |  用途
--- | ---
rax  |  函数返回值，或临时数据
rdi  |  第 1 个参数
rsi  |  第 2 个参数
rdx  |  第 3 个参数
rcx  |  第 4 个参数
r8  |  第 5 个参数
r9  |  第 6 个参数
r10  |  临时寄存器
r11  |  临时寄存器
xmm0-7  |  浮点参数和返回值寄存器
xmm8-15  |  临时浮点寄存器

###### 调用者保存寄存器的使用规则

- 函数调用后，这些寄存器的值可能被覆盖。
- 如果调用者需要保留这些寄存器的值，必须在调用前保存，调用后恢复。

##### 被调用者保存寄存器

被调用者保存寄存器 是那些在函数调用中，由被调用函数（callee）负责保存和恢复的寄存器。调用者可以假定这些寄存器在函数调用后保持不变。

###### 被调用者保存寄存器列表

寄存器  |  用途
--- | ---
rbx  |  被调用者保存的通用寄存器
rbp  |  基址指针寄存器
rsp  |  栈指针寄存器
r12-r15  |  被调用者保存的通用寄存器

###### 被调用者保存寄存器的使用规则

- 如果被调用函数修改了这些寄存器的值，它必须在修改之前保存原值，并在函数返回之前恢复。
- 栈指针（rsp）是特殊的：它必须在函数调用过程中保持正确的栈帧状态。

**示例1**：随机数的生成

- rand(): 返回一个 0 ∼ RAND_MAX 之间的伪随机整数
- srand(seed): 设置种子. 如不设定, 默认种子为 1
- 相同的种子对应相同的伪随机整数
- 每次执行 rand() 后, 种子会自动改变, 但变化规律是固定的

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
 int x=rand();
 printf("x=%d\n\n", x);
 
 int seed=2023;
 x=rand();
 printf("seed=%d, x=%d\n\n", seed, x);
 
 srand(time(0));
 int a=5, b=10;
 x=rand()%(b‐a+1) + a;
 printf("x=%d in [%d,%d]\n\n", x,a,b);
 
 double y;
 y=rand()/(double)RAND_MAX;
 printf("y=%f in [0,1], RAND_MAX=%d\n\n", y, RAND_MAX);
 
 return 0;
}
```

**示例2**：显示系统当前的时间
头文件 **time.h** 中函数 **time(0)** 或 **time(NULL)** 返回当前时间与 1970 年 1 月 1 日零时零分零秒的时间差（格林威治时间, 以秒为单位）, 北京时间: 格林威治时间 + 8 小时.

```c
#include <stdio.h>
#include <time.h>

int main()
{
 long Second, Minute, Hour;
 
 Second = time(0);
 Minute = Second / 60;
 Hour = Minute / 60;
 printf("当前北京时间是 %02d:%02d:%02d\n", (Hour+8)%24, Minute%60, Second%60);
 
 return 0;
}
```

**示例3**：计时函数clock

- **clock()** : 返回进程启动后所使用的 cpu 总毫秒数。

```c
#include <stdio.h>
#include <time.h>

int main() {

const int N = 300;
float A[N][N], B[N][N], C[N][N];
time_t t0, t1;
double tt, tc;

for (int i = 0; i < N; i++) {
 for (int j = 0; j < N; j++) {
 A[i][j] = 1.0 * (i + 1);
 B[i][j] = 1.0 * (j + 1);
 C[i][j] = 0.0;
 }
}

t0 = time(0);
tc = clock();

for (int i = 0; i < N; i++) {
 for (int j = 0; j < N; j++) {
  for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
 }
} 

tc = (double)(clock() - tc) / CLOCKS_PER_SEC;
t1 = time(0);
tt = t1 - t0;

printf("Elapsed time is %.6e or %.6e \n", tt, tc);
return 0;
}
// CLOCKS_PER_SEC: 每秒的滴答数, 通常为 1000.
```

## 函数参数传递

C语言中函数参数传递有两种二形式：一种是值传递，另外一种是地址传递。

### 值传递

1. 形参是局部变量，在函数被调用时才分配存储单元，调用结束即被释放
2. 实参可以是常量、变量、表达式、函数 (名) 等, 但它们必须要有确定的值，以便把具体的值传送给形参;
3. 将实参的值传递给对应的形参, 即单向传递;
4. 实参和形参在数量、类型、顺序上应严格一致;
5. 形参获得实参传递过来的值后, 便与实参脱离关系, 即对形参的任何改变都不会对实参产生任
何影响.

### 地址传递

地址传递目的是为了节省资源和开销，不再另外分配存储空间，而是直接将实参数组所在的内存地址告诉被调函数，让被调函数直接作用在实参数组上（即传递的是数组的首地址）

地址传递的实现方法是将数组名作为参数，形参和实参都是数组名，类型一样。

1. 若形参是数组, 为增加灵活性, 通常省略长度，如果是二维数组，则只能省略行数;
2. 如果数组形参没有指定长度, 则需另加一个形参, 用来传递实参数组的大小, 或者通过全局变
量实现;

```c
void my_swap(int a[], int b[], int n); // 可以省略长度, 但中括号不能省
void sum_col(double A[][n], double s[]); // 这里的 n 不能省略, 只能省略行数
```

3. 函数调用时, 只需用数组名。

> [!note] 笔记
> 由于被调函数是直接作用到实参数组上的，即实参与形参代表的是同一个数组，
因此在函数中对形参数组的任何修改都会影响到实参数组！

**示例1**：交换两个数组

```c
#include <stdio.h>

void my_swap(int a[], int b[], int n)
{
 int t, i;
 
 for (i=0; i<n; i++)
 {
  t=a[i]; a[i]=b[i]; b[i]=t;
 }
}

int main()
{
 int x[3]={1,2,3}, y[3]={2,4,6};
 int n = sizeof(x)/sizeof(x[0]);
 
 printf("\nBefore swapping:\n");
 for(int i=0; i<n; i++)
 printf("x[%d]=%d, y[%d]=%d\n", i, x[i], i, y[i]);
 
 my_swap(x,y,n);
 
 printf("\nAfter swapping:\n");
 for(int i=0; i<n; i++)
 printf("x[%d]=%d, y[%d]=%d\n", i, x[i], i, y[i]);
 return 0;
}
```

**示例2**：计算矩阵各列的和

```c
#include <stdio.h>

const int m=3, n=4;

void sum_col(double A[][n], double s[])
{
int i, j;
 for(j=0; j<n; j++) s[j]=0.0;
 for(j=0; j<n; j++)
  for(i=0; i<m; i++)
   s[j] = s[j] + A[i][j];
}

int main()
{
 double H[m][n], s[n];
 
 for(int i=0; i<m; i++)
  for(int j=0; j<n; j++)
   H[i][j]=1.0/(i+j+1);
 sum_col(H, s);
 printf("s[0]=%f, s[%d]=%f\n", s[0], n‐1, s[n‐1]);
 
 return 0;
}
```

## 函数嵌套与递归

函数的嵌套调用:

1. 函数可以嵌套调用, 但不能嵌套定义
2. 函数也可以 递归调用（函数可以直接或间接调用自己）

**示例1**：计算阶乘

$$
n! =
\begin{cases}
1 & \text{当 } n = 0, \\
n \times (n-1)! & \text{当 } n > 0.
\end{cases}
$$

```c
#include <stdio.h>

int factorial_loop(int n); // 普通方式（循环）
int factorial_recursion(int n); // 递归方式

int main()
{
 int n, y;
 printf("Please input n: ");
 scanf("%d", &n);
 
 y = factorial_loop(n);
 printf("普通方式：%d!=%d\n", n, y);
 
 y = factorial_recursion(n);
 printf("递归方式：%d!=%d\n", n, y);
 
 return 0;
}

int factorial_loop(int n) // 普通方式
{
 int y = 1;
 for (int i=1; i<=n; i++)
  y = y * i;
 return y;
}

int factorial_recursion(int n) // 递归方式
{
 if (n==0) return 1;
 else return n*factorial_recursion(n‐1);
}
```

## 内联函数

在C语言中，内联函数（`inline`）是一种优化技术，通过将函数调用替换为函数体来减少函数调用开销，从而提高程序性能。

1. 使用内联函数能节省参数传递、控制转移等开销, 提高代码的执行效率;
2. 内联函数通常应该是功能简单、规模小、使用频繁的函数;
3. 内联函数体内不建议使用循环语句和 switch 语句;
4. 有些函数无法定义成内联函数, 如递归调用函数等.
 

```c
inline double f(double x) // 内联函数
{
 return 2*x*x ‐ 1; // f(x) = 2x^2 ‐1
}
```

## 入口函数

也称作主函数，用户代码入口，有三种不同参数签名。

```c
int main（void）；

int main（int argc， char *argv［l）；// int main（int argc，char **argy）；

int main（int argc， char *argy［］， char *envp ［］）
```

```c
#include <stdio.h>
#include <stdlib.h>  

int main (int argc, char *argv[], char *envp[])
{ 
 for (int i = 0; i < argc; i++) { 
  puts(argv[i]);
 }  
 while (*envp) { 
  puts(*envp++);
 }  
 return EXIT_SUCCESS;
}
```

### 退出

- 任何位置都可调用 exit 函数终止进程。  
- main函数中返回 0 或 EXIT_SUCCESS 表示正常退出。其他，比如 EXIT_FAILURE 表示执行异常。  
- 如果 main函数 没有 return，则默认表示 return 0。  
  
进程终止前（exit 或 main return），将执行如下操作：  

- 执行 atexit 注册的清理函数。  
- 关闭所有 C stream。  
- 删除临时文件（tmpfile）。  

## 变参

可选变参前，至少有一个固定命名参数。  
  
1. 定义 va_list 参数指针对象。  
2. 使用 va_start 通过最后一个固定参数，初始化变参。  
3. 使用 va_arg 迭代获取变参值，须指定类型。（实参可以是不同类型）  
4. 使用 va_end 结束。如重新使用，或 va_copy，则必须先结束。  

```c
#include <stdio.h>
#include <stdarg.h>  
void test (int count, ...) { 
 va_list args; 
 va_start(args, count);  

 for (int i = 0; i < count; i++) {
  int a = va_arg(args, int); 
  printf("%d\n", a);
 }  
 va_end(args);
}

int main (void)
{ 
 test(3, 11, 22, 33);
 return 0;
}
```
