#include "corelogic.h"
#include "menu.h"
#include "mysqloperation.h"
#include <string.h>
#include <stdlib.h>
#include <typeinfo.h>
#include <iostream>
#include "WinBase.h"
#include "linklist.h"
MYSQL mysql,*sock;
MYSQL_RES *result;
MYSQL_ROW row;
char sql[SQL_LENGTH] = "";

using namespace std;

void core_menu()
{
	connect_database(mysql,sock);
	while(true)
	{
		//cout << mysql_ping(&mysql) << endl;
		my_mysql_free_result(result);
		clear_sql(sql);
		if(welcome_menu_select())
		{
			
		}
		else
		{
			//system("cls");
			cout << "\n\t\t\t\t输入非法!\n" << endl;
			//clear_msg_queue();
		}
	}
}


void clear_sql(char sql[SQL_LENGTH])
{
	strcpy(sql," ");
}

bool welcome_menu_select()
{
	char choice[STRING_MAX_LENGTH];
	int flag = -1;
	bool sub_flag = true;
	
	welcome_menu();
	cout << "\n\t\t\t\t请输入服务序号>>>:";
	gets(choice);
	if(strlen(choice) == 1 )
	{
		if(typeid(choice[0]).name() == typeid(char).name())
		{
			switch(choice[0])
			{
				case '1':
					flag = is_vip_user();/*-1-input illegal 1-admin 2-vip_user 0-user*/
					if(flag == 0)
					{
						while(sub_flag)
						{
							
							cout << "\n\t\t\t\t欢迎您使用本机器!"<<endl;
							sub_flag = customer_menu_select();							
						}
						//system("cls");
						return true;

					}
					else if(flag == 1)
					{
						while(sub_flag)
						{
							sub_flag = admin_menu_select();
						}
						return true;	
					}
					else if(flag == 2)
					{
						while(sub_flag)
						{
							sub_flag = customer_menu_select();//vip
						}
						return true;
					}
					else
					{
						return false;
					}
					break;
				case '2':	
					if(user_register())
					{
						cout << "\n\t\t\t\t注册成功!" << endl;
					}
					else
					{
						cout << "\n\t\t\t\t注册失败!" << endl;
					}
					clear_msg_queue();
					return true;
				case '3':
					system("cls");
					cout << "\n\n\t\t\t\t996加班不容易,感谢用户大人们的打赏!!!" << endl;
					system("D:\\ProgramLearning\\CLanguage\\改版大作业\\paycode.png");
					//WinExec("rundll32.exe C:\\Windows\\System32\\shimgvw.dll,ImageView_Fullscreen D:\\ProgramLearning\\CLanguage\\改版大作业\\paycode.png",SW_NORMAL);
					cout << "\n\n\t\t\t\t感谢您使用本软件，再见!" << endl;
					my_mysql_close(sock);//回收资源 
					exit(0);
				default:
					return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void get_item_info(char sql[SQL_LENGTH],int flag)
{
	/*一种菜单多种用法，追加参数 0 时 不显示商品库存,追加 1显示商品库存*/ 
	//cout << sql << endl;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	system("cls");
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);//change color GREEN
	if(flag == 0)
	{
		cout << "\n\n\t\t\t\t\t\t" <<"商品id  " << "\t" << "商品名称" << "\t" << "商品价格" << "\t"<< endl;
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t" << "商品id  "<<"商品名称  " << "\t" << "商品价格" << "\t" << "商品库存" << endl;
	}
	
	if(select_data(mysql,sql,result,row))
	{
		
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t暂无商品!" << endl;
	}
}

void get_item_info_by_gname()
{
	char gname[STRING_MAX_LENGTH];
	int num;
	system("cls");
	cout << "\n\t\t\t\t请输入想要查询的饮品名称>>>:";
	cin >> gname;
	clear_sql(sql);
	sprintf(sql,"select gid,gname,price from goodslist where gname = '%s'",gname);
	if(search_data(mysql,sql,result))
	{
		cout << "\n\t\t\t\t查询结果如下>>>:";
		get_item_info(sql,0);
		/*数量*/
		clear_sql(sql);
		sprintf(sql,"select count(gname) from goodslist group by gname having gname = '%s'",gname);
		num = select_number_int(mysql,sql,result,row);
		cout << "\n\n\t\t\t\t\t\t总计>>>: " << num << " 瓶" << endl;;
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t无此商品!" << endl;
	}
	
		
}

void get_trade_info(char sql[SQL_LENGTH])
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	system("cls");
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);//change color GREEN
	cout << "\n\n\t\t\t\t\t\t" <<"商品id  " << "\t" << "商品名称" << "\t" << "商品价格" << "\t" << "商品入库时间" << "\t\t" << "商品出库时间"<< endl;
	if(select_data(mysql,sql,result,row))
	{
		
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t暂无商品交易明细!" << endl;
	}
	
}

void get_log_info(char sql[SQL_LENGTH])
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);//change color GREEN
	cout << "\n\n\t\t\t\t\t\t" <<"商品名称  " << "\t" << "商品价格" << "\t" << "支付时间"<< endl;
	if(select_data(mysql,sql,result,row))
	{
		
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t暂无商品交易记录!" << endl;
	}	
}

