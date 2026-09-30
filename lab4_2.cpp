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

    if (data > r->data)
        r->left = CreateTree(r->left, data);
    else
        r->right = CreateTree(r->right, data);

    return r;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
        return;

    print_tree(r->right, l + 1);

    for (int i = 0; i < l; i++)
        printf("    ");

    printf("%d\n", r->data);

    print_tree(r->left, l + 1);
}

int Count(struct Node* r, int data)
{
    if (r == NULL)
        return 0;

    int count = (r->data == data) ? 1 : 0;

    return count + Count(r->left, data) + Count(r->right, data);
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
        if (scanf_s("%d", &D) != 1)
        {
            printf("Некорректный ввод, попробуйте снова.\n");
            while (getchar() != '\n');
            continue;
        }

        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else
        {
            root = CreateTree(root, D);
        }
    }

    printf("Дерево:\n");
    print_tree(root, 0);

    printf("\nВведите число для подсчёта: ");
    scanf_s("%d", &D);

    printf("Количество вхождений элемента %d: %d\n", D, Count(root, D));

    return 0;
}