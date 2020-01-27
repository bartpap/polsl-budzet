
#include <iostream>
#include <fstream>

#include "struktury.h"
#include "funkcje.h"

using namespace std;

KATEGORIA * szukajKStart ( KATEGORIA * kRoot, string dataK ) {
    int dzien = stoi( dataK.substr( 0, 2 ) );
    int miesiac = stoi( dataK.substr( 3, 2 ) );
    int rok = stoi( dataK.substr( 6, -1 ) );
    
    return szukajK( kRoot, rok, miesiac, dzien );
}

KATEGORIA * szukajPStart ( KATEGORIA * kRoot, string dataP ) {
    int dzien = stoi( dataP.substr( 0, 2 ) );
    int miesiac = stoi( dataP.substr( 3, 2 ) );
    int rok = stoi( dataP.substr( 6, -1 ) );
    
    return szukajP( kRoot, rok, miesiac, dzien );
}

KATEGORIA * szukajK ( KATEGORIA * kRoot , int rok, int miesiac, int dzien ) {
    if ( not kRoot )
        return nullptr;
    
    KATEGORIA * tmp = new KATEGORIA;
    tmp->nazwaKategori = kRoot->nazwaKategori;
    tmp->poziom = kRoot->poziom;
    tmp->nastepnaKategoria = nullptr;
    tmp->podKategoria = nullptr;
    tmp->wartosc = nullptr;
    
    WARTOSC * wart = kRoot->wartosc;
    
    while ( wart ) {
        int rokw = wart->data.rok;
        int miesiacw = wart->data.miesiac;
        int dzienw = wart->data.dzien;
        
        if ( rok == rokw ) {
            if ( miesiac == miesiacw ) {
                if ( dzien > dzienw ) {
                    WARTOSC * nowy = new WARTOSC;
                    
                    nowy->opis = wart->opis;
                    nowy->kwota = wart->kwota;
                    nowy->data.rok = rokw;
                    nowy->data.miesiac = miesiacw;
                    nowy->data.dzien = dzienw;
                    
                    nowy->nastepnaWartosc = tmp->wartosc;
                    tmp->wartosc = nowy;
                }
            }
            else if ( miesiac > miesiacw ) {
                WARTOSC * nowy = new WARTOSC;
                
                nowy->opis = wart->opis;
                nowy->kwota = wart->kwota;
                nowy->data.rok = rokw;
                nowy->data.miesiac = miesiacw;
                nowy->data.dzien = dzienw;
                
                nowy->nastepnaWartosc = tmp->wartosc;
                tmp->wartosc = nowy;
            }
        }
        else if ( rok > rokw ) {
            WARTOSC * nowy = new WARTOSC;
            
            nowy->opis = wart->opis;
            nowy->kwota = wart->kwota;
            nowy->data.rok = rokw;
            nowy->data.miesiac = miesiacw;
            nowy->data.dzien = dzienw;
            
            nowy->nastepnaWartosc = tmp->wartosc;
            tmp->wartosc = nowy;
        }
        
        wart = wart->nastepnaWartosc;
    }
        
    tmp->nastepnaKategoria = szukajK( kRoot->nastepnaKategoria, rok, miesiac, dzien );
    
    tmp->podKategoria = szukajK( kRoot->podKategoria, rok, miesiac, dzien );
    
    if ( not tmp->nastepnaKategoria && not tmp->podKategoria && not tmp->wartosc ) {
        usunKategorie( tmp );
        return nullptr;
    }
    return tmp ;
}

