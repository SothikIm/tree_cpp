#include<iostream>
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
};

int main(){

    Tree t;
    t.create();
    t.preorder();

    return 0;
}