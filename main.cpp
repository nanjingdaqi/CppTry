#include <iostream>
#include <string.h>
#include <list>

using namespace std;

void quit(char *msg, int exit_code) {
    size_t len = strlen(msg);
    char suffix[] = ": %d";
    char *buffer = static_cast<char *>(malloc(len + strlen(suffix)));
    strcpy(buffer, msg);
    strcat(buffer, suffix);
    printf(buffer, errno);
    exit(exit_code);
}

struct Node {
    Node *p_l = 0;
    Node* p_r = 0;
    int val;
};

Node* build() {
    Node* n1 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n2 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n3 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n4 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n5 = static_cast<Node *>(malloc(sizeof(Node)));
    n1->val = 1;
    n2->val = 2;
    n3->val = 3;
    n4->val = 4;
    n5->val = 5;
    n1->p_l = n2;
    n1->p_r = n3;
    n2->p_l = n4;
    n2->p_r = n5;
    return n1;
}

void print(Node* p_root) {
    if (p_root) {
        print(p_root->p_l);
        printf("%d  ", p_root->val);
        print(p_root->p_r);
    }
}

void print2(Node* p_root) {
    list<Node*> n_l;
    while (p_root || !n_l.empty()) {
        while (p_root) {
            n_l.push_back(p_root);
            p_root = p_root->p_l;
        }
        Node* top = n_l.back();
        n_l.pop_back();
        printf("%d  ", top->val);
        p_root = top->p_r;
    }
}

int main() {
    Node* p_root = build();
    print2(p_root);
    return 0;
}