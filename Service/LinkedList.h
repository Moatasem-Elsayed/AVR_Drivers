/*****************************************************
*Author :Moatasem
*Date:   12/10/2020
*Version: v02
*Brief: ....
*******************************************************/

#ifndef SERVICE_LINKEDLIST_H_
#define SERVICE_LINKEDLIST_H_

#include <Std_Types.h>
#include <Utils.h>
typedef struct St_node_t {
	uint8 Name[10];
	uint8 ID;
	 struct St_node_t* next;
	struct St_node_t* Prev;
}ST_node;

void LinkedList_InitList();
ST_node* LinkedList_CreateNode(uint8 Name[],uint8 ID);
void LinkedList_insert(ST_node* ptr);
void LinkedList_printList();
ST_node* LinkedList_Search(int ID);

#endif /* SERVICE_LINKEDLIST_H_ */
