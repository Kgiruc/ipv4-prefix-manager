#include <stdio.h>
#include "ip_utils.h"

/**
 * Funkcja wypisuje adres IP zapisany w zmiennej typu uint32_t
 * w formacie klasycznym: a.b.c.d (czytelny dla człowieka).
 *
 * Adresy IP przechowywane są jako liczby 32-bitowe (np. 0xC0A8011E),
 * gdzie każdy bajt odpowiada kolejnemu oktetowi.
 *
 * Przesunięcia bitowe i maski pozwalają wyciągnąć odpowiednie bajty:
 * - >> 24: najbardziej znaczący bajt (pierwszy oktet, np. 192)
 * - >> 16: drugi bajt (np. 168)
 * - >> 8:  trzeci bajt (np. 1)
 * - : najmniej znaczący bajt (np. 30)
 */
void print_ip(uint32_t ip) {
    printf("%u.%u.%u.%u",
           (ip >> 24) & 0xFF,
           (ip >> 16) & 0xFF,
           (ip >> 8) & 0xFF,
           ip & 0xFF);
}