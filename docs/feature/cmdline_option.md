在编写命令行工具时，解析用户输入的参数是一个常见的需求。C语言提供了 `getopt` 和 `getopt_long` 函数，帮助我们高效地处理命令行参数。本文将详细介绍这两个函数的使用方法，并通过代码示例展示其使用方法。

## 什么是命令行参数？

命令行参数（也称为命令行选项）是通过命令行传递给程序的字符串数据。在 C 语言中，`main` 函数的定义支持两个参数：

```c
int main(int argc, char *argv[]);
```

- `argc`：表示命令行参数的个数，包括程序本身的名称。
- `argv`：是一个字符串数组，存储了所有的命令行参数，其中argv[0]通常是程序的名称。

### 在没有使用C标准库情况下，如何解析命令行参数？

解析命令行参数通常包括以下步骤：

- 读取参数的个数和内容：使用argc和argv。
- 根据参数内容执行相应的逻辑：可以通过循环遍历argv数组来分析参数。
- 处理无效输入：在解析过程中，需要对非法参数进行处理并提示用户。

**代码示例：简单的命令行参数读取**

```{literalinclude} ./src/read_allopt.c
:language: c
```

运行程序时，可以通过命令行传递参数，例如：

```bash
cd src
make read_allopt
./read_allopt arg1 arg2 arg3
```

输出结果为：

```bash
参数个数： 4
参数 0: ./read_allopt
参数 1: arg1
参数 2: arg2
参数 3: arg3
```

接下来是一个稍复杂的示例，解析带有选项的命令行参数：

**代码示例：解析选项和参数**

```{literalinclude} ./src/read_opt.c
:language: c
```

运行示例：

```bash
➜  src ./read_opt
用法: ./read_opt [选项] [参数]
选项:
  -h, --help    显示帮助信息
  -v, --version 显示版本信息

➜  src ./read_opt -h
帮助信息: 这是一个命令行解析示例程序。

➜  src ./read_opt -h -v
帮助信息: 这是一个命令行解析示例程序。
版本信息: v1.0.0

➜  src ./read_opt unkown
未知选项: unkown
```

从上面示例可以看到手动解析参数可能会导致代码复杂且难以维护。为此C标准库中提供了 `getopt` 和 `getopt_long` 函数，它们可以自动解析命令行参数，简化了命令行参数解析的过程。

在介绍 `getopt` 和 `getopt_long` 函数之前，我们先来了解下C语言工具（如命令行程序）中 `help` 命令或帮助信息通常遵循的格式规范。

## help命令格式规范

在 C 语言工具中，`help` 命令中显示的命令选项格式通常遵循一些规范，通过这些规范，用户可以快速理解命令的使用方法，并根据参数格式提供所需的输入。以下是常见的规范及其含义：

### 1. 基本格式

帮助信息通常包括以下部分：
- 命令名称：程序的名称。
- 用法：命令的基本用法格式。
- 选项：支持的选项及其说明。
- 示例：示例用法（可选）。

### 2. 符号规范

#### 1. **尖括号 `<...>`**
   - 表示**必选参数**。
   - 用户必须提供尖括号中指定的值。
   - 示例：
     ```
     toolname <filename>
     ```
     表示工具需要一个必填的 `filename` 参数。

#### 2. **方括号 `[...]`**
   - 表示**可选参数**。
   - 用户可以选择是否提供这个参数。
   - 示例：
     ```
     toolname [options]
     ```
     表示 `options` 是可选的，用户可以忽略该参数。

#### 3. **方括号加等号 `[=<>]`**
   - 表示**可选参数可以接受值**。
   - 如果选项后需要附加一个值，则通过 `=` 指定。
   - 示例：
     ```
     toolname [--output=<path>]
     ```
     表示 `--output` 是可选的，但如果使用，需要指定一个路径值。

#### 4. **竖线 `|`**
   - 表示**多个选项之间的互斥关系**。
   - 用户只能选择其中一个。
   - 示例：
     ```
     toolname <start|stop|restart>
     ```
     表示用户只能选择 `start`、`stop` 或 `restart` 中的一个。

#### 5. **省略号 `...`**
   - 表示**参数可以重复出现**。
   - 示例：
     ```
     toolname <file1> <file2> ...
     ```
     表示用户可以指定一个或多个文件。

#### 6. **大小写约定**
   - **大写字母** 通常用于表示占位符，用户需要用实际值替换它。
     - 示例：`<FILENAME>` 表示文件名。
   - **小写字母** 通常表示实际命令或选项。
     - 示例：`--verbose` 表示详细模式选项。

