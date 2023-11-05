#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_WORKPLACE_LENGTH 100
#define MAX_PHONE_COUNT 3
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_COUNT 3
#define MAX_EMAIL_LENGTH 258
#define MAX_SOCIAL_MEDIA_COUNT 3
#define MAX_SOCIAL_MEDIA_LENGTH 100
#define MAX_MESSENGER_COUNT 3
#define MAX_MESSENGER_LENGTH 50

// Структура для хранения контакта
typedef struct {
    char name[MAX_NAME_LENGTH];
    char workplace[MAX_WORKPLACE_LENGTH];
    char phoneNumbers[MAX_PHONE_COUNT][MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_COUNT][MAX_EMAIL_LENGTH];
    char socialMedia[MAX_SOCIAL_MEDIA_COUNT][MAX_SOCIAL_MEDIA_LENGTH];
    char messenger[MAX_MESSENGER_COUNT][MAX_MESSENGER_LENGTH];
} Contact;

typedef struct {
    Contact contact;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} ContactList;

ContactList* creatContactList() {
    ContactList * list = (ContactList*)malloc(sizeof(ContactList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

Node* createNode(Contact contact) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(ContactList* list, Node* newNode) {
    if (list->size == 0) {
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
    }
    list->head = newNode;
    list->size++;
}

void insertAtEnd(ContactList* list, Node* newNode) {
    if (list->size == 0) {
        list->head = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->size++;
}

void insertInOrder(ContactList* list, Node* newNode) {
    if (list->size == 0) {
        insertAtBeginning(list, newNode);
        return;
    }

    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->contact.name, newNode->contact.name) > 0) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        insertAtEnd(list, newNode);
    } else if (current == list->head) {
        insertAtBeginning(list, newNode);
    } else {
        newNode->prev = current->prev;
        newNode->next = current;
        current->next = newNode;
        current->prev = newNode;
        list->size++;
    }
}

void printContacts(ContactList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Contact contact = current->contact;
        printf("Имя: %s\n", contact.name);
        printf("Место работы: %s\n", contact.workplace);
        printf("Номера телефонов:\n");
        for (int i = 0; i < MAX_PHONE_COUNT; i++) {
            if (strlen(contact.phoneNumbers[i]) > 0) {
                printf("%d. %s\n", i + 1, contact.phoneNumbers[i]);
            }
        }
        printf("Email:\n");
        for (int i = 0; i < MAX_EMAIL_COUNT; i++) {
            if (strlen(contact.email[i]) > 0) {
                printf("%d. %s\n", i + 1, contact.email[i]);
            }
        }
        printf("Ссылки на соцсети:\n");
        for (int i = 0; i < MAX_SOCIAL_MEDIA_COUNT; i++) {
            if (strlen(contact.socialMedia[i]) > 0) {
                printf("%d. %s\n", i + 1, contact.socialMedia[i]);
            }
        }
        printf("Профили в мессенджерах:\n");
        for (int i = 0; i < MAX_MESSENGER_COUNT; i++) {
            if (strlen(contact.messenger[i]) > 0) {
                printf("%d. %s\n", i + 1, contact.messenger[i]);
            }
        }
        printf("\n");
        current = current->next;
    }
}

