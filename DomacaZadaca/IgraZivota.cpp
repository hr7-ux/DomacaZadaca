#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int BROJ_REDAKA = 20;
const int BROJ_STUPACA = 40;


int indeks(int redak, int stupac) {
    return redak * BROJ_STUPACA + stupac;
}


void inicijalizirajPlocu(vector<int>& ploca) {

    srand(time(0));

    for (int i = 0; i < BROJ_REDAKA * BROJ_STUPACA; i++) {

        int slucajniBroj = rand() % 100;

        
        if (slucajniBroj < 25)
            ploca[i] = 1;
        else
            ploca[i] = 0;
    }
}


void ispisiPlocu(const vector<int>& ploca) {

    
    system("cls");

    for (int redak = 0; redak < BROJ_REDAKA; redak++) {

        for (int stupac = 0; stupac < BROJ_STUPACA; stupac++) {

            if (ploca[indeks(redak, stupac)] == 1)
                cout << "O";
            else
                cout << ".";
        }

        cout << endl;
    }
}


int prebrojiSusjede(const vector<int>& ploca, int redak, int stupac) {

    int brojSusjeda = 0;

    for (int r = redak - 1; r <= redak + 1; r++) {

        for (int s = stupac - 1; s <= stupac + 1; s++) {

            
            if (r == redak && s == stupac)
                continue;

            
            if (r >= 0 && r < BROJ_REDAKA &&
                s >= 0 && s < BROJ_STUPACA) {

                if (ploca[indeks(r, s)] == 1)
                    brojSusjeda++;
            }
        }
    }

    return brojSusjeda;
}


void sljedecaGeneracija(vector<int>& ploca) {

    vector<int> novaPloca(BROJ_REDAKA * BROJ_STUPACA);

    for (int redak = 0; redak < BROJ_REDAKA; redak++) {

        for (int stupac = 0; stupac < BROJ_STUPACA; stupac++) {

            int brojSusjeda =
                prebrojiSusjede(ploca, redak, stupac);

            int trenutnaCelija =
                ploca[indeks(redak, stupac)];

            
            if (trenutnaCelija == 1) {

                
                if (brojSusjeda == 2 ||
                    brojSusjeda == 3)

                    novaPloca[indeks(redak, stupac)] = 1;

                
                else
                    novaPloca[indeks(redak, stupac)] = 0;
            }

           
            else {

                
                if (brojSusjeda == 3)
                    novaPloca[indeks(redak, stupac)] = 1;

                else
                    novaPloca[indeks(redak, stupac)] = 0;
            }
        }
    }

    
    ploca = novaPloca;
}

int main() {

    vector<int> ploca(BROJ_REDAKA * BROJ_STUPACA);

    inicijalizirajPlocu(ploca);

    while (true) {

        ispisiPlocu(ploca);

        sljedecaGeneracija(ploca);

      
        this_thread::sleep_for(chrono::seconds(2));
    }

    return 0;
}