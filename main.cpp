#include<iostream>
#include"workerManager.h"
using namespace std;

int main()
{
	WorkerManager wm;
	int choice = 0;

	while (true)
	{
		wm.showMenu();   //显示菜单
		cout << "输入你的选择：";
		cin >> choice;  cout << endl;
		switch (choice)
		{
		case 0 :   //退出系统
			wm.exitSystem();
			break;
		case 1:  //添加职工
			wm.Add_Emp();
			break;
		case 2:  //显示职工
			wm.show_Emp();
			break;
		case 3:  //删除职工
			wm.Del_Emp();
			break;
		case 4:  //修改职工
			wm.Mod_Emp();
			break;
		case 5:  //查找职工
			wm.Find_Emp();
			break;
		case 6:  //编号排序
			break;
		case 7:  //清空文件
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}