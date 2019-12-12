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
			cout << "\n\t\t\t\t����Ƿ�!\n" << endl;
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
	cout << "\n\t\t\t\t������������>>>:";
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
							
							cout << "\n\t\t\t\t��ӭ��ʹ�ñ�����!"<<endl;
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
						cout << "\n\t\t\t\tע��ɹ�!" << endl;
					}
					else
					{
						cout << "\n\t\t\t\tע��ʧ��!" << endl;
					}
					clear_msg_queue();
					return true;
				case '3':
					system("cls");
					cout << "\n\n\t\t\t\t996�Ӱ಻����,��л�û������ǵĴ���!!!" << endl;
					system("D:\\ProgramLearning\\CLanguage\\�İ����ҵ\\paycode.png");
					//WinExec("rundll32.exe C:\\Windows\\System32\\shimgvw.dll,ImageView_Fullscreen D:\\ProgramLearning\\CLanguage\\�İ����ҵ\\paycode.png",SW_NORMAL);
					cout << "\n\n\t\t\t\t��л��ʹ�ñ�������ټ�!" << endl;
					my_mysql_close(sock);//������Դ 
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
	/*һ�ֲ˵������÷���׷�Ӳ��� 0 ʱ ����ʾ��Ʒ���,׷�� 1��ʾ��Ʒ���*/ 
	//cout << sql << endl;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	system("cls");
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);//change color GREEN
	if(flag == 0)
	{
		cout << "\n\n\t\t\t\t\t\t" <<"��Ʒid  " << "\t" << "��Ʒ����" << "\t" << "��Ʒ�۸�" << "\t"<< endl;
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t" << "��Ʒid  "<<"��Ʒ����  " << "\t" << "��Ʒ�۸�" << "\t" << "��Ʒ���" << endl;
	}
	
	if(select_data(mysql,sql,result,row))
	{
		
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t������Ʒ!" << endl;
	}
}

void get_item_info_by_gname()
{
	char gname[STRING_MAX_LENGTH];
	int num;
	system("cls");
	cout << "\n\t\t\t\t��������Ҫ��ѯ����Ʒ����>>>:";
	cin >> gname;
	clear_sql(sql);
	sprintf(sql,"select gid,gname,price from goodslist where gname = '%s'",gname);
	if(search_data(mysql,sql,result))
	{
		cout << "\n\t\t\t\t��ѯ�������>>>:";
		get_item_info(sql,0);
		/*����*/
		clear_sql(sql);
		sprintf(sql,"select count(gname) from goodslist group by gname having gname = '%s'",gname);
		num = select_number_int(mysql,sql,result,row);
		cout << "\n\n\t\t\t\t\t\t�ܼ�>>>: " << num << " ƿ" << endl;;
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t�޴���Ʒ!" << endl;
	}
	
		
}

void get_trade_info(char sql[SQL_LENGTH])
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	system("cls");
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);//change color GREEN
	cout << "\n\n\t\t\t\t\t\t" <<"��Ʒid  " << "\t" << "��Ʒ����" << "\t" << "��Ʒ�۸�" << "\t" << "��Ʒ���ʱ��" << "\t\t" << "��Ʒ����ʱ��"<< endl;
	if(select_data(mysql,sql,result,row))
	{
		
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t������Ʒ������ϸ!" << endl;
	}
	
}

void get_log_info(char sql[SQL_LENGTH])
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);//change color GREEN
	cout << "\n\n\t\t\t\t\t\t" <<"��Ʒ����  " << "\t" << "��Ʒ�۸�" << "\t" << "֧��ʱ��"<< endl;
	if(select_data(mysql,sql,result,row))
	{
		
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t������Ʒ���׼�¼!" << endl;
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
			/*ԭ�����ڸ���Ʒ*/	
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
				cout << "\n\t\t\t\t��ӳɹ�!" << endl;
			}
			else
			{
				cout << "\n\t\t\t\t���ʧ��!" << endl;
			}
		}
		else
		{
			/*ԭ����������Ʒ*/
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
				cout << "\n\t\t\t\t��ӳɹ�!" << endl;
			}
			else
			{
				cout << "\n\t\t\t\t���ʧ��!" << endl;
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
	cout << "\n\t\t\t\t\t\t����Ӫҵ��>>>: "<< total_price << " Ԫ\n"<<endl;
	
}

