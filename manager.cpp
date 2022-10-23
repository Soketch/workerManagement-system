#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepId = dId;
}

void Manager::showInfo()
{
	cout << "职工编号:" << this->m_Id
		<< "\t" << "职工姓名:" << this->m_Name
		<< "\t" << "部门名称:" << this->getDeptName() << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}