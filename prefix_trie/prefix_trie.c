#include <stdlib.h>
#include <stdio.h>
#include "prefix_trie.h"

// Wskaźnik na korzeń trie – globalny dla tego modułu
static TrieNode* root = NULL;


/**
 * Inicjalizuje pusty korzeń trie.
 * Należy wywołać przed użyciem innych funkcji.
 */
void init_trie() {
    root = (TrieNode*)calloc(1, sizeof(TrieNode));
}


/**
 * Dodaje prefiks (base/mask) do trie.
 * Przechodzi przez kolejne bity adresu IP i tworzy węzły po drodze.
 * Jeśli dany prefiks już istnieje – aktualizuje is_prefix/mask.
 * Zwraca 0 w przypadku sukcesu, -1 jeśli maska niepoprawna lub brak pamięci.
 */
int add(uint32_t base, char mask) {
    if (mask < 0 || mask > 32 || root == NULL)
    return -1;

    TrieNode* node = root;
    for (int i = 31; i>= 32 -mask; --i) {
        int bit = (base >> i) & 1;
        if (!node->children[bit]) {
            node->children[bit] = (TrieNode*)calloc(1, sizeof(TrieNode));
            if (!node->children[bit]) return -1;
        }
        node = node->children[bit];
    }

    node->is_prefix = 1;
    node->mask = mask;

    return 0;
}


/**
 * Usuwa prefiks (base/mask) z trie.
 * Nie usuwa węzłów podrzędnych – tylko oznacza węzeł jako nieaktywny.
 * Zwraca 0 jeśli usunięto poprawnie, -1 jeśli prefiks nie istnieje.
 */
int del(uint32_t base, char mask) {
    if (mask < 0 || mask > 32 || root == NULL) {
    return -1;
    }

    TrieNode* node = root;
    for (int i = 31; i >= 32 - mask; i--) {
        int bit = (base >> i) & 1;
        if (!node->children[bit]) {
            return -1; // Nie ma takiego prefiksu
        }
        node = node->children[bit];
    }

    if (node->is_prefix && node->mask == mask) {
        node->is_prefix = 0;
        node->mask = 0;
        return 0;
    }

    return -1;
}


/**
 * Sprawdza, czy adres IP zawiera się w jakimkolwiek prefiksie z trie.
 * Zwraca długość najlepiej dopasowanego (najdłuższego) prefiksu lub -1.
 */
char check(uint32_t ip) {
    TrieNode* node = root;
    char best_match = -1;

    for (int i = 31; i >= 0 && node; i--) {
        if (node->is_prefix)
            best_match = node->mask;

        int bit = (ip >> i) & 1;
        node = node->children[bit];
    }

    if (node && node->is_prefix)
        best_match = node->mask;

    return best_match;
}

/**
 * Pomocnicza funkcja rekurencyjna – zwalnia całą gałąź trie.
 */
static void free_node(TrieNode* node) {
    if (!node) return;
    free_node(node->children[0]);
    free_node(node->children[1]);
    free(node);
}


/**
 * Zwalnia cały obiekt trie i ustawia root na NULL.
 * Powinna być wywołana na końcu programu.
 */
void free_trie() {
    free_node(root);
    root = NULL;
}
