#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void printList(const int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sortList(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int removeDuplicates(int* arr, int size) {
    if (size == 0) return 0;

    int uniqueIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[uniqueIndex]) {
            uniqueIndex++;
            arr[uniqueIndex] = arr[i];
        }
    }
    return uniqueIndex + 1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int List1[10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        List1[i] = rand() % 10;
    }

    printf("Список (1):\n");
    printList(List1, 10);

    sortList(List1, 10);
    printf("Відсортований список:\n");
    printList(List1, 10);

    int size = removeDuplicates(List1, 10);
    printf("Список без дублікатів:\n");
    printList(List1, size);

    int List2[10];
    for (int i = 0; i < 10; i++) {
        List2[i] = rand() % 10;
    }

    printf("Список (2):\n");
    printList(List2, 10);

    List2[0] = 10;
    List2[9] = rand() % 10;  // Додав випадкове значення замість копіювання попереднього

    return 0;
}
