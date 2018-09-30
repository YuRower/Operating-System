#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
ArrayList * arrlist_create();
void check_index(ArrayList *, size_t);
void check_ptr(void *);
void _realloc(ArrayList *);
void clear(ArrayList *list);
void add(ArrayList *list, void *p_elem);
void insert(ArrayList *list, size_t index, void *p_elem);
size_t size(ArrayList *list);
void* _remove_(ArrayList *list, size_t index);
void * get(ArrayList *list, size_t index);
void set(ArrayList* list, size_t index, void *p_elem) ;

ArrayList * arrlist_create(){
	ArrayList *list;
	list = (ArrayList *) malloc(sizeof(ArrayList) * (1));
	check_ptr(list);
	list->size = 0;
	list->capacity = INITIAL_CAPACITY;
	list->arraylist = (void  *) malloc(sizeof(void  *) * (list->capacity));
	check_ptr(list->arraylist);
	return list;
}

void check_index(ArrayList *list, size_t index){
	if (index >= list->size) {
		(void)fprintf(stderr, 
		      "arraylist: index [%zu] out of range [0, %zu]\n",
			  index,
			  list->size - 1);
		exit(EXIT_FAILURE);
	}
}
void check_ptr(void *ptr){
	if (ptr == NULL) {
		(void)fprintf(stderr, "arraylist: NULL pointer\n");
		exit(EXIT_FAILURE);
	}
}
void _realloc(ArrayList *list){
	if (list->size >= list->capacity) {
		list->capacity = (list->capacity *3 ) / 2 + 1;
		list -> arraylist = (void * ) realloc (list -> arraylist,sizeof(void *) * (list->capacity));
		check_ptr(list -> arraylist);
	}
}
void clear(ArrayList *list){
	check_ptr(list);
	free(list->arraylist);
	list->arraylist = NULL;
	list->size = 0;
	list->capacity = 0;
	free(list);
}


void add(ArrayList *list, void *p_elem){
	check_ptr(list);
	list->size++;
	_realloc(list);
	list->arraylist[list->size - 1] = p_elem;
}

void insert(ArrayList *list, size_t index, void *p_elem){
	size_t i;
	check_ptr(list);
	check_index(list, index);
	void * temp ;
	_realloc(list);
	for (i=index;i < list->size ;++i){
		temp = list->arraylist[i];
		list->arraylist[i] = p_elem;
		p_elem = temp;
	}
	
    add(list,p_elem);
}

size_t size(ArrayList *list){
	check_ptr(list);
	return list->size;
}


void* _remove_(ArrayList *list, size_t index){
	void *target;
	size_t i;
	check_ptr(list);
	/*free(list->arraylist[index]);
	for ( ; index < list->size - 1; ++index) {
			list->arraylist[index] = list->arraylist[index + 1];
}*/
	check_index(list, index);
	target = list->arraylist[index];
	for (i = index + 1; i < list->size; i++)
		list->arraylist[i - 1] = list->arraylist[i];
	list->size--;
	
return target;
}

void * get(ArrayList *list, size_t index){
	check_ptr(list);
	check_index(list, index);
	return list->arraylist[index];
}

void set(ArrayList* list, size_t index, void *p_elem) {
		check_ptr(list);
		list->arraylist[index] = p_elem;
}


