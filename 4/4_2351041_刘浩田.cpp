#include "BackChange.h"

int main()
{
    char infix[kMaxSize]; // �洢�������׺���ʽ
    char postfix[kMaxSize * 2]; // �洢ת����ĺ�׺���ʽ

    // ��ʾ�û�������׺���ʽ
    cout << "��������׺���ʽ��" << endl;
    cin.getline(infix, kMaxSize);

    // ���ú�������׺���ʽת��Ϊ��׺���ʽ
    InfixToPostfix(infix, postfix);

    // ���ת����ĺ�׺���ʽ
    cout << "ת����ĺ�׺���ʽ��" << endl;
    cout << postfix << endl;

#ifdef _WIN32
    system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    cout << "���س�������..." << endl;
    cin.get();
#endif

    return 0;
}