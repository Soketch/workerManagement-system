#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

WorkerManager::WorkerManager()
{
	//��ʼ��
	this->m_EmpArray = NULL;
	this->m_EmpNum = 0;

	ifstream ifs;
	ifs.open(FILENAME, ios::in);   //  in ���ļ�
	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;   //�������
		this->m_EmpNum = 0;   //��ʼ������
		this->m_FileIsEmpty = true;   //��ʼ���ļ�Ϊ�ձ�־
		this->m_EmpArray = NULL;  //��ʼ������
		ifs.close();   //�ر��ļ�
		return;
	}

	//�ļ����ڣ���û������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�����Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}


	//���ļ����ڣ��ұ���������
	int num = this->get_EmpNum();
	cout << "��ǰְ��������" << num << endl;
	this->m_EmpNum = num;


	//����ְ������������
	this->m_EmpArray = new Worker * [this->m_EmpNum];

	//��ʼ��ְ��
	init_Emp();

	//���Դ���
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "ְ�����:" << this->m_EmpArray[i]->m_Id << "\t"
	//		<< "  ְ������:" << this->m_EmpArray[i]->m_Name << "\t"
	//		<< "  ����ְ��:" << this->m_EmpArray[i]->m_DepId << endl;
	//}

}

void WorkerManager::showMenu()
{
	cout << "***********�˵�����***********" << endl;
	cout << "****   0 -- �˳�ְ��ϵͳ  ****" << endl;
	cout << "****   1 -- ����ְ����Ϣ  ****" << endl;
	cout << "****   2 -- ��ʾְ����Ϣ  ****" << endl;
	cout << "****   3 -- ɾ����ְְ��  ****" << endl;
	cout << "****   4 -- �޸�ְ����Ϣ  ****" << endl;
	cout << "****   5 -- ����ְ����Ϣ  ****" << endl;
	cout << "****   6 -- ���ձ������  ****" << endl;
	cout << "****   7 -- ��������ĵ�  ****" << endl;
	cout << "******************************" << endl;
	cout << "������������������������������" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::save()
{  
	ofstream ofs;
	ofs.open(FILENAME, ios::out);   //���ļ�

	for (int i = 0; i < this->m_EmpNum; i++)   //����ÿ��ְ������
	{
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DepId << endl;
	}
	ofs.close();  //�ر��ļ�
}


void WorkerManager::Add_Emp()  //���ְ��
{
	cout << "�������ְ������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//����ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ�ռ������ݷŵ��¿ռ�
		if (this->m_EmpNum != NULL)
		{
			for (int i = 0; i<this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//����������
		for (int j = 0; j < addNum; j++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������" << j + 1 << "����ְ�����" << endl;
			cin >> id;

			cout << "�������" << j + 1 << "����ְ������" << endl;
			cin >> name;

			cout << "��ѡ��ְ����λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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

		//�ͷ�ԭ���ռ�
		delete[] this->m_EmpArray;
		//���¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//���¿ռ�����
		this->m_EmpNum = newSize;
		//��ʾ��Ϣ
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		this->save();  //�������ݵ��ļ���

	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��!" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id)
{
	//�ж�ְ���Ƿ����
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
		cout << "�ļ�������" << endl;
	}
	else
	{
		int id;
		//����ְ�����ɾ��
		cout << "������Ҫɾ����ְ�����:";
		cin >> id;      cout << endl;
		int index = this->IsExist(id);
		if (index != -1)
		{
			//������ɾ�� ��������ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;  //ɾ����������һ

			this->save();  //������ļ�
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "δ�ҵ���ɾ��ʧ��" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�������Ϊ��" << endl;
	}
	else
	{
		int id;
		cout << "������Ҫ�޸ĵ�ְ����ţ�";
		cin >> id;  cout << endl;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//�鵽ְ�����
			delete this->m_EmpArray[ret];
			int NewId = 0; 
			string NewName = "";
			int dSelect = 0;

			cout << "�鵽" << id << "��ְ�����������µ�ְ����ţ�";
			cin >> NewId; cout << endl;

			cout << "�����µ�������";
			cin >> NewName; cout << endl;

			cout << "�����µĸ�λ" << endl;
			cout << "1 -- ��ְͨ��" << endl;
			cout << "2 --   ����  " << endl;
			cout << "3 --   �ϰ�  " << endl;
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

			//���µ�������

			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << this->m_EmpArray[ret]->m_DepId << endl;

			//���浽�ļ�
			this->save();
		}
		else
		{
			cout << "δ�ҵ�������ʧ�ܣ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�������Ϊ��" << endl;
	}
	else
	{
		int select = 0;
		cout << "���ҷ�ʽ�� 1 -- ��Ų���  ||  2 -- ��������" << endl;
		cout << "�����룺";
		cin >> select;  cout << endl;
		
		if (select == 1)
		{
			//���ձ�Ų���
			int id;
			cout << "�������ţ�";
			cin >> id; cout << endl;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�!  ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "δ�ҵ��ñ��" << endl;
			}
		}
		else if (select == 2)
		{
			//������������
			string F_name;
			cout << "������������";
			cin >> F_name; cout << endl;

			bool flag = false;  //Ĭ��Ϊδ�ҵ�
			for (int k = 0; k < this->m_EmpNum; k++)
			{
				if (this->m_EmpArray[k]->m_Name == F_name)
				{
					cout << "���ҳɹ�!  ְ����Ϣ���£�" << endl;
					flag = true;
					this->m_EmpArray[k]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "δ�ҵ���ְ��" << endl;
			}

		}
		else {
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}


//�ļ����ڣ���������
//ͳ������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);   //��ȡ����

	int id;
	string name;
	int dId;

	int num = 0;    //����-����

	while (ifs >> id && ifs >> name && ifs>>dId)
	{
		//��¼����
		num++;
	}
	ifs.close();

	return num;
}

//��ʼ������
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::out);
	int id; 
	string name; 
	int dId;

	int index = 0;   //����

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;  

		//���ݲ�ְͬ��ID������ͬ����
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

		//����������
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