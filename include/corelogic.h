#ifndef CORELOGIC_H
#define CORELOGIC_H




#include "linklist.h"
#include "menu.h"
#include "mysqloperation.h"



#define STRING_MAX_LENGTH 80+5
#define SQL_LENGTH 200

/*Program logic functions*/

int authorize(void);
bool user_register();
int is_vip_user();
bool is_double(char str[STRING_MAX_LENGTH],int len);
void clear_sql(char sql[SQL_LENGTH]);

/*Menu select logic function*/
void core_menu();
bool welcome_menu_select();
bool customer_menu_select();
bool admin_menu_select();
void change_goods_info_select();
/*Administrator functions*/
void append_item_info(LinkList list);
void get_trade_info(char sql[SQL_LENGTH]);
void get_item_info(char sql[SQL_LENGTH],int flag);
void get_item_info_by_gname();
void calculate_today_profit();
bool change_goods_price(char gname[STRING_MAX_LENGTH]);
bool change_goods_name(char gname[STRING_MAX_LENGTH]);

/*user functions*/
void buy_item();
void get_log_info(char sql[SQL_LENGTH]);
#endif

