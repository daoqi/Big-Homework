#include "linklist.h"
#include<iostream>
#include<string.h>
#include<malloc.h>
#include <typeinfo.h>

using namespace std;

bool create_list(LinkList &list)
{
	char ch;
	int num;
	LinkList p,r;
	cout << "\n\n\t\t\t\t请输入想要添加的饮品种类>>>:";
	scanf("%d",&num);
	while((ch = getchar()) != '\n' && ch != EOF);
	//setbuf(stdin,NULL);
	if(typeid(num).name() == typeid(int).name())
	{
		
		for(register int i = 1;i<=num;i++)
		{
			p = (LinkList)malloc(LINKLIST_NODE_SIZE);
			p->next = NULL;
			cout << "\n\t\t\t\t请输入饮品名称>>>:";
			cin >> p->data.gname;
			cout << "\n\t\t\t\t请输入饮品价格>>>:";
			cin >> p->data.price;
			cout << "\n\t\t\t\t请输入饮品数量>>>:";
			cin >> p->data.number;
			while((ch = getchar()) != '\n' && ch != EOF);
			if(list == NULL)
			{
				list = p;
			}
			else
			{
				r->next = p;
			}
			r = p;
		}
		
		return true;
	}
	else
	{
		cout << "\n\t\t\t\t输入非法!\n" << endl;
		while((ch = getchar()) != '\n' && ch != EOF);
		return false;
	}
}

void print_list(LinkList list)
{
	LinkList p = list;
	while(p != NULL)
	{
		cout << p->data.gname << ",";
		cout << p->data.price << ",";
		cout << p->data.number << endl;
		p = p->next;
	}
	cout << endl;
}

