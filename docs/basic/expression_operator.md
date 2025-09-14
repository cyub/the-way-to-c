## 表达式

表达式是由**运算符、操作数、函数调用**等组成的代码结构，其目的是**计算一个值**。例如：

```c
3 + 5;          // 计算整数8
a * (b + 2);    // 包含变量和运算符的表达式
func();         // 函数调用表达式
```

表达式分为三类：

- **基本表达式**：变量、字面量、函数调用（如 `a`, `5`, `func()`）。
- **复合表达式**：通过运算符组合多个表达式（如 `a + b`, `x = y`）。
- **赋值表达式**：将右侧的值赋给左侧变量（如 `x = 10`）。

#### 赋值

赋值是将一个值赋予一个变量的过程。赋值运算符是 **=**，左边是变量，右边是值。

```c
int x;
x = 10;     // 将10赋值给x
```

我们可以使用`+=`, `-=`, `*=`等复合赋值运算符来简化运算。

```c
int a = 5;
a += 3;     // 等价于 a = a + 3 → a = 8
a++; // 自增赋值语句
```

#### 左值与右值

##### 左值

左值（L-Value）指的是可以出现在赋值运算符**左侧**的表达式，表示一个**可寻址的内存位置**（即能被赋值）。左值具有以下特点：

- 代表具体存储位置的变量或表达式（如变量名、指针解引用、数组元素）。
- 可以取地址（如 `&x`）。

```c
int x = 5;
x = 10;         // x是左值
int *p = &x;
*p = 20;        // *p是左值（解引用）
int arr[3];
arr[0] = 100;   // arr[0]是左值
```

##### 右值

右值指的是只能出现在赋值运算符**右侧**的表达式，表示**临时的值**或**不可寻址的数据**。右值具有以下特点：

- 无持久存储位置（如字面量、计算结果、函数返回值）。
- 不能被赋值（如 `5 = x` 非法）。

##### 左值与右值的转换

- **左值 → 右值**：在需要值的上下文中，左值会被隐式转换为右值（读取其存储的值）：

 ```c
 int x = 5;
 int y = x + 1;  // x被转换为右值5参与运算
 ```

- **右值 → 左值**：右值无法直接转为左值，但可通过某些操作间接实现（如指针指向临时对象）。

## 运算符

**运算符**(operator) 是用于执行特定操作的符号，如算术运算、比较、逻辑操作等。常见运算符有：

1. 算术运算符: `+`、`-`、`*`、`/`、`%`、`++` (自增)、`--` (自减)
2. 赋值运算符: =、`+=`、`-=`、`*=`、`/=`、`%=` 、`&=`、`|=`、`^=`、`>>=`、`<<=`
3. 逗号运算符: `,` (把若干表达式组合成一个表达式)
4. 关系运算符: 用于比较运算, `>`、`<`、**==**、`>=`、`<=`、`!=`
5. 逻辑运算符: 用于逻辑运算, `&&`、`||`、`!`
6. 条件运算符: `?:` , 是一个三目运算符, 用于条件求值
7. 求字节数运算符: `sizeof` (变量/数据/类型标识符)
8. 位操作运算符: 按二进制位进行运算, `&`、`|`、`~`、`^` (异或)、`<<` (左移)、`>>` (右移)
9. 指针运算符: `*` (取内容)、`&` (取地址)

### 关系运算符

关系运算符用于关系运算, 即比较大小。

- 结论是真则返回 1, 否则返回 0
- C 语言中用 1 表示 true, 0 表示 false
- bool 型变量的值为 0 时表示 false, 其他它值都表示 true
- 注意 == 与 = 的区别
- 对浮点数进行比较运算时尽量不要使用 ==

### 自增自减: ++,--

- 前置: 先自增或自减, 然后参与表达式运算;
- 后置: 先参与表达式运算, 然后自增或自减;
- 不要在同一语句中包含一个变量的多个 `++` 或`--`, 因为它们的解释在 C/C++ 标准中没有
规定, 完全取决于编译器的个人行为. 另外, 也不要出现 `y=x++*x;` 以及类似的语句。

