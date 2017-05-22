#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	struct element* before;
	char* payload;
	int length;
	struct element* after;
} lListElement;

typedef struct lList {
	lListElement *first, *last;
	int size;
} lList;

void reverse_list(lList*);
void clear_list(lList*);
void print_element(lListElement*);
void print_list(lList*);
void push_back(lList*, lListElement*);
void push_front(lList*, lListElement*);
void remove_index(lList*, int);
lListElement* newElement(char*, int);
lListElement* get_index(lList*, int);

int main(void) {
	lList* liste = malloc(sizeof(lList));
	liste->size = 0;

	printf("Created list\n");
	lListElement* e1 = newElement("E1", 2);
	lListElement* e2 = newElement("E2", 2);
	lListElement* e3 = newElement("E3", 2);

	push_back(liste, e1);
	push_back(liste, e2);
	push_back (liste, e3);

	reverse_list(liste);

	printf("Filled list\nSize: %d\n", liste->size);

	print_list(liste);

	clear_list(liste);
	free(liste);

	system("pause");

	return 0;
}

void reverse_list(lList* l) {
	lListElement* root = l->first;
	lListElement* new_root = 0;
	while (root) {
	   lListElement* next = root->after;
	   root->after = new_root;
	   new_root = root;
	   root = next;
	}
	l->last = l->first;
	l->first = new_root;
}

void clear_list(lList* l) {
	while(l->size) remove_index(l, 0);
}

void print_element(lListElement* e) {
	printf("%p|%p|%p\t%s\n", e->before, e, e->after, e->payload);
}

void print_list(lList* l) {
	lListElement* e = l->first;
	for(int i = 0; i < l->size; i++) {
		print_element(e);
		e = e->after;
	}
}

lListElement* get_index(lList* l, int i) {
	lListElement* temp;
	if(i <= (l->size / 2)) {
		temp = l->first;
		for(int a = 0; a < i; a++) {
			temp = temp->after;
		}
	} else {
		temp = l->last;
		for(int a = l->size - 1; a > l->size - i + 1; a--) {
			temp = temp->before;
		}
	}
	return temp;
}

lListElement* newElement(char* content, int length) {
	lListElement* element = malloc(sizeof(lListElement));
	element->before = 0;
	element->after = 0;
	element->length = length;
	element->payload = content;
	return element;
}

void push_back(lList* l, lListElement* e) {
	if (l->size) {
		l->last->after = e;
		e->before = l->last;
		e->after = 0;
	} else {
		l->first = e;
	}
	l->last = e;
	l->size++;
}

void push_front(lList* l, lListElement* e) {
	if (l->size){
		l->first->before = e;
		e->after = l->first;
		e->before = 0;
	} else {
		l->last = e;
	}
	l->first = e;
	l->size++;
}

void remove_index(lList* l, int i) {
	lListElement* temp = get_index(l, i);

	lListElement* bef = temp->before;
	lListElement* aft = temp->after;

	if (bef) {
	} else { // first
		l->first = aft;
	}

	if (aft) {
		aft->before = bef;
	} else { // last
		l->last = bef;
	}

	free(temp);

	l->size--;
}
