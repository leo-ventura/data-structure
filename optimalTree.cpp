#include <iostream>

#define MAX_INT 2147483647

using namespace std;

class Square {
    public:
        int key, cost, frequency;

    Square() {
        key = cost = frequency = -1;
    }

    ~Square() {}
};

// definindo variaveis globais
Square **matrix;

void printTree(int i, int j) {
    if(matrix[i][j].frequency == 0 || matrix[i][j].cost == 0)
        return;

    cout << matrix[i][j].key << " ";
    printTree(i, matrix[i][j].key-1);
    printTree(matrix[i][j].key,j);
}

int main() {

    int n;
    cin >> n;   // n => quantidade de chaves

    matrix = new Square *[n+1];
    int keys[n+1], frequencies[n+1], bfrequencies[n+1];

    // inicializando os Squares
    for(int i = 0; i <= n; i++) {
        matrix[i] = new Square[n+1];
        for(int j = i; j <= n; j++)
            matrix[i][j] = Square();
    }

    // lendo key
    for(int i = 0; i < n; i++)
        cin >> keys[i];     // nao é nunca usada, nao sei pq precisa ainda (provavelmente só preciso na hora do output)

    // lendo frequency
    frequencies[0] = 0;
    for(int i = 1; i <= n; i++)
        cin >> frequencies[i];

    // lendo frequency'
    for(int i = 0; i <= n; i++)
        cin >> bfrequencies[i];

    // montando diagonal principal
    for(int i = 0; i <= n; i++) {
        matrix[i][i].key       = i;
        matrix[i][i].frequency = bfrequencies[i];
        matrix[i][i].cost      = 0;
    }

    // agora tenho a diagonal principal montada, preciso completar as linhas com as frequencias
    for(int i = 0; i <= n; i++) {
        for(int j = i+1; j <= n; j++)
            matrix[i][j].frequency = matrix[i][j-1].frequency + frequencies[j] + bfrequencies[j]; //matrix[i+1][j].frequency + matrix[i+1][j].bfrequency;
    }

    // montando a primeira diagonal (ao lado da principal)
    for(int i = 0; i < n; i++) {
        matrix[i][i+1].key = i+1;
        matrix[i][i+1].cost = matrix[i][i+1].frequency;
    }

    // agora começo a entrar no padrao para concluir as outras diagonais
    int i = 0;
    for(int a = 2; i <= n-a || (!(i = 0) && a++< n); i++) { // usando bruxaria pra evitar fazer outro for
        // aproveito o fato da condição após o || só ser executada caso a primeira seja falsa
        // para colocar i = 0 e incrementar a variável a checando condição de ser menor que n
        int j = i+a;
        int menor = MAX_INT;
        for(int k = i+1; k <= j; k++) {
            int cost = matrix[i][k-1].cost + matrix[k][j].cost + matrix[i][j].frequency;
            if(cost < menor) {
                matrix[i][j].cost = menor = cost;
                matrix[i][j].key  = k;
            }
        }
    }

    cout << "Custo: " << matrix[0][n].cost << endl;

    cout << "Pre-Ordem: ";
    printTree(0,n);

    return 0;
}