void append_item_info(LinkList list)
{
	LinkList p = list;
	int num = 0,flag = 0;
	double price;
	int logid;
	clear_sql(sql);
	sprintf(sql,"select max(logid) from goodslist");
	logid = select_number_int(mysql,sql,result,row);
	if(logid == 0)
	{
		logid = 1;
	}
	while(p!= NULL)
	{
		num = 0;
		flag = 0;
		
		clear_sql(sql);
		sprintf(sql,"select * from goodslist where gname = \'%s\'",p->data.gname);
		if(search_data(mysql,sql,result))
		{
			/*原来存在该饮品*/	
			clear_sql(sql);
			sprintf(sql,"select price from goodslist where gname = '%s'",p->data.gname);
			price = select_number_double(mysql,sql,result,row);
			p->data.price = price;
			for(int i = 0;i<p->data.number;i++)
			{
				clear_sql(sql);
				sprintf(sql,"insert into goodslist(gname,price,logid) values(\'%s\',%lf,%d)",p->data.gname,p->data.price,logid);
				if(my_mysql_execute(mysql,sql))
				{
					clear_sql(sql);
					sprintf(sql,"insert into log(gname,price,in_time,out_time) values(\'%s\',%lf,now(),null)",p->data.gname,p->data.price);
					if(my_mysql_execute(mysql,sql))
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
					logid++;		
				}
				else
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
			{
				cout << "\n\t\t\t\t添加成功!" << endl;
			}
			else
			{
				cout << "\n\t\t\t\t添加失败!" << endl;
			}
		}
		else
		{
			/*原来不存在饮品*/
			for(int i = 0;i<p->data.number;i++)
			{
				clear_sql(sql);
				sprintf(sql,"insert into goodslist(gname,price,logid) values(\'%s\',%lf,%d)",p->data.gname,p->data.price,logid);
				if(my_mysql_execute(mysql,sql))
				{
					clear_sql(sql);
					sprintf(sql,"insert into log(gname,price,in_time,out_time) values(\'%s\',%lf,now(),null)",p->data.gname,p->data.price);
					if(my_mysql_execute(mysql,sql))
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
					logid++;		
				}
				else
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
			{
				cout << "\n\t\t\t\t添加成功!" << endl;
			}
			else
			{
				cout << "\n\t\t\t\t添加失败!" << endl;
			}
		}
		
		p = p->next;	
	}
}


void calculate_today_profit()
{
	double total_price;
	clear_sql(sql);
	sprintf(sql,"select sum(price) from log where out_time <= now() and out_time > curdate()-1");
	total_price = select_number_double(mysql,sql,result,row);
	clear_sql(sql);
	sprintf(sql,"select * from log where month(out_time) = month(now()) and day(out_time) = day(now())");
	get_trade_info(sql);
	cout << "\n\t\t\t\t\t\t当日营业额>>>: "<< total_price << " 元\n"<<endl;
	
}

bool admin_menu_select()
{
	char choice[STRING_MAX_LENGTH];
	int flag = -1;
	LinkList list = NULL;
	admin_menu();
	cout << "\n\t\t\t\t请输入服务序号>>>:";
	gets(choice);
	if(strlen(choice) == 1 || strlen(choice) == 0)
	{
		if(typeid(choice[0]).name() == typeid(char).name())
		{
			switch(choice[0])
			{
				case '1':
					clear_sql(sql);
					sprintf(sql,"select gid,gname,price,count(gname) from goodslist group by gname having count(gname) > 0");
					get_item_info(sql,1);
					break;
				case '2':	
					get_item_info_by_gname();
					clear_msg_queue();
					break;
				case '3':
					create_list(list);
					append_item_info(list);
					break;
				case '4':
					clear_sql(sql);
					sprintf(sql,"select * from log");
					get_trade_info(sql);
					break;
				case '5':
					calculate_today_profit();
					break;
				case '6':
					cout << "Change goods info" << endl;
					change_goods_info_select();
					break;
				case '7':
					return false;
				default:
					cout << "\n\t\t\t\t无此序列号!\n" << endl;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

int is_vip_user()
{
	/*-1 input illegal 1 admin 2 vip_user 0 user*/	
	char choice[STRING_MAX_LENGTH];
	cout << "\n\t\t\t\t请问您是否为我店VIP用户>>>:";
	binary_choice_menu();
	cout << "\n\t\t\t\t请输入服务序号>>>:";
	gets(choice);
	if(strlen(choice) == 1 )
	{
		if(typeid(choice[0]).name() == typeid(char).name())
		{
			//cout << "in switch" << endl;
			//puts(choice);
			switch(choice[0])
			{
				case '1':
					return (authorize());
				case '2':	
					return 0;
				default:
					return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

int authorize(void)
{
	/*Logic function 1 == admin 2 == vip user*/
	char username[STRING_MAX_LENGTH],password[STRING_MAX_LENGTH];
	cout << "\n\t\t\t\t请输入用户名>>>:";
	cin >> username;
	sprintf(sql,"select * from userlist where usn = \'%s\'",username);
	if(search_data(mysql,sql,result))
	{
		//cout << "Find usn" << endl;
		cout << "\n\t\t\t\t请输入密码>>>:";
		cin >> password;
		strcat(sql," and psd = password(\'");
		strcat(sql,password);
		strcat(sql,"\')");
		if(search_data(mysql,sql,result))
		{
			strcat(sql," and state = 0");
			if(search_data(mysql,sql,result))
			{
				system("cls");
				cout << "\n\t\t\t\t欢迎亲爱的管理员 " << username << " 使用本机器!"<<endl;
				clear_msg_queue();
				return 1;
			}
			else
			{
				system("cls");
				cout << "\n\t\t\t\t欢迎VIP用户 " << username << " 使用本机器!"<<endl;
				clear_msg_queue();
				return 2;
			}
		}
		else
		{
			system("cls");
			cout << "\n\t\t\t\t用户名或密码错误!" << endl;
			clear_msg_queue();
			return 0;
		}
	}
	else
	{
		system("cls");
		cout << "\n\t\t\t\t无此用户名!" << endl;
		clear_msg_queue();
		return 0;
	}
}

bool user_register()
{
	char usn[STRING_MAX_LENGTH],psd[STRING_MAX_LENGTH],psd2[STRING_MAX_LENGTH];
	char code[STRING_MAX_LENGTH];
	int cnt = 3;
	while(cnt > 0)
	{
		cout << "\n\n\t\t\t\t请输入用户名>>>:";
		cin >> usn;
		clear_sql(sql);
		sprintf(sql,"select * from userlist where usn = \'%s\'",usn);
		if(!search_data(mysql,sql,result))//有记录返回true,没有才能添加 
		{
			cout << "\n\t\t\t\t请输入密码>>>:";
			cin >> psd;
			cout << "\n\t\t\t\t请再次确认密码>>>:";
			cin >> psd2;
			if(strcmp(psd,psd2) == 0)
			{
				cout << "\n\t\t\t\t请输入静态口令(若无则输入非空字符)>>>:";
				cin >> code;
				clear_sql(sql);
				system("cls");//为安全起见输入之后直接清屏 
				if(strcmp(code,"10010") == 0)// 0 admin
				{
					sprintf(sql,"insert into userlist(usn,psd,state) values (\'%s\',password(\'%s\'),0)",usn,psd);
					if(my_mysql_execute(mysql,sql))
					{
						
						return true;
					}
					else
					{
						return false;
					}
					
				}
				else// vip user
				{
					sprintf(sql,"insert into userlist(usn,psd,state) values (\'%s\',password(\'%s\'),1)",usn,psd);
					if(my_mysql_execute(mysql,sql))
					{
						
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				cout << "\n\t\t\t\t前后两次密码输入不一致,请重新注册!" << endl;
				cout << "\n\t\t\t\t剩余操作次数:"<< cnt << endl;
				cnt--;	
				continue;
			}	
		}
		else
		{
			cout << "\n\t\t\t\t用户名已存在,请重新输入!" << endl;
			cout << "\n\t\t\t\t剩余操作次数:"<< cnt << endl;
			cnt--;	
		}
	}
	return false;
}

bool customer_menu_select()
{
	char choice[STRING_MAX_LENGTH];
	customer_menu();
	cout << "\n\t\t\t\t请输入服务序号>>>:";
	gets(choice);
	if(strlen(choice) == 1 )
	{
		if(typeid(choice[0]).name() == typeid(char).name())
		{
			switch(choice[0])
			{
				case '1':
					clear_sql(sql);
					sprintf(sql,"select gid,gname,price from goodslist");
					get_item_info(sql,0);
					return false;
				case '2':	
					buy_item();
					return false;
				case '3':
					system("cls");	
					return false;
				default:
					return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void buy_item()
{
	char choice[STRING_MAX_LENGTH];
	unsigned long long number;
	int remain;
	int logid;
	system("cls"); 
	clear_sql(sql);
	sprintf(sql,"select gid,gname,price from goodslist");
	get_item_info(sql,0);
	clear_sql(sql);
	sprintf(sql,"select max(logid) from  goodslist");
	number = select_number_int(mysql,sql,result,row);
	//number = my_mysql_num_rows(mysql,sql,result);
	//cout << "number " << number << endl;
	if(number != 0)
	{
		cout << "\n\t\t\t\t请输入购买序号>>>:";
		gets(choice);
		if(strlen(choice) == 1 )
		{
			if(typeid(choice[0]).name() == typeid(char).name())
			{
				if((choice[0]-'0' >=1) && (choice[0]-'0' <= number))
				{
					clear_sql(sql);
					sprintf(sql,"select logid from goodslist where gid = %c",choice[0]);
					logid = select_number_int(mysql,sql,result,row);
					clear_sql(sql);
					sprintf(sql,"delete from goodslist where gid = %c",choice[0]);
					my_mysql_execute(mysql,sql);
					/*生成log*/
					clear_sql(sql);
					sprintf(sql,"select * from log where lid = %d",logid);
					if(search_data(mysql,sql,result))
					{
						/*在log中继续查找，找到的话，即饮品存在可以打印账单*/
						clear_sql(sql);
						sprintf(sql,"update log set out_time = now() where lid = %d",logid);
						my_mysql_execute(mysql,sql);
						/*打印小票*/
						system("cls");
						clear_sql(sql);
						cout << "\n\t\t\t\t支付记录>>>:\n" << endl;
						sprintf(sql,"select gname,price,out_time from log where lid = %d",logid);
						get_log_info(sql); 
						cout << "\n\t\t\t\t购买成功!\n" << endl;
					}
					else
					{
						cout << "\n\t\t\t\t\t抱歉,无此商品,无法购买!\n" << endl;
					}
				}
				else
				{
					cout << "\n\t\t\t\t无该产品编号!\n" << endl;
				}
			}
			else
			{
				cout << "\n\t\t\t\t输入非法!\n" << endl;
			}
		}
		else
		{
			cout << "\n\t\t\t\t输入非法!\n" << endl;
		}
	}
	else
	{
		cout << "\n\t\t\t\t抱歉,暂无商品,无法购买!\n" << endl;
	}	
}

void change_goods_info_select()
{
	char change[STRING_MAX_LENGTH],gname[STRING_MAX_LENGTH],choice[STRING_MAX_LENGTH];;
	system("cls");
	cout << "\n\t\t\t\t请输入饮品名称>>>:";
	cin >> gname;
	clear_msg_queue();
	clear_sql(sql);
	sprintf(sql,"select gid,gname,price from goodslist where gname = '%s'",gname);
	if(search_data(mysql,sql,result))
	{
		cout << "\n\t\t\t\t请问您是否要更改饮品名称>>>:";
		binary_choice_menu();
		cout << "\n\t\t\t\t请输入服务序号>>>:";
		gets(choice);
		if(strlen(choice) == 1 )
		{
			if(typeid(choice[0]).name() == typeid(char).name())
			{
				//cout << "in switch" << endl;
				//puts(choice);
				switch(choice[0])
				{
					case '1':
						/*更改名称*/
						if(change_goods_name(gname))
						{
							cout << "\n\t\t\t\t修改成功!\n" << endl;	
						}
						else
						{
							cout << "\n\t\t\t\t修改失败!\n" << endl;
						}
						break;
					case '2':	
						/*更改价格*/ 
						if(change_goods_price(gname))
						{
							cout << "\n\t\t\t\t修改成功!\n" << endl;
						}
						else
						{
							cout << "\n\t\t\t\t修改失败!\n" << endl;
						}
						break;
					default:
						cout << "\n\t\t\t\t输入非法!\n" << endl;
				}
			}
			else
			{
				cout << "\n\t\t\t\t输入非法!\n" << endl;
			}
		}
		else
		{
			cout << "\n\t\t\t\t输入非法!\n" << endl;
		}
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t无此商品!" << endl;
	}
	clear_msg_queue();
}

bool change_goods_name(char gname[STRING_MAX_LENGTH])
{
	char new_name[STRING_MAX_LENGTH];
	cout << "\n\t\t\t\t请输入饮品的新名称>>>:";
	cin >> new_name;
	clear_sql(sql);
	sprintf(sql,"update goodslist set gname = '%s' where gname = '%s' ",new_name,gname);
	my_mysql_execute(mysql,sql);
	clear_sql(sql);
	sprintf(sql,"update log set gname = '%s' where gname = '%s' ",new_name,gname);
	my_mysql_execute(mysql,sql);
	return true;
}

bool change_goods_price(char gname[STRING_MAX_LENGTH])
{
	char new_price[STRING_MAX_LENGTH];
	cout << "\n\t\t\t\t请输入饮品的新价格>>>:";
	cin >> new_price;
	if(is_double(new_price,strlen(new_price)))
	{
		clear_sql(sql);
		sprintf(sql,"update goodslist set price = %s where gname = '%s' ",new_price,gname);
		my_mysql_execute(mysql,sql);
		clear_sql(sql);
		sprintf(sql,"update log set price = %s where gname = '%s' ",new_price,gname);
		my_mysql_execute(mysql,sql);
		return true;
	}
	else
	{
		cout << "\n\t\t\t\t请输入数字!\n" << endl;
		return false;
	}
	
}

bool is_double(char str[STRING_MAX_LENGTH],int len)
{
	char *p = str;
	for(;p<str+len;p++)
	{
		if( !((*p == '.') || ('0'<= *p && *p <= '9')))
		{
			return false;
		}
	}
	return true;
}



