#include <stdio.h>
#include <stdint.h>
#include "../prefix_trie/prefix_trie.h"
#include "../utils/ip_utils.h"

int tests_passed = 0;
int tests_failed = 0;

void assert_equal(int actual, int expected, const char* msg) {
    if (actual == expected) {
        printf("[OK] %s\n", msg);
        tests_passed++;
    } else {
        printf("[BŁĄD] %s – oczekiwano: %d, otrzymano: %d\n", msg, expected, actual);
        tests_failed++;
    }
}

void test_dodaj_i_sprawdz() {
    init_trie();
    add(0xC0A80100, 24);  // 192.168.1.0/24
    int wynik = check(0xC0A8011E);  // 192.168.1.30
    assert_equal(wynik, 24, "Adres pasuje do dodanego prefiksu /24");
    free_trie();
}

void test_najdluzsze_dopasowanie() {
    init_trie();
    add(0xC0A80000, 16);  // 192.168.0.0/16
    add(0xC0A80100, 24);  // 192.168.1.0/24
    int wynik = check(0xC0A80137);  // 192.168.1.55
    assert_equal(wynik, 24, "Zwrócono najdłuższe dopasowanie (prefiks /24)");
    free_trie();
}

void test_usun_prefiks() {
    init_trie();
    add(0x0A000000, 8);   // 10.0.0.0/8
    add(0x0A010000, 16);  // 10.1.0.0/16
    del(0x0A010000, 16);  // usuwamy 10.1.0.0/16
    int wynik = check(0x0A010101);  // 10.1.1.1
    assert_equal(wynik, 8, "Po usunięciu /16 zwrócono nadrzędny /8");
    free_trie();
}

void test_brak_dopasowania() {
    init_trie();
    add(0xAC100000, 12);  // 172.16.0.0/12
    int wynik = check(0xC0A80101);  // 192.168.1.1
    assert_equal(wynik, -1, "Brak dopasowania dla nieznanego adresu");
    free_trie();
}

void test_duplikat_prefiksu() {
    init_trie();
    add(0xC0000200, 24);  // 192.0.2.0/24
    int wynik = add(0xC0000200, 24);  // duplikat 192.0.2.0/24
    assert_equal(wynik, 0, "Dodanie duplikatu nie zmienia trie i zwraca 0");
    int sprawdz = check(0xC0000201);  // 192.0.2.1
    assert_equal(sprawdz, 24, "Adres nadal pasuje do istniejącego prefiksu /24");
    free_trie();
}

void test_usun_nieistniejacy() {
    init_trie();
    int wynik = del(0xC6336400, 24);  // 198.51.100.0/24
    assert_equal(wynik, -1, "Usunięcie nieistniejącego prefiksu zwraca -1");
    free_trie();
}

/**
 * Uruchamia wszystkie testy i wypisuje podsumowanie.
 */
void run_all_tests() {
    printf("=== Testy funkcjonalne drzewa trie ===\n\n");
    test_dodaj_i_sprawdz();
    test_najdluzsze_dopasowanie();
    test_usun_prefiks();
    test_brak_dopasowania();
    test_duplikat_prefiksu();
    test_usun_nieistniejacy();

    printf("\n=== Podsumowanie testów ===\n");
    printf("Zaliczono: %d\n", tests_passed);
    printf("Niepowodzenia: %d\n", tests_failed);
}