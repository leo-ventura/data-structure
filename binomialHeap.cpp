/* Binomial Heap implementation in C++
*  Leonardo Ventura
*  UFRJ - 2018
*/

#include <iostream>

#define SIZE 500

using namespace std;

typedef struct _Node {
    int key, degree;
    _Node *parent, *sibling, *children;
} Node;

class Heap {
    public:
        // vetor de Nodes , layer 1 -> os vetores as ordens, layer 2 -> heap em si
        // vector<Node*> heap;
        Node *heap[SIZE];
        int last = 0;

        Heap()  {}
        ~Heap() {}

        void insert(int key) {
            // vou na ultima posicao da heap para inserir a chave nova criando uma "arvore" binomial de ordem 0
            Node* t      = new Node;
            t->key       = key;
            t->degree    = 0;
            t->children  = t->parent = t->sibling = NULL;
            heap[last++] = t;
            checkOrder();
        }

        void checkOrder() {
            // faço loop enquanto houverem heaps existentes [NAO ESQUECER DE DELETAR ULTIMA POSICAO DA HEAP DEPOIS DE UNIR]
            // como estao em ordem (ordem de heap[0] >= ordem de heap[1] >= ordem de heap[2]) só preciso de um loop
            // cout << "[heap size: " << heap.size() << "]" << endl;
            // for(int i = 1; i < heap.size(); i++) {
            for(int i = 0; heap[i] != NULL; i++) {
                for(int j = i+1; heap[j] != NULL; j++) {
                    if(heap[i]->degree == heap[j]->degree) {
                        join(i, j);
                        checkOrder();
                    }
                }
            }
        }

        void join(int i, int j) {
            if(heap[j]->key < heap[i]->key) {
                // se a raiz da heap[j] for menor que a heap[i], heap[j] vai ser a raiz da uniao
                heap[i]->parent = heap[j];
                heap[j]->degree++;
                if(heap[j]->children == NULL) {
                    // se o filho da heap[j] for NULL (ou seja, nao tinha filho anterior), coloco heap[i] como primeiro filho
                    heap[j]->children = heap[i];
                } else {
                    // vou procurando até achar o que nao possui irmao
                    Node *_sibling = heap[j]->children;
                    while(_sibling->sibling != NULL) {
                        _sibling = _sibling->sibling;
                    }
                    _sibling->sibling = heap[i];
                }
                reorder(i);
            } else {
                // se a raiz de heap[i] for menor ou igual a heap[j], heap[i] vai ser a raiz da uniao
                heap[j]->parent = heap[i];
                heap[i]->degree++;
                // agora devo fazer os mesmos checks que fiz acima
                if(heap[i]->children == NULL) {
                    // se o filho da heap[i] for NULL (ou seja, nao tinha filho anterior), coloco heap[j] como primeiro filho
                    heap[i]->children = heap[j];
                } else {
                    // vou procurando até achar o que nao possui irmao
                    Node *_sibling = heap[i]->children;
                    while(_sibling->sibling != NULL) {
                        _sibling = _sibling->sibling;
                    }
                    _sibling->sibling = heap[j];
                }
                reorder(j);
            }
            last--;
        }

        void reorder(int begin) {
            for(; heap[begin] != NULL; begin++) {
                heap[begin] = heap[begin+1];
            }
        }

        int getMinimum() {
            if(heap[0] == NULL) return -1;
            int min = heap[0]->key;
            for(int i = 1; heap[i] != NULL; i++) {
                if(heap[i]->key < min) {
                    min = heap[i]->key;
                }
            }
            return min;
        }

        void removeMinimum() {
            // primeiro preciso checar se há o que remover
            if(heap[0] == NULL) return;
            // last--;
            if(heap[1] == NULL && heap[0]->children == NULL) {
                for(int i = 0; i < SIZE; i++)
                    heap[i] = NULL;
                return;
            }

            // preciso achar qual o menor filho
            // para fazer isso, pego o primeiro filho e depois vou visitando os irmaos
            int minIndex = 0;
            for(int i = 0; heap[i] != NULL; i++) {
                if(heap[i]->key < heap[minIndex]->key) {
                    minIndex = i;
                }
            }

            Node* _s = heap[minIndex]->children;
            Node* next_sibling;
            while(_s->sibling != NULL) {
                next_sibling = _s->sibling;
                _s->sibling  = NULL;
                heap[last++] = _s;
                _s = next_sibling;
            }
            heap[minIndex] = _s;
            checkOrder();
        }
};

int main() {
    Heap h = Heap();

    char command;
    while(cin >> command) {
        switch(command) {
            case 'i':
                int element;
                cin >> element;
                h.insert(element);
                break;
            case 'a':
                cout << h.getMinimum() << endl;
                break;
            case 'r':
                h.removeMinimum();
                break;
        }
    }

    return 0;
}