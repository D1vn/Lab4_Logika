#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        root = (struct Node*)malloc(sizeof(struct Node));
        if (root == NULL) {
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

void print_tree(struct Node* r, int l) {
    if (r == NULL) return;

    print_tree(r->right, l + 1);

    for (int i = 0; i < l; i++)
        printf("    ");

    printf("%d\n", r->data);

    print_tree(r->left, l + 1);
}

struct Node* Search(struct Node* r, int data) {
    if (r == NULL) return NULL;
    if (r->data == data) return r;

    if (data < r->data)
        return Search(r->left, data);
    else
        return Search(r->right, data);
}

int main() {
    setlocale(LC_ALL, "");

    int D;
    int start = 1;

    root = NULL;

    printf("-1 - окончание построения дерева\n");

    while (start) {
        printf("Введите число: ");
        scanf_s("%d", &D);

        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D);
        }
    }

    printf("Дерево:\n");
    print_tree(root, 0);

    printf("\nВведите число для поиска: ");
    scanf_s("%d", &D);

    if (Search(root, D) != NULL)
        printf("Элемент %d найден в дереве.\n", D);
    else
        printf("Элемент %d не найден в дереве.\n", D);

    return 0;
}