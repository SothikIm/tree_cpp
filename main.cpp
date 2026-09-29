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

    ~Queue(){
        delete[] q;
    }
};

template <typename T>
class Stack{
private:
    int top;
    int size;
    T *s;
public:
    Stack(int sSize){
        size = sSize;
        s = new T[size];
        top = -1;
    }

    bool isFull(){
        return top == size - 1;
    }

    bool isEmpty(){
        return top == -1;
    }

    void push(T x){
        if(!isFull())
            s[++top] = x;
    }

    T pop(){
        return s[top--];
    }

    T peek(){
        return s[top];
    }

    ~Stack(){
        delete[] s;
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

    int countNode(Node* node){
        int x, y;
        if(node){
            x = countNode(node->left);
            y = countNode(node->right);
            return x + y + 1;
        }
        return 0;
    }

    int countHeight(Node* node){
        int x, y;
        if(node){
            x = countHeight(node->left);
            y = countHeight(node->right);
            if(x > y)
                return x + 1;
            return y + 1;
        }
        return 0;
    }

    int countLeafNode(Node* node){
        if(!node) return 0;
        if(!node->left && !node->right) return 1;
        return countLeafNode(node->left) + countLeafNode(node->right);
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
            cout << "Enter left child value of " << p->data << ": ";
            cin >> x;
            if(x != -1){
                Node* t = new Node(x);
                t->data = x;
                t->left = t->right = nullptr;
                p->left = t;
                q.enqueue(t);
            }
            cout << "Enter right child value " << p->data << ": ";
            cin >> x;
            if(x != -1){
                Node* t = new Node(x);
                t->data = x;
                t->left = t->right = nullptr;
                p->right = t;
                q.enqueue(t);
            }
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

    void Ipreoder(){
        Stack<Node*> s(20);
        Node* p = root;
        s.push(p);
        while(!s.isEmpty()){
            if(p){
                cout << p->data << " ";
                s.push(p);
                p = p->left;
            }
            else{
                p = s.pop();
                p = p->right;
            }
        }
    }

    void Iinorder(){
        Stack<Node*> s(20);
        Node* p = root;
        s.push(p);
        while(!s.isEmpty()){
            if(p){
                s.push(p);
                p = p->left;
            }
            else{
                p = s.pop();
                cout << p->data << " ";
                p = p->right;
            }
        }
    }

    void Ipostorder(){
        Stack<Node*> s1(20);
        Stack<Node*> s2(20);
        s1.push(root);
        while (!s1.isEmpty())
        {
            Node* current = s1.pop();
            s2.push(current);

            if(current->left) 
                s1.push(current->left);
            if(current->right) 
                s1.push(current->right);
        }
        while (!s2.isEmpty())
        {
            cout << s2.pop()->data << " ";
        }
        cout << endl;
    }

    void levelorder(){
        if(!root)
            return;
        Queue<Node*> q(20);
        q.enqueue(root);
        while(!q.isEmpty()){
            Node* p = q.dequeue();
            cout << p->data << " ";
            if(p->left)
                q.enqueue(p->left);
            if(p->right)
                q.enqueue(p->right);
        }
        cout << endl;
    }

    int countNode(){
        return countNode(root);
    }

    int countHeight(){
        return countHeight(root);
    }

    int countLeafNode(){
        return countLeafNode(root);
    }
};

int main(){

    Tree t;
    t.create();
    t.levelorder();
    cout << t.countLeafNode() << endl; 

    return 0;
}