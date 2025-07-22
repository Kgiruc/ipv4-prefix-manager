#ifndef PREFIX_TRIE_H
#define PREFIX_TRIE_H

#include <stdint.h>

/**
 * Struktura węzła drzewa trie do przechowywania prefiksów IPv4.
 * 
 * children[0] – wskaźnik na dziecko reprezentujące bit 0
 * children[1] – wskaźnik na dziecko reprezentujące bit 1
 * is_prefix   – flaga oznaczająca, że ten węzeł kończy poprawny prefiks
 * mask        – długość maski prefiksu (np. 24 dla /24)
 */

typedef struct TrieNode {
    struct TrieNode* children[2];
    char is_prefix;
    char mask;
} TrieNode;

void init_trie(); //Inicjalizuje strukturę trie

/**
 * Dodaje prefiks IP do trie.
 * base – adres IP (np. 0xC0A80000 dla 192.168.0.0)
 * mask – długość maski (0–32)
 * Zwraca 0 jeśli sukces, -1 jeśli błędne dane lub brak pamięci.
 */
int add(uint32_t base, char mask);

/**
 * Usuwa dany prefiks IP z trie (nie usuwa poddrzew).
 * Zwraca 0 jeśli sukces, -1 jeśli błędne dane.
 */
int del(uint32_t base, char mask);

/**
 * Sprawdza, czy adres IP pasuje do któregoś z prefiksów w trie.
 * Zwraca długość najlepiej dopasowanego prefiksu lub -1 jeśli brak dopasowania.
 */
char check(uint32_t ip);

/**
 * Zwalnia całą zaalokowaną pamięć w strukturze trie.
 * Powinna być wywołana na końcu programu.
 */
void free_trie();

#endif