#### 7. **组合使用**
   - 多种符号会组合使用，增加表达能力。
   - 示例：
     ```
     toolname [--config=<file>] <input> [output]
     ```
     含义：
     - `--config=<file>` 是可选的，如果使用，需要指定一个配置文件。
     - `<input>` 是必填的输入参数。
     - `[output]` 是可选的输出参数。

### 示例帮助文档
以下是一个完整的命令行工具帮助文档示例：

```bash
Usage: toolname [options] <input> [output]

Options:
  -h, --help              Show this help message and exit
  -o, --output=<file>     Specify output file
  -v, --verbose           Enable verbose mode
  --config=<file>         Use specified configuration file
  -o <file>, --output=<file>
                          Specify the output file.
  --mode=<fast|slow>      Set the mode (fast or slow)
```

## 使用 `getopt` 和 `getopt_long` 解析命令行参数

`getopt` 和 `getopt_long` 是 C 语言中用于解析命令行参数的函数，`getopt` 用于解析短选项，适合简单的命令行工具，而 `getopt_long` 支持长选项和短选项，适合复杂的命令行工具。`getopt` 和 `getopt_long` 对命令行参数格式要求如下：

**短选项：**

- 以单个 `-` 开头，后跟一个字符（如 `-a`）。
- 如果需要参数，可以直接跟在选项后面（如 `-bvalue`）或用空格分隔（如 `-b value`）。

**长选项：**

- 以 `--` 开头，后跟选项名称（如 `--help`）。
- 如果需要参数，可以用 `=` 连接（如 `--output=file.txt`）或用空格分隔（如 `--output file.txt`）。

**选项顺序：**

- 选项可以任意顺序排列。
- 非选项参数（如文件名）必须放在所有选项之后。

### `getopt` 函数

#### 函数原型
```c
#include <unistd.h>

int getopt(int argc, char *const argv[], const char *optstring);
```

- **`argc`**: 命令行参数的数量（和 `main()` 的 `argc` 相同）。
- **`argv`**: 命令行参数的数组（和 `main()` 的 `argv` 相同）。
- **`optstring`**: 选项字符串，定义支持的短选项。

#### 选项字符串格式

- **单个字符**：表示一个短选项（如 `a` 表示 `-a`）。
- **字符后加冒号 `:`**：表示该选项需要一个参数（如 `a:` 表示 `-a` 需要一个参数）。
- **字符后加两个冒号 `::`**：表示该选项的参数是可选的（GNU 扩展）。

#### 返回值

- 返回找到的选项字符。
- 如果选项需要参数，`optarg` 变量会指向该参数。
- 如果所有选项都解析完毕，返回 `-1`。
- 如果遇到未知选项，返回 `?`。

#### 示例

```{literalinclude} ./src/getopt.c
:language: c
```

运行示例:

```bash
➜  src make getopt # 构建
gcc -o getopt getopt.c

➜  src ./getopt -a -b hello -cworld
Option -a
Option -b with value 'hello'
Option -c with value 'world'

➜  src ./getopt -a -b hello -c world
Option -a
Option -b with value 'hello'
Option -c with value 'none' 
```

注意：`-c world`输出的是 `none`，因为根据 `getopt` 规则：

- 如果选项定义为可选参数（`c::`），则参数必须紧跟在选项后面，不能有空格。
- `cworld` 是正确的，而 `-c world` 会被解析为：
    - `-c` 没有参数（`optarg` 为 `NULL`）。
    - `world` 被视为非选项参数（存储在 `argv` 的剩余部分）。
因此，`-c` 输出 `none`，因为 `optarg` 为 `NULL`。

### `getopt_long` 函数

#### 函数原型

```c
#include <getopt.h>

int getopt_long(int argc, char *const argv[], const char *optstring,
                const struct option *longopts, int *longindex);
```

- **`argc`**: 命令行参数的数量。
- **`argv`**: 命令行参数的数组。
- **`optstring`**: 短选项字符串（和 `getopt` 相同）。
- **`longopts`**: 长选项结构体数组。
- **`longindex`**: 如果非 `NULL`，返回匹配的长选项在 `longopts` 中的索引。

#### 长选项结构体

```c
struct option {
    const char *name;    // 长选项名称
    int         has_arg; // 是否需要参数
    int        *flag;    // 如果为 NULL，返回 val；否则将 val 存入 flag
    int         val;     // 返回值或存储的值
};
```

