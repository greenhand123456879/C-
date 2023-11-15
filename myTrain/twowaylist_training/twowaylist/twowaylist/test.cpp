#include"TWList.h"

void test()
{
	TwNode* list = (TwNode*)malloc(sizeof(TwNode));
	InitList(&list, 0);
	//PrintList(list);
	pushfrontlist(&list, 1);
	pushfrontlist(&list, 2);
	pushfrontlist(&list, 3);
	pushfrontlist(&list, 4);
	PrintList(list);
	popfrontlist(&list);
	popfrontlist(&list);
	popfrontlist(&list);
	popfrontlist(&list);
	popfrontlist(&list);


	PrintList(list);

	pushbacklist(&list, 1);
	PrintList(list);
}



int main()
{
	test();
	return 0;
}