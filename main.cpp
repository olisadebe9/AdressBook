#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>

using namespace std;

struct Uzytkownik
{
    int id;
    string imie, nazwisko, nrTelefonu, adresEmail, adres;
};

int wczytajOsobyZPliku (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    int id, nrLinii = 1;
    string imie, nazwisko, nrTelefonu, adresEmail, adres, linia, pobierz;
    char separator = '|';
    size_t pozycja = 0;

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in );
     if(plik.good()==true)
        {
            while (getline(plik,linia))
                {
                    while ((pozycja = linia.find(separator)) != string::npos)
                        {
                            pobierz = linia.substr(0,pozycja);
                            linia.erase(0, pozycja+1);
                            switch(nrLinii)
                                {
                                    case 1: id = atoi(pobierz.c_str());    break;
                                    case 2: imie = pobierz;                break;
                                    case 3: nazwisko = pobierz;            break;
                                    case 4: nrTelefonu = pobierz;          break;
                                    case 5: adresEmail = pobierz;          break;
                                    case 6: adres = pobierz; uzytkownicy.push_back (Uzytkownik{id, imie, nazwisko, nrTelefonu, adresEmail, adres}); break;
                                }
                            if( nrLinii >= 6 )
                                {
                                    nrLinii = 1;
                                    iloscUzytkownikow++;
                                }
                            else
                                {
                                    nrLinii ++;
                                }
                        }
                }
            plik.close();
        }
    return iloscUzytkownikow;
}

void wyswietlKsiazke(vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    for (int i=0; i<uzytkownicy.size(); i++)
    {
        cout << "ID uzytkownika " << uzytkownicy[i].id << ": " << uzytkownicy[i].imie << " " << uzytkownicy[i].nazwisko << ", telefon: " << uzytkownicy[i].nrTelefonu
        << ", adres e-mail: " << uzytkownicy[i].adresEmail << ", adres zamieszkania: " << uzytkownicy[i].adres << endl;
    }
    system("pause");
}

void zapiszNowaOsobeDoPliku (vector<Uzytkownik> uzytkownicy, int iloscUzytkownikow)
{
    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::out | ios::app);
    if (plik.good() == true)
        {
            plik << uzytkownicy[iloscUzytkownikow].id << "|" << uzytkownicy[iloscUzytkownikow].imie << "|" << uzytkownicy[iloscUzytkownikow].nazwisko
                 << "|" << uzytkownicy[iloscUzytkownikow].nrTelefonu << "|" << uzytkownicy[iloscUzytkownikow].adresEmail << "|" << uzytkownicy[iloscUzytkownikow].adres << "|" << endl;
        }
    else
        {
            cout << "Nie udalo sie utworzyc pliku" << endl;
        }
    plik.close();
    cout << "Dane zostaly wprowadzone poprawnie. Za chwile nastapi powrot do glownego menu " << endl;
}

int wprowadzNowaOsobe(vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    Uzytkownik obiekt;

    if (iloscUzytkownikow == 0)
        obiekt.id = iloscUzytkownikow+1;
    else
        obiekt.id = uzytkownicy[iloscUzytkownikow-1].id+1;

    system ("cls");
    cout << "Podaj imie: ";
    cin >> obiekt.imie;
    cout << "Podaj nazwisko: ";
    cin >> obiekt.nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, obiekt.nrTelefonu);
    cout << "Podaj adres e-mail: ";
    cin >> obiekt.adresEmail;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, obiekt.adres);
    uzytkownicy.push_back( obiekt );

    zapiszNowaOsobeDoPliku(uzytkownicy,iloscUzytkownikow);

    Sleep(2500);

    return iloscUzytkownikow+1;
}

int wyszukajPoImieniu (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    string imie;
    system ("cls");
    cout << "Podaj imie osoby ktora chcesz wyszukac: ";
    cin >> imie;
    for (int i = 0; i<uzytkownicy.size(); i++)
        {
            if (uzytkownicy[i].imie == imie)
                {
                    cout << "ID uzytkownika " << uzytkownicy[i].id << ": " << uzytkownicy[i].imie << " " << uzytkownicy[i].nazwisko
                         << ", telefon: " << uzytkownicy[i].nrTelefonu << ", adres e-mail: " << uzytkownicy[i].adresEmail
                         << ", adres zamieszkania: " << uzytkownicy[i].adres << endl;
                }
        }
    system("pause");
    return 1;
}

