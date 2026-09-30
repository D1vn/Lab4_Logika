#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        r->data = data;
        r->left = NULL;
        r->right = NULL;
        return r;
    }

    if (data > r->data)
        r->left = CreateTree(r->left, data);
    else
        r->right = CreateTree(r->right, data);

    return r;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL) return;

    print_tree(r->right, l + 1);

    for (int i = 0; i < l; i++)
        printf("    ");

    printf("%d\n", r->data);

    print_tree(r->left, l + 1);
}

struct Node* Search(struct Node* r, int data, int* steps)
{
    if (r == NULL)
        return NULL;

    (*steps)++;

    if (r->data == data)
        return r;

    if (data > r->data)
        return Search(r->left, data, steps);
    else
        return Search(r->right, data, steps);
}

int main()
{
    setlocale(LC_ALL, "");

    int D;
    int start = 1;
    root = NULL;

    printf("-1 - окончание построения дерева\n");

    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);

        if (D == -1)
        {
            printf("\nПостроение дерева окончено.\n\n");
            start = 0;
        }
        else
        {
            root = CreateTree(root, D);
        }
    }

    printf("Полученное дерево:\n");
    print_tree(root, 0);

    printf("\nВведите число для поиска: ");
    scanf_s("%d", &D);

    int steps = 0;
    struct Node* result = Search(root, D, &steps);

    if (result != NULL)
        printf("Элемент %d найден.\n", D);
    else
        printf("Элемент %d не найден.\n", D);

    printf("Количество проверенных узлов: %d\n", steps);

    printf("\nОценка сложности поиска:\n");
    printf("В среднем случае: O(log n)\n");
    printf("В худшем случае: O(n)\n");

    return 0;
}