```c
x++; // 等价于 x=x+1;
++x; // 等价于 x=x+1;
y=x++*3; // 等价于 y=x*3; x=x+1; 如果是 y=x++*x, 则结果怎样？
y=++x*3; // 等价于 x=x+1; y=x*3;
```

### 逻辑运算符

逻辑运算运算符用于逻辑运算。

- 表达式1 && 表达式2
  - 先计算 表达式1 的值, 若是 true, 再计算 表达式2 的值;
  - 若 表达式1 的值是 false, 则不再计算 表达式2.
- 表达式1 || 表达式2
  - 先计算 表达式1 的值, 若是 false, 再计算 表达式2 的值;
  - 若 表达式1 的值是 true, 则不再计算 表达式2.
- 优先级: ! 优于 && 优于 ||

### 逗号运算符

> 表达式1, 表达式2

逗号运算符中操作数会从左到右被顺序处理，即先计算 表达式 1, 再计算 表达式 2, 并将 表达式 2 的值作为整个表达式的结果。

```c
int a=2, b;
a = 3*5, a+10; // a=12 or 15?
b = (3*5, a+10); // b=?
```

### sizeof

^1a3f41

`sizeof`是求字节数运算符，它返回操作数占用内存空间⼤小，单位是字节(byte)。`sizeof`返回值是`size_t`类型，操作数可以是下面几种:

```c
sizeof(变量) // 返回指定变量所占的字节数
sizeof(数据类型) // 返回存储单个指定数据类型的数据所需的字节数
sizeof(表达式) // 返回存储表达式结果所需的字节数
```

sizeof 是一个编译时运算符，用于计算表达式中所包含的字节数：

```c
char str1[] = "will be 11";
char* str2 = "will be 8";
sizeof(str1) //11 因为这是一个数组 
sizeof(str2) //8 因为这是一个指针  
```

### 条件运算符: ?

> 条件表达式 ? 表达式1 : 表达式2

1. C 语言中唯一的 三目运算符;
2. 条件表达式 为真时返回 表达式1 的值, 否则返回 表达式2 的值;
3. 表达式1 的值和 表达式2 的值的数据类型要一致.

### 位操作运算符

C语言提供了6种位运算符，用于直接操作二进制位的运算：

| 运算符  | 名称   | 功能说明             | 示例表达式    |
| ---- | ---- | ---------------- | -------- |
| `&`  | 按位与  | 两个位都为 1，结果为 1    | `a & b`  |
| \|   | 按位或  | 只要有一个位为 1，结果为 1  | a\|b     |
| `~`  | 按位取反 | 将 0 变为 1，1 变为 0  | `~a`     |
| `^`  | 按位异或 | 相同为 0，不同为 1      | `a ^ b`  |
| `<<` | 左移   | 向左移动 n 位，相当于乘 2ⁿ | `a << n` |
| `>>` | 右移   | 向右移动 n 位，相当于除 2ⁿ | `a >> n` |

#### 按位与

对两个操作数的每一位进行逻辑与操作（同为1时结果为1，否则为0）。

```c
int a = 0b1101;   // 13
int b = 0b1011;   // 11
int c = a & b;    // 0b1001 = 9
```

#### 按位或

对两个操作数的每一位进行逻辑或操作（任一为1时结果为1）。

```c
int a = 5;    // 0101
int b = 3;    // 0011
int c = a | b; // 0111 → 7
```

#### 按位取反

对操作数的每一位取反（0变1，1变0）。

```c
int a = 5;     // 0000 0101
int b = ~a;    // 1111 1010 → -6（补码表示）
```

#### 按位异或

对两个操作数的每一位进行异或操作（不同为1，相同为0）。

```c
int a = 5;    // 0101
int b = 3;    // 0011
int c = a ^ b; // 0110 → 6
```

#### 左移

将操作数的所有位向左移动指定位数，右侧空位补0。

```c
int a = 5;     // 0101
int b = a << 2; // 010100 → 20
```

