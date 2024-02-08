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

/**
 * Create and return a pointer to a valid Queue
*/
Queue* queue();
/**
 * Print an entire queue to STDOUT.
*/
void printQueue(Queue* queue);
/**
 * Enqueue a given value into the queue properly.
*/
void enqueue(Queue* queue, char* value);