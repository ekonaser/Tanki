#include "funkcije.hpp"

struct Matrika{
    std::vector<Vector2> mat;
    Matrika() {
    }
    //operator [] vrne Vector2
    Vector2& operator[](size_t i) {
        return mat[i];
    }
    void dodaj(Vector2 vek) {
        mat.push_back(vek);
    }
    void premaknix(float i){
        for (auto& vek: mat) {
            vek.x += i;
        }
    }
    void premakniy(float i){
        for (auto& vek: mat) {
            vek.y += i;
        }
    }
};

class Izstrelek{
public:
    Izstrelek(float rot, Vector2 poz, float hitr, const char* vrsta) {
        rotacija = rot;
        pozicija = poz;
        s = hitr;
        izstrelek = LoadTexture(vrsta);
    }
    void Premakni() {
        pozicija.x += s * sin(rotacija * DEG2RAD);
        pozicija.y -= s * cos(rotacija * DEG2RAD);        
    }
    void Narisi() {
        DrawTextureEx(izstrelek, pozicija, rotacija, 1.0f , WHITE);
    }

    Vector2& Pozicija() {
        return pozicija;
    }

    ~Izstrelek() {
        UnloadTexture(izstrelek);
    }
private:
    Texture2D izstrelek;
    // s = hitrost
    float rotacija, s;
    Vector2 pozicija;
};

class Mreza{
public:
    Mreza(int a, int b) {
        dolzina = a;
        visina = b;
    }
    void Narisi() {
        DrawRectangleLines(VEL_CELICE, VEL_CELICE, dolzina, visina, BLACK);
    }
private:
    int dolzina;
    int visina;
};

class Tank{
public:
    Tank(std::vector<const char*> vek) {
        for (unsigned int i = 0; i < vek.size(); i++) {
            sTank.push_back(LoadTexture(vek[i]));
        }
        pozicija = {150, 150};
        rotacija = 0.0f;
    }
    void Narisi() {
        // slika - pozicija - rotacija - velikost - barva
        DrawTextureEx(sTank[0], pozicija, rotacija, 1.0f , WHITE);
    }
    void Premakni(char znak, float a) {
        if (znak == 'y') {
            pozicija.x -= a * sin(rotacija * DEG2RAD);
            pozicija.y += a * cos(rotacija * DEG2RAD);
            sTank.push_front(sTank.back());
            sTank.pop_back();
        }
        if (znak == 'x') {
            pozicija.x += a * sin(rotacija * DEG2RAD);
            pozicija.y -= a * cos(rotacija * DEG2RAD);
            sTank.push_back(sTank.front());
            sTank.pop_front();
        }
    }
    void Rotacija(char znak) {
        // metoda nam rotira tank za 0.01 stopinjo
        if (znak == 'd') {
            rotacija += 0.01f;
        }
        if (znak == 'l') {
            rotacija -= 0.01f;
        }
    }
    Texture2D SlikaTanka() {
        // vrne trenutno sliko tanka
        return sTank[0];
    }
    Vector2 PozicijaTanka() {
        return pozicija;
    }
    float RotacijaTanka() {
        return rotacija;
    }
private:
    std::deque<Texture2D> sTank;
    float rotacija;
    Vector2 pozicija;
};

class Igra{
public:
    void Narisi(Mreza& m, Tank& t) {
        m.Narisi();
        t.Narisi();
        // i = iterator
        for (auto i = izstrelki.begin(); i != izstrelki.end(); ) {
            if (PreveriMeje(0.0, 750.0, i->Pozicija().y)) {
                i = izstrelki.erase(i);
            } else {
                i->Narisi();
                i->Premakni();
                ++i;
            }
        }
    }
    void Top(Tank& t) {
        /* Metoda za streljanje iz topa */
        Vector2 poz(t.PozicijaTanka());
        float rotacija = t.RotacijaTanka();
        // potrebno je na novo izracunati pozicijo x in y zaradi rotacije
        // in velikosti tanka oz. slike
        poz.x += (t.SlikaTanka().width / 2) * cos(rotacija * DEG2RAD);
        poz.y += (t.SlikaTanka().width / 2) * sin(rotacija * DEG2RAD);
        Izstrelek strel(rotacija, poz, 0.05f,"izstrelki/izstrelekAP.png");
        izstrelki.push_back(strel);
    }
    void Strojnica(Tank& t) {
        double zdaj = GetTime();
        if ((zdaj - zadnji_izstrelek_strojnice) >= strojnicaCD) {
            Vector2 poz(t.PozicijaTanka());
            float rotacija = t.RotacijaTanka();
            poz.x += (t.SlikaTanka().width / 2) * cos(rotacija * DEG2RAD);
            poz.y += (t.SlikaTanka().width / 2) * sin(rotacija * DEG2RAD);
            Izstrelek strel(rotacija, poz, 0.08f,"izstrelki/50cal.png");
            izstrelki.push_back(strel);
            zadnji_izstrelek_strojnice = zdaj;
        }
    }
private:
    std::deque<Izstrelek> izstrelki;
    const double strojnicaCD = 0.2;
    double zadnji_izstrelek_strojnice = 0.0;
};
