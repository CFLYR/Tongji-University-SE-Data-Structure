#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"

using namespace std;

// 主函数
int main()
{
    print_line(); // 打印分割线
    cout << "首先请建立考生信息系统！" << endl;
    print_line();
    cout << "请输入考生人数：" << endl;
    print_line();
    int num;
    while (1) {
        cin >> num; // 输入考生人数
        if (cin.fail()) { // 检查输入是否失败
            cin.clear();
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "输入错误，请重新输入" << endl;
            continue;
        } else if (num <= 0) { // 检查输入是否为正数
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "输入错误，请重新输入" << endl;
            continue;
        } else {
            cin.ignore(IGNORE_SIZE, '\n');
            break;
        }
    }
    print_line();
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
    print_line();
    stu_list all_list; // 创建学生列表对象
    all_list.input_students(num); // 输入考生信息
    print_line();
    cout << "系统信息为：" << endl;
    print_line();
    print_chart(); // 打印图表
    print_line();
    all_list.print_students(); // 打印所有考生信息
    print_line();
    int choice = 1;
    while (choice) { // 操作循环
        cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
        while (1) {
            cin >> choice; // 输入操作选择
            if (cin.fail()) { // 检查输入是否失败
                cin.clear();
                cin.ignore(IGNORE_SIZE, '\n');
                cout << "输入错误，请重新输入" << endl;
                continue;
            } else if (choice < 0 || choice > 5) { // 检查选择是否在有效范围
                cin.ignore(IGNORE_SIZE, '\n');
                cout << "输入错误，请重新输入" << endl;
                continue;
            } else {
                cin.ignore(IGNORE_SIZE, '\n');
                break;
            }
        }
        switch (choice) {
        case 0:
            break; // 取消操作
        case 1:
            cout << "请输入想要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
            all_list.input_students(1); // 插入新考生
            break;
        case 2:
            cout << "请输入想要删除的考生的考号" << endl;
            int id_2;
            while (1) {
                cin >> id_2; // 输入要删除的考生编号
                if (cin.fail()) { // 检查输入是否失败
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "输入错误，请重新输入" << endl;
                    continue;
                } else if (!all_list.find_student(id_2)) { // 检查考生是否存在
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "不存在此考生，请重新输入" << endl;
                    continue;
                } else {
                    cin.ignore(IGNORE_SIZE, '\n');
                    break;
                }
            }
            id_2 = all_list.find_studentpos(id_2); // 查找考生位置
            all_list.remove_student(id_2); // 删除考生
            break;
        case 3:
            cout << "请输入想要查找的考生的考号" << endl;
            int id_3;
            while (1) {
                cin >> id_3; // 输入要查找的考生编号
                if (cin.fail()) { // 检查输入是否失败
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "输入错误，请重新输入" << endl;
                    continue;
                } else if (!all_list.find_studentpos(id_3)) { // 检查考生是否存在
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "不存在此考生，请重新输入" << endl;
                    continue;
                } else {
                    cin.ignore(IGNORE_SIZE, '\n');
                    break;
                }
            }
            print_line();
            cout << "你想查找的考生为：" << endl;
            print_line();
            all_list.print_single_stu(id_3); // 打印单个考生信息
            print_line();
            break;
        case 4:
            cout << "请输入想要修改的考生的考号" << endl;
            int id_4;
            while (1) {
                cin >> id_4; // 输入要修改的考生编号
                if (cin.fail()) { // 检查输入是否失败
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "输入错误，请重新输入" << endl;
                    continue;
                } else if (!all_list.find_studentpos(id_4)) { // 检查考生是否存在
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "不存在此考生，请重新输入" << endl;
                    continue;
                } else {
                    cin.ignore(IGNORE_SIZE, '\n');
                    break;
                }
            }
            all_list.remove_student(all_list.find_studentpos(id_4)); // 删除旧信息
            cout << "请输入想要修改的考生的姓名，性别，年龄及报考类别！" << endl;
            all_list.input_students(1, id_4); // 输入新信息
            print_line();
            cout << "你成功将考号为" << id_4 << "的考生信息修改为：" << endl;
            print_line();
            all_list.print_single_stu(id_4); // 打印修改后的信息
            print_line();
            break;
        case 5:
            print_line();
            cout << "开始统计......" << endl;
            print_line();
            cout << "考生人数为：" << endl;
            cout << all_list.find_studentnum() << endl; // 打印考生人数
            print_line();
            cout << "考生性别汇总为：" << endl;
            all_list.student_sex(); // 汇总性别
            print_line();
            cout << "考生平均年龄为：" << endl;
            all_list.average_age(); // 计算平均年龄
            print_line();
            cout << "考生报考类别汇总为：" << endl;
            MyJob job_count;
            all_list.summarize_jobs(job_count); // 汇总报考类别
            job_count.print(); // 打印报考类别统计
            print_line();
            break;
        }
        cout << endl;
        cout << "操作完成！！" << endl;
        cout << endl;
        print_line();
        cout << "进行操作后的系统信息为" << endl;
        print_line();
        print_chart(); // 打印更新后的图表
        print_line();
        all_list.print_students(); // 打印更新后的考生信息
        print_line();
    }
    cout << "完成操作，退出系统......" << endl;
    print_line();
    return 0; // 程序结束
}