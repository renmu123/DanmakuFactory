# 调试版本编译指南

## 1. 标准调试模式（命令行参数）

程序已添加 `--debug` 参数支持，无需重新编译即可启用：

```bash
./DanmakuFactory --debug -i input.xml -o output.ass --blacklist blacklist.txt
```

### 输出内容：
- 黑名单文件读取过程
- 每个黑名单条目的内容和长度
- 内存分配信息
- 弹幕处理详情（前5条）

## 2. 高级调试模式（编译时启用）

如果需要更详细的黑名单处理调试信息，可以在编译时启用 `DEBUG_BLOCKLIST` 宏：

### 方法 1：修改源码

在 `src/List/DanmakuFactoryList.c` 文件顶部添加：

```c
#define DEBUG_BLOCKLIST 1
```

### 方法 2：使用编译参数

```bash
xmake config --cflags="-DDEBUG_BLOCKLIST"
xmake
```

或使用 gcc/clang 直接编译时：

```bash
gcc -DDEBUG_BLOCKLIST -o DanmakuFactory src/*.c src/**/*.c -lpcre2-8
```

### 高级调试输出包括：
- blockByType 函数的参数详情
- 所有黑名单关键字列表
- 每个弹幕节点的内存地址和内容
- 指针有效性检查

## 3. 使用 GDB 调试

### 编译调试版本：

```bash
xmake config --mode=debug
xmake
```

### 运行 GDB：

```bash
gdb --args ./build/windows/x64/debug/DanmakuFactory -i input.xml -o output.ass --blacklist blacklist.txt
```

### 常用 GDB 命令：

```gdb
# 设置断点
break blockByType
break main.c:720

# 运行程序
run

# 查看变量
print ptr
print ptr->text
print *keyStrings@10

# 查看内存
x/10x ptr
x/s ptr->text

# 查看堆栈
backtrace

# 单步执行
next
step

# 继续执行
continue
```

## 4. 使用 Valgrind 检测内存问题

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  ./DanmakuFactory -i input.xml -o output.ass --blacklist blacklist.txt
```

## 5. 使用 strace 跟踪系统调用

```bash
strace -f ./DanmakuFactory -i input.xml -o output.ass --blacklist blacklist.txt
```

## 6. 使用 AddressSanitizer (ASan)

编译时启用 ASan：

```bash
export CFLAGS="-fsanitize=address -g"
export LDFLAGS="-fsanitize=address"
xmake config --cflags="-fsanitize=address -g" --ldflags="-fsanitize=address"
xmake
```

运行：

```bash
./build/windows/x64/debug/DanmakuFactory -i input.xml -o output.ass --blacklist blacklist.txt
```

## 7. Docker 环境调试

如果在 Docker 中运行：

```bash
# 安装调试工具
docker exec -it <container> apt-get update
docker exec -it <container> apt-get install -y gdb valgrind strace

# 进入容器
docker exec -it <container> bash

# 使用上述调试方法
gdb --args /app/video/DanmakuFactory --debug -i aa.xml -o aa.ass --blacklist blacklist
```

## 8. 调试技巧

### 添加自定义调试点

在代码中任意位置添加：

```c
DEBUG_PRINT("Variable value: %d, pointer: %p\n", someVar, (void*)somePtr);
```

### 检查指针有效性：

```c
if (ptr == NULL) {
    DEBUG_PRINT("ERROR: ptr is NULL at line %d\n", __LINE__);
}
```

### 打印数组内容：

```c
DEBUG_PRINT("Array contents:\n");
for (int i = 0; keyStrings[i] != NULL; i++) {
    DEBUG_PRINT("  [%d] = '%s'\n", i, keyStrings[i]);
}
```

## 9. 常见问题诊断

### 段错误 (SIGSEGV)

1. 使用 `--debug` 参数查看最后处理的数据
2. 使用 gdb 的 `backtrace` 查看崩溃位置
3. 检查是否访问了 NULL 指针
4. 检查数组越界

### 内存泄漏

1. 使用 Valgrind 检测
2. 确保每个 malloc 都有对应的 free
3. 检查 config.blocklist 是否在程序结束时被释放

### 黑名单不生效

1. 使用 `--debug` 查看黑名单是否正确加载
2. 检查黑名单文件编码（应为 UTF-8）
3. 检查关键字是否包含特殊字符
