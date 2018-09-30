#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_
#define INITIAL_CAPACITY 10

typedef struct arraylist {
	size_t size;
	size_t capacity;
	void **arraylist;
} ArrayList;

ArrayList *arrlist_create();
void add(ArrayList *, void *);
void insert(ArrayList *, size_t, void *);
size_t size(ArrayList *);
void *get(ArrayList *, size_t);
void set(ArrayList* , size_t , void *);
void* _remove_(ArrayList *, size_t);
void clear(ArrayList *);
void check_index(ArrayList *, size_t);
void check_ptr(void *);
void _realloc(ArrayList *);

#endif /* !_ARRAYLIST_H_ */
