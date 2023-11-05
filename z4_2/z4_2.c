#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    int priority;
} Element;

typedef struct {
    Element* elements;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->elements = (Element*)malloc(capacity * sizeof(Element));
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void destroyQueue(PriorityQueue* queue) {
    free(queue->elements);
    free(queue);
}

void addQueue(PriorityQueue* queue, int data, int priority) {
    if (priority < 0 || priority > 255){
        printf("Элемент не добавлен! Приоритет задаётся целым числом в диапазоне от 0 до 255\n");
        return;
    }

    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->elements = (Element*)realloc(queue->elements, queue->capacity * sizeof(Element));
    }
    int position = queue->size;
    while (position > 0 && queue->elements[position - 1].priority < priority) {
        queue->elements[position] = queue->elements[position - 1];
        position--;
    }
    queue->elements[position].data = data;
    queue->elements[position].priority = priority;
    queue->size++;
}

int getFirstElement(PriorityQueue* queue) {
    if (queue->size == 0) {
        printf("Очередь пуста\n");
        return -1;
    }
    int data = queue->elements[0].data;
    for (int i = 1; i < queue->size; i++) {
        queue->elements[i - 1] = queue->elements[i];
    }
    queue->size--;
    return data;
}

int getSpecElement(PriorityQueue* queue, int priority) {
    if (queue->size == 0) {
        printf("Очередь пуста\n");
        return -1;
    }

    for (int i = 0; i < queue->size; i++) {
        if (queue->elements[i].priority == priority) {
            int data = queue->elements[i].data;
            for (int j = i + 1; j < queue->size; j++) {
                queue->elements[j - 1] = queue->elements[j];
            }
            queue->size--;
            return data;
        }
    }
    printf("Элемент с указанным приоритетом не найден\n");
    return -1;
}

// Функция для извлечения элемента из очереди с указанным приоритетом или выше
int getSpecOrHighElement(PriorityQueue* queue, int priority) {
    if (queue->size == 0) {
        printf("Очередь пуста\n");
        return -1;
    }

    for (int i = 0; i < queue->size; i++) {
        if (queue->elements[i].priority == priority) {
            int data = queue->elements[i].data;
            for (int j = i + 1; j < queue->size; j++) {
                queue->elements[j - 1] = queue->elements[j];
            }
            queue->size--;
            return data;
        }

        if (queue->elements[i].priority < priority) {
            int data = queue->elements[i-1].data;
            for (int j = i; j < queue->size; j++) {
                queue->elements[j - 1] = queue->elements[j];
            }
            queue->size--;
            return data;
        }
    }
    printf("Элемент с указанным или выше приоритетом не найден.\n");
    return -1;
}

void testQueue() {
    int eldate[] = {10000, 10006, 10250, 10010, 10099, 10007, 10008, 10011, 10195, 10111};
    int elprio[] = {0, 6, 250, 10, 99, 7, 8, 11, 195, 111};
    PriorityQueue* queue = createQueue(10);

    printf("\nВ очередь добавлены элементы с данными приоритетами (содержание элементов '10' + 'приоритет элемента'\n");
    for (int i = 0; i < 10; i++){
        printf("Добавление №%d: %d\n",i+1,elprio[i]);
        addQueue(queue,eldate[i],elprio[i]);
    }

    printf("\nПопытка добавить элемент '10300' с приоритетом 300:\n");
    addQueue(queue, 10300, 300);

    printf("\nИзвлечение сообщений с наивысшим приоритетом:\n");
    int data = getFirstElement(queue);
    printf("Извлечено: %d\n", data);

    printf("\nИзвлечение сообщений с приоритетом 7:\n");
    data = getSpecElement(queue, 7);
    if (data != -1) {
        printf("Извлечено: %d\n", data);
    }

    printf("\nИзвлечение сообщений с приоритетом не ниже 7:\n");
    data = getSpecOrHighElement(queue, 7);
    if (data != -1) {
        printf("Извлечено: %d\n", data);
    }
    destroyQueue(queue);
}

int main() {
    testQueue();
    return 0;
}