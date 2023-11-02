#include <stdio.h>
#include <string.h>

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

// Функция для добавления контакта в телефонную книгу
void addContact(Contact contacts[], int *numContacts) {
    if (*numContacts >= MAX_CONTACTS) {
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

    contacts[*numContacts] = newContact;
    (*numContacts)++;

    printf("Контакт успешно добавлен\n");
}

// Функция для вывода информации о контакте
void printContact(Contact contact) {
    printf("Имя: %s\n", contact.name);
    printf("Место работы: %s\n", contact.workplace);
    printf("Номера телефонов: ");
    for (int i = 0; i < MAX_PHONE_COUNT && strlen(contact.phoneNumbers[i]) > 0; i++) {
        printf("%s ", contact.phoneNumbers[i]);
    }
    printf("\n");
    printf("Адреса электронной почты: ");
    for (int i = 0; i < MAX_EMAIL_COUNT && strlen(contact.email[i]) > 0; i++){
        printf("%s ", contact.email[i]);
    }
    printf("\n");
    printf("Ссылки на страницы в соцсетях: ");
    for (int i = 0; i < MAX_SOCIAL_MEDIA_COUNT && strlen(contact.socialMedia[i]) > 0; i++){
        printf("%s ", contact.socialMedia[i]);
    }
    printf("\n");
    printf("Профили в мессенджерах: ");
    for (int i = 0; i < MAX_MESSENGER_COUNT && strlen(contact.messenger[i]) > 0; i++){
        printf("%s ", contact.messenger[i]);
    }
    printf("\n");
}

// Функция для редактирования контакта
void editContact(Contact contacts[], int numContacts) {
    char searchName[MAX_NAME_LENGTH];
    printf("Введите имя контакта, которого хотите отредактировать: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    int foundContactIndex = -1;
    for (int i = 0; i < numContacts; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            foundContactIndex = i;
            break;
        }
    }
    if (foundContactIndex == -1) {
        printf("Контакт с таким именем не найден\n");
    }
    else {
        printf("Найден контакт:\n");
        printContact(contacts[foundContactIndex]);

        printf("Введите новое место работы (или оставьте пустым): ");
        fgets(contacts[foundContactIndex].workplace, MAX_WORKPLACE_LENGTH, stdin);
        contacts[foundContactIndex].workplace[strcspn(contacts[foundContactIndex].workplace, "\n")] = '\0';

        for (int i = 0; i < MAX_PHONE_COUNT; i++){
            printf("Введите новый номер телефона №%d (или оставьте пустым): ", i + 1);
            fgets(contacts[foundContactIndex].phoneNumbers[i], MAX_PHONE_LENGTH, stdin);
            contacts[foundContactIndex].phoneNumbers[i][strcspn(contacts[foundContactIndex].phoneNumbers[i], "\n")] = '\0';
            if (strlen(contacts[foundContactIndex].phoneNumbers[i]) == 0) {
                break;
            }
        }

        for (int i = 0; i < MAX_EMAIL_COUNT; i++){
            printf("Введите новый адрес электронной почты №%d (или оставьте поле пустым): ", i + 1);
            fgets(contacts[foundContactIndex].email[i], MAX_EMAIL_LENGTH, stdin);
            contacts[foundContactIndex].email[i][strcspn(contacts[foundContactIndex].email[i], "\n")] = '\0';
            if (strlen(contacts[foundContactIndex].email[i]) == 0){
                break;
            }
        }

        for (int i = 0; i < MAX_SOCIAL_MEDIA_COUNT; i++){
            printf("Введите новую ссылку на страницу в соцсетях №%d (или оставьте поле пустым): ", i + 1);
            fgets(contacts[foundContactIndex].socialMedia[i], MAX_SOCIAL_MEDIA_LENGTH, stdin);
            contacts[foundContactIndex].socialMedia[i][strcspn(contacts[foundContactIndex].socialMedia[i], "\n")] = '\0';
            if (strlen(contacts[foundContactIndex].socialMedia[i]) == 0){
                break;
            }
        }

        for (int i = 0; i < MAX_MESSENGER_COUNT; i++){
            printf("Введите новый профиль в мессенджере №%d (или оставьте поле пустым): ", i + 1);
            fgets(contacts[foundContactIndex].messenger[i], MAX_MESSENGER_LENGTH, stdin);
            contacts[foundContactIndex].messenger[i][strcspn(contacts[foundContactIndex].messenger[i], "\n")] = '\0';
            if (strlen(contacts[foundContactIndex].messenger[i]) == 0){
                break;
            }
        }

        printf("Контакт успешно отредактирован\n");
    }
}

// Функция для удаления контакта
void deleteContact(Contact contacts[], int *numContacts) {
    char searchName[MAX_NAME_LENGTH];
    printf("Введите имя контакта, которого хотите удалить: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    int foundContactIndex = -1;
    for (int i = 0; i < *numContacts; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            foundContactIndex = i;
            break;
        }
    }

    if (foundContactIndex == -1) {
        printf("Контакт с таким именем не найден\n");
    }
    else {
        // Сжатие списка контактов
        for (int i = foundContactIndex; i < *numContacts - 1; i++) {
            contacts[i] = contacts[i + 1];
        }

        (*numContacts)--;
        printf("Контакт успешно удален\n");
    }
}

// Функция для вывода всех контактов
void printAllContacts(Contact contacts[], int numContacts) {
    if (numContacts == 0) {
        printf("Телефонная книга пуста\n");
    } else {
        for (int i = 0; i < numContacts; i++) {
            printf("\nКонтакт #%d:\n", i + 1);
            printContact(contacts[i]);
            printf("-------------------\n");
        }
    }
}

int main() {
    Contact contacts[MAX_CONTACTS];
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
                addContact(contacts, &numContacts);
                break;
            case 2:
                editContact(contacts, numContacts);
                break;
            case 3:
                deleteContact(contacts, &numContacts);
                break;
            case 4:
                printAllContacts(contacts, numContacts);
                break;
            case 5:
                printf("Телефонная книга закрыта\n");
                return 0;
            default:
                printf("Неверный номер действия\n");
        }
    }
}