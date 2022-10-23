#pragma once

#include<iostream>
#include "worker.h"

#include<fstream>  //文件流
#define FILENAME "empFile.txt"   //文件
using namespace std;

class WorkerManager
{

public:
	//记录文件中的人数
	int m_EmpNum;

	//员工数组的指针
	Worker** m_EmpArray;

	//标志文件为空
	bool m_FileIsEmpty;

	//统计人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	WorkerManager();   //构造函数

	void showMenu();   // 菜单功能

	void Add_Emp();  //添加职工

	void save();  //保存文件

	void exitSystem();   //退出系统

	void show_Emp(); //显示职工

	int IsExist(int id);  //判断职工是否存在

	void Del_Emp();   //删除职工

	void Mod_Emp();   //修改职工

	void Find_Emp();  //查找职工

	~WorkerManager();  //析构函数
};