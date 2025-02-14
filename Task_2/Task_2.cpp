#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Помилка виділення пам'яті!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void displayList(Node* head) {
    Node* temp = head;
    printf("Список: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void deleteNode(Node** head, int key) {
    if (*head == NULL) {
        printf("Список порожній!\n");
        return;
    }
    Node* temp = *head;
    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Елемент не знайдено в списку!\n");
        return;
    }
    if (temp->prev == NULL) {
        *head = temp->next;
    }
    else {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void destroyList(Node** head) {
    Node* current = *head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Node* head = NULL;
    int choice, data;

    do {
        printf("\n1. Додати елемент\n");
        printf("2. Видалити елемент\n");
        printf("3. Вивести список\n");
        printf("4. Знищити список\n");
        printf("5. Вийти\n");
        printf("Виберіть дію: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введіть дані для додавання: ");
            scanf_s("%d", &data);
            addNode(&head, data);
            break;
        case 2:
            printf("Введіть дані для видалення: ");
            scanf_s("%d", &data);
            deleteNode(&head, data);
            break;
        case 3:
            displayList(head);
            break;
        case 4:
            destroyList(&head);
            printf("Список знищено.\n");
            break;
        case 5:
            printf("Вихід з програми.\n");
            break;
        default:
            printf("Невірний вибір!\n");
        }
    } while (choice != 5);

    return 0;
}