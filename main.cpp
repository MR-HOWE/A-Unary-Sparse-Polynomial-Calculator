#include <iostream>
#include <cmath>

using namespace std;

struct item
{
	double coe;//coefficient ϵ��
	int exp;//exponent ָ��
	item* next;
};

void insert(item* pol,item* head)
{
	if(pol->coe == 0)
	{
		delete pol;
		return;
	}
	item* f = head;
	head = head->next;
	while(head != NULL && pol->exp < head->exp)//���Ҳ���λ��,ָ����������
	{
		f = head;
		head = head->next;
	}
	if(head != NULL && pol->exp == head->exp)//���ָ����ͬ��ϲ���
	{
		head->coe += pol->coe;
		delete pol;
		if(head->coe == 0)//ϵ����Ӻ����Ϊ0�Ļ��ͷŽ��
		{
			f->next = head->next;
			delete head;
		}
	}
	else//ָ��Ϊ��ʱ��������
	{
		pol->next = head;
		f->next = pol;
	}
}

item* createPol(int num,void insertPol(item* pol,item* head))//�������ʽ����
{
	item* head = new item;

	head->coe = 0;
	head->exp = 0;
	head->next = NULL;
	
	item* tempHead = head;

	for(int i = 1;i <= num;i++)
	{
		item* temp = new item;
		cout << "�������" << i << "���ϵ����ָ��:";
		cin >> temp->coe >> temp->exp;
		temp->next = NULL;

		insertPol(temp,head);
	}
	return tempHead;
}

void destoryPol(item* head)//��������
{
	item* lead = head->next;
	while(lead->next != NULL)
	{
		delete head;
		head->next = NULL;
		head = lead;
		lead = head->next;
	}
	delete head,lead;
	head->next = NULL;
}

void printPol(item* pol)//��ӡ����
{
	int k = 0;
	pol = pol->next;
	item* firstItem = pol; 
	while(pol != NULL)
	{
		if(pol->coe == 0)
		{
			pol = pol->next;
			continue;
		}
		if(pol->coe == 1)
		{
			if(pol != firstItem) cout << "+";
			if(pol->exp < 0)
			{
				cout << "x^(" << pol->exp << ")" ;
				pol = pol->next;
				continue;
			}
			if(pol->exp > 0)
			{
				cout << "x^" << pol->exp ;
				pol = pol->next;
				continue;
			}
			if(pol->exp == 0)
			{
				cout << "1";
				pol = pol->next;
				continue;
			}
		}
		if(pol->coe == -1)
		{
			if(pol->exp < 0)
			{
				cout << "-x^(" << pol->exp << ")" ;
				pol = pol->next;
				continue;
			}
			if(pol->exp > 0)
			{
				cout << "-x^" << pol->exp ;
				pol = pol->next;
				continue;
			}
			if(pol->exp == 0)
			{
				cout << "-1";
				pol = pol->next;
				continue;
			}
		}
		if(pol->coe < -1)
		{
			if(pol->exp < 0)
			{
				cout << pol->coe << "x^(" << pol->exp << ")" ;
				pol = pol->next;
				continue;
			}
			if(pol->exp > 0)
			{
				cout << pol->coe << "x^" << pol->exp ;
				pol = pol->next;
				continue;
			}
			if(pol->exp == 0)
			{
				cout << pol->coe;
				pol = pol->next;
				continue;
			}
		}
		if(pol->coe > 1)
		{
			if(pol != firstItem) cout << "+";
			if(pol->exp < 0)
			{
				cout << pol->coe << "x^(" << pol->exp << ")" ;
				pol = pol->next;
				continue;
			}
			if(pol->exp > 0)
			{
				cout << pol->coe << "x^" << pol->exp;
				pol = pol->next;
				continue;
			}
			if(pol->exp == 0)
			{
				cout << pol->coe;
				pol = pol->next;
				continue;
			}
		}
	}
	cout << endl;
}



item* addPol(item* pol1,item* pol2,void insertPol(item* pol,item* head))
{
	item* head = new item;

	head->coe = 0;
	head->exp = 0;
	head->next = NULL;
	
	item* tempHead = head;

	pol1 = pol1->next;
	pol2 = pol2->next;


	while(pol1 != NULL)
	{
		item* temp = new item;
		temp->coe = pol1->coe;
		temp->exp = pol1->exp;
		temp->next = NULL;
		insertPol(temp,head);
		pol1 = pol1->next;
	}

	while(pol2 != NULL)
	{
		item* temp = new item;
		temp->coe = pol2->coe;
		temp->exp = pol2->exp;
		temp->next = NULL;
		insertPol(temp,head);
		pol2 = pol2->next;
	}

	return tempHead;
}

item* minusPol(item* pol1,item* pol2,void insertPol(item* pol,item* head))
{
		item* head = new item;

	head->coe = 0;
	head->exp = 0;
	head->next = NULL;
	
	item* tempHead = head;

	pol1 = pol1->next;
	pol2 = pol2->next;


	while(pol1 != NULL)
	{
		item* temp = new item;
		temp->coe = pol1->coe;
		temp->exp = pol1->exp;
		temp->next = NULL;
		insertPol(temp,head);
		pol1 = pol1->next;
	}

	while(pol2 != NULL)
	{
		item* temp = new item;
		temp->coe = -pol2->coe;
		temp->exp = pol2->exp;
		temp->next = NULL;
		insertPol(temp,head);
		pol2 = pol2->next;
	}

	return tempHead;
}

