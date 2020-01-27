#ifndef funkcje_h
#define funkcje_h


#include <fstream>

#include "struktury.h"

using namespace std;

/// Funkcja zapisuje strukture do  podanego strumienia
/// @param kRoot wskaźnik na strukture do zapisu
/// @param plik strumień pliku
void zapisz( KATEGORIA * kRoot, ostream & plik );

/// Funkcja otwiera plik do odczytu
/// @param nazwa nazawa pliku
/// @return zwraca otwarty strumień
ifstream otworzPlik ( string nazwa ) ;

/// Funkcja zamyka podany strumień
/// @param plik strumień pliku
void zamknijPlik ( ifstream & plik ) ;

/// Funkcja otwiera strumień i rozpoczyna zapis struktury do pliku
/// @param kRoot wskaźnik na strukture do zapisu
/// @param nazwa nazwa pliku
void otworzZapisz ( KATEGORIA * kRoot, string nazwa );

/// Funkcja liczy z ilu liczb składa się podana liczba
/// @param liczba liczba do zbadania wielkości
int rozmiarLiczby ( int liczba );

/// Funkcja wyprowadza białe znaki w podanej ilości
/// @param ilosc ilość białych znaków
void drukujSpacje ( int ilosc );

/// Funkcja liczy wielkość kategori na podstawie listy jej wartości i nazwy kategorii
/// @param kRoot wskaźnik kategorii którą należy zmierzyć
int rozmiarKategori ( KATEGORIA * kRoot);

/// Funkcja zwraca dlugość pod kategorii uwzględniając przerwy miedzy nimi
/// @param kRoot wskaźnik na kategorie której podkategorie funkcja liczy
int rozmiarWiersza ( KATEGORIA * kRoot );

/// Funkcja liczy maksymala możliwą długość pod kategorii na podstawie ich ułożenia i długości
/// @param kRoot wskaźnik struktury której pod kategorie funkcja liczy
int maxPodKategoria ( KATEGORIA * kRoot );

/// Funkcja wypisuje kategorie i jej następne
/// @param kRoot wskaźnik kategorii od którego zacznie działać
void wypiszWiersz ( KATEGORIA * kRoot );

/// Funkcja wyszukuje kategori z podanym poziomem i wypisuje wartości
/// @param kRoot wskaźnik na strukture
/// @param l numer kolumny
/// @param poziom numer wiersza
/// @param max wielkość kategorii jeżeli jest ona większa od jej maksymalnej długości pod kategori
int wypisz ( KATEGORIA * kRoot , int l , int poziom , int max = 0 );

/// Funkcja wywołuje wypisywanie kolejnych poziomów struktury
/// @param kRoot wskaźnik na strukture do wypisania
void wypisz ( KATEGORIA * kRoot, int p = 0);

/// Funkcja szuka nazwy kategorii w strukturze
/// @param kRoot wskażnik na strukture
/// @param nazwa nazwa szukanej kategorii
KATEGORIA * znajdz ( KATEGORIA * kRoot, string nazwa );

/// Funkcja sumuje kwoty wartości z pod kategorii
/// @param kRoot wskaźnik na kategorie
int sumujpodkategorie ( KATEGORIA * kRoot );

/// Funkcja wyświetla sume wszystkich transakcji kategorii i pod kategorii
/// @param kRoot wskaźnik na strukture
/// @param nazwa nazwa kategorii
void wyswietlkategorie ( KATEGORIA * kRoot, string nazwa );

/// Funkcja dodaje nową wartość do podanej kategorii
/// @param kRoot wskaźnik na kategorie
/// @param opis opis wartości
/// @param data data wartości
/// @param kwota kwota wartości
void dodajCechy ( KATEGORIA *& kRoot, string opis, string data, int kwota );

/// Funkcja dodaje nowe wartości z otwatego strumienia
/// @param kRoot wskaźnik na strukture gdzie zostaną dodane nowe wartości
/// @param plik strumień pliku
void dodajnowe ( KATEGORIA * kRoot, ifstream & plik );

/// Funkcja w uporządkowany sposób dodaje kategorie i wartości do struktury
/// @param kRoot wskażnik na strukture
/// @param plik strumień pliku
int dodajdodrzewa ( KATEGORIA *& kRoot, ifstream & plik );

/// Funkcja usuwa wartości od podanego wskźanika
/// @param wRoot wskaźnik na wartość początkową
void usunWartosc( WARTOSC *& wRoot );

/// Funkcja usuwa kategorie od podanego wskaźnika
/// @param kRoot wskaźnik poczatkowy
void usunKategorie ( KATEGORIA *& kRoot );

/// Funkcja zapisuje struture do podanego źródła
/// @param kRoot wskaźnik na strukture
/// @param plik strumień gdzie funkcja zapisze dane
void zapisz ( KATEGORIA * kRoot, fstream & plik);

/// Funkcja szuka w podanej strukturze wartości do podanej daty
/// @param kRoot wskaźnik na strukture do przeszukania
/// @param rok rok do którego funkcja filtruje
/// @param miesiac miesiąc do którego funkcja filtruje
/// @param dzien dzień do którego funkcja filtruje
KATEGORIA * szukajK( KATEGORIA * kRoot , int rok, int miesiac, int dzien );

/// Funkcja szuka w podanej strukturze wartości od podanej daty
/// @param kRoot wskaźnik na strukture do przeszukania
/// @param rok rok od którego funcja filtruje
/// @param miesiac miesiąc od którego funkcja filtruje
/// @param dzien dzień od którego funkcja filtruje
KATEGORIA * szukajP( KATEGORIA * kRoot , int rok, int miesiac, int dzien );

/// Funkcja rozpoczyna szukanie w podanej strukturze wartości do podanej daty
/// @param kRoot wskaźnik na strukture do przeszukania
/// @param dataP data do której funkcja filtruje
KATEGORIA * szukajPStart( KATEGORIA * kRoot , string dataP );

/// Funkcja rozpoczyna szukanie w podanej strukturze wartości do podanej daty
/// @param kRoot wskaźnik na strukture do przeszukania
/// @param dataK data do której funkcja filtruje
KATEGORIA * szukajKStart( KATEGORIA * kRoot , string dataK );

/// Funkcja zaczyna filtrowanie w zalezności jakie daty zostały podane
/// @param kRoot wskaźnik struktury  którą funkcja będzie filtrować
/// @param datap data od której wypisać wartości
/// @param datak data do której wypisać wartości
void sortujstart( KATEGORIA * kRoot, string datap, string datak );

/// Funkcja rozpoczytana wczytywanie z pliku do nowej struktury
/// @param kRoot wskaźnik gdzie zostanie zapisana struktura
/// @param odczytPlik nzawa pliku z którego zostanie odczytany plik
void wczytajDoDrzewa ( KATEGORIA *& kRoot, string odczytPlik );

/// Funkcja rozpoczyna dodawanie jeżeli jest podana nazwa pliku
/// @param kRoot wskaźnik na strukture do której zostaną dodane nowe wartości
/// @param odczytPlik nazwa pliku do odczytu
void dodajStart ( KATEGORIA * kRoot, string odczytPlik );


#endif
