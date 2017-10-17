#include <iostream>
#include <string.h>

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
    Node *p_next;
    int val;
};

Node *reverse(Node *p_l) {
    Node* p_next = NULL;
    Node* p_head = p_l;
    while (p_l->p_next) {
        p_next = p_l->p_next;
        p_l->p_next = p_next->p_next;
        p_next->p_next = p_head;
        p_head = p_next;
    }
    return p_head;
}

Node *reverse2(Node *p_l) {
    Node *p_new = NULL;
    Node *current = p_l;
    Node *p_next;
    while (current) {
        p_next = current->p_next;
        current->p_next = p_new;
        p_new = current;
        current = p_next;
    }
    return p_new;
}

Node* build() {
    Node* n1 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n2 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n3 = static_cast<Node *>(malloc(sizeof(Node)));
    Node* n4 = static_cast<Node *>(malloc(sizeof(Node)));
    n1->val = 1;
    n2->val = 2;
    n3->val = 3;
    n4->val = 4;
    n1->p_next = n2;
    n2->p_next = n3;
    n3->p_next = n4;
    return n1;
}

void print(Node* p_l) {
    while (p_l) {
        printf("%d  ", p_l->val);
        p_l = p_l->p_next;
    }
    printf("\n");
}

int main() {
    Node* p_l = build();
    print(p_l);
    print(reverse(p_l));
//    print(reverse2(p_l));
    return 0;
}