>[!warning] 注意
>需要注意**位移操作的位数限制**，位移位数超过变量位数是未定义行为：
>
> ```c
>int a = 1;
>int b = a << 33; // 错误！int通常为32位
>```

#### 右移

将操作数的所有位向右移动指定位数。对于有符号数和有符号数，最高位如何填充是不同的：

- **有符号数**：左侧空位补符号位（算术右移）
- **无符号数**：左侧空位补0（逻辑右移）

```c
int a = -8;      // 1111 1000（补码）
int b = a >> 2;  // 1111 1110 → -2（算术右移）
```

> [!warning] 注意
> 算术右移可能导致符号位扩展，逻辑右移需使用无符号数：
>
> ```c
> unsigned int x = 0x80000000;
> int y = x >> 1;    // 算术右移 → 0xC0000000
> unsigned z = x >> 1; // 逻辑右移 → 0x40000000
> ```

#### 常用位运算技巧

##### 快速判断奇偶

```c
if (n & 1) {
    // 奇数（最后一位为1）
} else {
    // 偶数（最后一位为0）
}
```

##### 交换两个变量（无需临时变量）

利用异或可逆操作，我们可以在无需临时变量情况下，交换两个变量的值。

```c
a ^= b;  // a = a ^ b
b ^= a;  // b = b ^ (a ^ b) → a
a ^= b;  // a = (a ^ b) ^ a → b
```

##### 取模运算（模数为2的幂次）

```c
int mod = num & (mod_power_of_two - 1);
// 例如：num % 8 → num & 0x07
```

通过位运算实现取模运算是哈希表中常用的技巧。当哈希表的容量为 **2的幂次方**（如 8、16、32）时，可通过 **位与（&）运算** 替代 **取模运算** 计算键的槽位（Bucket Index）。

```c
// 哈希表容量必须为2的幂次方（例如 m = 8 → 0b1000）
size_t m = 8;

// 计算键的哈希值
size_t hash = some_hash_function(key);

// 传统取模运算
size_t index_mod = hash % m;       // 等价于 hash & (m - 1)

// 位运算优化
size_t index_bitmask = hash & (m - 1); 
```

此外哈希表扩容时，将容量调整为 **最近的2的幂次方**时，我们可以通过位运算更高效的实现：

```c
// 计算大于等于n的最小2的幂次方
size_t next_power_of_two(size_t n) {
    n--; 
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}
```

**布隆过滤器（Bloom Filter）** 中，我们可以通过位运算快速定位多个哈希位:

```c
// 使用3个哈希函数
void set_bit(char* bitmap, const char* key) {
    size_t h1 = hash1(key) & (BITMAP_SIZE - 1);
    size_t h2 = hash2(key) & (BITMAP_SIZE - 1);
    size_t h3 = hash3(key) & (BITMAP_SIZE - 1);
    bitmap[h1 >> 3] |= 1 << (h1 & 7); // 设置位
    bitmap[h2 >> 3] |= 1 << (h2 & 7);
    bitmap[h3 >> 3] |= 1 << (h3 & 7);
}
```

##### 置位操作

1. **设置某一位为1**

```c
a |= (1 << n);
```

2. **清零某一位**

```c
a &= ~(1 << n);
```

3. **取反某一位**

```c
a ^= (1 << n);
```

示例：

```c
// 设置第3位为1（从0开始计数）
num |= (1 << 3);

// 清除第3位为0
num &= ~(1 << 3);

// 切换第3位状态（0变1，1变0）
num ^= (1 << 3);
```

##### 检查第 n 位是否为 1

```c
if (x & (1 << n)) {
    // 第 n 位是 1
}
```

##### 取第 n 位的值

```c
(x >> n) & 1
```

##### 快速乘/除以2的幂次

```c
int multiply = num << 3;  // num * 8
int divide = num >> 2;    // num / 4（算术右移保留符号）
```

##### 符号位检测

```c
int sign = (num >> (sizeof(int)*8 - 1)) & 1; // 符号位（1为负，0为正）
```

##### 清除最低位的 1

```c
x = x & (x - 1);
```

借此我们可以统计数中二进制位1的个数：

