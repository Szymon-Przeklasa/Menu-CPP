#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

void ZwolnijPamiec(int* tablica) {
    delete[] tablica;
}

void DodajElement(int*& tablica, int& rozmiar, int element) {
    int* nowaTablica = new int[rozmiar + 1];
    for (int i = 0; i < rozmiar; ++i) {
        nowaTablica[i] = tablica[i];
    }
    nowaTablica[rozmiar] = element;
    delete[] tablica;
    tablica = nowaTablica;
    ++rozmiar;
}

void WstawElement(int*& tablica, int& rozmiar, int pozycja, int element) {
    int* nowaTablica = NULL;
    nowaTablica = new int[rozmiar + 1];
    for (int i = 0; i < pozycja; i++) {
        nowaTablica[i] = tablica[i];
    }
    nowaTablica[pozycja] = element;
    for (int i = pozycja + 1; i < rozmiar + 1; i++) {
        nowaTablica[i] = tablica[i - 1];
    }
    delete[] tablica;
    tablica = nowaTablica;
    rozmiar++;
}

void UsunElement(int*& tablica, int& rozmiar, int pozycja) {
    int* nowaTablica = new int[rozmiar - 1];
    for (int i = 0; i < pozycja; i++) {
        nowaTablica[i] = tablica[i];
    }
    for (int i = pozycja; i < rozmiar - 1; i++) {
        nowaTablica[i] = tablica[i + 1];
    }
    delete[] tablica;
    tablica = nowaTablica;
    rozmiar--;
}

void Zapisz(int*& tablica, int rozmiar) {
    ofstream Plik("dane.txt");
    for (int i = 0; i < rozmiar; i++) {
        Plik << tablica[i] << endl;
    }
    cout << "   Pomyslnie zapisano dane w pliku dane.txt" << endl;
    Plik.close();
}

void Wczytaj(int*& tablica, int& rozmiar) {
    ifstream plik("dane.txt");
    if (plik.is_open()) {
        int liczba;
        while (plik >> liczba) {
            DodajElement(tablica, rozmiar, liczba);
        }
        plik.close();
        cout << "Tablica wczytana z pliku." << endl;
    } else {
        cout << "Błąd podczas otwierania pliku do odczytu." << endl;
    }
}

int Menu() {
    int wybor;
    system("cls");
    cout << "|=========| Menu |=========| " << endl;
    cout << "|   1. Dodaj element       |" << endl;
    cout << "|   2. Wstaw element       |" << endl;
    cout << "|   3. Usun element        |" << endl;
    cout << "|   4. Wyswietl            |" << endl;
    cout << "|   5. Zapisz              |" << endl;
    cout << "|   6. Wczytaj             |" << endl;
    cout << "|   0. Exit                |" << endl;
    cout << "|==========================| " << endl;
    cout << "       Podaj opcje: ";

    cin >> wybor;
    return wybor;
}

int main() {
    int w;
    int* p = NULL;
    int n = 0;
    while (true) {
        w = Menu();
        switch (w) {
            case 1: { ///Dodaj
                int element;
                cout << "   Podaj wartosc elementu: ";
                cin >> element;
                int* t = new int[n + 1];
                for (int i = 0; i < n; i++) {
                    t[i] = p[i];
                }
                t[n] = element;
                delete[] p;
                p = t;
                n++;
                break;
            }
            case 2: { ///Wstaw
                int pozycja, element;
                cout << "   Podaj pozycje do wstawienia elementu: ";
                cin >> pozycja;
                if (pozycja < 0 || pozycja > n) {
                    cout << "   Nieprawidlowa pozycja!" << endl;
                    break;
                }
                cout << "   Podaj wartosc elementu: ";
                cin >> element;
                WstawElement(p, n, pozycja, element);
                break;
            }
            case 3: { ///Usuñ
                int pozycja;
                cout << "   Podaj pozycje do usuniecia elementu: ";
                cin >> pozycja;
                if (pozycja < 0 || pozycja >= n) {
                    cout << "   Nieprawidlowa pozycja!" << endl;
                    break;
                }
                UsunElement(p, n, pozycja);
                break;
            }
            case 4: { ///Wyœwietl
                cout << "[";
                for (int i = 0; i < n; i++) {
                    cout << p[i];
                    if (i < n - 1) {
                        cout << ", ";
                    }
                }
                cout << "]" << endl;
                break;
            }
            case 5: { ///Zapisz
                Zapisz(p, n);
                break;
            }
            case 6: { ///Wczytaj
                Wczytaj(p, n);
                break;
            }
            case 0: { ///Exit
                ZwolnijPamiec(p);
                return 0;
            }
            default:
                cout << "   Nieprawidlowa opcja!" << endl;
        }
        system("pause");
    }
    return 0;
}
