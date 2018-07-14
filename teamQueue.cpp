#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>

using namespace std;

typedef struct Node {
    Node *next;
    int value;
} Node;

/* global variables */
Node *head, *tail;
Node **teamTail;

void enqueue(int value, int team[]) {
    Node *n = (Node*) malloc(sizeof(Node));
    n->value = value;

    if(head == NULL) { // se a queue tiver vazia
        //cout << "head estava vazia, fazendo enqueue" << endl;
        //printf("head->next => %d\n", n->value);
        head = n;
        tail = n;
        teamTail[team[value]] = n;
        //head->prev = n;
        return;
        /* isso parece muito redundante. mas faz sentido */
    }

    if(tail == head) {
        head->next = n;
        tail = n;
        return;
    }

    if(teamTail[team[value]] == NULL) { //nao tem ninguem do time dele na queue, entra no ultimo lugar (tail)
        //cout << "teamtail estava vazia" << endl;
        //n->next = tail->next; // faco o n apontar para o tail->next (que eh o no cabeca)
        teamTail[team[value]] = n; // coloco como ultimo da tail do time dele
        //printf("   tail->next = %d\n", tail->next->value);
        tail->next = n;
        //printf("   tail->next->next = %d\n", tail->next->next->value);
        tail = n;
        //printf("   tail->next agora vale: %d\n", tail->next->value);

        //tail->next = n;
        return;
    }

    // agora acontece o caso de ja ter alguem do time dele na fila
    //n->next = teamTail[team[value]]->next; // o que o n vai apontar será o mesmo que o ultimo do time dele estava apontando antes
    //printf("   teamTail[team[value]]->next = %d\n", teamTail[team[value]]->next->value);
    n->next = teamTail[team[value]]->next;
    teamTail[team[value]]->next = n; // vou no ultimo da fila do time dele e faço esse apontar pro n
    teamTail[team[value]] = n; // ultimo da fila do time passa a ser o n
    //printf("   agora teamTail[team[value]]->next vale: %d\n", teamTail[team[value]]->next->value);
}

void dequeue() {
    if(head == NULL)
        return;

    cout << head->value << endl;
    head = head->next;

}

int main() {
    int scenario = 1;

    while(1) {
        head = (Node*) malloc(sizeof(Node));
        tail = (Node*) malloc(sizeof(Node));
        head = tail = NULL;
        int team[1000000];

        int numberOfTeams;
        cin >> numberOfTeams;

        if (!numberOfTeams) break;

        printf("Scenario #%d\n", scenario++);

        teamTail = (Node**) malloc(numberOfTeams*sizeof(Node*));
        for (int i = 0; i < numberOfTeams; i++) {
            teamTail[i]= (Node*) malloc(sizeof(Node));
            teamTail[i] = NULL;
            int teamplayers;
            cin >> teamplayers;
            for (int j = 0; j < teamplayers; j++) {
                int player;
                cin >> player;
                team[player] = i;
            }
        }

        string command;
        int value;

        cin >> command;
        while(command != "STOP") {
            if(command == "ENQUEUE") {
                cin >> value;
                enqueue(value, team);
            } else if (command == "DEQUEUE") {
                dequeue();
            }
            cin >> command;
        }
        cout << endl;
    }

    return 0;
}