```c
// 计算二进制中1的个数
int count_ones(int num) {
    int count = 0;
    while (num) {
        num &= (num - 1); // 清除最低位的1
        count++;
    }
    return count;
}
```

##### 获取最低位的 1

```c
x & -x  // 或者 x & (~x + 1) // 提取最右边的 1
```

##### 内存对齐

Linux系统中进行内存操作，有时候需要保证提供的地址需要内存对齐。比如调用`mmap`系统调用，使用`MAP_FIXED`标志时，如果提供的地址不是页对齐的，`mmap`会失败。

假设需要将地址 `addr` 对齐到 `align` 字节边界（`align` 必须是 2 的幂次方，如 4、8、16 等），对齐后的地址计算公式为：

```c
aligned_addr = ((addr + align - 1) / align) * align; // 效率低（涉及除法）

aligned_addr = (addr + align - 1) & ~(align - 1); // 高效（无分支、无除法）
```

示例：

```c
#include <stdio.h>

// 对齐函数
#define ALIGN_UP(addr, align) (((addr) + (align) - 1) & ~((align) - 1))

int main() {
    size_t addr = 7;   // 原始地址
    size_t align = 4;  // 对齐到4字节
    size_t aligned = ALIGN_UP(addr, align);
    printf("原始地址: %zu, 对齐后地址: %zu\n", addr, aligned);
    return 0;
}
```

上面代码输出以下内容：

```c
原始地址: 7, 对齐后地址: 8
```

我们可以在在 `malloc` 分配的内存基础上对齐：

```c
void* allocate_aligned(size_t size, size_t align) {
    void* ptr = malloc(size + align - 1);
    return (void*)ALIGN_UP((size_t)ptr, align);
}
```

##### 哈希函数设计

通过移位、异或运算，我们可以设计出一个高效的哈希函数：

```c
uint32_t hash_function(uint32_t key) {
    uint32_t hash = key;
    
    /* 第一阶段：混合高位与低位信息 */
    hash = (hash ^ (hash >> 16)) * 0x85ebca6b; // 0x85ebca6b = 2,241,975,915 (质数)
    
    /* 第二阶段：二次扰动与扩散 */
    hash = (hash ^ (hash >> 13)) * 0xc2b2ae35; // 0xc2b2ae35 = 3,265,928,245 (质数)
    
    /* 第三阶段：最终位混合 */
    hash ^= (hash >> 16);
    return hash;
}

// 字符串哈希扩展
uint32_t string_hash(const char* str) {
    uint32_t hash = 0;
    for (; *str; ++str) {
        hash = hash_function(hash ^ *str);
    }
    return hash;
}

// 64位版本适配
uint64_t hash64(uint64_t key) {
    key ^= key >> 33;
    key *= 0xff51afd7ed558ccd;
    key ^= key >> 33;
    key *= 0xc4ceb9fe1a85ec53;
    key ^= key >> 33;
    return key;
}
```

##### 位图存储

当需要存储大规模布尔数据（如用户在线状态）时，我们可以用位图（Bitmap）压缩存储。比如存储1亿个状态仅需12.5MB，而用布尔数组，需要100MB。

