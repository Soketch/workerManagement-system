#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class Manager:public Worker
{
public:
	Manager(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();

	//获取职工岗位名称
	virtual string getDeptName();
};