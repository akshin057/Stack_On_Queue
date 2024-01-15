#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct queue { // �������. ���������� ������ � ��������� ������� �������
	struct queue_node* head;
	struct queue_node* tail;
};

struct queue_node { // ���� �������
	int value;
	struct queue_node* next;
	struct queue_node* prev;
};

struct stack_on_queue { // ���� �� �������, �������� � ���� ��������� �� ������� 
	struct queue* queue;
};

struct queue* create_queue(); 
struct stack_on_queue* create_stack_on_queue();
void enqueue(struct queue* queue, int value);
int dequeue(struct queue* queue);
void push(struct stack_on_queue* stack, int value);
int pop(struct stack_on_queue* stack);
int pull(struct stack_on_queue* stack);
int is_empty(struct stack_on_queue* stack);


int main() {
	setlocale(LC_ALL, "RUS");
	struct stack_on_queue* stack = create_stack_on_queue();

	push(stack, 1); // ���������� �������� � ����
	push(stack, 2);
	push(stack, 3);

	printf("%d\n", pop(stack)); // �������� � ����� �� ����� ���������� ��������
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));


	
	for (int i = 0; i < 1+rand()%100000; i++)
	{
		push(stack, rand());
	}

	push(stack, 1);
	

	printf("���� ���� ��� ���? %d\n", is_empty(stack));
	printf("%d\n", pop(stack)); // �������� � ����� �� ����� ���������� ��������
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	

	printf("���� ���� ��� ���? %d\n", is_empty(stack));
	return 0;
}

struct queue* create_queue() { // ������� �������� �������
	struct queue* queue = malloc(sizeof(struct queue)); // �������� ������������� ������� ���� ������� 
	queue->head = NULL; // ������ ������������� ���� ��� ��� ������ ������
	queue->tail = NULL; // ������ ������������� ���� 
	return queue;
}

struct stack_on_queue* create_stack_on_queue() { // ������� �������� ����� �� �������
	struct stack_on_queue* stack = malloc(sizeof(struct stack_on_queue)); // �������� �����
	stack->queue = create_queue(); // �������� ������ ����� ������� 
	return stack;
}
 
void enqueue(struct queue* queue, int value) { // ���������� ��������� � ����
	struct queue_node* node = malloc(sizeof(struct queue_node)); // �������� ���� �������
	node->value = value; // ���������� ��������
	node->next = NULL; // ���������� ���������� ���������� �� ��������� � ���������� ������� ������� ���������������� 
	node->prev = NULL;

	if (queue->head == NULL) // ���� ������� �����, �� ������ � ��������� ������� ����� ���������� ��������
	{
		queue->head = node;
		queue->tail = node;
	}
	else
	{
		queue->tail->next = node; //  ���������� ����� ������ �������� ������������� ����� ���� ������� 
		node->prev = queue->tail; // ����������� �������� ����� ����� ����� ������������� ���� ������� ������
		queue->tail = node; // ������ ������������� ����� ���� 
	}
}

int dequeue(struct queue* queue) {
	if (queue->tail == NULL) // ���� ������� ����� �� ���������� -1
	{
		return -1;
	}

	struct queue_node* node = queue->tail; // �������� ������ ����, �������� ������������� ����� �������
	int value = node->value; // ���������� �������� ����  

	if (queue->head == queue->tail) // ���� ������ � ��������� ������� ��������� �� ������� ��������� ������������ 
	{
		queue->head = NULL; 
		queue->tail = NULL;
	}
	else
	{
		queue->tail = node->prev;  // ������ ������������� �������, ������� ��� ����� ���
		queue->tail->next = NULL; // ����� ���������� ������ � ���������
	}
	free(node);
	return value;
}

void push(struct stack_on_queue* stack, int value) {
	enqueue(stack->queue, value); // ���������� � ������� ���������
}

int pop(struct stack_on_queue* stack) {
	return dequeue(stack->queue);// �������� ���������� t�������� �� �������
}

int pull(struct stack_on_queue* stack) {
	if (stack->queue->head == NULL) // ���� ������� ������ �� ���������� ���� 
	{
		return -1;
	}

	struct queue_node* node = stack->queue->head; // �������� ������ ���� �������
	int value = node->value; // ����������� �������� �� ����

	stack->queue->head = node->next; // ������ ������������� ��������� ����� ��� ��������
	if (stack->queue->head == NULL) // ���� ��������� ������� ������������ � �������
	{
		stack->queue->tail = NULL; // ���������� ��������� �� ����� �������
	}
	else {
		stack->queue->head->prev = NULL; // ���������� ��������� �� �������������� ����
	}

	free(node);
	return value;
}

int is_empty(struct stack_on_queue* stack) {
	return stack->queue->head == NULL; //���� ������ ����� ����, �� ������� �����
}

