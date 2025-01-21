#include "BankService.h"

int main()
{
    // 提示用户输入顾客总数和顾客编号
    cout << "请输入一行正整数，其中第一数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号。" << endl;

    int sum;
    // 检查输入的sum是否在0到1000之间
    checkCin(sum, 0, 1000, 0);

    // 初始化两个队列A和B，最大容量为1000
    Queue<int> Q_A(1000);
    Queue<int> Q_B(1000);

    // 将顾客编号分配到队列A或B
    for (int i = 0; i < sum; i++) {
        int id;
        checkCin(id, 0, 1000, 0);
        if (Q_A.CheckQuene(id)) {
            Q_A.EnQueue(id); // 奇数编号进入A窗口
        } else {
            Q_B.EnQueue(id); // 偶数编号进入B窗口
        }
    }

    // 打印A窗口的顾客
    cout << "A窗口顾客为：" << endl;
    Q_A.Print();

    // 打印B窗口的顾客
    cout << "B窗口顾客为：" << endl;
    Q_B.Print();

    // 提示用户按回车键开始办理业务
    cout << "按下enter开始办理业务" << endl;
    wait_for_enter();

    // 办理结束，显示办理顺序
    cout << "办理结束，办理结束先后顺序为：" << endl;
    Queue<int> Q_out(1000);
    int time_1;

    // 确定办理的轮数
    if (Q_A.Length() / 2 > Q_B.Length()) {
        time_1 = Q_B.Length();
    } else {
        time_1 = Q_A.Length() / 2;
    }

    // 依次从A和B队列中出队并加入输出队列
    for (int i = 0; i < time_1; i++) {
        Q_out.EnQueue(Q_A.GetFront());
        Q_A.DeQueue();
        Q_out.EnQueue(Q_A.GetFront());
        Q_A.DeQueue();
        Q_out.EnQueue(Q_B.GetFront());
        Q_B.DeQueue();
    }

    // 处理剩余的A队列顾客
    if (!Q_A.IsEmpty()) {
        Q_out.EnQueue(Q_A.GetFront());
        Q_A.DeQueue();
    }
    if (!Q_A.IsEmpty()) {
        for (; Q_A.Length();) {
            Q_out.EnQueue(Q_A.GetFront());
            Q_A.DeQueue();
        }
    } else if (!Q_B.IsEmpty()) {
        for (; Q_B.Length();) {
            Q_out.EnQueue(Q_B.GetFront());
            Q_B.DeQueue();
        }
    }
    // 打印办理顺序
    Q_out.Print();
#ifdef _WIN32
    system("pause"); // 暂停系统，等待用户操作
#else
    cout << "按下enter键退出程序" << endl;
    wait_for_enter();
#endif
    return 0;
}