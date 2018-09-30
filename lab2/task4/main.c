#include <stdio.h>

#include "mylib/ArrayList.h"

int main(int argc, char *argv[]){

	char *str1;
	char *str2;
	char *str3;
	ArrayList *list;
	
	list = arrlist_create();

	str1 = "string";
	str2 = "123 string 123";
	str3 = "String 3";
	printf("Size of ArrayList = %ld\n", size(list));
	printf("Initial Capacity = %ld\n", list->capacity);

	add(list, str1);
	add(list, str2);
	add(list, str3);

	printf("Added %ld elements\n", size(list));
	printf("Print :\n");
	size_t i;
	for (i = 0; i < size(list); i++)
		printf("\t %ld) %s\n",i,(char *)get(list, i));
	printf("Size = %ld\n", size(list));

	printf("Insert elem  '%s' to index %d \n", "String for insertion" , 2) ;
	insert(list,2,"String for insertion");
	printf("Print :\n");
	for (i = 0; i < size(list); i++)
		printf("\t %ld) %s\n",i,(char *)get(list, i));
	printf("Size = %ld\n", size(list));

	printf("Remove elem with to index %d \n", 2) ;
	_remove_(list,2);
	printf("Print :\n");
	for (i = 0; i < size(list); i++)
		printf("\t %ld) %s\n",i,(char *)get(list, i));
	printf("Size = %ld\n", size(list));

	printf("Get elem with to index %d \n", 2) ;
	printf("\t %s \n",get(list,2));
	

	printf("Set elem  %s at index %d \n", "String 0", 0) ;
	set(list,0,"String 0");

	for (i = 0; i < size(list); i++)
		printf("\t %ld) %s\n",i,(char *)get(list, i));
	printf("Size = %ld\n", size(list));

for (i = 0; i < 10; i++){
			add(list, str1);
	}
	printf("Added %ld elements\n", 10);
	printf("Size = %ld\n", size(list));
	printf("Current Capacity = %ld\n", list->capacity);
	printf("Clear array \n");

	clear(list);
	printf("Size = %ld\n", size(list));
	printf("Current Capacity = %ld\n", list->capacity);
	return 0;
}
