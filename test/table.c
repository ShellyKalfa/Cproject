#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

unsigned int hash(char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}


Node* create_node(char* key, char* value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;
    return new_node;
}


void insert(HashTable* hashtable, char* key, char* value) {
    Node* temp ;
    unsigned int hash_key = hash(key);
    Node* new_node = create_node(key, value);
    if (hashtable->table[hash_key] == NULL) {
        hashtable->table[hash_key] = new_node;
    } else {
       temp = hashtable->table[hash_key];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

char* search(HashTable* hashtable, char* key) {
    unsigned int hash_key = hash(key);
    Node* temp = hashtable->table[hash_key];
        while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}


void delete(HashTable* hashtable, char* key) {
    unsigned int hash_key = hash(key);
    Node* temp = hashtable->table[hash_key];
    Node* prev = NULL;
    while (temp != NULL && strcmp(temp->key, key) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;  
    }
    if (prev == NULL) {
        hashtable->table[hash_key] = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp->key);
    free(temp->value);
    free(temp);
}


HashTable* create_table() {
    int i ;
    HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
    for (i= 0; i < TABLE_SIZE; i++) {
        hashtable->table[i] = NULL;
    }
    return hashtable;
}


void free_table(HashTable* hashtable) {
    int i;
     Node* temp ,to_free;
    for ( i= 0; i < TABLE_SIZE; i++) {
        temp = hashtable->table[i];
        while (temp != NULL) {
            to_free = temp;
            temp = temp->next;
            free(to_free->key);
            free(to_free->value);
            free(to_free);
        }
    }
    free(hashtable);
}

int main() {
    HashTable* hashtable = create_table();

    insert(hashtable, "name", "Alice");
    insert(hashtable, "age", "25");
    insert(hashtable, "city", "Wonderland");

    printf("Name: %s\n", search(hashtable, "name"));
    printf("Age: %s\n", search(hashtable, "age"));
    printf("City: %s\n", search(hashtable, "city"));

    delete(hashtable, "age");
    printf("Age after deletion: %s\n", search(hashtable, "age"));

    free_table(hashtable);
    return 0;
}
