#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **buckets;
    int size;
    int count;
} HashTable;
unsigned int hash(const char *key, int table_size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % table_size;
}
HashTable* create_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->buckets = calloc(size, sizeof(Node*));
    return table;
}
void insert(HashTable *table, const char *key, int value) {
    unsigned int index = hash(key, table->size);
    Node *new_node = malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->count++;

    if ((float)table->count / table->size > LOAD_FACTOR) {
        resize_table(table);
    }
}
int search(HashTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    Node *node = table->buckets[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return -1;  
}
void removed(HashTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    Node *node = table->buckets[index];
    Node *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                table->buckets[index] = node->next;
            }
            free(node->key);
            free(node);
            table->count--;
            return;
        }
        prev = node;
        node = node->next;
    }
}
void resize_table(HashTable *table) {
    int old_size = table->size;
    Node **old_buckets = table->buckets;

    table->size *= 2;
    table->buckets = calloc(table->size, sizeof(Node*));
    table->count = 0;

    for (int i = 0; i < old_size; i++) {
        Node *node = old_buckets[i];
        while (node) {
            insert(table, node->key, node->value);
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(old_buckets);
}
void free_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Node *node = table->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}
int main() {
    HashTable *table = create_table(INITIAL_SIZE);

    insert(table, "key1", 1);
    insert(table, "key2", 2);

    printf("key1: %d\n", search(table, "key1"));
    printf("key2: %d\n", search(table, "key2"));

    remove(table, "key1");
    printf("key1 after removal: %d\n", search(table, "key1"));

    free_table(table);
    return 0;
}