```c
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// 定义位图（每字节存8个状态）
uint8_t bitmap[1024]; // 可表示8192个状态

// 设置第n位为1
void set_bit(int n) {
    bitmap[n / 8] |= (1 << (n % 8));
}

// 检查第n位是否为1
int get_bit(int n) {
    return (bitmap[n / 8] >> (n % 8)) & 1;
}

// 批量操作，设置第n字节全为1
void set_byte(int n) {
    bitmap[n] |= OxFF;
}

/**
 * @brief 设置位图中连续多个位为1
 * @param bitmap 位图数组指针
 * @param start_bit 起始位位置（从0开始计数）
 * @param num_bits 需要设置的位数
 * 
 * 示例：设置第3位开始的5个位为1（即bit[3]-bit[7]）
 * set_bits(bitmap, 3, 5);
 */
void set_bits(uint8_t* bitmap, size_t start_bit, size_t num_bits) {
    // 计算起始字节位置和位偏移
    size_t start_byte = start_bit / 8;
    size_t bit_offset = start_bit % 8;
    
    // 处理起始字节的部分位
    if (bit_offset > 0) {
        size_t bits_in_first_byte = 8 - bit_offset;
        size_t bits_to_set = (num_bits < bits_in_first_byte) ? num_bits : bits_in_first_byte;
        
        // 生成掩码：例如 offset=3, bits=5 → 0b11111000
        uint8_t mask = (0xFF << bit_offset) & (0xFF >> (8 - (bit_offset + bits_to_set)));
        bitmap[start_byte] |= mask;
        
        num_bits -= bits_to_set;
        if (num_bits == 0) return;
        start_byte++;
    }

    // 处理完整的中间字节（每次设置整个字节）
    while (num_bits >= 8) {
        bitmap[start_byte++] = 0xFF; // 设置整个字节为1
        num_bits -= 8;
    }

    // 处理剩余的末尾位
    if (num_bits > 0) {
        uint8_t mask = 0xFF >> (8 - num_bits); // 例如剩余3位 → 0b00000111
        bitmap[start_byte] |= mask;
    }
}

void print_bitmap(const uint8_t* bitmap, size_t num_bytes) {
    for (size_t i = 0; i < num_bytes; ++i) {
        for (int j = 7; j >= 0; --j) {
            printf("%d", (bitmap[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    uint8_t bitmap[4] = {0}; // 32位位图

    // 测试用例1：设置第3位开始的5个位
    set_bits(bitmap, 3, 5);
    print_bitmap(bitmap, 4); // 00011111 00000000 00000000 00000000

    // 测试用例2：跨字节设置（第6位开始的10位）
    memset(bitmap, 0, sizeof(bitmap));
    set_bits(bitmap, 6, 10);
    print_bitmap(bitmap, 4); // 11000000 11111111 11000000 00000000

    // 测试用例3：设置整个位图
    memset(bitmap, 0, sizeof(bitmap));
    set_bits(bitmap, 0, 32);
    print_bitmap(bitmap, 4); // 11111111 11111111 11111111 11111111

    return 0;
}
```

> [!note] 笔记
> **位图（Bitmap）** 是一种数据结构，用于用一组连续的二进制位表示状态或信息，其中每个位代表一个特定的元素或状态。位图通过位运算实现高效的内存利用率和快速的状态检查，常用于图像处理、内存管理、数据压缩和集合操作等领域。

##### IP地址转换

代码示例：

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // 用于字节序转换（Linux/Unix）
// Windows 用户可使用 <winsock2.h> 中的 htonl/ntohl

/**
 * @brief 将32位网络字节序整数转换为点分十进制IP字符串
 * @param ip 网络字节序的IP地址（uint32_t）
 * @param buf 输出缓冲区（至少16字节）
 * @return 成功返回0，失败返回-1
 */
int ipv4_int_to_str(uint32_t ip, char* buf) {
    if (!buf) return -1;

    // 转换为本地字节序（确保正确解析）
    uint32_t host_ip = ntohl(ip);

    // 提取四个字节（大端序：第一个字节为最高位）
    uint8_t a = (host_ip >> 24) & 0xFF;
    uint8_t b = (host_ip >> 16) & 0xFF;
    uint8_t c = (host_ip >> 8)  & 0xFF;
    uint8_t d = host_ip & 0xFF;

    // 格式化为字符串
    snprintf(buf, 16, "%d.%d.%d.%d", a, b, c, d);
    return 0;
}

/**
 * @brief 将点分十进制IP字符串转换为32位网络字节序整数
 * @param ip_str 点分十进制IP字符串（如 "192.168.1.1"）
 * @param result 输出转换后的网络字节序IP地址
 * @return 成功返回0，失败返回-1（格式错误）
 */
