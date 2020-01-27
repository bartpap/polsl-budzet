
#include <iostream>
#include <string>

#include "struktury.h"
#include "funkcje.h"

using namespace std;

int main( int argc, char ** argv ) {
    string odczytPlik = "", dodajPlik = "", pokazKategorie = "", dataP = "", dataK = "" , zapisPlik = "";
    
    for( int i = 1; i < argc; i++ ) {

        if ( strcmp(  argv[ i ], "-file" ) == 0 ) {
            odczytPlik = argv[i+1];
        }
        
        else if ( strcmp(  argv[ i ], "-fileNew" ) == 0 ) {
            dodajPlik = argv[i+1];
            
        }
        
        else if ( strcmp(  argv[ i ], "-t" ) == 0 ) {
            pokazKategorie = argv[i+1];
        }
        
        else if ( strcmp(  argv[ i ], "-dp" ) == 0 ) {
            dataP = argv[i+1];
        }
        
        else if ( strcmp(  argv[ i ], "-dk" ) == 0 ) {
            dataK = argv[i+1];
        }
        
        else if ( strcmp(  argv[ i ], "-fout" ) == 0 ) {
            zapisPlik = argv[i+1];
        }
    }
    
    if( odczytPlik == "" ){
        cout << "Brak nazwy pliku wejsciowego" << endl;
        return 0;
    }
    
    if ( odczytPlik == "" )
        zapisPlik = odczytPlik;
    
    KATEGORIA * kKorzen = nullptr;
    
    wczytajDoDrzewa(kKorzen, odczytPlik);
    
    wypisz(kKorzen);
    
    if ( pokazKategorie != "" )
        wyswietlkategorie( kKorzen, pokazKategorie );
    
    sortujstart(kKorzen, dataP, dataK);
    
    dodajStart(kKorzen, dodajPlik);
    
    otworzZapisz(kKorzen, zapisPlik);
    
    usunKategorie(kKorzen);
    
    return 0;
}