- **`has_arg`**：
  - `no_argument`（0）：不需要参数。
  - `required_argument`（1）：需要参数。
  - `optional_argument`（2）：参数可选。

#### 返回值

- 返回短选项字符或长选项的 `val` 值。
- 如果选项需要参数，`optarg` 变量会指向该参数。
- 如果所有选项都解析完毕，返回 `-1`。
- 如果遇到未知选项，返回 `?`。

#### 示例

```{literalinclude} ./src/getopt_long.c
:language: c
```

运行示例：

```bash
➜  src make getopt_long
gcc -o getopt_long getopt_long.c

➜  src ./getopt_long -h
Help message

➜  src ./getopt_long --output output.txt -v
Output file: output.txt
Verbose mode enabled
```

#### `getopt_long` 解析行为控制

在 `getopt_long` 函数中，可以在选项字符串（optstring）开头的添加特殊字符来对进行解析行为控制。特殊字符有：

1. `+`: 启用 **严格模式**。
  - 在严格模式下，`getopt_long` 会在遇到非选项参数（即不以 `-` 开头的参数）时停止解析选项。

  - 例如，如果命令行参数是 `./program -a foo -b bar，getopt_long` 会在遇到 `foo` 时停止解析，`foo` 和 `-b bar` 会被视为非选项参数。

2. `-` 模式：
  - 如果选项字符串以 `-` 开头，`getopt_long` 会将非选项参数视为选项参数 `1`。
  - 例如，`./program -a foo -b bar` 会将 `foo` 视为选项 `1`。

3. 默认模式：无(`+`/`-`前缀)
  - getopt_long 会重新排列命令行参数，将所有非选项参数移到末尾。
  - 例如，./program -a foo -b bar 会被重新排列为 ./program -a -b foo bar。

:::{note}
只有 `getopt_long` 支持解析行为控制，`getopt` 不支持。
:::
##### 示例

```{literalinclude} ./src/getopt_long_mode.c
:language: c
```

运行示例：

```bash
➜  src git:(main) ✗ ./getopt_long_mode -a foo -b bar
Option -a
Non-option argument: foo
Non-option argument: -b
Non-option argument: bar
```

由于启用了严格模式（+），`getopt_long` 在遇到 `foo` 时停止解析，`foo`、`-b` 和 `bar` 被视为非选项参数。

#### 自定义选项如何避免与短选项字符(-a、-b等)冲突？

通过将长选项结构 `option` 中 `val` 字段标识为特定选项值，来避免与形如 `-a`、`-b` 等ASCII字符串构成的短选项字符冲突。常见解决办法是将 `val` 字段设置成 `CHAR_MAX + 1` 等值，这样不会与短选项字符冲突。`CHAR_MAX` 是 C 标准库中定义的一个宏，表示 char 类型的最大值（通常是 127 或 255，取决于平台）。

```{literalinclude} ./src/getopt_long_customopt.c
:language: c
```

运行示例：

```bash
➜  src make getopt_long_customopt
gcc -o getopt_long_customopt getopt_long_customopt.c

➜  src ./getopt_long_customopt /program --preserve-credentials --keepcaps
Preserve Credentials: 1
Keep Capabilities: 1
User Parent: 0
```

### 获取非选项参数

在使用 `getopt` 或 `getopt_long` 解析命令行参数后，剩余的参数（即非选项参数）可以通过 `optind` 变量获取。`optind` 是 `getopt` 和 `getopt_long` 提供的一个全局变量，表示下一个待处理的参数在 `argv` 中的索引。

**`optind` 的作用：**
- `optind` 初始值为 `1`（因为 `argv[0]` 是程序名称）。
- 每次调用 `getopt` 或 `getopt_long` 时，`optind` 会更新为下一个待处理的参数索引。
- 解析完成后，`optind` 指向第一个非选项参数的位置。

**获取非选项参数的步骤：**
1. 使用 `getopt` 或 `getopt_long` 解析选项。
2. 解析完成后，`optind` 指向第一个非选项参数。
3. 遍历 `argv` 从 `optind` 到 `argc`，即可获取所有剩余参数。

#### 示例
以下是一个完整的示例，展示如何获取剩余参数：

```{literalinclude} ./src/getopt_remain.c
:language: c
```


运行示例：

```bash
➜  src git:(main) ✗ ./getopt_remain -a -b hello foo bar
Option -a
Option -b with value 'hello'
Remaining arguments:
  foo
  bar
```