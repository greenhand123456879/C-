#include"list.h"

int main()
{
	LNode* List = NULL;
	listpushfront(1, &List);

	listpushfront(2, &List);
	listpushfront(3, &List);
	listpushfront(4, &List);
	//PrintList(List);
	//listpopfront(&List);
	//PrintList(List);
	//listpopfront(&List);
	//PrintList(List);
	//listpopfront(&List);
	//PrintList(List);
	//listpopfront(&List);
	//PrintList(List);
	//PrintList(List);
	//PrintList(List);
	//PrintList(List);
	//PrintList(List);
	if (listfind(4, List))
		printf("1!");
	return 0;
}