#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <deque>

#define SVETLO_ZELENA (Color){150, 225, 88, 255}
#define VEL_CELICE 10
// zaenkrat je 75 kasneje lahko razdelis
// na vertikalno in horizontalno
#define ST_CELIC 75

int NVrednost(int a, int b) {
    // Funkcija nam vrne nakljucno vrednost v mejah a, b
    return (float)GetRandomValue(a, b);
}

bool PreveriMeje(float a, float b, float vr) {
    /* Funkcija nam preveri meje objekta
        glede na 2 podana parametra:
        a, b <-- parametra so float vrednosti
        a in b predstavljajo meje vr
    */
    return (vr <= a) || (vr >= b);
}
