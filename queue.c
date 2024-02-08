#include <string.h>
#define BASE_LENGTH 10;

typedef struct QueueNode {
	char* v;
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

QueueNode* createNode(char* value, QueueNode* next, QueueNode* before) {
	QueueNode* qn = malloc(sizeof(QueueNode));
	qn->value = strdup(value);
	qn->next = next;
	qn->before = before;
	return qn
}

void findLast(Queue* queue) {
	QueueNode* n = queue->first;
	QueueNode* next = n->next;
	while(next != NULL) {
		n = queue->next;
		next = n->next;
	}
	queue->last = n;
}

void enqueue(Queue* queue, char* value) {
	QueueNode* node = createNode(value, NULL, NULL);
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

void dequeue(Queue* queue) {
	QueueNode* last = queue->last;

}

