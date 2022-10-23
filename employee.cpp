#include"employee.h"

Employee::Employee(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepId = dId;
}

void Employee::showInfo()
{
	cout << "职工编号:" << this->m_Id
		<< "\t" << "职工姓名:" << this->m_Name
		<< "\t" << "部门名称:" << this->getDeptName() << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}