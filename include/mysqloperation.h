#ifndef MYSQLOPERATION_H
#define MYSQLOPERATION_H

#include <winsock.h>
#include <D:\\mysql-5.6.43-winx64\\include\\mysql.h>


bool connect_database(MYSQL &mysql,MYSQL *sock);
bool search_data(MYSQL &mysql,char *sql,MYSQL_RES *result);
bool select_data(MYSQL &mysql,char *sql,MYSQL_RES *result,MYSQL_ROW row);
int select_number_int(MYSQL &mysql,char *sql,MYSQL_RES *result,MYSQL_ROW row);
double select_number_double(MYSQL &mysql,char *sql,MYSQL_RES *result,MYSQL_ROW row);
bool my_mysql_execute(MYSQL &mysql,char *sql);
void my_mysql_free_result(MYSQL_RES *result);
void my_mysql_close(MYSQL *sock);
unsigned long long my_mysql_num_rows(MYSQL &mysql,char *sql,MYSQL_RES *result);
#endif

