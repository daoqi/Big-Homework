#include "menu.h"

#include<iostream>
#include<string.h>
#include<typeinfo.h>

using namespace std;

void clear_msg_queue()
{
	char ch;
	while((ch = getchar()) != '\n' && ch != EOF);
}


void welcome_menu()
{
	cout << "\n\n\t\t\t\t��ӭʹ����Ʒ�Զ�����ϵͳ!\n\n";
	cout << "\t\t\t\t   |1    <-- ���� -->|"<<endl;
	cout << "\t\t\t\t   |2    <-- ע�� -->|"<<endl;//???????? 
	cout << "\t\t\t\t   |3    <-- �˳� -->|"<<endl;
	
}

void admin_menu()
{
	cout << "\n\t\t\t\t   1    <-- ��ѯ������Ʒ��Ϣ -->"<<endl;
	cout << "\t\t\t\t   2    <-- ����Ʒ����ѯ���� -->"<<endl;
	cout << "\t\t\t\t   3    <-- �����Ʒ -->"<<endl;
	cout << "\t\t\t\t   4    <-- ��ѯ���й����¼ -->"<<endl;
	cout << "\t\t\t\t   5    <-- ͳ�Ƶ���Ӫҵ�� -->"<<endl;
	cout << "\t\t\t\t   6    <-- ������Ʒ��Ϣ -->"<<endl;
	cout << "\t\t\t\t   7    <-- ������ҳ�� -->"<<endl;
}

void customer_menu()
{
	cout << "\n\t\t\t\t   1    <-- ��ѯ������Ʒ��Ϣ -->"<<endl;
	cout << "\t\t\t\t   2    <-- ������Ʒ -->"<<endl;//
	cout << "\t\t\t\t   3    <-- ������ҳ�� -->"<<endl;
}

void binary_choice_menu()
{
	cout << "\n\n\t\t\t\t   1    <-- �� -->"<<endl;
	cout << "\t\t\t\t   2    <-- �� -->"<<endl;

}


