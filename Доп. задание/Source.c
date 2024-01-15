#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct queue { // очередь. Содержится первый и последний элемент очереди
	struct queue_node* head;
	struct queue_node* tail;
};

struct queue_node { // узел очереди
	int value;
	struct queue_node* next;
	struct queue_node* prev;
};

struct stack_on_queue { // стек на очереди, содержит в себе указатель на очередь 
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

	push(stack, 1); // добавление элемента в стэк
	push(stack, 2);
	push(stack, 3);

	printf("%d\n", pop(stack)); // удаление и вывод на экран последнего элемента
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));


	
	for (int i = 0; i < 1+rand()%100000; i++)
	{
		push(stack, rand());
	}

	push(stack, 1);
	

	printf("Стек пуст или нет? %d\n", is_empty(stack));
	printf("%d\n", pop(stack)); // удаление и вывод на экран последнего элемента
	printf("%d\n", pop(stack));
	printf("%d\n", pop(stack));
	

	printf("Стек пуст или нет? %d\n", is_empty(stack));
	return 0;
}

struct queue* create_queue() { // функция создания очереди
	struct queue* queue = malloc(sizeof(struct queue)); // создание динамического массива типа очереди 
	queue->head = NULL; // голове присваивается нуль так как голова пустая
	queue->tail = NULL; // хвосту присваивается нуль 
	return queue;
}

struct stack_on_queue* create_stack_on_queue() { // функция создания стека на очереди
	struct stack_on_queue* stack = malloc(sizeof(struct stack_on_queue)); // создание стека
	stack->queue = create_queue(); // создание внутри стека очереди 
	return stack;
}
 
void enqueue(struct queue* queue, int value) { // добавление элементов в стек
	struct queue_node* node = malloc(sizeof(struct queue_node)); // создание узла очереди
	node->value = value; // присвоение значения
	node->next = NULL; // объявления предыдущих указателей на следующий и предыдущий элемент очереди недейсвительными 
	node->prev = NULL;

	if (queue->head == NULL) // если очередь пуста, то первый и последний элемент имеют одинаковое значение
	{
		queue->head = node;
		queue->tail = node;
	}
	else
	{
		queue->tail->next = node; //  следующему после хвоста элементу присваивается новый узел очереди 
		node->prev = queue->tail; // предыдущему элементу перед новым узлом присваивается узел старого хвоста
		queue->tail = node; // хвосту присваивается новыф узел 
	}
}

int dequeue(struct queue* queue) {
	if (queue->tail == NULL) // если очередь пуста то возвращает -1
	{
		return -1;
	}

	struct queue_node* node = queue->tail; // создание нового узла, которому присваивается хвост очереди
	int value = node->value; // присвоение значению узла  

	if (queue->head == queue->tail) // если первый и последний элемент одинаковы то очередь перестает существовать 
	{
		queue->head = NULL; 
		queue->tail = NULL;
	}
	else
	{
		queue->tail = node->prev;  // хвосту присваивается элемент, который был перед ним
		queue->tail->next = NULL; // хвост становится пустым и удаляется
	}
	free(node);
	return value;
}

void push(struct stack_on_queue* stack, int value) {
	enqueue(stack->queue, value); // добавление в очередь элементов
}

int pop(struct stack_on_queue* stack) {
	return dequeue(stack->queue);// удаление последнего tэлемента из очереди
}

int pull(struct stack_on_queue* stack) {
	if (stack->queue->head == NULL) // если очередь пустая то возвращает нуль 
	{
		return -1;
	}

	struct queue_node* node = stack->queue->head; // создание нового узла очереди
	int value = node->value; // извлекается значение из узла

	stack->queue->head = node->next; // голове присваивается следующее после нее значение
	if (stack->queue->head == NULL) // если удаляемый элемент единственный в очереди
	{
		stack->queue->tail = NULL; // обнуляется указатель на хвост очереди
	}
	else {
		stack->queue->head->prev = NULL; // обнуляется указатель на предшествующий узел
	}

	free(node);
	return value;
}

int is_empty(struct stack_on_queue* stack) {
	return stack->queue->head == NULL; //если голова равна нулю, то очередь пуста
}

