#include <iostream>
#include <string>
#include <bitset>
#include <cstdio>
#include <cstdlib>

using namespace std;

// definindo variaveis globais
int ip_array[32];

// usando a nossa struct de nó
typedef struct Node {
    Node *left, *right;
    string domain;
} Node;

class Tree {
    public:
        Node *root;

        Tree() {
            root = new Node;
        }

        ~Tree() {
            delete root;
        }

        void insert(string domain, int range) {
            // ando pela arvore ate chegar no bit que definirá o dominio das arvores abaixo dele
            Node *pt = root;
            for(int i = 0; i < range; i++) {
                if(ip_array[i] == 0) {
                    if(!pt->left)
                        pt->left = new Node;
                    pt= pt->left;
                } else {
                    if(!pt->right)
                        pt->right = new Node;
                    pt= pt->right;
                }
            }

            // agora estou no nó do range, a partir daqui todos resolvem para o dominio "domain"
            pt->domain = domain;
        }

        string find_domain() {
            Node *pt = root;
            string domain;
            // como sao 32 bits, preciso de no maximo 32 iterações
            for(int i = 0; i < 32; i++) {
                // se encontro um nó nulo, significa que esse nó não foi criado.
                // consequentemente, o dominio só pode ter sido definido acima dele
                // posso parar sem me preocupar
                if(pt == NULL) break;

                // se encontro um dominio que nao seja vazio, atualizo o dominio mais proximo do nosso nó
                if(pt->domain != "") {
                    domain = pt->domain;
                }

                // se o array for 0, vou para a esquerda
                if(ip_array[i] == 0) {
                    pt = pt->left;
                } else {
                    // se for 1 (ou diferente de 0) vou para a direita
                    pt = pt->right;
                }
            }
            // retorno o que define nosso nó
            return domain;
        }
};


void binary_ip(int *ip) {
    // convertendo os 32 bits 
    int pos = 32;
    // passo 4 vezes (uma para cada parte do endereço após a separação no .)
    for(int i = 3; i >= 0; i--) {
        // transforma ip[i] em um bitset com 8 posicoes e depois passa esse bitset pra ip_array
        int x[8];
        int _ = ip[i];
        for(int j = 0; j < 8; j++,_/=2) {
            ip_array[--pos] = _%2;
        }
    }
}

int main() {
    // inicializo a arvore que será utilizada
    Tree tree = Tree();

    // lendo quantidade de ips que ele vai entrar
    int n;
    cin >> n;

    // faço loop lendo a quantidade de ips que ele passa
    for(int i = 0; i < n; i++) {
        // ip[4] é um array com tamanho 4 que receberá as quatro partes do IP (cada uma com 8 bits)
        // range é o inteiro que definirá até qual bit a nossa máscara irá ter 1 (Ex: /16 -> 11111111111111110000000000000000)
        // para calcular até onde o ip definirá o domínio, é feito [IP & range]
        // domain é a string que terá o nome do nosso domínio
        // ip__str é a string de ips que é lida na primeira parte da leitura (192.168.0.0/24 por exemplo)
        int ip[4], range;
        string domain;
        string ip_str;


        cin >> ip_str;
        // Pega somente o que importa do input usando sscanf
        sscanf(ip_str.c_str(),"%d.%d.%d.%d/%d ",&ip[0],&ip[1],&ip[2],&ip[3],&range);

        // transforma o IP em um array equivalente de 32 bits
        binary_ip(ip);

        // Pegando o dominio do ip acima
        getline(cin, domain);

        // agora que ja tenho o IP num array de 32 bits, preciso adicionar esse endereço a arvore
        tree.insert(domain, range);

    }

    string ip_str;
    while(cin >> ip_str) {
        // agora vou para a parte de checagem -> ver a qual dominio o ip inserido está associado
        int ip[4];

        // Pega somente o que importa do input usando sscanf
        sscanf(ip_str.c_str(),"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);

        // transforma o IP em um array equivalente de 32 bits
        binary_ip(ip);

        cout << ip_str << tree.find_domain() << endl;
    }

    return 0;
}