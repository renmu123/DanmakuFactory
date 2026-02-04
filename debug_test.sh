#!/bin/bash
# 调试测试脚本

echo "=== DanmakuFactory 调试测试 ==="
echo ""

# 检查文件是否存在
if [ ! -f "./DanmakuFactory" ]; then
    echo "错误: 找不到 DanmakuFactory 可执行文件"
    echo "请先编译: xmake"
    exit 1
fi

# 创建测试黑名单文件
echo "创建测试黑名单文件..."
cat > test_blacklist.txt << 'EOF'
11
22
测试
EOF

# 检查是否有测试 XML 文件
if [ ! -f "test.xml" ]; then
    echo "警告: 找不到 test.xml，请提供测试文件"
fi

echo ""
echo "=== 运行基本测试 ==="
./DanmakuFactory --debug -i test.xml -o test.ass --blacklist test_blacklist.txt 2>&1 | tee debug.log

echo ""
echo "=== 调试日志已保存到 debug.log ==="
echo ""
echo "如果程序崩溃，请使用以下命令进行深度调试："
echo ""
echo "1. 使用 GDB:"
echo "   gdb --args ./DanmakuFactory --debug -i test.xml -o test.ass --blacklist test_blacklist.txt"
echo ""
echo "2. 使用 Valgrind (Linux):"
echo "   valgrind --leak-check=full ./DanmakuFactory --debug -i test.xml -o test.ass --blacklist test_blacklist.txt"
echo ""
echo "3. 查看调试日志:"
echo "   cat debug.log"
echo ""
