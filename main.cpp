#include <iostream>
#include <cmath>

using namespace std;

struct item
{
	double coe;//coefficient 系数
	int exp;//exponent 指数
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
	while(head != NULL && pol->exp < head->exp)//查找插入位置,指数降序排列
	{
		f = head;
		head = head->next;
	}
	if(head != NULL && pol->exp == head->exp)//如果指数相同则合并。
	{
		head->coe += pol->coe;
		delete pol;
		if(head->coe == 0)//系数相加后如果为0的话释放结点
		{
			f->next = head->next;
			delete head;
		}
	}
	else//指数为新时将结点插入
	{
		pol->next = head;
		f->next = pol;
	}
}

item* createPol(int num,void insertPol(item* pol,item* head))//创造多项式链表
{
	item* head = new item;

	head->coe = 0;
	head->exp = 0;
	head->next = NULL;
	
	item* tempHead = head;

	for(int i = 1;i <= num;i++)
	{
		item* temp = new item;
		cout << "请输入第" << i << "项的系数和指数:";
		cin >> temp->coe >> temp->exp;
		temp->next = NULL;

		insertPol(temp,head);
	}
	return tempHead;
}

void destoryPol(item* head)//销毁链表
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

void printPol(item* pol)//打印链表
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


double valuePol(item* pol,int x)//输入x的值，求出多项式的值。
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
	//polynomial多项式
	//operator 运算符
	restart:
	int num1,num2;
	cout << "请输入多项式a的项数:" ;
	cin >> num1;
	item* pol1 = createPol(num1,insert);

	cout << "请输入多项式b的项数:" ;
	cin >> num2;
	item* pol2 = createPol(num2,insert);

	begin:
	cout << "**************  请输入接下来要进行的操作的数字: **************" << endl;
	cout << "                1.输出多项式a和b" << endl;
	cout << "                2.输出多项式a+b" << endl;
	cout << "                3.输出多项式a-b" << endl;
	cout << "                4.输出多项式a*b" << endl;
	cout << "                5.输入未知数x的值，求出多项式a和b的值" << endl;
	cout << "                6.输出多项式a和b的导数" << endl;
	cout << "                7.重新输入多项式a和b" << endl;
	cout << "                8.退出程序" << endl;
	cout << "**************************************************************" << endl;
	
	int choice;
	cin >> choice;
	cout << "执行操作 【 " << choice << " 】" << endl; 
	switch(choice)
	{
		case 1:
			cout << "多项式a为: " << endl;
			printPol(pol1);
			cout << "多项式b为: " << endl;
			printPol(pol2);
			goto begin;
			break;
		case 2:
			{
				item* addResult = addPol(pol1,pol2,insert);
				cout << "多项式a+b为: " << endl;
				printPol(addResult);
				destoryPol(addResult);
				goto begin;
				break;
			}
		case 3:
			{
				item* minusResult = minusPol(pol1,pol2,insert);
				cout << "多项式a-b为: " << endl;
				printPol(minusResult);
				destoryPol(minusResult);
				goto begin;
				break;
			}
			
		case 4:
			{
				item* multiplyRes = multiplyPol(pol1,pol2,insert);
				cout << "多项式a*b为: " << endl;
				printPol(multiplyRes);
				destoryPol(multiplyRes);
				goto begin;
				break;
			}
		case 5:
			int x;
			cout << "请输入未知数x的值：" ;
			cin >> x;
			cout << "多项式a的值为:  " << valuePol(pol1,x) << endl;
			cout << "多项式b的值为:  " << valuePol(pol2,x) << endl;
			goto begin;
			break;
		case 6:
			/*原先在case中初始化变量，出现了错误
			error: jump to case label
			error: crosses initialization of ，
			详情见下面链接。*/
			//http://blog.csdn.net/u014492513/article/details/46639577
			{
				item* derResult1 = derivativePol(pol1,insert);
				item* derResult2 = derivativePol(pol2,insert);
				cout << "多项式a的导数为: " << endl;
				printPol(derResult1);
				cout << "多项式b的导数为: " << endl;
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
			cout << "程序结束！感谢您的使用~" << endl;
			cin.get();
			cin.get();
			exit(0);
			break;
		default:
			cout << "没有该命令哦~请重新输入命令代号。"  << endl;
			goto begin;
			break;
	}
	return 0;
}
