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

    int isBalance(Node* node){
        int hl, hr;
        hl = node && node->left ? countHeight(node->left) : 0;
        hr = node && node->right ? countHeight(node->right) : 0;
        return hl - hr;
    }

    Node* LLRotation(Node* node){
        Node* p = node->left;
        Node* t = p->right;
        
        p->right = node;
        node->left = t;
        if(root == node) root = p;
        return p;
    }

    Node* RRRotation(Node* node){
        Node* p = node->right;
        Node* t = p->left;
        p->left = node;
        node->right = t;
        if(root == node) root = p;
        return p;
    }

    Node* RLRotation(Node* node){
        Node* p = node->right;
        Node* t = p->left;
        p->left = t->right;
        node->right = t->left;

        t->left = node;
        t->right = p;
        if(root == node) root = t;
        return t;
    }

    Node* LRRotation(Node* node){
        Node* p = node->left;
        Node* t = p->right;
        p->right = t->left;
        node->left = t->right;

        t->left = p;
        t->right = node;
        if(root == node) root = t;
        return t;
    }

    Node* RInsert(Node* node, int key){
        if(!node){
            return new Node(key);
        }
        if(key < node->data)
            node->right = RInsert(node->right, key);
        else if(key > node->data)
            node->left = RInsert(node->left, key);
        
        if(isBalance(node) > 2 && key < node->left->data){
            return LLRotation(node);
        }
        else if(isBalance(node) > 2 && key > node->left->data)
            return LRRotation(node);
        else if(isBalance(node) > -2 && key > node->right->data)
            return RRRotation(node);
        else if(isBalance(node) > -2 && key < node->right->data)
            return RLRotation(node);

        return node;
    }

    Node* RDelete(Node* node,int key){
        if(!node) return nullptr;
        if(key < node->data)
            node->left = RDelete(node->left, key);
        else if(key > node->data)
            node->right = RDelete(node->right, key);
        else{
            if(!node->right && !node->left){
                delete node;
                return nullptr;
            }
            else if(!node->left){
                Node* t = node->right;
                delete node;
                return t;
            }
            else if(!node->right){
                Node* t = node->left;
                delete node;
                return t;
            }
            Node* t = inSuccessor(node);
            node->data = t->data;
            node->right = RDelete(node->right, t->data);
        }

        int balance = isBalance(node);
        if(balance > 1 && isBalance(node->left) > 0)
            return LLRotation(node);
        else if(balance < -1 && key > isBalance(node->right) < 0)
            return RRRotation(node);
        else if(balance > 1 && isBalance(node->left) < 0){
            return LRRotation(node);
        }
        else if(balance < -1 && isBalance(node->right) > 0)
            return RLRotation(node);
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