item* multiplyPol(item* pol1,item* pol2,void insertPol(item* pol,item* head))
{
	item* head = new item;

	head->coe = 0;
	head->exp = 0;
	head->next = NULL;
	
	item* tempHead = head;

	pol1 = pol1->next;
	pol2 = pol2->next;

	item* oripol1 = pol1;
	item* oripol2 = pol2;

	for(pol1 = oripol1;pol1 != NULL;pol1 = pol1->next)
	{
		for(pol2 = oripol2;pol2 != NULL;pol2 = pol2->next)
		{
			item* temp = new item;
			temp->coe = pol1->coe * pol2->coe;
			temp->exp = pol1->exp + pol2->exp;
			temp->next = NULL;
			insertPol(temp,head);
		}
	}

	return tempHead;
}

item* derivativePol(item* pol,void insertPol(item* pol,item* head))
{
	item* head = new item;

	head->coe = 0;
	head->exp = 0;
	head->next = NULL;
	
	item* tempHead = head;

	pol = pol->next;

	while(pol != NULL)
	{
		item* temp = new item;
		temp->coe = pol->coe * pol->exp;
		temp->exp = pol->exp - 1;
		temp->next = NULL;
		insertPol(temp,head);
		pol = pol->next;
	}

	return tempHead;
}


double valuePol(item* pol,int x)//����x��ֵ���������ʽ��ֵ��
{
	double result = 0;
	while(pol != NULL)
	{
		result += pol->coe * pow(x,pol->exp);
		pol = pol->next;
	}
	return result;
}


int main()
{
	//polynomial����ʽ
	//operator �����
	restart:
	int num1,num2;
	cout << "���������ʽa������:" ;
	cin >> num1;
	item* pol1 = createPol(num1,insert);

	cout << "���������ʽb������:" ;
	cin >> num2;
	item* pol2 = createPol(num2,insert);

	begin:
	cout << "**************  �����������Ҫ���еĲ���������: **************" << endl;
	cout << "                1.�������ʽa��b" << endl;
	cout << "                2.�������ʽa+b" << endl;
	cout << "                3.�������ʽa-b" << endl;
	cout << "                4.�������ʽa*b" << endl;
	cout << "                5.����δ֪��x��ֵ���������ʽa��b��ֵ" << endl;
	cout << "                6.�������ʽa��b�ĵ���" << endl;
	cout << "                7.�����������ʽa��b" << endl;
	cout << "                8.�˳�����" << endl;
	cout << "**************************************************************" << endl;
	
	int choice;
	cin >> choice;
	cout << "ִ�в��� �� " << choice << " ��" << endl; 
	switch(choice)
	{
		case 1:
			cout << "����ʽaΪ: " << endl;
			printPol(pol1);
			cout << "����ʽbΪ: " << endl;
			printPol(pol2);
			goto begin;
			break;
		case 2:
			{
				item* addResult = addPol(pol1,pol2,insert);
				cout << "����ʽa+bΪ: " << endl;
				printPol(addResult);
				destoryPol(addResult);
				goto begin;
				break;
			}
		case 3:
			{
				item* minusResult = minusPol(pol1,pol2,insert);
				cout << "����ʽa-bΪ: " << endl;
				printPol(minusResult);
				destoryPol(minusResult);
				goto begin;
				break;
			}
			
		case 4:
			{
				item* multiplyRes = multiplyPol(pol1,pol2,insert);
				cout << "����ʽa*bΪ: " << endl;
				printPol(multiplyRes);
				destoryPol(multiplyRes);
				goto begin;
				break;
			}
		case 5:
			int x;
			cout << "������δ֪��x��ֵ��" ;
			cin >> x;
			cout << "����ʽa��ֵΪ:  " << valuePol(pol1,x) << endl;
			cout << "����ʽb��ֵΪ:  " << valuePol(pol2,x) << endl;
			goto begin;
			break;
		case 6:
			/*ԭ����case�г�ʼ�������������˴���
			error: jump to case label
			error: crosses initialization of ��
			������������ӡ�*/
			//http://blog.csdn.net/u014492513/article/details/46639577
			{
				item* derResult1 = derivativePol(pol1,insert);
				item* derResult2 = derivativePol(pol2,insert);
				cout << "����ʽa�ĵ���Ϊ: " << endl;
				printPol(derResult1);
				cout << "����ʽb�ĵ���Ϊ: " << endl;
				printPol(derResult2);
				destoryPol(derResult1);
				destoryPol(derResult2);
				goto begin;		
			}
			break;
		case 7:
			destoryPol(pol1);
			destoryPol(pol2);
			goto restart;
			break;
		case 8:
			cout << "�����������л����ʹ��~" << endl;
			cin.get();
			cin.get();
			exit(0);
			break;
		default:
			cout << "û�и�����Ŷ~����������������š�"  << endl;
			goto begin;
			break;
	}
	return 0;
}
