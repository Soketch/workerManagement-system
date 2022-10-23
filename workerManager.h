#pragma once

#include<iostream>
#include "worker.h"

#include<fstream>  //�ļ���
#define FILENAME "empFile.txt"   //�ļ�
using namespace std;

class WorkerManager
{

public:
	//��¼�ļ��е�����
	int m_EmpNum;

	//Ա�������ָ��
	Worker** m_EmpArray;

	//��־�ļ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	WorkerManager();   //���캯��

	void showMenu();   // �˵�����

	void Add_Emp();  //���ְ��

	void save();  //�����ļ�

	void exitSystem();   //�˳�ϵͳ

	void show_Emp(); //��ʾְ��

	int IsExist(int id);  //�ж�ְ���Ƿ����

	void Del_Emp();   //ɾ��ְ��

	void Mod_Emp();   //�޸�ְ��

	void Find_Emp();  //����ְ��

	~WorkerManager();  //��������
};