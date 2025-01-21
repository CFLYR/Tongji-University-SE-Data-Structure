#include "maze.h" // 包含迷宫相关的头文件

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // 使用当前时间设置随机数种子
    int rows; // 行数
    int cols; // 列数
    cout << "请输入行数（奇数）" << endl; // 提示用户输入行数
    while (1) {
        cin >> rows; // 获取用户输入的行数
        if (cin.fail()) { // 检查输入是否失败
            cin.clear(); // 清除错误标志
            cin.ignore(IGNORE_SIZE, '\n'); // 忽略错误输入
            cout << "输入错误，请重新输入" << endl; // 提示用户重新输入
            continue; // 继续循环
        } else if (rows % 2 == 0) { // 检查输入的行数是否为偶数
            cin.clear(); // 清除错误标志
            cin.ignore(IGNORE_SIZE, '\n'); // 忽略错误输入
            cout << "不支持偶数，请重新输入" << endl; // 提示用户重新输入
            continue; // 继续循环
        } else {
            cin.ignore(IGNORE_SIZE, '\n'); // 忽略多余输入
            break; // 退出循环
        }
    }
    cout << "请输入列数（奇数）" << endl; // 提示用户输入列数
    while (1) {
        cin >> cols; // 获取用户输入的列数
        if (cin.fail()) { // 检查输入是否失败
            cin.clear(); // 清除错误标志
            cin.ignore(IGNORE_SIZE, '\n'); // 忽略错误输入
            cout << "输入错误，请重新输入" << endl; // 提示用户重新输入
            continue; // 继续循环
        } else if (cols % 2 == 0) { // 检查输入的列数是否为偶数
            cin.clear(); // 清除错误标志
            cin.ignore(IGNORE_SIZE, '\n'); // 忽略错误输入
            cout << "不支持偶数，请重新输入" << endl; // 提示用户重新输入
            continue; // 继续循环
        }

        else {
            cin.ignore(IGNORE_SIZE, '\n'); // 忽略多余输入
            break; // 退出循环
        }
    }
    rows = rows + 2; // 增加行数以适应迷宫边界
    cols = cols + 2; // 增加列数以适应迷宫边界
    int startRow = 1; // 起始行
    int startCol = 1; // 起始列
    int targetRow = rows - 2; // 目标行
    int targetCol = cols - 2; // 目标列

    Maze maze(rows, cols, startRow, startCol, targetRow, targetCol); // 创建迷宫对象

    cout << "以PRIM方式生成迷宫如下：" << endl; // 提示用户迷宫生成方式
    maze.output(); // 输出生成的迷宫
    cout << "按ENTER开始寻路" << endl; // 提示用户按回车键开始寻路
    wait_for_enter(); // 等待用户按回车键
    cout << "路线为:" << endl; // 提示用户显示路线
    maze.FindWay(); // 寻找迷宫路径
    maze.output(); // 输出带有路径的迷宫
    cout << "按ENTER开始表示具体路线（文本）" << endl; // 提示用户按回车键显示具体路线
    wait_for_enter(); // 等待用户按回车键
    cout << "路线为:" << endl; // 提示用户显示具体路线
    maze.PrintStack(); // 打印具体路线

#ifdef _WIN32
    system("pause"); // 暂停程序，等待用户按任意键继续
#else
    cout << "按任意键继续..." << endl;
    cin.get(); // 暂停程序，等待用户按任意键继续
#endif

    return 0; // 返回0，表示程序正常结束
}