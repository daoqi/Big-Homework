#include "mysqloperation.h"
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

#include<string.h>

using namespace std;


bool connect_database(MYSQL &mysql,MYSQL *sock)
{
	const char *host = "127.0.0.1";
	unsigned int port = 3306;
	const char *user = "root";
	const char *psd = "wangzheng10010";
	const char *db = "bighomework";
	const char *unix_socket = NULL;
	unsigned long client_flag = 0;
	mysql_init(&mysql);

	mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"gbk"); //CHANGE char-set
	if((sock = mysql_real_connect(&mysql,host,user,psd,db,port,unix_socket,client_flag))!= NULL)
	{
		cout << "\n\t\t\t\t Connect MySQL Successfully!" << endl;
		return true;
	}
	else
	{
		cout << "\t\t\t\t Connect MySQL Failed!" << endl;
		fprintf(stderr,"\t\t\t\t%s\n",mysql_error(&mysql));
		return false;
	}
}

bool search_data(MYSQL &mysql,char *sql,MYSQL_RES *result)
{
	/*Find data if not in list*/
	mysql_free_result(result);
	if(mysql_query(&mysql,sql) == 0)
	{
		result = mysql_store_result(&mysql);
		if(result != NULL)
		{
			if(mysql_num_rows(result) != 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			fprintf(stderr,"Fail to store result!\n");
			return false;
		}
	}
	else
	{
		//fprintf(stderr,"Fail to query1!\n");
		return false;
	}
}


bool select_data(MYSQL &mysql,char *sql,MYSQL_RES *result,MYSQL_ROW row)
{
	short int fields_num;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get a handle
	SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_GREEN);//change color GREEN
	mysql_free_result(result);
	if(mysql_query(&mysql,sql) == 0)
	{
		result = mysql_store_result(&mysql);
		if(result != NULL)
		{
			if(mysql_num_rows(result) != 0)
			{
				fields_num = mysql_num_fields(result);
				while((row = mysql_fetch_row(result)) != NULL)
				{
					cout << "\n\t\t\t\t\t\t";
					for(int i = 0;i<fields_num;i++)
					{
						if(row[i] != NULL)
						{
							/*cout.setf(ios::left); //???????left 
							cout.width(7); //?????7,??????? */
							//cout.fill("")
							if(strlen(row[i]) <= 4)//两个汉字或4个字母 
							{
								cout << row[i] << "\t\t";
							}
							else if(strlen(row[i]) <= 8)
							{
								cout << row[i] << "\t";
							}
							else
							{
								cout << row[i] << "\t";
							}
						}
						
					}
					cout << endl;
					
				}
				SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			fprintf(stderr,"Fail to store result!\n");
			return false;
		}
	}
	else
	{
		fprintf(stderr,"Fail to query2!\n");
		return false;
	}	
}

int select_number_int(MYSQL &mysql,char *sql,MYSQL_RES *result,MYSQL_ROW row)
{
	/*
		return double
	*/
	short int fields_num;
	mysql_free_result(result);
	if(mysql_query(&mysql,sql) == 0)
	{
		//cout << "query ok!" <<endl;
		result = mysql_store_result(&mysql);
		if(result != NULL)
		{
			if(mysql_num_rows(result) != 0)
			{
				fields_num = mysql_num_fields(result);
				row = mysql_fetch_row(result);
				return atoi(row[0]);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			fprintf(stderr,"Fail to store result!\n");
			return -1;
		}
	}
	else
	{
		fprintf(stderr,"Fail to query3!\n");
		return -1;
	}	
}

double select_number_double(MYSQL &mysql,char *sql,MYSQL_RES *result,MYSQL_ROW row)
{
	/*
		return double
	*/
	short int fields_num;
	mysql_free_result(result);
	if(mysql_query(&mysql,sql) == 0)
	{
		//cout << "query ok!" <<endl;
		result = mysql_store_result(&mysql);
		if(result != NULL)
		{
			if(mysql_num_rows(result) != 0)
			{
				fields_num = mysql_num_fields(result);
				row = mysql_fetch_row(result);
				return atof(row[0]);
			}
			else
			{
				return 0.0;
			}
		}
		else
		{
			fprintf(stderr,"Fail to store result!\n");
			return -1;
		}
	}
	else
	{
		fprintf(stderr,"Fail to query4!\n");
		return -1;
	}	
}

bool my_mysql_execute(MYSQL &mysql,char *sql)
{
	
	if(mysql_query(&mysql,sql) == 0)
	{
		/*Zero for success. Nonzero if an error occurred. */
		return true;
	}
	else
	{
		fprintf(stderr,"Fail to query5!\n");
		return false;
	}	
}

void my_mysql_free_result(MYSQL_RES *result)
{
	mysql_free_result(result);
}

unsigned long long my_mysql_num_rows(MYSQL &mysql,char *sql,MYSQL_RES *result)
{
	mysql_query(&mysql,sql);
	result = mysql_store_result(&mysql);
	if(result != NULL)
	{
		
		return mysql_num_rows(result);
	}
	else
	{
		
		return 0;
	}
	
}

void my_mysql_close(MYSQL *sock)
{
	mysql_close(sock);
}

