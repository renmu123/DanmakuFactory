@echo off
REM Windows 调试测试脚本

echo === DanmakuFactory 调试测试 ===
echo.

REM 检查文件是否存在
if not exist ".\build\windows\x64\release\DanmakuFactory.exe" (
    echo 错误: 找不到 DanmakuFactory.exe
    echo 请先编译: xmake
    exit /b 1
)

REM 创建测试黑名单文件
echo 创建测试黑名单文件...
(
echo 11
echo 22
echo 测试
) > test_blacklist.txt

REM 检查是否有测试 XML 文件
if not exist "test.xml" (
    echo 警告: 找不到 test.xml，请提供测试文件
)

echo.
echo === 运行基本测试 ===
.\build\windows\x64\release\DanmakuFactory.exe --debug -i test.xml -o test.ass --blacklist test_blacklist.txt 2>&1 | tee debug.log

echo.
echo === 调试日志已保存到 debug.log ===
echo.
echo 如果程序崩溃，请使用以下命令进行深度调试：
echo.
echo 1. 使用调试版本:
echo    xmake config --mode=debug
echo    xmake
echo    .\build\windows\x64\debug\DanmakuFactory.exe --debug -i test.xml -o test.ass --blacklist test_blacklist.txt
echo.
echo 2. 查看调试日志:
echo    type debug.log
echo.
pause