KATEGORIA * szukajP ( KATEGORIA * kRoot , int rok, int miesiac, int dzien ) {
    if ( not kRoot )
        return nullptr;
    
    KATEGORIA * tmp = new KATEGORIA;
    
    tmp->nazwaKategori = kRoot->nazwaKategori;
    tmp->poziom = kRoot->poziom;
    tmp->nastepnaKategoria = nullptr;
    tmp->podKategoria = nullptr;
    tmp->wartosc = nullptr;
    
    WARTOSC * war = kRoot->wartosc;
    
    while ( war ) {
        int rokw = war->data.rok;
        int miesiacw = war->data.miesiac;
        int dzienw = war->data.dzien;
        
        if ( rok == rokw ) {
            if ( miesiac == miesiacw ) {
                if ( dzien < dzienw ) {
                    WARTOSC * tmpw = new WARTOSC;
                    
                    tmpw->opis = war->opis;
                    tmpw->kwota = war->kwota;
                    tmpw->data.rok = rokw;
                    tmpw->data.miesiac = miesiacw;
                    tmpw->data.dzien = dzienw;
                    
                    tmpw->nastepnaWartosc = tmp->wartosc;
                    tmp->wartosc = tmpw;
                }
            }
            else if ( miesiac < miesiacw ) {
                WARTOSC * tmpw = new WARTOSC;
                
                tmpw->opis = war->opis;
                tmpw->kwota = war->kwota;
                tmpw->data.rok = rokw;
                tmpw->data.miesiac = miesiacw;
                tmpw->data.dzien = dzienw;
                
                tmpw->nastepnaWartosc = tmp->wartosc;
                tmp->wartosc = tmpw;
            }
        }
        else if ( rok < rokw ) {
            WARTOSC * tmpw = new WARTOSC;
            
            tmpw->opis = war->opis;
            tmpw->kwota = war->kwota;
            tmpw->data.rok = rokw;
            tmpw->data.miesiac = miesiacw;
            tmpw->data.dzien = dzienw;
            
            tmpw->nastepnaWartosc = tmp->wartosc;
            tmp->wartosc = tmpw;
        }
        
        war = war->nastepnaWartosc;
    }
        
    tmp->nastepnaKategoria = szukajP(kRoot->nastepnaKategoria, rok, miesiac, dzien);
    
    tmp->podKategoria = szukajP(kRoot->podKategoria, rok, miesiac, dzien);
    
    if ( not tmp->nastepnaKategoria && not tmp->podKategoria && not tmp->wartosc ) {
        usunKategorie( tmp );
        return nullptr;
    }
    return tmp;
}

void zapisz( KATEGORIA * kRoot, ostream & plik ) {
    KATEGORIA * tmp = kRoot;
    
    while ( tmp ) {
        if ( tmp->poziom > 0 ) {
            plik << tmp->poziom << endl;
            plik << "#" << endl;
        }
        
        plik << tmp->poziom << endl;
        plik << tmp->nazwaKategori << endl;
        
        WARTOSC * wart = tmp->wartosc;
        
        while ( wart ) {
            plik << "-1-" << wart->opis << endl;
            plik << "-2-" << wart->data.formatDaty() << endl;
            plik << "-3-" << wart->kwota << endl;
            plik << "-0" << endl;
            wart = wart->nastepnaWartosc;
        }
        zapisz( tmp->podKategoria, plik );
        tmp = tmp->nastepnaKategoria;
    }
}

void otworzZapisz ( KATEGORIA * kRoot, string nazwa ) {
    ofstream plik;
    plik.open( nazwa, ios::out );
    
    if ( plik.good() == false ) {
        cout << "plik nie istnieje" << endl;
        plik.close();
    }
    
    zapisz(kRoot, plik);
    
    plik.close();
}


void usunWartosc ( WARTOSC *& wRoot ) {
   if ( wRoot ) {
        auto p = wRoot->nastepnaWartosc;
        delete wRoot;
        wRoot = nullptr;
        usunWartosc( p );
    }
}

void usunKategorie ( KATEGORIA *& kRoot ) {
    if ( kRoot ) {
        usunKategorie( kRoot->podKategoria );
        usunWartosc( kRoot->wartosc );
        auto p = kRoot->nastepnaKategoria;
        delete kRoot;
        kRoot = nullptr;
        usunKategorie( p );
    }
}

ifstream otworzPlik ( string nazwa ) {
    ifstream plik;
    plik.open( nazwa, ios::in );
    
    if ( plik.good() == false ) {
        cout << "plik nie istnieje" << endl;
        plik.close();
    }
    
    return plik;
}

void zamknijPlik ( ifstream & plik ) {
    plik.close();
}

int rozmiarLiczby ( int liczba ) {
    int licznik = 0;
    while( liczba > 0 ) {
        licznik++;
        liczba  =  liczba / 10;
    }
    return licznik;
}

int rozmiarKategori ( KATEGORIA * kRoot ) {
    int rozmiar = 0;
    
    if ( kRoot ) {
        rozmiar += kRoot->nazwaKategori.length();
        WARTOSC * tmp = kRoot->wartosc;
        if ( tmp )
            rozmiar += 2;
        while ( tmp) {
            rozmiar += tmp->opis.length() +1;
            rozmiar += rozmiarLiczby(tmp->kwota) + 1;
            rozmiar += (tmp->data.formatDaty()).length() + 1;
            
            tmp = tmp->nastepnaWartosc;
        }
    }
    return rozmiar;
}

void drukujSpacje ( int ilosc ) {
    for ( int i =0 ; i<ilosc; i++ )
        cout << " ";
}

int maxPodKategoria ( KATEGORIA * kRoot ) {
    if( not kRoot )
        return 0;
    
    int suma = 0;
    KATEGORIA * tmp = kRoot->podKategoria;
    
    while( tmp != nullptr ) {
        int wynik = 0;
        if ( tmp->podKategoria )
            wynik = maxPodKategoria( tmp );

        int rozmiar = rozmiarKategori( tmp );
        if ( wynik < rozmiar )
            wynik = rozmiar;
        suma += wynik;
        
        tmp = tmp->nastepnaKategoria;
        if ( tmp )
            suma += 2;
    }
    return suma;
}

