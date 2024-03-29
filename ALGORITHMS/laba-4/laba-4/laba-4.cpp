﻿#include <iostream>
#include <Windows.h>

const int N = 15;
HANDLE hCon;
COORD cPos;

void set_position(int x, int y);

class binary_tree {
public:
    int key;
    binary_tree* left, *right, *root, *parent;

    binary_tree(int key, binary_tree* left, binary_tree* right, binary_tree* root, binary_tree* parent) {
        this->key = key;
        this->left = left;
        this->right = right;
        this->root = root;
        this->parent = parent;
    }
    binary_tree(int N) {
        left = right = root = parent = nullptr;
        key = -1;
        int p = 1007;
        int cur = 300;
        for (int i = 0; i < N; i++) {
            cur = (cur + (i + 1)) * (i + 1);
            cur %= p;
            add(cur);
        }
    }
    void add(int value) {
        if (root == nullptr) {
            root = new binary_tree(value, nullptr, nullptr, nullptr, nullptr);
            return;
        }
        binary_tree* tmp = root;
        for (;;) {
            if (value > tmp->key) {
                if (tmp->right == nullptr) {
                    tmp->right = new binary_tree(value, nullptr, nullptr, nullptr, tmp);
                    return;
                } 
                tmp = tmp->right;
            }
            else {
                if (tmp->left == nullptr) {
                    tmp->left = new binary_tree(value, nullptr, nullptr, nullptr, tmp);
                    return;
                }
                tmp = tmp->left;
            }
        }
    }
    int get_max() {
        binary_tree *tmp = root;
        while (tmp->right != nullptr) tmp = tmp->right;
        return tmp->key;
    }
    int get_min() {
        binary_tree* tmp = root;
        while (tmp->left != nullptr) tmp = tmp->left;
        return tmp->key;
    }
    // preorder
    void preorder(binary_tree* current) {
        std::cout << current->key << " ";
        if (current->left) preorder(current->left);
        if (current->right) preorder(current->right);
    }
    void preorder() { preorder(root); };
    // in order
    void inorder(binary_tree* current) {
        if (current->left) inorder(current->left);
        std::cout << current->key << " ";
        if (current->right) inorder(current->right);
    }
    void inorder() { inorder(root); };
    // post order
    void postorder(binary_tree* current) {
        if (current->left) postorder(current->left);
        if (current->right) postorder(current->right);
        std::cout << current->key << " ";
    }
    void postorder() { postorder(root); };
    // searh value
    bool search(int value) {
        binary_tree* tmp = root;
        while (tmp != nullptr) {
            if (tmp->key == value) break;
            if (tmp->key > value) tmp = tmp->left;
            else tmp = tmp->right;
        }
        return (tmp != nullptr);
    }
    // print_tree
    void print_tree(binary_tree* current, int x, int y, int step) {
        set_position(x, y);
        if (current == nullptr) {
            std::cout << "null";
            return;
        }
        std::cout << current->key;
        for (int i = 1; i < step; i++) {
            set_position(x - i, y + i);
            std::cout << "/";
        }
        for (int i = 1; i < step; i++) {
            set_position(x + i, y + i);
            std::cout << "\\";
        }
        print_tree(current->left, x - step, y + step, max((step + 1) / 2, 1));
        print_tree(current->right, x + step, y + step, max((step + 1) / 2,1));
    }
    void print_tree() { print_tree(root, 70, 1, 40); }

};

int main()
{
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleDisplayMode(hCon, CONSOLE_FULLSCREEN_MODE, 0);

    binary_tree a(N); // create a tree with N random numbers[0; 1006]
    
   
    while (1) {
        std::cout << "0. Exit\n"
            << "1.Print tree\n"
            << "2.Inorder\n"
            << "3.Preorder\n"
            << "4.Postorder\n"
            << "5.Contains value\n"
            << "6.Get maximum\n"
            << "7.Get minimum\n"
            << "8.Add value\n"
            << "Enter: ";
        int t;
        std::cin >> t;
        system("cls");
        if (!t) break;
        if (t == 1) a.print_tree();
        else if (t == 2) a.inorder();
        else if (t == 3) a.preorder();
        else if (t == 4) a.postorder();
        else if (t == 5) {
            std::cout << "\nEnter value to check its contains: ";
            int v;
            std::cin >> v;
            if (a.search(v)) std::cout << "\nThis number in the tree\n";
            else std::cout << "\nThis number NOT in the tree\n";
        }
        else if (t == 6) std::cout << "Maximum value is: " << a.get_max() << "\n";
        else if (t == 7) std::cout << "Minimum value is: " << a.get_min() << "\n";
        else if (t == 8) {
            std::cout << "Enter value to add: ";
            int v;
            std::cin >> v;
            if (!a.search(v)) a.add(v);
        }
        system("pause");
        system("cls");
    }
    return 0;

}

void set_position(int x, int y) {
    cPos.X = x;
    cPos.Y = y;
    SetConsoleCursorPosition(hCon, cPos);
}
