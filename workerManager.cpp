#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

WorkerManager::WorkerManager()
{
	//初始化
	this->m_EmpArray = NULL;
	this->m_EmpNum = 0;

	ifstream ifs;
	ifs.open(FILENAME, ios::in);   //  in 读文件
	//文件不存在的情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;   //测试输出
		this->m_EmpNum = 0;   //初始化人数
		this->m_FileIsEmpty = true;   //初始化文件为空标志
		this->m_EmpArray = NULL;  //初始化数组
		ifs.close();   //关闭文件
		return;
	}

	//文件存在，但没有数据
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件数据为空" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}


	//当文件存在，且保存有数据
	int num = this->get_EmpNum();
	cout << "当前职工人数：" << num << endl;
	this->m_EmpNum = num;


	//根据职工数创建数组
	this->m_EmpArray = new Worker * [this->m_EmpNum];

	//初始化职工
	init_Emp();

	//测试代码
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "职工编号:" << this->m_EmpArray[i]->m_Id << "\t"
	//		<< "  职工姓名:" << this->m_EmpArray[i]->m_Name << "\t"
	//		<< "  部门职务:" << this->m_EmpArray[i]->m_DepId << endl;
	//}

}

void WorkerManager::showMenu()
{
	cout << "***********菜单功能***********" << endl;
	cout << "****   0 -- 退出职工系统  ****" << endl;
	cout << "****   1 -- 增加职工信息  ****" << endl;
	cout << "****   2 -- 显示职工信息  ****" << endl;
	cout << "****   3 -- 删除离职职工  ****" << endl;
	cout << "****   4 -- 修改职工信息  ****" << endl;
	cout << "****   5 -- 查找职工信息  ****" << endl;
	cout << "****   6 -- 按照编号排序  ****" << endl;
	cout << "****   7 -- 清空所有文档  ****" << endl;
	cout << "******************************" << endl;
	cout << "———————————————" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::save()
{  
	ofstream ofs;
	ofs.open(FILENAME, ios::out);   //打开文件

	for (int i = 0; i < this->m_EmpNum; i++)   //保存每个职工数据
	{
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DepId << endl;
	}
	ofs.close();  //关闭文件
}


void WorkerManager::Add_Emp()  //添加职工
{
	cout << "输入添加职工数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//计算空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间下内容放到新空间
		if (this->m_EmpNum != NULL)
		{
			for (int i = 0; i<this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int j = 0; j < addNum; j++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << j + 1 << "个新职工编号" << endl;
			cin >> id;

			cout << "请输入第" << j + 1 << "个新职工姓名" << endl;
			cin >> name;

			cout << "请选择职工岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id,name,3);
				break;
			
			}
			newSpace[this->m_EmpNum + j] = worker;
		}

		//释放原来空间
		delete[] this->m_EmpArray;
		//更新空间指向
		this->m_EmpArray = newSpace;
		//更新空间人数
		this->m_EmpNum = newSize;
		//提示信息
		cout << "成功添加" << addNum << "名新职工" << endl;

		this->save();  //保存数据到文件中

	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	//判断职工是否存在
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		int id;
		//按照职工编号删除
		cout << "输入需要删除的职工编号:";
		cin >> id;      cout << endl;
		int index = this->IsExist(id);
		if (index != -1)
		{
			//数组中删除 本质数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;  //删除完人数减一

			this->save();  //保存进文件
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "未找到，删除失败" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者数据为空" << endl;
	}
	else
	{
		int id;
		cout << "输入需要修改的职工编号：";
		cin >> id;  cout << endl;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查到职工编号
			delete this->m_EmpArray[ret];
			int NewId = 0; 
			string NewName = "";
			int dSelect = 0;

			cout << "查到" << id << "号职工，请输入新的职工编号：";
			cin >> NewId; cout << endl;

			cout << "输入新的姓名：";
			cin >> NewName; cout << endl;

			cout << "输入新的岗位" << endl;
			cout << "1 -- 普通职工" << endl;
			cout << "2 --   经理  " << endl;
			cout << "3 --   老板  " << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(NewId, NewName, dSelect);
				break;
			case 2:
				worker = new Manager(NewId, NewName, dSelect);
				break;
			case 3:
				worker = new Boss(NewId, NewName, dSelect);
				break;
			default:
				break;
			}

			//更新到数组中

			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << this->m_EmpArray[ret]->m_DepId << endl;

			//保存到文件
			this->save();
		}
		else
		{
			cout << "未找到，更新失败！" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者数据为空" << endl;
	}
	else
	{
		int select = 0;
		cout << "查找方式： 1 -- 编号查找  ||  2 -- 姓名查找" << endl;
		cout << "请输入：";
		cin >> select;  cout << endl;
		
		if (select == 1)
		{
			//按照编号查找
			int id;
			cout << "请输入编号：";
			cin >> id; cout << endl;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功!  职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "未找到该编号" << endl;
			}
		}
		else if (select == 2)
		{
			//按照姓名查找
			string F_name;
			cout << "请输入姓名：";
			cin >> F_name; cout << endl;

			bool flag = false;  //默认为未找到
			for (int k = 0; k < this->m_EmpNum; k++)
			{
				if (this->m_EmpArray[k]->m_Name == F_name)
				{
					cout << "查找成功!  职工信息如下：" << endl;
					flag = true;
					this->m_EmpArray[k]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "未找到该职工" << endl;
			}

		}
		else {
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}


//文件存在，且有数据
//统计人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);   //读取数据

	int id;
	string name;
	int dId;

	int num = 0;    //人数-计数

	while (ifs >> id && ifs >> name && ifs>>dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}

//初始化数组
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::out);
	int id; 
	string name; 
	int dId;

	int index = 0;   //索引

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;  

		//根据不同职务ID创建不同对象
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}

		//存入数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
}


WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}