int rozmiarWiersza ( KATEGORIA * kRoot ) {
    int suma = 0;
    
    while ( kRoot ) {
        int roz = rozmiarKategori( kRoot );
        int maxpod = maxPodKategoria( kRoot );
        
        if( maxpod > roz )
            suma += maxpod;
        else
            suma += roz;
        
        kRoot = kRoot->nastepnaKategoria;
        suma += 2;
    }
    suma -= 2;
    return suma;
}

void wypiszWiersz ( KATEGORIA * kRoot ) {
    if ( kRoot ) {
        KATEGORIA * tmp = kRoot;
        
        while ( tmp ) {
            cout << tmp->nazwaKategori;
            
            WARTOSC * tmpw = tmp->wartosc;
            
            if ( tmpw )
                cout << " (";
            while ( tmpw ) {
                cout << tmpw->opis << ",";
                cout << tmpw->data.formatDaty() << ",";
                cout << tmpw->kwota;
                
                tmpw = tmpw->nastepnaWartosc;
                if( tmpw )
                    cout<< ";";
                else
                    cout << ")";
            }
            if ( tmp->nastepnaKategoria ) {
                int maxpod = maxPodKategoria( tmp );
                int roz = rozmiarKategori( tmp );
                if ( maxpod < roz )
                    maxpod = roz;
                drukujSpacje( maxpod - rozmiarKategori( tmp ) +2 );
            }
            else
                drukujSpacje( 2 );
            tmp = tmp->nastepnaKategoria;
        }
    }
}

int wypisz ( KATEGORIA * kRoot , int l , int poziom , int max ) {
    if ( kRoot ) {
        
        KATEGORIA * tmp = kRoot;
        int licznik = l, suma = 0;
        while ( tmp ) {
            if ( poziom == tmp->poziom ) {
                
                if ( l == 1 )
                    cout << endl;
                wypiszWiersz( tmp );
                drukujSpacje( max - rozmiarWiersza( tmp ) );
                return 1;
            }
            else {
                if ( not tmp->podKategoria ) {
                    if ( licznik == 1 )
                        cout << endl;
                    drukujSpacje( rozmiarKategori( tmp ) + 2 );
                }
                
                int rozmiar = rozmiarKategori( tmp );
                if ( maxPodKategoria( tmp ) < rozmiar )
                    max = rozmiar;
                
                suma += wypisz( tmp->podKategoria, licznik, poziom , max );
                licznik++;
                
                tmp = tmp->nastepnaKategoria;
            }
        }
        return suma;
    }
    return 0;
}

void wypisz ( KATEGORIA * kRoot, int p ) {
    int a = 1;
    int i = p;
    
    while( a ) {
        a = wypisz( kRoot, 1, i );
        i++;
    }
    cout << endl;
}

KATEGORIA * znajdz ( KATEGORIA * kRoot, string nazwa ) {
    if ( not kRoot )
        return nullptr;
    
    if ( kRoot->nazwaKategori == nazwa )
        return kRoot;

    KATEGORIA * szukaj = znajdz( kRoot->podKategoria, nazwa );

    if ( szukaj )
        return szukaj;
    szukaj = znajdz( kRoot->nastepnaKategoria, nazwa );

    if ( szukaj )
        return szukaj;
    
    return nullptr;
}

int sumujpodkategorie ( KATEGORIA * kRoot ) {
    int suma = 0;
    KATEGORIA * tmp = kRoot;
    
    while ( tmp ) {
        WARTOSC * war = tmp->wartosc;
        while ( war ) {
            suma += war->kwota;
            war = war->nastepnaWartosc;
        }
        
        suma += sumujpodkategorie ( tmp->podKategoria );
        
        tmp = tmp->nastepnaKategoria;
    }
    return suma;
}

void wyswietlkategorie ( KATEGORIA * kRoot, string nazwa ) {
    KATEGORIA * tmp = znajdz( kRoot, nazwa );
    if ( not tmp ) {
        return;
    }
    int suma = sumujpodkategorie( tmp->podKategoria );
    WARTOSC * war = tmp->wartosc;
    while ( war ) {
        suma += war->kwota;
        war = war->nastepnaWartosc;
    }
    cout << tmp->nazwaKategori << ": " << suma << endl;
}

void dodajCechy ( KATEGORIA *& kRoot, string opis, string data, int kwota ) {
    WARTOSC * nowy = new WARTOSC;
    
    nowy->opis = opis;
    nowy->kwota = kwota;
    nowy->data.dzien = stoi( data.substr( 0, 2 ) );
    nowy->data.miesiac = stoi( data.substr( 3, 2) );
    nowy->data.rok = stoi( data.substr( 6, -1 ) );
    
    nowy->nastepnaWartosc = kRoot->wartosc;
    kRoot->wartosc = nowy;
}

