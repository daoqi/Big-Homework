#ifndef _HLINKLIST_H_
#define _HLINKLIST_H_


#define INFO_LENGTH 80

struct GoodsInfo
{
	char gname[INFO_LENGTH];
	double price;
	int number;	
};

typedef struct Node
{
	struct GoodsInfo data;
	struct Node * next;
}LinkedList, *LinkList;


#define LINKLIST_NODE_SIZE sizeof(LinkedList)
bool create_list(LinkList &list);
void print_list(LinkList list);

#endif