bool admin_menu_select()
{
	char choice[STRING_MAX_LENGTH];
	int flag = -1;
	LinkList list = NULL;
	admin_menu();
	cout << "\n\t\t\t\t������������>>>:";
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
					cout << "\n\t\t\t\t�޴����к�!\n" << endl;
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
	cout << "\n\t\t\t\t�������Ƿ�Ϊ�ҵ�VIP�û�>>>:";
	binary_choice_menu();
	cout << "\n\t\t\t\t������������>>>:";
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
	cout << "\n\t\t\t\t�������û���>>>:";
	cin >> username;
	sprintf(sql,"select * from userlist where usn = \'%s\'",username);
	if(search_data(mysql,sql,result))
	{
		//cout << "Find usn" << endl;
		cout << "\n\t\t\t\t����������>>>:";
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
				cout << "\n\t\t\t\t��ӭ�װ��Ĺ���Ա " << username << " ʹ�ñ�����!"<<endl;
				clear_msg_queue();
				return 1;
			}
			else
			{
				system("cls");
				cout << "\n\t\t\t\t��ӭVIP�û� " << username << " ʹ�ñ�����!"<<endl;
				clear_msg_queue();
				return 2;
			}
		}
		else
		{
			system("cls");
			cout << "\n\t\t\t\t�û������������!" << endl;
			clear_msg_queue();
			return 0;
		}
	}
	else
	{
		system("cls");
		cout << "\n\t\t\t\t�޴��û���!" << endl;
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
		cout << "\n\n\t\t\t\t�������û���>>>:";
		cin >> usn;
		clear_sql(sql);
		sprintf(sql,"select * from userlist where usn = \'%s\'",usn);
		if(!search_data(mysql,sql,result))//�м�¼����true,û�в������ 
		{
			cout << "\n\t\t\t\t����������>>>:";
			cin >> psd;
			cout << "\n\t\t\t\t���ٴ�ȷ������>>>:";
			cin >> psd2;
			if(strcmp(psd,psd2) == 0)
			{
				cout << "\n\t\t\t\t�����뾲̬����(����������ǿ��ַ�)>>>:";
				cin >> code;
				clear_sql(sql);
				system("cls");//Ϊ��ȫ�������֮��ֱ������ 
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
				cout << "\n\t\t\t\tǰ�������������벻һ��,������ע��!" << endl;
				cout << "\n\t\t\t\tʣ���������:"<< cnt << endl;
				cnt--;	
				continue;
			}	
		}
		else
		{
			cout << "\n\t\t\t\t�û����Ѵ���,����������!" << endl;
			cout << "\n\t\t\t\tʣ���������:"<< cnt << endl;
			cnt--;	
		}
	}
	return false;
}

bool customer_menu_select()
{
	char choice[STRING_MAX_LENGTH];
	customer_menu();
	cout << "\n\t\t\t\t������������>>>:";
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
		cout << "\n\t\t\t\t�����빺�����>>>:";
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
					/*����log*/
					clear_sql(sql);
					sprintf(sql,"select * from log where lid = %d",logid);
					if(search_data(mysql,sql,result))
					{
						/*��log�м������ң��ҵ��Ļ�������Ʒ���ڿ��Դ�ӡ�˵�*/
						clear_sql(sql);
						sprintf(sql,"update log set out_time = now() where lid = %d",logid);
						my_mysql_execute(mysql,sql);
						/*��ӡСƱ*/
						system("cls");
						clear_sql(sql);
						cout << "\n\t\t\t\t֧����¼>>>:\n" << endl;
						sprintf(sql,"select gname,price,out_time from log where lid = %d",logid);
						get_log_info(sql); 
						cout << "\n\t\t\t\t����ɹ�!\n" << endl;
					}
					else
					{
						cout << "\n\t\t\t\t\t��Ǹ,�޴���Ʒ,�޷�����!\n" << endl;
					}
				}
				else
				{
					cout << "\n\t\t\t\t�޸ò�Ʒ���!\n" << endl;
				}
			}
			else
			{
				cout << "\n\t\t\t\t����Ƿ�!\n" << endl;
			}
		}
		else
		{
			cout << "\n\t\t\t\t����Ƿ�!\n" << endl;
		}
	}
	else
	{
		cout << "\n\t\t\t\t��Ǹ,������Ʒ,�޷�����!\n" << endl;
	}	
}

void change_goods_info_select()
{
	char change[STRING_MAX_LENGTH],gname[STRING_MAX_LENGTH],choice[STRING_MAX_LENGTH];;
	system("cls");
	cout << "\n\t\t\t\t��������Ʒ����>>>:";
	cin >> gname;
	clear_msg_queue();
	clear_sql(sql);
	sprintf(sql,"select gid,gname,price from goodslist where gname = '%s'",gname);
	if(search_data(mysql,sql,result))
	{
		cout << "\n\t\t\t\t�������Ƿ�Ҫ������Ʒ����>>>:";
		binary_choice_menu();
		cout << "\n\t\t\t\t������������>>>:";
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
						/*��������*/
						if(change_goods_name(gname))
						{
							cout << "\n\t\t\t\t�޸ĳɹ�!\n" << endl;	
						}
						else
						{
							cout << "\n\t\t\t\t�޸�ʧ��!\n" << endl;
						}
						break;
					case '2':	
						/*���ļ۸�*/ 
						if(change_goods_price(gname))
						{
							cout << "\n\t\t\t\t�޸ĳɹ�!\n" << endl;
						}
						else
						{
							cout << "\n\t\t\t\t�޸�ʧ��!\n" << endl;
						}
						break;
					default:
						cout << "\n\t\t\t\t����Ƿ�!\n" << endl;
				}
			}
			else
			{
				cout << "\n\t\t\t\t����Ƿ�!\n" << endl;
			}
		}
		else
		{
			cout << "\n\t\t\t\t����Ƿ�!\n" << endl;
		}
	}
	else
	{
		cout << "\n\n\t\t\t\t\t\t\t\t�޴���Ʒ!" << endl;
	}
	clear_msg_queue();
}

bool change_goods_name(char gname[STRING_MAX_LENGTH])
{
	char new_name[STRING_MAX_LENGTH];
	cout << "\n\t\t\t\t��������Ʒ��������>>>:";
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
	cout << "\n\t\t\t\t��������Ʒ���¼۸�>>>:";
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
		cout << "\n\t\t\t\t����������!\n" << endl;
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



