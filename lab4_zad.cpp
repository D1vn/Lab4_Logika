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

struct Node* CreateTree(struct Node* root, int data)
{
    if (root == NULL)
    {
        root = (struct Node*)malloc(sizeof(struct Node));

        if (root == NULL)
        {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }

        root->data = data;
        root->left = NULL;
        root->right = NULL;

        return root;
    }

    if (data < root->data)
        root->left = CreateTree(root->left, data);
    else
        root->right = CreateTree(root->right, data);

    return root;
}

void print_tree(struct Node* r, int level)
{
    if (r == NULL)
        return;

    print_tree(r->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d (уровень %d)\n", r->data, level);

    print_tree(r->left, level + 1);
}

void Search(struct Node* r, int data, int level, int* found)
{
    if (r == NULL)
        return;

    if (r->data == data)
    {
        printf("Элемент %d найден на уровне %d.\n", data, level);
        *found = 1;
    }

    Search(r->left, data, level + 1, found);
    Search(r->right, data, level + 1, found);
}

void RemoveDuplicates(struct Node* r, struct Node* current)
{
    if (r == NULL)
        return;

    RemoveDuplicates(r->left, current);
    RemoveDuplicates(r->right, current);
}

int IsDuplicate(struct Node* root, int data)
{
    if (root == NULL)
        return 0;

    if (root->data == data)
        return 1;

    if (data < root->data)
        return IsDuplicate(root->left, data);
    else
        return IsDuplicate(root->right, data);
}

struct Node* DeleteNode(struct Node* root, int data)
{
    if (root == NULL)
        return NULL;

    if (data < root->data)
    {
        root->left = DeleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = DeleteNode(root->right, data);
    }
    else
    {
        if (root->left == NULL)
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL)
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }


        struct Node* temp = root->right;

        while (temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;

        root->right = DeleteNode(root->right, temp->data);
    }

    return root;
}


void RemoveAllDuplicates(struct Node* r)
{
    if (r == NULL)
        return;

    RemoveAllDuplicates(r->left);
    RemoveAllDuplicates(r->right);


    while (r->right != NULL && r->right->data == r->data)
    {
        struct Node* duplicate = r->right;

        r->right = duplicate->right;

        free(duplicate);
    }
}
void FreeTree(struct Node* r)
{
    if (r == NULL)
        return;

    FreeTree(r->left);
    FreeTree(r->right);

    free(r);
}

int main()
{
    setlocale(LC_ALL, "");

    int D;
    int start = 1;

    root = NULL;

    printf("-1 - окончание построения дерева\n\n");

    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);

        if (D == -1)
        {
            printf("ние дерева окончено.\n\n");
            start = 0;
        }
        else
        {
            root = CreateTree(root, D);
        }
    }


    printf("Исходное дерево:\n\n");
    print_tree(root, 0);

    printf("\nВведите число для поиска: ");
    scanf_s("%d", &D);

    int found = 0;

    Search(root, D, 0, &found);

    if (!found)
        printf("Элемент %d не найден в дереве.\n", D);

    printf("\nУдаление дубликатов...\n");

    RemoveAllDuplicates(root);

    printf("\nДерево после удаления дубликатов:\n\n");
    print_tree(root, 0);
    FreeTree(root);

    return 0;
}