int wyszukajPoNazwisku (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    string nazwisko;
    system ("cls");
    cout << "Podaj imie osoby ktora chcesz wyszukac: ";
    cin >> nazwisko;
    for (int i = 0; i<uzytkownicy.size(); i++)
        {
            if (uzytkownicy[i].nazwisko == nazwisko)
                {
                    cout << "ID uzytkownika " << uzytkownicy[i].id << ": " << uzytkownicy[i].imie << " " << uzytkownicy[i].nazwisko
                         << ", telefon: " << uzytkownicy[i].nrTelefonu << ", adres e-mail: " << uzytkownicy[i].adresEmail
                         << ", adres zamieszkania: " << uzytkownicy[i].adres << endl;
                }
        }
    system("pause");
    return 1;
}

string zwroc(string linia, string id)
{
    size_t pozycja = 0;
    char separator = '|';
    string pobierz, idDoPorownania = "";
    while (pozycja = linia.find(separator))
        {
            pobierz = linia.substr(0,pozycja);
            if (id == pobierz)
                {
                    idDoPorownania = linia.erase(pozycja, linia.length() );
                }
            break;
        }
    return idDoPorownania;
}

void aktualizujPlikTekstowyPoUsunieciuDanychUzytkownika (vector<string> kopiuj)
{
    ofstream plikDrugi;
    plikDrugi.open("Ksiazka adresowa.txt", ios::out | ios::app);
    if(plikDrugi.good()==true)
        for( int i = 0; i < kopiuj.size(); i++ )
            plikDrugi << kopiuj[i] << endl;

    plikDrugi.close();
    system("pause");
}

int usunPozycje (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    vector<string> kopiuj;
    string linia, id;
    int licznik = 0;
    char znak;

    system ("cls");
    cout << "Podaj ID uzytkownika, ktorego chcesz usunac"<<endl;
    cin >> id;
    fstream plikPierwszy;
    plikPierwszy.open("Ksiazka adresowa.txt", ios::in );
    if(plikPierwszy.good()==true)
        {
        while (getline(plikPierwszy,linia))
            {
                if (id != zwroc(linia, id))
                    {
                        kopiuj.push_back( linia );
                    }
                else
                    {
                        for( int i = licznik; i < uzytkownicy.size() -1; i++ )
                            {
                                uzytkownicy[i] = uzytkownicy[i+1];
                            }
                        iloscUzytkownikow-=1;
                        uzytkownicy.pop_back();
                    }
                licznik++;
            }
            plikPierwszy.close();
        }
    remove( "Ksiazka adresowa.txt" );
    aktualizujPlikTekstowyPoUsunieciuDanychUzytkownika(kopiuj);
    return 1;
}

void aktualizujPlikTekstowyPoEdycjiDanychUzytkownika (vector<Uzytkownik> uzytkownicy)
{
    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::out | ios::app);
    if (plik.good() == true)
        {
            for( int i = 0; i < uzytkownicy.size(); i++ )
                {
                    plik << uzytkownicy[i].id << "|" << uzytkownicy[i].imie << "|" << uzytkownicy[i].nazwisko
                         << "|" << uzytkownicy[i].nrTelefonu << "|" << uzytkownicy[i].adresEmail << "|" << uzytkownicy[i].adres << "|" << endl;
                }
        }
    else
        {
            cout << "Nie udalo sie utworzyc pliku" << endl;
        }
    plik.close();
    cout << "Dane zostaly wprowadzone poprawnie. Za chwile nastapi powrot do glownego menu " << endl;
    Sleep(2500);
}

