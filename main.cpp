#include<iostream>
#include"workerManager.h"
using namespace std;

int main()
{
	WorkerManager wm;
	int choice = 0;

	while (true)
	{
		wm.showMenu();   //��ʾ�˵�
		cout << "�������ѡ��";
		cin >> choice;  cout << endl;
		switch (choice)
		{
		case 0 :   //�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1:  //���ְ��
			wm.Add_Emp();
			break;
		case 2:  //��ʾְ��
			wm.show_Emp();
			break;
		case 3:  //ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4:  //�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:  //����ְ��
			wm.Find_Emp();
			break;
		case 6:  //�������
			break;
		case 7:  //����ļ�
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}