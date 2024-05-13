#include <iostream>
#include <fstream>

using namespace std;

struct tree {// Структура узла с потомками left и right и ключом val
    int val;
    tree* left;
    tree* right;
};

tree* createnode(int a) {//Создание узла
    tree* T = new tree;
    T->val = a;
    T->left = T->right = NULL;
    return T;
}

void push(tree*& root, tree* node) {//Вставка узла в дерево
    if (root)
    {
        if (node->val <= root->val)//Если значение ребенка <= значения родителя, он располагается слева
            push(root->left, node);
        else
            push(root->right, node);//Если значение ребенка > значения родителя, он располагается справа
    }
    else
        root = node;//Если дерево пустое то создать корень

}

void loadtree(ifstream& input, tree*& root)//Создание всего дерева со значениями из файла
{
    int a;

    while (!input.eof())
    {
        input >> a;
        push(root, createnode(a));

    }

}

void erasetree(tree*& root) {//Удаление дерева и освобождение памяти
    if (root)
    {
        erasetree(root->left);//Рекурсивное удаление левых узлов
        erasetree(root->right);//Рекурсивное удаление правых узлов
        delete root;
        root = NULL;
    }
}

void printTree(ofstream& fout, tree* root)//Вывод дерева симметричным обходом
{
    if (root)
    {
        printTree(fout, root->left);//Сначала левый потомок
        fout << root->val << " ";//Потом родитель
        printTree(fout, root->right);//Потом правый потомок
    }
}
tree* invertTree(tree* root) {//Отражение дерева

    if (root == NULL) {//Если ничего нет то нечего возвращать
        return NULL;
    }

    tree* left = invertTree(root->left);//Рекурсивно отразить слева
    tree* right = invertTree(root->right);//Рекурсивно отразить справа

    root->left = right;//Поменять корни
    root->right = left;//местами
    return root;
}

int main()
{
    ifstream input("input.txt");//Открытие файла ввода
    ofstream output("output.txt");//Открытие файла вывода

    tree* root = NULL;//Создание корня

    loadtree(input, root);//Загрузка дерева из файла ввода 
    invertTree(root);//Отражение дерева
    printTree(output, root);//Вывод дерева в файл вывода
    erasetree(root);//Освобождение памяти
    input.close();//Закрытие файла ввода
    output.close();//Закрытие файла вывода
    return 0;
}


