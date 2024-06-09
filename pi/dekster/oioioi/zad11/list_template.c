#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

struct List;
typedef void (*DataFp)(void*);
typedef void (*ConstDataFp)(const void*);
typedef  int (*CompareDataFp)(const void*, const void*);

typedef struct ListElement {
	struct ListElement *next;
	void *data;
} ListElement;

typedef struct {
	ListElement *head;
	ListElement *tail;
	ConstDataFp dump_data;
	DataFp free_data;
	CompareDataFp compare_data;
	DataFp modify_data;
} List;

void *safe_malloc(size_t size) {
	void *ptr = malloc(size);
	if(ptr) return ptr;
	printf("malloc error\n");
	exit(EXIT_FAILURE);
}

void *safe_strdup(const char *string) {
	void *ptr = strdup(string);
	if(ptr) return ptr;
	printf("strdup error\n");
	exit(EXIT_FAILURE);
}

// --- generic functions --- for any data type

void init_list(List *p_list, ConstDataFp dump_data, DataFp free_data,
		CompareDataFp compare_data, DataFp modify_data) {
  p_list->head = NULL;
  p_list->tail = NULL;
  p_list->dump_data = dump_data;
  p_list->free_data = free_data;
  p_list->compare_data = compare_data;
  p_list->modify_data = modify_data;
}

// Print elements of the list
void dump_list(const List* p_list) {
  ListElement *p = p_list->head;
  while(p != NULL)
  {
    p_list->dump_data(p->data);
    p = p->next;
  }
}

// Print elements of the list if comparable to data
void dump_list_if(List *p_list, void *data) {
  ListElement *p = p_list->head;
  while(p != NULL)
  {
    if(p_list->compare_data(data, p->data)) {
      p_list->dump_data(p->data);
    }
    p = p->next;
  }
}

// Free element pointed by data using free_data() function
void free_element(DataFp free_data, ListElement *to_delete) {
  free_data(to_delete->data);
  free(to_delete);
}

// Free all elements of the list
void free_list(List* p_list) {
  ListElement *p = p_list->head, *next;
  while(p != NULL)
  {
    next = p->next;
    free_element(p_list->free_data, p);
    p = next;
  }
}

// Push element at the beginning of the list
void push_front(List *p_list, void *data) {
  ListElement *p = (ListElement *)safe_malloc(sizeof(ListElement));
  p->data = data;
  p->next = NULL;
  if(p_list->head == NULL) {
    p_list->head = p;
    p_list->tail = p;
    return;
  }
  p->next = p_list->head;
  p_list->head = p;
}

// Push element at the end of the list
void push_back(List *p_list, void *data) {
  ListElement *p = (ListElement *)safe_malloc(sizeof(ListElement));
  p->data = data;
  p->next = NULL;
  if(p_list->head == NULL) {
    p_list->head = p;
    p_list->tail = p;
    return;
  }
  p_list->tail->next = p;
  p_list->tail = p;
}

// Remove the first element
void pop_front(List *p_list) {
  if(p_list->head == NULL) {
    return;
  }
  if(p_list->head == p_list->tail) {
    p_list->tail = NULL;
  }
  ListElement *p = p_list->head;
  p_list->head = p->next;
  free_element(p_list->free_data, p);
}

// Reverse the list
void reverse(List *p_list) {
  ListElement *q = p_list->head, *temp;
  if(q == NULL) {
    return;
  }
  ListElement *p = q->next;
  while(p != NULL)
  {
    temp = p->next;
    p->next = q;
    q = p;
    p = temp;
  }
  temp = p_list->head;
  p_list->head = p_list->tail;
  p_list->tail = temp;
  p_list->tail->next = NULL;
}

// find element in sorted list after which to insert given element
ListElement* find_insertion_point(const List *p_list, ListElement *p_element) {
  ListElement *q = p_list->head;
  if(q == NULL || p_list->compare_data(q->data, p_element->data) > 0) {
    return NULL;
  }
  ListElement *p = q->next;
  while(p != NULL && p_list->compare_data(p->data, p_element->data) <= 0)
  {
    q = p;
    p = p->next;
  }
  return q;
}

// Insert element after 'previous'
void push_after(List *p_list, void *data, ListElement *previous) {
  ListElement *p = (ListElement *)safe_malloc(sizeof(ListElement));
  p->data = data;
  ListElement *next = previous->next;
  previous->next = p;
  p->next = next;
  if(p_list->tail == previous) {
    p_list->tail = p;
  }
}

