#include"manager.h"

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DepId = dId;
}

void Manager::showInfo()
{
	cout << "ְ�����:" << this->m_Id
		<< "\t" << "ְ������:" << this->m_Name
		<< "\t" << "��������:" << this->getDeptName() << endl;
}

string Manager::getDeptName()
{
	return string("����");
}