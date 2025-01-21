#include "BackChange.h"

int main()
{
    char infix[kMaxSize]; // 存储输入的中缀表达式
    char postfix[kMaxSize * 2]; // 存储转换后的后缀表达式

    // 提示用户输入中缀表达式
    cout << "请输入中缀表达式：" << endl;
    cin.getline(infix, kMaxSize);

    // 调用函数将中缀表达式转换为后缀表达式
    InfixToPostfix(infix, postfix);

    // 输出转换后的后缀表达式
    cout << "转换后的后缀表达式：" << endl;
    cout << postfix << endl;

#ifdef _WIN32
    system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    cout << "按回车键继续..." << endl;
    cin.get();
#endif

    return 0;
}