#include<iostream>
#include<algorithm>
using namespace std;

template <typename T>
class Queue
{
private:
    int front;
    int rear;
    int size;
    T *q;
public:
    Queue(int s){
        size = s;
        front = -1;
        rear = -1;
        q = new T[size];
    }

    bool isFull(){
        return rear == size - 1;
    }

    bool isEmpty(){
        return front == rear;
    }

    void enqueue(T val){
        if(isFull())
            return;
        q[++rear] = val;
    }

    T dequeue(){
        if(isEmpty())
            return nullptr;
        return q[++front];
    }
};


class Tree{
private:
    struct Node
    {
        int data;
        Node* right;
        Node* left;

        Node(int val): data(val), right(nullptr), left(nullptr) {}
    };
    Node* root;

    void preorder(Node* node){
        if(!node)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node){
        if(!node)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node* node){
        if(!node)   return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    Node* insert(Node* node, int num){
        if(!node){
            return new Node(num);
        }
        if(num < node->data)
            node->left = insert(node->left, num);
        else if(num > node->data)
            node->right = insert(node->right, num);
        return node;
    }

    int height(Node* node){
        if(!node)
            return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    Node* inPre(Node* node){
        node = node->left;
        while(node && node->right){
            node = node->right;
        }
        return node;
    }

    Node* inSuccessor(Node* node){
        node = node->right;
        while(node && node->left){
            node = node->left;
        }
        return node;
    }

    Node* Delete(Node* node, int key){
        if(!node)
            return nullptr;
        if(key < node->data)
            node->left = Delete(node->left, key);
        else if(key > node->data)
            node->right = Delete(node->right, key);
        else{
            if(!node->left && !node->right){
                delete node;
                return nullptr;
            }
            else if(!node->right){
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else if(!node->left){
                Node* temp = node->right;
                delete node;
                return temp;
            }
            Node* temp = inSuccessor(node);
            node->data = temp->data;
            node->right = Delete(node->right, temp->data);
        }
        return node;
    }
public:
    Tree(): root(nullptr) {}
    void create(){
        if(root)
            return;
        int x;
        Queue<Node*> q(20);
        cout << "Enter root value: ";
        cin >> x;
        root = new Node(x);
        q.enqueue(root);
        while (!q.isEmpty())
        {
            Node* p = q.dequeue();
            cout << "Enter left child value: ";
            cin >> x;
            if(x != -1){
                Node* t = new Node(x);
                t->data = x;
                t->left = t->right = nullptr;
                p->left = t;
                q.enqueue(t);
            }
            cout << "Enter right child value: ";
            cin >> x;
            if(x != -1){
                Node* t = new Node(x);
                t->data = x;
                t->left = t->right = nullptr;
                p->right = t;
                q.enqueue(t);
            }
            p = q.dequeue();
        }
    }

    void insert(int value){
        root = insert(root, value);
    }

    void preorder(){
        preorder(root);
        cout << endl;
    }

    void inorder(){
        inorder(root);
        cout << endl;
    }

    void postorder(){
        postorder(root);
        cout << endl;
    }

    void Delete(int key){
        root = Delete(root, key);
    }
};

int main(){

    Tree t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.preorder();
    t.Delete(3);
    t.preorder();
    t.Delete(1);
    t.inorder();

    return 0;
}