// Insert element preserving order
void insert_in_order(List *p_list, void *p_data) {
  ListElement *p = (ListElement *)safe_malloc(sizeof(ListElement));
  p->data = p_data;
  p->next = NULL;
  ListElement *prev = find_insertion_point(p_list, p);
  if(prev == NULL) {
    push_front(p_list, p_data);
  } else {
    if (p_list->compare_data(p->data, prev->data) == 0) {
      p_list->modify_data(prev->data);
      p_list->free_data(p->data);
      free(p);
    } else {
      push_after(p_list, p_data, prev);
    }
  }
}

// -----------------------------------------------------------
// --- type-specific definitions

// int element

void dump_int(const void *d) {
  printf("%d ",*(const int *)d);
}

void free_int(void *d) {
  free(d);
}

int cmp_int(const void *a, const void *b) {
  const int* x = (const int *)a;
  const int* y = (const int *)b;
  return *x - *y;
}

int *create_data_int(int v) {
  void *ptr = safe_malloc(sizeof(int));
  memcpy(ptr, (void *)&v, sizeof(int));
  return ptr;
}

// Word element

typedef struct DataWord {
	char *word;
	int counter;
} DataWord;

void dump_word (const void *d) {
  const DataWord *dw = (const DataWord *)d;
  printf("%s ", dw->word);
}

void free_word(void *d) {
  const DataWord *dw = (const DataWord *)d;
  free(dw->word);
}

int cmp_word_alphabet(const void *a, const void *b) {
  const DataWord *x = (const DataWord *)a;
  const DataWord *y = (const DataWord *)b;
  return strcasecmp(x->word, y->word);
}

int cmp_word_counter(const void *a, const void *b) {
  const DataWord *x = (const DataWord *)a;
  const DataWord *y = (const DataWord *)b;
  return x->counter == y->counter;
}

void modify_word(void *p) {
  DataWord *dw = (DataWord *)p;
  dw->counter++;
}

void *create_data_word(const char *string, int counter) {
  DataWord* dw = (DataWord *)safe_malloc(sizeof(DataWord));
  dw->counter = counter;
  dw->word = safe_strdup(string);
  return dw;
}

// read text, parse it to words, and insert those words to the list.
// Order of insertions is given by the last parameter of type CompareDataFp.
// (comparator function address). If this address is not NULL the element is
// inserted according to the comparator. Otherwise, read order is preserved.
void stream_to_list(List *p_list, FILE *stream, CompareDataFp cmp) {
		const char delimits[] = " \r\t\n.,?!:;-";
    char line[BUFFER_SIZE];
    char* word;
    DataWord* dw;
    if(cmp) {
      p_list->compare_data = cmp;
    }
    int i = 0;
    fgets(line, BUFFER_SIZE, stream);
    while(!feof(stream)) {
      fgets(line, BUFFER_SIZE, stream);
      if(line[0] == '\n') {
        break;
      }
      i++;
      word = strtok(line, delimits);
      while(word != NULL) {
        if(cmp) {
          for(int i = 0; word[i]; i++){
            word[i] = tolower(word[i]);
          }
          dw = create_data_word(word, 1);
          insert_in_order(p_list,dw);
        } else {
          dw = create_data_word(word, 1);
          push_back(p_list, dw);
        }
        word = strtok(NULL, delimits);
      }
    }
}

/////

void initList(List *list, ConstDataFp dump, DataFp free, CompareDataFp cmp, DataFp modify) {
  list->head = NULL;
  list->tail = NULL;
  list->dump_data = dump;
  list->free_data = free;
  list->compare_data = cmp;
  list->modify_data = modify;
}

void dumpList(const List* list) {
  if(list->dump_data == NULL) return;
  ListElement *i;
  for(i=list->head; i!=0; i=i->next) list->dump_data(i->data);
}

// Zwalnia pamiêæ elementów listy i danych
void freeList(List *list) {
  ListElement *current = 0;
  current = list->head;
  while(current) {
    ListElement *todelete = current;
    current = current->next;
    if(list->free_data) list->free_data(todelete->data); // zwolnienie pamiêci struktury data
    free(todelete);              // zwolnienie pamiêci elementu
  }
  list->head = NULL;
  list->tail = NULL;
}

// Uniwersalne funkcje obs³ugi elementów listy

// Dodaje element na pocz¹tku listy
void pushFront(List *list, void *data) {
  ListElement *element=(ListElement *)safe_malloc(sizeof(ListElement));
  element->data=data;
  element->next=list->head;
  list->head=element;
  if(!list->tail)list->tail=list->head;
}

// Dodaje element na koñcu listy
void pushBack(List *list, void *data) {
  ListElement *element=(ListElement *)safe_malloc(sizeof(ListElement));
  element->data=data;
  element->next=NULL;
  if(list->tail)list->tail->next=element;
  list->tail=element;
  if(!list->head)list->head=list->tail;
}

