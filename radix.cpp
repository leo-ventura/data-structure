#include <iostream>
#include <string>

//#define BASE 16

using namespace std;

class Queue {
    public:
        typedef struct Node {
            Node *next;
            int value;
        } Node;

        Node *head, *tail;

        void enqueue(int value);
        int dequeue();

    Queue() {
        head = new Node;
        tail = new Node;
        head = tail = NULL;
    }
    ~Queue() {
        delete head;
        delete tail;
    }
};

void Queue::enqueue(int value) {
    //Node *n = (Node*) malloc(sizeof(Node));
    Node *n  = new Node;
    n->value = value;

    if(head == NULL) { // se a queue tiver vazia
        head = tail = n;
        return;
    }

    if(tail == head) {
        head->next = n;
        tail       = n;
        return;
    }

    tail->next = n;
    tail       = n;
}

int Queue::dequeue() {
    if(head == NULL)
        return -1;

    int r = head->value;
    head = head->next;

    if(head == NULL) {
        tail = NULL;
    }

    return r;
}

int main() {
    Queue queue[16];
    for(int i = 0; i < 16; i++)
        queue[i] = Queue();

    int n, maior = 0;
    while(cin >> n) {
        if(n > maior)
            maior = n;
        queue[n%16].enqueue(n); 
    }

    Queue bucket[16];
    for(int i = 0; i < 16; i++)
        bucket[i] = Queue();

    for(int j = 0; maior; maior /= 16, j++) {
        int current;
        for(int i = 0; i < 16; i++) {
            while((current = queue[i].dequeue()) != -1) {
                // cout << " com current igual a (" << current << ") temos (current >> (" << j << "*4))&15 = " << ((current >> (j*4))&15) << endl;
                bucket[(current >> (j*4))&15].enqueue(current);
            }
        }
        for(int i = 0; i < 16; i++) {
            while((current = bucket[i].dequeue()) != -1) {
                //cout << "enqueueuing " << current << " to (" << i << ")" << endl;
                queue[i].enqueue(current);
            }
        }
    }

    for(int i = 0; i < 16; i++) {
        int c;
        while((c = queue[i].dequeue()) != -1) {
            cout << c << endl;
        }
    }

    return 0;
}