int ipv4_str_to_int(const char* ip_str, uint32_t* result) {
    if (!ip_str || !result) return -1;

    unsigned int a, b, c, d;
    // 使用sscanf严格校验输入格式
    if (sscanf(ip_str, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
        return -1; // 格式错误
    }

    // 验证每个字节范围 (0~255)
    if (a > 255 || b > 255 || c > 255 || d > 255) {
        return -1;
    }

    // 组合为本地字节序整数（大端序）
    uint32_t host_ip = (a << 24) | (b << 16) | (c << 8) | d;

    // 转换为网络字节序
    *result = htonl(host_ip);
    return 0;
}

/*********************** 测试用例 **************************/
void test_conversion(const char* ip_str) {
    uint32_t ip_int;
    char buf[16];

    // 字符串转整数
    if (ipv4_str_to_int(ip_str, &ip_int) {
        printf("错误：无效IP地址 %s\n", ip_str);
        return;
    }

    // 整数转字符串
    if (ipv4_int_to_str(ip_int, buf)) {
        printf("错误：转换失败\n");
        return;
    }

    // 验证转换一致性
    printf("测试 %-15s → 0x%08X → %s [%s]\n",
           ip_str, ip_int, buf,
           strcmp(ip_str, buf) == 0 ? "✓" : "✗");
}

int main() {
    // 常规测试
    test_conversion("0.0.0.0");
    test_conversion("255.255.255.255");
    test_conversion("192.168.1.1");
    test_conversion("8.8.8.8");

    // 边界测试
    test_conversion("127.0.0.1");
    test_conversion("224.0.0.251"); // 多播地址

    // 错误格式测试
    test_conversion("192.168.1");      // 错误：段不足
    test_conversion("192.168.1.256");  // 错误：数值超限
    test_conversion("192.168.1.abcd"); // 错误：非数字字符

    return 0;
}
```

##### 状态标志管理

当需要管理多个布尔状态（如文件权限、设备状态）时，可以用位掩码代替多个布尔变量，节省内存且提升访问速度。此时每个二进制位表示一个独立的状态，通过位掩码快速设置、清除或检查状态。

```c
// 定义状态掩码
#define FLAG_A (1 << 0) // 0b00000001
#define FLAG_B (1 << 1) // 0b00000010
#define FLAG_C (1 << 2) // 0b00000100

// 设置状态
int state = 0;
state |= FLAG_A;       // 启用A: 0b00000001
state |= FLAG_B;       // 启用B: 0b00000011

// 清除状态
state &= ~FLAG_A;      // 禁用A: 0b00000010

// 检查状态
if (state & FLAG_B) {  // 检查B是否启用
    // 执行操作
}
```

再看一个实例：一个字节有 8 位，可以用来表示 8 个开关，每个位分别代表一个开关的**开/关状态**。

```c
#include <stdio.h>
#include <stdint.h>

typedef uint8_t SwitchFlags;

#define SET_BIT(flags, n)      ((flags) |=  (1 << (n)))
#define CLEAR_BIT(flags, n)    ((flags) &= ~(1 << (n)))
#define TOGGLE_BIT(flags, n)   ((flags) ^=  (1 << (n)))
#define GET_BIT(flags, n)      (((flags) >> (n)) & 1)

// 调试输出函数
void print_bits(SwitchFlags flags) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", GET_BIT(flags, i));
    }
    printf("\n");
}

// 示例用法
int main() {
    SwitchFlags flags = 0;

    SET_BIT(flags, 3);    // 开启第3位
    SET_BIT(flags, 6);    // 开启第6位
    CLEAR_BIT(flags, 3);  // 关闭第3位
    TOGGLE_BIT(flags, 6); // 翻转第6位

    print_bits(flags);    // 输出 00000000

    return 0;
}
```

##### 权限控制系统

通过位运算，我们可以设计一个基于位运算的权限控制系统。

|权限位|权限名|值 (1 << n)|
|---|---|---|
|0|读权限|0x01|
|1|写权限|0x02|
|2|执行权限|0x04|
|3|删除权限|0x08|

代码示例：

```c
#include <stdio.h>
#include <stdint.h>

typedef uint8_t Permission;

#define PERM_READ   (1 << 0)
#define PERM_WRITE  (1 << 1)
#define PERM_EXEC   (1 << 2)
#define PERM_DELETE (1 << 3)

