#include "LinkListIntersection.h" // 包含头文件

using namespace std;

int main()
{
    // 提示用户输入第一行非降序链表序列，以-1结尾
    cout << "请输入第一行非降序链表序列，以-1结尾" << endl;
    List<int> Link_1 = {}; // 创建第一个链表对象
    Link_1.Insert_multiple(); // 插入多个元素到第一个链表
    cout << "你输入的第一行非降序链表序列为：" << endl;
    if (!Link_1.Length()) { // 如果链表为空
        cout << "NULL" << endl; // 输出NULL
    } else {
        Link_1.Print(); // 打印链表
        cout << endl;
    }
    cin.ignore(IGNORE_SIZE, '\n'); // 忽略输入缓冲区中的字符
    // 提示用户输入第二行非降序链表序列，以-1结尾
    cout << "请输入第二行非降序链表序列，以-1结尾" << endl;
    List<int> Link_2 = {}; // 创建第二个链表对象
    Link_2.Insert_multiple(); // 插入多个元素到第二个链表
    cout << "你输入的第二行非降序链表序列为：" << endl;
    if (!Link_2.Length()) { // 如果链表为空
        cout << "NULL" << endl; // 输出NULL
    } else {
        Link_2.Print(); // 打印链表
        cout << endl;
    }
    int pos = 1; // 初始化位置变量
    int check = 0; // 初始化检查变量
    List<int> Link_same = {}; // 创建存储相同元素的链表对象
    // 遍历第一个链表
    for (int i = 1; i <= Link_1.Length(); i++) {
        // 遍历第二个链表
        for (int j = 1; j <= Link_2.Length(); j++) {
            // 如果两个链表的元素相同
            if (Link_1.Truenum(i) == Link_2.Truenum(j)) {
                // 如果相同元素不在Link_same中
                if (!Link_same.Findpos(Link_2.Truenum(j))) {
                    Link_same.Insert(Link_1.Truenum(i), pos); // 插入相同元素到Link_same
                    check++; // 增加检查计数
                    pos++; // 增加位置计数
                }
            }
        }
    }
    // 输出对比结果
    cout << "对比两链表结果如下：" << endl;
    cout << "相同数据为：";
    if (!Link_same.Length()) { // 如果没有相同元素
        cout << "NULL" << endl; // 输出NULL
    } else {
        Link_same.Print(); // 打印相同元素
        cout << endl;
    }
    // 输出具体说明
    cout << "具体说明为：";
    if (!Link_1.Length() || !Link_2.Length()) { // 如果其中一个链表为空
        cout << "其中一个序列为空的情况" << endl;
    } else if (!Link_same.Length()) { // 如果没有相同元素
        cout << "交集为空的情况" << endl;
    } else if (check == Link_1.Length() && check == Link_2.Length()) { // 如果两个链表完全相交
        cout << "完全相交的情况" << endl;
    } else if (check == Link_1.Length() || check == Link_2.Length()) { // 如果其中一个链表完全属于交集
        cout << "其中一个序列完全属于交集的情况" << endl;
    } else {
        cout << "一般情况" << endl; // 一般情况
    }
#ifdef _WIN32
    system("pause"); // 暂停系统，等待用户输入
#elif __linux__
    cout << "按回车键继续..." << endl;
    cin.get(); // 暂停系统，等待用户输入
#endif
    return 0; // 返回0
}