int edytujAdresata (vector<Uzytkownik> &uzytkownicy, int &iloscUzytkownikow)
{
    int id;
    char daneAdresataDoZmiany;
    string imie, nazwisko, nrTelefonu, adresEmail, adres;
    bool czyIstniejeAdresat = false;

    system ("cls");
    cout << "Podaj ID uzytkownika, ktorego chcesz edytowac"<<endl;
    if (!uzytkownicy.empty())
        {
            for (int pozycjaOsobyNaLiscie = 0; pozycjaOsobyNaLiscie<uzytkownicy.size(); pozycjaOsobyNaLiscie++)
                {
                    cin >> id;
                    if (uzytkownicy[pozycjaOsobyNaLiscie].id == id)
                        {
                            czyIstniejeAdresat = true;
                            cout << "Wybierz dane adresata, ktore chcesz edytowac:" << endl;
                            cout <<  "1. Imie" << endl;
                            cout <<  "2. Nazwisko" << endl;
                            cout <<  "3. Numer telefonu" << endl;
                            cout <<  "4. Email" << endl;
                            cout <<  "5. Adres zamieszkania" << endl;
                            cout <<  "6. Powrot do glownego menu" << endl;
                            cin >> daneAdresataDoZmiany;

                            if (daneAdresataDoZmiany == '1')
                                {
                                    cout << "Podaj nowe imie" << endl;
                                    cin >> imie ;
                                    uzytkownicy[pozycjaOsobyNaLiscie].imie = imie;
                                }
                            else if (daneAdresataDoZmiany == '2')
                                {
                                    cout << "Podaj nowe nazwisko" << endl;
                                    cin >> nazwisko ;
                                    uzytkownicy[pozycjaOsobyNaLiscie].nazwisko = nazwisko;
                                }
                            else if (daneAdresataDoZmiany == '3')
                                {
                                    cout << "Podaj nowy numer telefonu" << endl;
                                    cin.sync();
                                    getline(cin,nrTelefonu);
                                    uzytkownicy[pozycjaOsobyNaLiscie].nrTelefonu = nrTelefonu;
                                }
                            else if (daneAdresataDoZmiany == '4')
                                {
                                    cout << "Podaj nowy numer telefonu" << endl;
                                    cin >> adresEmail ;
                                    uzytkownicy[pozycjaOsobyNaLiscie].adresEmail = adresEmail;
                                }
                            else if (daneAdresataDoZmiany == '5')
                                {
                                    cout << "Podaj nowy adres" << endl;
                                    cin >> adres ;
                                    cin.sync();
                                    getline(cin,adres);
                                    uzytkownicy[pozycjaOsobyNaLiscie].adres = adres;
                                }
                            else if (daneAdresataDoZmiany == '6')
                                return 1;
                        }
                    if (czyIstniejeAdresat == false)
                        {
                            cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
                        }
                }
            remove( "Ksiazka adresowa.txt" );
            aktualizujPlikTekstowyPoEdycjiDanychUzytkownika (uzytkownicy);
        }
    else
        {
            cout << "Ksiazka adresowa jest pusta." << endl << endl;
        }

    return 1;
}
int main()
{
    vector<Uzytkownik> uzytkownicy;
    int iloscUzytkownikow = 0;
    char wybor;
    iloscUzytkownikow = wczytajOsobyZPliku(uzytkownicy, iloscUzytkownikow);

    while (true)
    {
        system ("cls");
        cout << "1. Wprowadz dane nowej osoby" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl ksiazke adresowa" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zamknij program" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if (wybor == '1')
            iloscUzytkownikow = wprowadzNowaOsobe(uzytkownicy, iloscUzytkownikow);
        else if (wybor == '2')
            wyszukajPoImieniu (uzytkownicy, iloscUzytkownikow);
        else if (wybor == '3')
            wyszukajPoNazwisku (uzytkownicy, iloscUzytkownikow);
        else if (wybor == '4')
            wyswietlKsiazke( uzytkownicy, iloscUzytkownikow);
        else if (wybor == '5')
            usunPozycje (uzytkownicy, iloscUzytkownikow);
        else if (wybor == '6')
             edytujAdresata(uzytkownicy, iloscUzytkownikow);
        else if (wybor == '9')
            exit (0) ;
    }
    return 0;
}