void addContact(ContactList* list) {
    if (list->size >= MAX_CONTACTS) {
        printf("Телефонная книга уже заполнена\n");
        return;
    }

    Contact newContact;

    printf("Введите имя: ");
    fgets(newContact.name, MAX_NAME_LENGTH, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0';  // Удаление символа новой строки

    printf("Введите место работы: ");
    fgets(newContact.workplace, MAX_WORKPLACE_LENGTH, stdin);
    newContact.workplace[strcspn(newContact.workplace, "\n")] = '\0';

    for (int i = 0; i < MAX_PHONE_COUNT; i++) {
        printf("Введите номер телефона №%d (или оставьте пустым): ", i + 1);
        fgets(newContact.phoneNumbers[i], MAX_PHONE_LENGTH, stdin);
        newContact.phoneNumbers[i][strcspn(newContact.phoneNumbers[i], "\n")] = '\0';
        if (strlen(newContact.phoneNumbers[i]) == 0) {
            break;
        }
    }

    for (int i = 0; i < MAX_EMAIL_COUNT; i++){
        printf("Введите адрес электронной почты №%d (или оставьте пустым): ", i + 1);
        fgets(newContact.email[i], MAX_EMAIL_LENGTH, stdin);
        newContact.email[i][strcspn(newContact.email[i], "\n")] = '\0';
        if (strlen(newContact.email[i]) == 0){
            break;
        }
    }

    for (int i = 0; i < MAX_SOCIAL_MEDIA_COUNT; i++){
        printf("Введите ссылку на страницу в соцсетях №%d (или оставьте пустым): ", i + 1);
        fgets(newContact.socialMedia[i], MAX_SOCIAL_MEDIA_LENGTH, stdin);
        newContact.socialMedia[i][strcspn(newContact.socialMedia[i], "\n")] = '\0';
        if (strlen(newContact.socialMedia[i]) == 0){
            break;
        }
    }

    for (int i = 0; i < MAX_MESSENGER_COUNT; i++){
        printf("Введите профиль в мессенджере: №%d (или оставьте пустым): ", i + 1);
        fgets(newContact.messenger[i], MAX_MESSENGER_LENGTH, stdin);
        newContact.messenger[i][strcspn(newContact.messenger[i], "\n")] = '\0';
        if (strlen(newContact.messenger[i]) == 0){
            break;
        }
    }

    Node* newNode = createNode(newContact);
    insertInOrder(list, newNode);

    printf("Контакт успешно добавлен\n");
}

// Функция для редактирования контакта
void editContact(ContactList* list) {
    char searchName[MAX_NAME_LENGTH];
    printf("Введите имя контакта, которого хотите отредактировать: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    Node* current = list->head;
    int foundContactIndex = -1;
    while (current != NULL) {
        if (strcmp(current->contact.name, searchName) == 0) {
            foundContactIndex = 1;
            break;
        }
        current = current->next;
    }

    if (foundContactIndex == -1) {
        printf("Контакт с таким именем не найден\n");
    } else {
        printf("Найден контакт:\n");

        printf("Введите новое место работы (или оставьте пустым): ");
        fgets(current->contact.workplace, MAX_WORKPLACE_LENGTH, stdin);
        current->contact.workplace[strcspn(current->contact.workplace, "\n")] = '\0';

        for (int i = 0; i < MAX_PHONE_COUNT; i++){
            printf("Введите новый номер телефона №%d (или оставьте пустым): ", i + 1);
            fgets(current->contact.phoneNumbers[i], MAX_PHONE_LENGTH, stdin);
            current->contact.phoneNumbers[i][strcspn(current->contact.phoneNumbers[i], "\n")] = '\0';
            if (strlen(current->contact.phoneNumbers[i]) == 0) {
                break;
            }
        }

        for (int i = 0; i < MAX_EMAIL_COUNT; i++){
            printf("Введите новый адрес электронной почты №%d (или оставьте поле пустым): ", i + 1);
            fgets(current->contact.email[i], MAX_EMAIL_LENGTH, stdin);
            current->contact.email[i][strcspn(current->contact.email[i], "\n")] = '\0';
            if (strlen(current->contact.email[i]) == 0){
                break;
            }
        }

        for (int i = 0; i < MAX_SOCIAL_MEDIA_COUNT; i++){
            printf("Введите новую ссылку на страницу в соцсетях №%d (или оставьте поле пустым): ", i + 1);
            fgets(current->contact.socialMedia[i], MAX_SOCIAL_MEDIA_LENGTH, stdin);
            current->contact.socialMedia[i][strcspn(current->contact.socialMedia[i], "\n")] = '\0';
            if (strlen(current->contact.socialMedia[i]) == 0){
                break;
            }
        }

        for (int i = 0; i < MAX_MESSENGER_COUNT; i++){
            printf("Введите новый профиль в мессенджере №%d (или оставьте поле пустым): ", i + 1);
            fgets(current->contact.messenger[i], MAX_MESSENGER_LENGTH, stdin);
            current->contact.messenger[i][strcspn(current->contact.messenger[i], "\n")] = '\0';
            if (strlen(current->contact.messenger[i]) == 0){
                break;
            }
        }

        printf("Контакт успешно отредактирован\n");
    }
}

// Функция для удаления контакта
void deleteContact(ContactList* list) {
    char searchName[MAX_NAME_LENGTH];
    printf("Введите имя контакта, которого хотите удалить: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    Node* current = list->head;
    int foundContactIndex = -1;
    int index = 0;
    while (current != NULL) {
        if (strcmp(current->contact.name, searchName) == 0) {
            foundContactIndex = index;
            break;
        }
        current = current->next;
        index++;
    }

    if (foundContactIndex == -1) {
        printf("Контакт с таким именем не найден\n");
    }
    else {
        // Удаление контакта из списка
        Node* toDelete = current;
        if (toDelete == list->head) {
            list->head = toDelete->next;
            if (list->head != NULL) {
                list->head->prev = NULL;
            }
        } else if (toDelete == list->tail) {
            list->tail = toDelete->prev;
            if (list->tail != NULL) {
                list->tail->next = NULL;
            }
        } else {
            toDelete->prev = toDelete->next;
            toDelete->next = toDelete->prev;
        }

        free(toDelete);
        list->size--;
        printf("Контакт успешно удален\n");
    }
}

int main() {
    ContactList* contactList = creatContactList();
    int numContacts = 0;
    int menu;
    printf("-----Телефонная книга-----\n");
    while (1) {
        printf(" 1 - Добавить контакт\n");
        printf(" 2 - Редактировать контакт\n");
        printf(" 3 - Удалить контакт\n");
        printf(" 4 - Вывести все контакты\n");
        printf(" 5 - Выйти из книги\n");
        printf("Выберите действие: ");
        scanf("%d", &menu);
        getchar();  // Чтение символа новой строки после ввода выбора
        switch (menu) {
            case 1:
                addContact(contactList);
                break;
            case 2:
                editContact(contactList);
                break;
            case 3:
                deleteContact(contactList);
                break;
            case 4:
                printContacts(contactList);
                break;
            case 5:
                printf("Телефонная книга закрыта\n");
                return 0;
            default:
                printf("Неверный номер действия\n");
        }
    }
}