void grant_permission(Permission* perm, uint8_t mask) {
    *perm |= mask;
}

void revoke_permission(Permission* perm, uint8_t mask) {
    *perm &= ~mask;
}

int has_permission(Permission perm, uint8_t mask) {
    return (perm & mask) == mask;
}

void print_permission(Permission perm) {
    printf("R:%d W:%d X:%d D:%d\n",
           !!(perm & PERM_READ),
           !!(perm & PERM_WRITE),
           !!(perm & PERM_EXEC),
           !!(perm & PERM_DELETE));
}

int main() {
    Permission user_perm = 0;

    grant_permission(&user_perm, PERM_READ | PERM_WRITE);
    print_permission(user_perm); // R:1 W:1 X:0 D:0

    if (has_permission(user_perm, PERM_WRITE)) {
        printf("You can write!\n");
    }

    revoke_permission(&user_perm, PERM_WRITE);
    print_permission(user_perm); // R:1 W:0 X:0 D:0

    return 0;
}
```

### 运算符优先级

**运算符优先级** 决定了表达式中运算符的执行顺序，优先级高的运算符会先于优先级低的运算符执行。

下表列出了 C 语言中各运算符的优先级和结合性，运算符按优先级从高到低排列[^1]。

|优先级|运算符|描述|结合性|
|---|---|---|---|
|1|`++` `--`|后缀自增、自减|从左到右|
||`()`|函数调用||
||`[]`|数组下标||
||`.` `->`|结构体和联合体成员访问||
||`(类型){列表}`|复合字面量（C99）||
|2|`++` `--`|前缀自增、自减|从右到左|
||`+` `-`|一元加号和减号||
||`!` `~`|逻辑非和按位非||
||`(类型)`|类型转换||
||`*`|间接寻址（解引用）||
||`&`|取地址||
||`sizeof`|求大小||
||`_Alignof`|对齐要求（C11）||
|3|`*` `/` `%`|乘法、除法和取余|从左到右|
|4|`+` `-`|加法和减法|从左到右|
|5|`<<` `>>`|按位左移和右移|从左到右|
|6|`<` `<=` `>` `>=`|关系运算符|从左到右|
|7|**==** `!=`|相等和不等|从左到右|
|8|`&`|按位与|从左到右|
|9|`^`|按位异或|从左到右|
|10|`|`|按位或|
|11|`&&`|逻辑与|从左到右|
|12|`||`|
|13|`?:`|条件运算符（三元）|从右到左|
|14|`=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `|=`|赋值运算符|
|15|`,`|逗号运算符|从左到右|

#### 说明

- **结合性**：当表达式中存在多个相同优先级的运算符时，结合性决定了运算的顺序。例如，赋值运算符是从右到左结合的，因此表达式 `a = b = c` 被解析为 `a = (b = c)`。

- **运算符优先级**：优先级高的运算符会先于优先级低的运算符进行计算。例如，表达式 `*p++` 被解析为 `*(p++)`，而不是 `(*p)++`。

- **注意事项**：

  - 前缀 `++` 和 `--` 的操作数不能是类型转换表达式。
  - `sizeof` 的操作数不能是类型转换表达式，例如，`sizeof (int) * p` 被解析为 `(sizeof(int)) * p`，而不是 `sizeof((int)*p)`。
  - 条件运算符中的中间表达式（即 `?` 和 `:` 之间的部分）被视为带括号的表达式，其优先级相对于 `?:` 被忽略。
  - 赋值运算符的左操作数必须是一级表达式（非类型转换）。

## 语句

**语句** 是程序中执行的最小单位，用于完成特定的操作或任务。语句通常以分号（`;`）结尾，表示一条语句的结束。常见语句有下面几种：

1. 空语句（只有分号）
2. 声明语句;
3. 表达式语句;
4. 复合语句（将多个语句用 { } 括起来组成的一个语句）;
5. 选择语句, 循环语句, 跳转语句;
6. ...

[^1]: <https://en.cppreference.com/w/c/language/operator_precedence>
