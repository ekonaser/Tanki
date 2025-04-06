#include "razredi.hpp"

int main() {
    InitWindow(VEL_CELICE * ST_CELIC + VEL_CELICE * 2, VEL_CELICE * ST_CELIC + VEL_CELICE*2, "Tanki");
    Mreza mreza(VEL_CELICE * ST_CELIC, VEL_CELICE * ST_CELIC);
    std::vector<const char*> pozicija = {
        "pozicija/tank1.png",
        "pozicija/tank2.png",
        "pozicija/tank3.png",
        "pozicija/tank4.png",
        "pozicija/tank5.png",
    };
    Tank tank(pozicija);
    Igra igra;
    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(SVETLO_ZELENA);
        if (IsKeyDown(KEY_UP)) {
            tank.Premakni('y', -0.01f);
        }
        if (IsKeyDown(KEY_DOWN)) {
            tank.Premakni('y', 0.01f);
        }
        if (IsKeyDown(KEY_LEFT)) {
            tank.Rotacija('l');
        }
        if (IsKeyDown(KEY_RIGHT)) {
            tank.Rotacija('d');
        }
        if (IsKeyPressed(KEY_SPACE)) {
            igra.Top(tank);
        }
        if (IsKeyDown(KEY_D)) {
            igra.Strojnica(tank);
        }
        igra.Narisi(mreza, tank);
        EndDrawing();
    }
    CloseWindow();
}
