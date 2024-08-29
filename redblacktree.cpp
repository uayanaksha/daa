#include <ios>
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

template <typename T>
class Node {
public:
    T data;
    bool color;
    Node<T> *left, *right, *parent;

    Node(T data) : data(data) {
        parent = left = right = nullptr;
        color = RED;
    }
};

template <typename T>
class RedBlackTree {
private:
    Node<T> *root;

protected:
    void bstInsert(Node<T>*&, Node<T>*&);
    void rotateLeft(Node<T> *&, Node<T> *&);
    void rotateRight(Node<T> *&, Node<T> *&);
    void fixInsert(Node<T> *&, Node<T> *&);
    void fixDelete(Node<T> *&, Node<T> *&);
    void transplant(Node<T> *&, Node<T> *, Node<T> *);
    Node<T> *minValueNode(Node<T> *&);
    void deleteNodeHelper(Node<T> *&, T);
    void inorderHelper(Node<T> *node) const;

public:
    RedBlackTree() { root = nullptr; }
    void insert(const T &n);
    void deleteNode(const T &data);
    bool search(const T &data) const;
    void inorder() const;
};

template <typename T>
void RedBlackTree<T>::rotateLeft(Node<T> *&root, Node<T> *&pt) {
    Node<T> *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

template <typename T>
void RedBlackTree<T>::rotateRight(Node<T> *&root, Node<T> *&pt) {
    Node<T> *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

template <typename T>
void RedBlackTree<T>::fixInsert(Node<T> *&root, Node<T> *&pt) {
    Node<T> *parent_pt = nullptr;
    Node<T> *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) &&
           (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {

            Node<T> *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }

            else {
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        else {
            Node<T> *uncle_pt = grand_parent_pt->left;

            if (uncle_pt != nullptr && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::fixDelete(Node<T> *&root, Node<T> *&x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node<T> *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            Node<T> *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::transplant(Node<T> *&root, Node<T> *u, Node<T> *v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

template <typename T>
Node<T> *RedBlackTree<T>::minValueNode(Node<T> *&node) {
    Node<T> *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

template <typename T>
void RedBlackTree<T>::deleteNodeHelper(Node<T> *&root, T key) {
    Node<T> *z = root;
    Node<T> *x, *y;

    while (z != nullptr) {
        if (z->data == key)
            break;
        else if (z->data <= key)
            z = z->right;
        else
            z = z->left;
    }

    if (z == nullptr)
        return;

    y = z;
    bool y_original_color = y->color;
    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK)
        fixDelete(root, x);
}

template <typename T>
void RedBlackTree<T>::bstInsert(Node<T>*& root, Node<T>*& node) {
    if (root == nullptr) {
        root = node;
    } else if (node->data < root->data) {
        bstInsert(root->left, node);
        root->left->parent = root;
    } else if (node->data > root->data) {
        bstInsert(root->right, node);
        root->right->parent = root;
    }
}

template <typename T>
void RedBlackTree<T>::insert(const T &data) {
    Node<T> *pt = new Node<T>(data);

    bstInsert(root, pt);
    fixInsert(root, pt);
}

template <typename T>
void RedBlackTree<T>::deleteNode(const T &data) {
    deleteNodeHelper(root, data);
}

template <typename T>
bool RedBlackTree<T>::search(const T &data) const {
    Node<T> *current = root;
    while (current != nullptr) {
        if (data == current->data)
            return true;
        else if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

template <typename T>
void RedBlackTree<T>::inorder() const {
    inorderHelper(root);
    cout << endl;
}

template <typename T>
void RedBlackTree<T>::inorderHelper(Node<T> *node) const {
    if (node == nullptr)
        return;

    inorderHelper(node->left);
    cout << node->data << " ";
    inorderHelper(node->right);
}

int menu(){
    unsigned choice;
    cout 
        << "Red Black Tree Operations --- " << endl 
        << "1. Insert" << endl 
        << "2. Delete" << endl 
        << "3. Search" << endl 
        << "4. Inorder Traversal" << endl 
        << "5. Exit" << endl;
    cout << "Enter choice [1~5]: ";
    cin >> choice;
    return choice;
}

int main() {
    RedBlackTree<int> rbt;
    int choice;
    int input;
    bool state = true;
    do {
        choice = menu();
        switch (choice) {
            case 1: {
                        cout << "Enter input element: " && cin >> input;
                        rbt.insert(input);
                        break;
                    }
            case 2: {
                        cout << "Enter deletion element: " && cin >> input;
                        rbt.deleteNode(input);
                        break;
                    }
            case 3: {
                        cout << "Enter element to search: " && cin >> input;
                        cout 
                            << boolalpha
                            << input
                            << " present in rbt : "
                            << rbt.search(input)
                            << endl;
                        break;
                    }
            case 4: {
                        cout << "Inorder Traversal of Created Tree: ";
                        rbt.inorder();
                        break;
                    }
            case 5: 
                    {
                        state = false;
                        cout << "[PROGRAM EXITED]" << endl;
                    }
        }
    } while ( state );
    return 0;
}
