/* MIT License
 *
 * Copyright (c) 2022 hkm
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

/* 
 * 调试宏定义
 * 
 * 用法：
 * 1. 运行时启用调试（推荐）：
 *    使用命令行参数 --debug
 * 
 * 2. 编译时启用特定模块调试：
 *    gcc -DDEBUG_BLOCKLIST -DDEBUG_XML_PARSE ...
 * 
 * 3. 在源码中临时启用：
 *    在包含此头文件前定义对应的宏
 */

/* 黑名单处理调试 */
#ifdef DEBUG_BLOCKLIST
    #define DEBUG_BLOCKLIST_PRINT(...) fprintf(stderr, "[DEBUG BLOCKLIST] " __VA_ARGS__)
#else
    #define DEBUG_BLOCKLIST_PRINT(...) ((void)0)
#endif

/* XML 解析调试 */
#ifdef DEBUG_XML_PARSE
    #define DEBUG_XML_PRINT(...) fprintf(stderr, "[DEBUG XML] " __VA_ARGS__)
#else
    #define DEBUG_XML_PRINT(...) ((void)0)
#endif

/* 内存分配调试 */
#ifdef DEBUG_MEMORY
    #define DEBUG_MEM_PRINT(...) fprintf(stderr, "[DEBUG MEMORY] " __VA_ARGS__)
#else
    #define DEBUG_MEM_PRINT(...) ((void)0)
#endif

/* 链表操作调试 */
#ifdef DEBUG_LIST
    #define DEBUG_LIST_PRINT(...) fprintf(stderr, "[DEBUG LIST] " __VA_ARGS__)
#else
    #define DEBUG_LIST_PRINT(...) ((void)0)
#endif

/* 文件操作调试 */
#ifdef DEBUG_FILE
    #define DEBUG_FILE_PRINT(...) fprintf(stderr, "[DEBUG FILE] " __VA_ARGS__)
#else
    #define DEBUG_FILE_PRINT(...) ((void)0)
#endif

/* 通用调试宏（总是可用，受 g_debugMode 控制） */
#ifndef DEBUG_PRINT
    extern int g_debugMode;
    #define DEBUG_PRINT(...) do { \
        if (g_debugMode) { \
            fprintf(stderr, "[DEBUG] "); \
            fprintf(stderr, __VA_ARGS__); \
        } \
    } while(0)
#endif

/* 调试辅助宏 */
#define DEBUG_VAR(var) DEBUG_PRINT(#var " = %d\n", (var))
#define DEBUG_PTR(ptr) DEBUG_PRINT(#ptr " = %p\n", (void*)(ptr))
#define DEBUG_STR(str) DEBUG_PRINT(#str " = '%s'\n", (str) ? (str) : "(null)")
#define DEBUG_FUNC() DEBUG_PRINT("Entering %s() at %s:%d\n", __func__, __FILE__, __LINE__)

/* 条件调试宏 */
#define DEBUG_IF(cond, ...) do { if (cond) { DEBUG_PRINT(__VA_ARGS__); } } while(0)

/* 错误调试宏 */
#define DEBUG_ERROR(...) fprintf(stderr, "[ERROR] " __VA_ARGS__)
#define DEBUG_WARN(...) fprintf(stderr, "[WARN] " __VA_ARGS__)

/* 性能计时宏（需要 time.h） */
#ifdef DEBUG_PERFORMANCE
    #include <time.h>
    #define DEBUG_TIMER_START() clock_t _debug_start = clock()
    #define DEBUG_TIMER_END(msg) do { \
        clock_t _debug_end = clock(); \
        double _debug_time = ((double)(_debug_end - _debug_start)) / CLOCKS_PER_SEC; \
        fprintf(stderr, "[DEBUG PERF] %s: %.6f seconds\n", msg, _debug_time); \
    } while(0)
#else
    #define DEBUG_TIMER_START() ((void)0)
    #define DEBUG_TIMER_END(msg) ((void)0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H__ */
