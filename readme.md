# IPv4 Prefix Manager – zadanie rekrutacyjne (język C)

Projekt implementuje prosty system zarządzania prefiksami IPv4 z wykorzystaniem struktury trie (drzewo prefiksowe).  
Prefiksy przechowywane są jako para: 32-bitowy adres bazowy (`uint32_t`) oraz długość maski (`char` 0–32).  
Wszystkie funkcje zawierają komentarze techniczne wyjaśniające działanie krok po kroku.

### 📌 Sposób działania

- Adresy IP reprezentowane są w postaci 32-bitowej (np. `192.168.1.0` to `0xC0A80100`).
- Funkcje operują bezpośrednio na liczbach całkowitych typu `uint32_t`, a nie na notacji dziesiętnej (czyli nie "192.168.1.0/24", tylko `0xC0A80100` + 24).

### ✨ Zaimplementowane funkcje

- `int add(uint32_t base, char mask)` – dodaje prefiks (jeśli unikalny)
- `int del(uint32_t base, char mask)` – usuwa dokładny prefiks (bez naruszania podrzędnych)
- `char check(uint32_t ip)` – zwraca maskę najdłuższego pasującego prefiksu lub -1
- `void free_trie()` – zwalnia pamięć drzewa

### 🧪 Testy

W katalogu `test/test_prefix_trie.c` znajduje się zestaw testów funkcjonalnych. Uruchamiane są przyciskiem ▶️ w Visual Studio Code.

Zakres testów:
- dodanie i sprawdzenie prefiksu
- najdłuższe dopasowanie (longest prefix match)
- usuwanie istniejących i nieistniejących
- przypadki brzegowe i duplikaty