// Usuwa pierwszy element listy
void popFront(List *list) {
  if(list->head==NULL) return;
  ListElement *toDel=list->head;
  list->head=list->head->next;
  free(toDel);
  if(!list->head) list->tail=NULL;
}

// Odwraca kolejnoœæ elementów listy
void reverse2(List *list) {
  ListElement *iter=list->head,*tmp=iter->next,*ptr;
  while(tmp){
    ptr=tmp->next;
    tmp->next=iter;
    iter=tmp;
    tmp=ptr;
  }
  list->tail=list->head;
  list->head=iter;
  list->tail->next=NULL;
}

// Zwraca element w posortowanej liœcie, a je¿eli nie ma, to element poprzedzaj¹cy (nie ma, to NULL)
ListElement* findInsertionPoint(const List *list, ListElement *element) {
  ListElement *insertionPoint=NULL;
  ListElement *current;
  for(current=list->head; current; current=current->next){
    if(list->compare_data(current->data,element->data)<=0)
      insertionPoint=current;
    else break;
  }
  return insertionPoint;
}


void insertInOrder(List *list, void *a) {
  ListElement *example=(ListElement *)safe_malloc(sizeof(ListElement));
  example->data=a;
  ListElement *ptr=findInsertionPoint(list,example);
  if (ptr==NULL) pushFront(list,example->data);
  else if (list->compare_data(ptr->data,example->data)==0){
    if (list->modify_data) list->modify_data(ptr->data);
    list->free_data(example->data);
    free(example);
  }
  else{
    example->next=ptr->next;
    ptr->next=example;
  }
}

typedef int DataInt;

void dumpInt(const void *d) {
  printf("%d ",*(const int *)d);
}

void freeInt(void *d) {
  free(d);
}

int cmpInt(const void *a, const void *b) {
  return *(const int *)a-*(const int *)b;
}

void *createDataInt(int v) {
  void *ptr=safe_malloc(sizeof(int));
  memcpy(ptr,(void *)&v,sizeof(int));
  return ptr;
}

////

// test integer list
void list_test(List *p_list, int n) {
	char op;
	int v;
	for (int i = 0; i < n; ++i) {
		scanf(" %c", &op);
		switch (op) {
			case 'f':
				scanf("%d", &v);
				push_front(p_list, create_data_int(v));
				break;
			case 'b':
				scanf("%d", &v);
				push_back(p_list, create_data_int(v));
				break;
			case 'd':
				pop_front(p_list);
				break;
			case 'r':
				reverse(p_list);
				break;
			case 'i':
				scanf("%d", &v);
				insert_in_order(p_list, create_data_int(v));
				break;
			default:
				printf("No such operation: %c\n", op);
				break;
		}
	}
}

void listTest(List *plist, int n) {
  char op[2];
  int v;
  ListElement element, *pelement;
  DataInt data;
  for (int i = 0; i < n; ++i) {
    scanf("%s", op);
    switch (op[0]) {
      case 'f': // dodaj na pocz¹tku listy
        scanf("%d", &v);
        pushFront(plist,createDataInt(v));
        break;
      case 'b': // dodaj na koñcu listy
        scanf("%d", &v);
        pushBack(plist,createDataInt(v));
        break;
      case 'd': // usuñ pierwszy element
        popFront(plist);
        break;
      case 'r': // odwróæ kolejnoœæ
        reverse2(plist);
        break;
      case 'i': // dodaj wg porz¹dku rosn¹cego (int) lub alfabetycznego (char),
        // je¿eli element ju¿ istnieje, to akcja zale¿na od typu danych
        scanf("%d",&v);
        insertInOrder(plist,createDataInt(v));
        break;
      default:
        printf("No such operation: %s\n", op);
        break;
    }
  }
}

int main(void) {
	int to_do, n;
	List list;

	scanf ("%d", &to_do);
	switch (to_do) {
		case 1: // test integer list
			scanf("%d",&n);
			initList(&list, dumpInt, freeInt, cmpInt, NULL);
			listTest(&list, n);
			dumpList(&list);
			freeList(&list);
			break;
		case 2: // read words from text, insert into list, and print
			init_list(&list, dump_word, free_word, NULL, NULL);
			stream_to_list(&list, stdin, NULL);
			dump_list(&list);
			free_list(&list);
			break;
		case 3: // read words, insert into list alphabetically, print words encountered n times
			scanf("%d",&n);
			init_list(&list, dump_word, free_word, NULL, modify_word);
			stream_to_list(&list, stdin, cmp_word_alphabet);
			list.compare_data = cmp_word_counter;
			DataWord data = { NULL, n };
			dump_list_if(&list, &data);
			free_list(&list);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

