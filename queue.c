#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BASE_LENGTH 10;

typedef struct QueueNode {
	char* value;
	struct QueueNode* next;
	struct QueueNode* before;
} QueueNode;

typedef struct {
	QueueNode* first;
	QueueNode* last;
	int length;
} Queue;

Queue* queue() {
	Queue* q = malloc(sizeof(Queue));
	q->first = NULL;
	q->last = NULL;
	q->length = 0;
	return q;
}

QueueNode* createNodeQueue(char* value, QueueNode* next, QueueNode* before) {
	QueueNode* qn = malloc(sizeof(QueueNode));
	qn->value = strdup(value);
	qn->next = next;
	qn->before = before;
	return qn;
}

void printQueue(Queue* queue) {
	if (queue->first == NULL) {
		return;
	}
	QueueNode* n = queue->first;
	QueueNode* next = n->next;
	while(next != NULL) {
		printf("%s", n->value);
		n = n->next;
		next = n->next;
	}
	printf("%s", n->value);
	queue->last = n;
}

void enqueue(Queue* queue, char* value) {
	QueueNode* node = createNodeQueue(value, NULL, NULL);
	if (queue->length == 0)  {
		queue->first = node;
		queue->last = queue->first;
		queue->length++;
		return;
	}
	node->before = queue->last;
	queue->last->next = node;
	queue->last = node;
	queue->length++;
	return;
}

char* dequeue(Queue* queue) {
	QueueNode* first = queue->first;
	char* v  = first->value;
	if (first->next != NULL) {
		first->next->before = NULL;
	}
	queue->first = first->next;
	free(first);
	return v;
}

char* pick(Queue *queue) {
	if (queue->first) {
		return queue->first->value;	
	}
	return NULL;
}