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
	cout << "\n\n\t\t\t\t欢迎使用饮品自动贩卖系统!\n\n";
	cout << "\t\t\t\t   |1    <-- 购买 -->|"<<endl;
	cout << "\t\t\t\t   |2    <-- 注册 -->|"<<endl;//???????? 
	cout << "\t\t\t\t   |3    <-- 退出 -->|"<<endl;
	
}

void admin_menu()
{
	cout << "\n\t\t\t\t   1    <-- 查询所有饮品信息 -->"<<endl;
	cout << "\t\t\t\t   2    <-- 按饮品名查询数量 -->"<<endl;
	cout << "\t\t\t\t   3    <-- 添加饮品 -->"<<endl;
	cout << "\t\t\t\t   4    <-- 查询所有购买记录 -->"<<endl;
	cout << "\t\t\t\t   5    <-- 统计当日营业额 -->"<<endl;
	cout << "\t\t\t\t   6    <-- 更改商品信息 -->"<<endl;
	cout << "\t\t\t\t   7    <-- 返回主页面 -->"<<endl;
}

void customer_menu()
{
	cout << "\n\t\t\t\t   1    <-- 查询所有饮品信息 -->"<<endl;
	cout << "\t\t\t\t   2    <-- 购买饮品 -->"<<endl;//
	cout << "\t\t\t\t   3    <-- 返回主页面 -->"<<endl;
}

void binary_choice_menu()
{
	cout << "\n\n\t\t\t\t   1    <-- 是 -->"<<endl;
	cout << "\t\t\t\t   2    <-- 否 -->"<<endl;

}


