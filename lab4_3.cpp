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

struct Node* root;

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

    if (r->data == data)
    {
        printf("Число %d уже есть в дереве. Добавление пропущено.\n", data);
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

int main()
{
    setlocale(LC_ALL, "");

    int D;
    int start = 1;
    root = NULL;

    printf("-1 - окончание построения дерева\n");
    printf("Одинаковые числа добавляться не будут.\n\n");

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

    return 0;
}