void dodajnowe ( KATEGORIA * kRoot, ifstream & plik ) {
    string wiersz, opis = "", data = "";
    int licznik = 0, kwota = 0;
    
    while ( getline( plik, wiersz ) ) {
        licznik++;
        switch ( licznik ) {
            case 1:
                opis= wiersz;
                break;
            case 2:
                data = wiersz;
                break;
            case 3:
                kwota = stoi(wiersz);
                break;
            case 4:{
                KATEGORIA * tmp = znajdz( kRoot, wiersz );
                if ( tmp )
                    dodajCechy( tmp, opis, data, kwota );
                break;
            }
            default:
                licznik = 0;
        }
    }
}

int dodajdodrzewa ( KATEGORIA *& kRoot, ifstream & plik ) {
    
    int linia = 0, poziom = -1;
    string wiersz, pwiersz = "";
    string opis = "", data = "";
    int kwota = 0;
    
    
    while( getline( plik, wiersz ) ) {
        linia++;
        if ( linia == 1 )
            poziom = stoi(wiersz);
        else if ( linia == 2 ) {
            if ( not kRoot ) {
                kRoot = new KATEGORIA;
                
                kRoot->wartosc = nullptr;
                kRoot->nastepnaKategoria = nullptr;
                kRoot->podKategoria = nullptr;
            }
            kRoot->nazwaKategori = wiersz;
            kRoot->poziom = poziom;
        }
        else if ( wiersz[0] == '-' ) {
            switch( stoi( wiersz.substr( 1, 1 ) ) ) {
                case 1:
                    opis = wiersz.substr( 3, -1 );
                    break;
                case 2:
                    data = wiersz.substr( 3, -1 );
                    break;
                case 3:
                    kwota = stoi( wiersz.substr( 3, -1 ) );
                    break;
                case 0:
                    dodajCechy( kRoot, opis, data , kwota );
                    break;
            }
        }
        else {
            if ( wiersz == "#" ) {
                int npoziom = stoi( pwiersz );
                
                if ( npoziom == poziom ) {
                    KATEGORIA * nowy = new KATEGORIA;
                    
                    nowy->wartosc = nullptr;
                    nowy->podKategoria = nullptr;
                    nowy->nastepnaKategoria = kRoot->nastepnaKategoria;
                    kRoot->nastepnaKategoria = nowy;
                    
                    return dodajdodrzewa( nowy, plik );
                }
                else if ( npoziom > poziom ) {
                    
                    KATEGORIA * nowy = new KATEGORIA;
                    nowy->wartosc = nullptr;
                    nowy->podKategoria = nullptr;
                    nowy->nastepnaKategoria = kRoot->podKategoria;
                    kRoot->podKategoria = nowy;
                    
                    int dodaj = dodajdodrzewa( nowy, plik );
                    if ( dodaj < poziom )
                        return dodaj;
                    else if ( dodaj == poziom ) {
                        KATEGORIA * nowy = new KATEGORIA;
                        nowy->wartosc = nullptr;
                        nowy->podKategoria = nullptr;
                        nowy->nastepnaKategoria = kRoot->nastepnaKategoria;
                        kRoot->nastepnaKategoria = nowy;
                        
                        return dodajdodrzewa( nowy, plik );
                    }
                }
                else
                    return npoziom;
            }
            else
                pwiersz = wiersz;
        }
    }
    return -1;
}

void sortujstart ( KATEGORIA * kRoot, string datap, string datak ) {
    KATEGORIA * sortuj = nullptr;
     if ( datak != "" ) {
         sortuj = szukajKStart( kRoot, datak );
         if ( datap != "" ) {
             KATEGORIA * tmp = sortuj;
             
             sortuj = szukajPStart( tmp, datap );
             usunKategorie( tmp );
         }
     }
     else if ( datap != "")
         sortuj = szukajPStart( kRoot, datap );
    
     
     if ( sortuj ) {
         wypisz( sortuj );
         usunKategorie( sortuj );
     }
     else if ( datap != "" || datak != "" )
         cout << "Brak wynikow " << endl;
     
}

void wczytajDoDrzewa ( KATEGORIA *& kRoot, string odczytPlik ) {
    ifstream plik = otworzPlik( odczytPlik );
    dodajdodrzewa( kRoot, plik );
    zamknijPlik( plik );
}

void dodajStart ( KATEGORIA * kRoot, string odczytPlik ) {
    if ( odczytPlik != "" ) {
        ifstream plik2 = otworzPlik( odczytPlik );
        dodajnowe( kRoot, plik2 );
        zamknijPlik( plik2 );

        wypisz( kRoot );
    }
}

