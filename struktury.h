#ifndef struktury_h
#define struktury_h


using namespace std;

struct DATA{
    int rok;
    int miesiac;
    int dzien;
    
    string formatDaty() {
        string data;
        
        if ( dzien < 10 )
            data += "0" + to_string( dzien ) + ".";
        else
            data += to_string( dzien ) + ".";
        
        if ( miesiac < 10 )
            data += "0" + to_string( miesiac ) + ".";
        else
            data += to_string( miesiac ) + ".";
        
        data += to_string( rok );
        
        return data;
    };
};

struct WARTOSC
{
    string opis;
    DATA data;
    int kwota;
    WARTOSC * nastepnaWartosc;
};

struct KATEGORIA
{
    string nazwaKategori;
    int poziom;
    WARTOSC * wartosc;
    KATEGORIA * podKategoria,
              * nastepnaKategoria;
};


#endif
