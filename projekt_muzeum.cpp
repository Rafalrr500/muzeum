// Projekt "Muzeum"
// Wykonal : Rafal Rudnicki

#include <iostream>
#include <fstream>

using namespace std;

int liczba_eksponatow=0;
int id_ostatniego_eksponatu=0;
int id_ostatniego_eksponatu_z_bazy=0;

struct eksponat
{
    int indeks;
    string nazwa;
    string opis;
    int rok1;
    int rok2;
    float waga;
    int dzien;
    int miesiac;
    int rok;
    int stan;
    struct eksponat* nast;
};

eksponat* pierwszy = NULL;
eksponat* ostatni = NULL;

struct ekspozycja
{
    int id;
    string nazwa_ekspo;
    string opis_ekspo;
    int sala;
    int status;
    eksponat* next;
    eksponat* ost;
    ekspozycja* kolejny;
};

ekspozycja* first = NULL;
ekspozycja* last = NULL;
int id_ostatniej_ekspozycji=0;

void blad()
{
    cout<<"Podano bledna wartosc. Sprobuj ponownie"<<endl;
}

void zapis_do_pliku()
{
    ofstream fout;
    fout.open("eksponaty.txt");
    eksponat* pom=pierwszy;
    while(pom != NULL)
    {
        fout<<pom->indeks<<endl;
        fout<<pom->nazwa<<endl;
        fout<<pom->opis<<endl;
        fout<<pom->rok1;
        if(pom->rok1==pom->rok2) fout<<endl;
        else fout<<"-"<<pom->rok2<<endl;
        fout<<pom->waga<<endl;
        fout<<pom->dzien<<"."<<pom->miesiac<<"."<<pom->rok<<endl;
        fout<<pom->stan<<endl<<endl;
        pom=pom->nast;
    }
    fout.close();
}

void zapis_do_pliku_ekspo()
{
    ofstream fout;
    fout.open("ekspozycje.txt");
    ekspozycja* pom1=first;
    eksponat* pom = NULL;
    while(pom1 != NULL)
    {
        fout<<endl;
        fout<<"*** Indeks ekspozycji: "<<pom1->id<<" ***"<<endl;
        fout<<"*** Nazwa ekspozycji: "<<pom1->nazwa_ekspo<<" ***"<<endl;
        fout<<"*** Opis ekspozycji: "<<pom1->opis_ekspo<<" ***"<<endl;
        fout<<"*** Sala: "<<pom1->sala<<" ***"<<endl;
        if(pom1->status==1) fout<<"*** Status: Aktywna ***"<<endl;
        else fout<<"*** Status: Zakonczona ***"<<endl;
        fout<<"*************************************"<<endl;
        pom=pom1->next;
        while(pom != NULL)
        {
            fout<<pom->indeks<<endl;
            fout<<pom->nazwa<<endl;
            fout<<pom->opis<<endl;
            if(pom->rok1==pom->rok2) fout<<pom->rok1<<endl;
            else fout<<pom->rok1<<"-"<<pom->rok2<<endl;
            fout<<pom->waga<<" kg"<<endl;
            fout<<pom->dzien<<"."<<pom->miesiac<<"."<<pom->rok<<endl;
            fout<<pom->stan<<endl;
            fout<<endl;
            pom = pom->nast;
        }
        pom1 = pom1->kolejny;
    }
    fout.close();
}

void dodaj_do_ekspo()
{

    int ile, id_eksponatu, id_ekspozycji;
    cout<<"Podaj indeks ekspozycji, do ktorej chcesz dodac eksponaty: "<<endl;
    cin>>id_ekspozycji;
    cin.ignore();
    ekspozycja* tmp = first;
    while(tmp->id !=id_ekspozycji )
    {
        tmp=tmp->kolejny;
    }
    tmp->status=1;
    cout<<"Ile eksponatow chcesz dodac: "<<endl;;
    cin>>ile;
    cin.ignore();
    eksponat* pom = pierwszy;
    for(int i=1; i<=ile; i++)
    {
        cout<<"Podaj indeks eksponatu, ktory chcesz dodac: "<<endl;
        cin>>id_eksponatu;
        cin.ignore();
        if(id_eksponatu==pierwszy->indeks)
        {
            pom=pierwszy;
            if(pom)
            {
                pierwszy=pom->nast;
                pom->nast=NULL;
                if(tmp->ost != NULL)
                {
                    tmp->ost->nast=pom;
                }
                else
                {
                    tmp->next = pom;
                }
                tmp->ost = pom;
            }
        }
        else if(id_eksponatu==ostatni->indeks)
        {
            pom=pierwszy;
            if( pom )
            {
                if( pom->nast )
                {
                    while( pom->nast->nast ) pom = pom->nast;

                    if(tmp->ost != NULL)
                    {
                        tmp->ost->nast=pom->nast;
                    }
                    else
                    {
                        tmp->next = pom->nast;
                    }
                    tmp->ost = pom->nast;
                    pom->nast = NULL;
                    ostatni=pom;
                }
            }
        }
        else
        {
            eksponat* pom=pierwszy;
            eksponat* do_przeniesienia=pierwszy->nast;
            while((do_przeniesienia->indeks)!=id_eksponatu)
            {
                pom=pom->nast;
                do_przeniesienia=do_przeniesienia->nast;
            }
            pom->nast=do_przeniesienia->nast;
            do_przeniesienia->nast=NULL;
            if(tmp->ost != NULL)
            {
                tmp->ost->nast=do_przeniesienia;
            }
            else
            {
                tmp->next = do_przeniesienia;
            }
            tmp->ost = do_przeniesienia;
        }
        liczba_eksponatow--;
        zapis_do_pliku();
        zapis_do_pliku_ekspo();
    }
}

void usun_z_ekspo()
{
    int ile, id_eksponatu, id_ekspozycji;
    cout<<"Podaj indeks ekspozycji, z ktorej chcesz usunac eksponaty: "<<endl;
    cin>>id_ekspozycji;
    cin.ignore();
    ekspozycja* tmp = first;
    while(tmp->id !=id_ekspozycji )
    {
        tmp=tmp->kolejny;
    }
    cout<<"Ile eksponatow chcesz usunac: "<<endl;;
    cin>>ile;
    cin.ignore();
    eksponat* pom = tmp->next;
    for(int i=1; i<=ile; i++)
    {
        cout<<"Podaj indeks eksponatu, ktory chcesz usunac: "<<endl;
        cin>>id_eksponatu;
        cin.ignore();
        if(id_eksponatu==tmp->next->indeks)
        {
            pom=tmp->next;
            if(pom)
            {
                tmp->next=pom->nast;
                pom->nast=NULL;
                if(ostatni != NULL)
                {
                    ostatni->nast=pom;
                }
                else
                {
                    pierwszy = pom;
                }
                ostatni = pom;
            }
        }
        else if(id_eksponatu==ostatni->indeks)
        {
            pom=tmp->next;
            if( pom )
            {
                if( pom->nast )
                {
                    while( pom->nast->nast ) pom = pom->nast;

                    if(ostatni != NULL)
                    {
                        ostatni->nast=pom->nast;
                    }
                    else
                    {
                        pierwszy = pom->nast;
                    }
                    ostatni = pom->nast;
                    pom->nast = NULL;
                }
            }
        }
        else
        {
            eksponat* pom=tmp->next;
            eksponat* do_przeniesienia=tmp->next->nast;
            while((do_przeniesienia->indeks)!=id_eksponatu)
            {
                pom=pom->nast;
                do_przeniesienia=do_przeniesienia->nast;
            }
            pom->nast=do_przeniesienia->nast;
            do_przeniesienia->nast=NULL;
            if(ostatni != NULL)
            {
                ostatni->nast=do_przeniesienia;
            }
            else
            {
                pierwszy = do_przeniesienia;
            }
            ostatni = do_przeniesienia;
        }
        zapis_do_pliku();
        zapis_do_pliku_ekspo();
        liczba_eksponatow++;
    }
}

void zmien_status_ekspo(int id_ekspozycji)
{
    ekspozycja* tmp = first;
    while(tmp->id !=id_ekspozycji )
    {
        tmp=tmp->kolejny;
    }
    ekspozycja* pom = tmp;
    while(pom->kolejny)
    {
        liczba_eksponatow++;
    }
    if(ostatni != NULL)
    {
        ostatni->nast=tmp->next;
    }
    else
    {
        pierwszy = tmp->next;
    }
    ostatni = tmp->next;
    tmp->next=NULL;
    tmp->ost=NULL;
    tmp->status=0;
    zapis_do_pliku();
    zapis_do_pliku_ekspo();
}

void status()
{
    int id_ekspozycji;
    cout<<"Podaj indeks ekspozycji, ktora chcesz zamknac: "<<endl;
    cin>>id_ekspozycji;
    cin.ignore();
    zmien_status_ekspo(id_ekspozycji);
}

void usun_ekspo_first()
{
    ekspozycja* pom;
    pom=first;
    if(pom)
    {
        first=pom->kolejny;
        delete pom;
    }
}

void usun_ekspo_last()
{
    ekspozycja* pom = first;
    if( pom )
    {
        if( pom->kolejny )
        {
            while( pom->kolejny->kolejny ) pom = pom->kolejny;
            delete pom->kolejny;
            pom->kolejny = NULL;
        }
    }
}

void usun_ekspo()
{
    int id_ekspozycji;
    cout<<"Podaj indeks ekspozycji, ktora chcesz usunac: "<<endl;
    cin>>id_ekspozycji;
    cin.ignore();
    zmien_status_ekspo(id_ekspozycji);
    if(id_ekspozycji==first->id) usun_ekspo_first();
    else if(id_ekspozycji==last->id) usun_ekspo_last();
    else
    {
        ekspozycja* pom=first;
        ekspozycja* do_usuniecia=first->kolejny;
        while((do_usuniecia->id)!=id_ekspozycji)
        {
            pom=pom->kolejny;
            do_usuniecia=do_usuniecia->kolejny;
        }
        pom->kolejny=do_usuniecia->kolejny;
        delete do_usuniecia;
    }
    zapis_do_pliku_ekspo();
}

void utworz_ekspo()
{
    int licznik=0, tmp;
    ekspozycja *nowy = new ekspozycja;
    nowy->id=id_ostatniej_ekspozycji+1;
    id_ostatniej_ekspozycji++;
    cout<<"Podaj nazwe ekspozycji : "<<endl;
    getline(cin,nowy->nazwa_ekspo);
    cout<<"Podaj opis ekspozycji : "<<endl;
    getline(cin,nowy->opis_ekspo);
    while(licznik==0)
    {
        cout<<"Podaj numer sali (W muzeum znajduje sie 100 sal) : "<<endl;
        cin>>tmp;
        if(tmp>0 && tmp<=100)
        {
            nowy->sala=tmp;
            licznik++;
        }
        else blad();
    }
    nowy->status=1;
    nowy->next=NULL;
    nowy->ost=NULL;
    nowy->kolejny=NULL;
    if(last != NULL)
    {
        last->kolejny=nowy;
    }
    else
    {
        first = nowy;
    }
    last = nowy;
    zapis_do_pliku_ekspo();
}

void wyswietl()
{
    eksponat* pom=pierwszy;
    while(pom != NULL)
    {
        cout<<endl;
        cout<<"Indeks: "<<pom->indeks<<endl;
        cout<<"Nazwa: "<<pom->nazwa<<endl;
        cout<<"Opis: "<<pom->opis<<endl;
        if(pom->rok1==pom->rok2) cout<<"Rok powstania: "<<pom->rok1<<endl;
        else cout<<"Okres powstania: "<<pom->rok1<<"-"<<pom->rok2<<endl;
        cout<<"Waga: "<<pom->waga<<" kg"<<endl;
        cout<<"Data dodania do zbioru: "<<pom->dzien<<"."<<pom->miesiac<<"."<<pom->rok<<endl;
        cout<<"Stan: "<<pom->stan<<endl;
        pom = pom->nast;
    }
}

void sort_nazwa()
{
    eksponat* pom = NULL;
    eksponat* pom1 = pierwszy;
    int licznik=0;
    int tmp;
    string napis="~";
    int tab[liczba_eksponatow];
    for(int k=0; k<liczba_eksponatow; k++) tab[k]=0;
    for(int i=0; i<liczba_eksponatow; i++)
    {
        pom=pierwszy;
        while(pom != NULL)
        {
            licznik=0;
            for(int j=0; j<liczba_eksponatow; j++)
            {
                if(pom->indeks==tab[j]) licznik++;
            }
            if(licznik==0)
            {
                if(pom->nazwa<=napis)
                {
                    napis=pom->nazwa;
                    tab[i]=pom->indeks;
                    tmp=pom->indeks;
                }
            }

            pom=pom->nast;
         }
        pom1=pierwszy;
        while(pom1->indeks != tmp) pom1=pom1->nast;
        cout<<endl;
        cout<<"Indeks: "<<pom1->indeks<<endl;
        cout<<"Nazwa: "<<pom1->nazwa<<endl;
        cout<<"Opis: "<<pom1->opis<<endl;
        if(pom1->rok1==pom1->rok2) cout<<"Rok powstania: "<<pom1->rok1<<endl;
        else cout<<"Okres powstania: "<<pom1->rok1<<"-"<<pom1->rok2<<endl;
        cout<<"Waga: "<<pom1->waga<<" kg"<<endl;
        cout<<"Data dodania do zbioru: "<<pom1->dzien<<"."<<pom1->miesiac<<"."<<pom1->rok<<endl;
        cout<<"Stan: "<<pom1->stan<<endl;
        napis="~";
    }
}

void sort_data()
{
    eksponat* pom = NULL;
    eksponat* pom1 = pierwszy;
    int licznik=0;
    int x;
    int tmp;
    int mini=2147483647;
    int tab[liczba_eksponatow];
    for(int k=0; k<liczba_eksponatow; k++) tab[k]=0;
    for(int i=0; i<liczba_eksponatow; i++)
    {
        pom=pierwszy;
        while(pom != NULL)
        {
            x=10000*(pom->rok)+100*(pom->miesiac)+(pom->dzien);
            licznik=0;
            for(int j=0; j<liczba_eksponatow; j++)
            {
                if(pom->indeks==tab[j]) licznik++;
            }
            if(licznik==0)
            {
                if(x<=mini)
                {
                    mini=x;
                    tab[i]=pom->indeks;
                    tmp=pom->indeks;
                }
            }

            pom=pom->nast;
         }
        pom1=pierwszy;
        while(pom1->indeks != tmp) pom1=pom1->nast;
        cout<<endl;
        cout<<"Indeks: "<<pom1->indeks<<endl;
        cout<<"Nazwa: "<<pom1->nazwa<<endl;
        cout<<"Opis: "<<pom1->opis<<endl;
        if(pom1->rok1==pom1->rok2) cout<<"Rok powstania: "<<pom1->rok1<<endl;
        else cout<<"Okres powstania: "<<pom1->rok1<<"-"<<pom1->rok2<<endl;
        cout<<"Waga: "<<pom1->waga<<" kg"<<endl;
        cout<<"Data dodania do zbioru: "<<pom1->dzien<<"."<<pom1->miesiac<<"."<<pom1->rok<<endl;
        cout<<"Stan: "<<pom1->stan<<endl;
        mini=2147483647;
    }
}

void wyswietl_sort()
{
    int numer=0;
    cout<<"Wybierz numer odpowiadajacy operacji, ktora chcesz wykonac:"<<endl;
    cout<<"1. Sortowanie alfabetyczne wzgledem nazwy eksponatu"<<endl;
    cout<<"2. Sortowanie wzgledem daty dodania eksponatu do muzeum"<<endl;
    cout<<"Dowolny inny klawisz. Powrot"<<endl;
    cout<<"Podaj numer operacji: ";
    cin>>numer;
    cin.ignore();
    switch(numer)
    {
        case 1: sort_nazwa();
                break;
        case 2: sort_data();
                break;
    }
}

void wyswietl_ekspo()
{
    eksponat* pom = NULL;
    ekspozycja* pom1 = first;
    while(pom1 != NULL)
    {
        cout<<endl<<"*** Indeks ekspozycji: "<<pom1->id<<" ***"<<endl;
        cout<<endl<<"*** Nazwa ekspozycji: "<<pom1->nazwa_ekspo<<" ***"<<endl;
        cout<<endl<<"*** Opis ekspozycji: "<<pom1->opis_ekspo<<" ***"<<endl;
        cout<<endl<<"*** Sala: "<<pom1->sala<<" ***"<<endl;
        if(pom1->status==1) cout<<endl<<"*** Status: Aktywna ***"<<endl;
        else cout<<endl<<"*** Status: Zakonczona ***"<<endl;
        pom=pom1->next;
        while(pom != NULL)
        {
            cout<<"Indeks: "<<pom->indeks<<endl;
            cout<<"Nazwa: "<<pom->nazwa<<endl;
            cout<<"Opis: "<<pom->opis<<endl;
            if(pom->rok1==pom->rok2) cout<<"Rok powstania: "<<pom->rok1<<endl;
            else cout<<"Okres powstania: "<<pom->rok1<<"-"<<pom->rok2<<endl;
            cout<<"Waga: "<<pom->waga<<" kg"<<endl;
            cout<<"Data dodania do zbioru: "<<pom->dzien<<"."<<pom->miesiac<<"."<<pom->rok<<endl;
            cout<<"Stan: "<<pom->stan<<endl;
            pom = pom->nast;
        }
        pom1 = pom1->kolejny;
    }
}

void wyszukaj()
{

    eksponat* pom = pierwszy;
    string k;
    cout<<"Podaj nazwe szukanego eksponatu:"<<endl;
    cin>>k;
    cin.ignore();
    cout<<endl;
    cout<<"Wyszukane rekordy: "<<endl;
    cout<<endl;
    while(pom != NULL)
    {
       if(pom->nazwa.find(k)!=string::npos)
       {
            cout<<endl;
            cout<<"Indeks: "<<pom->indeks<<endl;
            cout<<"Nazwa: "<<pom->nazwa<<endl;
            cout<<"Opis: "<<pom->opis<<endl;
            if(pom->rok1==pom->rok2) cout<<"Rok powstania: "<<pom->rok1<<endl;
            else cout<<"Okres powstania: "<<pom->rok1<<"-"<<pom->rok2<<endl;
            cout<<"Waga: "<<pom->waga<<" kg"<<endl;
            cout<<"Data dodania do zbioru: "<<pom->dzien<<"."<<pom->miesiac<<"."<<pom->rok<<endl;
            cout<<"Stan: "<<pom->stan<<endl;
       }
       pom=pom->nast;
    }

}

void edytuj()
{
    int id_eksponatu, numer, ile, a, licznik=0, y;
    cout<<"Podaj indeks eksponatu, ktory chcesz edytowac: "<<endl;
    cin>>id_eksponatu;
    cin.ignore();
    eksponat* pom=pierwszy;
    while(pom->indeks != id_eksponatu)
    {
        pom = pom->nast;
    }
    cout<<"Podaj nazwe eksponatu : "<<endl;
        getline(cin,pom->nazwa);
        cout<<"Podaj opis eksponatu : "<<endl;
        getline(cin,pom->opis);
        while(licznik==0)
        {
            cout<<"Wybierz numer odpowiadajacy operacji, ktora chcesz wykonac:"<<endl;
            cout<<"1. Rok powstania"<<endl;
            cout<<"2. Przedzial lat"<<endl;
            cin>>numer;
            cin.ignore();
            switch(numer)
            {
                case 1: cout<<"Podaj rok powstania : "<<endl;
                        cin>>y;
                        cin.ignore();
                        if(y<2021)
                        {
                        pom->rok1=pom->rok2=y;
                        licznik++;
                        }
                        else blad();
                        break;
                case 2: cout<<"Podaj rok poczatkowy : "<<endl;
                        cin>>y;
                        cin.ignore();
                        if(y<2021)
                        {
                            pom->rok1=y;
                            cout<<"Podaj rok koncowy : "<<endl;
                            cin>>y;
                            cin.ignore();
                            if(y>(pom->rok1) && y<2021)
                            {
                                pom->rok2=y;
                                licznik++;
                            }
                            else blad();
                        }
                        else blad();
                        break;
            }
        }
        licznik=0;
        cout<<"Podaj wage eksponatu w kilogramach: "<<endl;
        cin>>pom->waga;
        cin.ignore();
        while(licznik<1)
        {
            cout<<"Podaj rok dodania eksponatu do zbioru (Muzeum powstalo 01.01.1950r.) : "<<endl;
            cin>>y;
            cin.ignore();
            if(y>1949 && y<2021)
            {
                pom->rok=y;
                licznik++;
            }
            else blad();
        }
        licznik=0;
        while(licznik<1)
        {
            cout<<"Podaj numer miesiaca, w ktorym dodano eksponat do zbioru: "<<endl;
            cin>>y;
            cin.ignore();
            if(y>=1 && y<=12)
            {
                pom->miesiac=y;
                licznik++;
            }
            else blad();
        }
        licznik=0;
        while(licznik<1)
        {
            cout<<"Podaj dzien miesiaca, w ktorym dodano eksponat do zbioru: "<<endl;
            cin>>y;
            cin.ignore();
            if(pom->miesiac==1 || pom->miesiac==3 || pom->miesiac==5 || pom->miesiac==7 || pom->miesiac==8 || pom->miesiac==10 || pom->miesiac==12)
            {
                if(y>=1 && y<=31)
                {
                    pom->dzien=y;
                    licznik++;
                }
                else blad();
            }
            if(pom->miesiac==4 || pom->miesiac==6 || pom->miesiac==9 || pom->miesiac==11)
            {
                if(y>=1 && y<=30)
                {
                    pom->dzien=y;
                    licznik++;
                }
                else blad();
            }
            if((pom->miesiac==2) && ((pom->rok%4==0 && pom->rok%100!=0) || pom->rok%400==0))
            {
                if(y>=1 && y<=29)
                {
                    pom->dzien=y;
                    licznik++;
                }
                else blad();
            }
            else if(pom->miesiac==2)
            {
                if(y>=1 && y<=28)
                {
                    pom->dzien=y;
                    licznik++;
                }
                else blad();
            }
        }
        licznik=0;
        while(licznik<1)
        {
            cout<<"Podaj stan eksponatu ( w skali 1-5 ) : "<<endl;
            cin>>y;
            cin.ignore();
            if(y>=1 && y<=5)
            {
                pom->stan=y;
                licznik++;
            }
            else blad();
        }
        zapis_do_pliku();
}

void usun_pierwszy()
{
    eksponat* pom;
    pom=pierwszy;
    if(pom)
    {
        pierwszy=pom->nast;
        delete pom;
        liczba_eksponatow--;
    }
}

void usun_ostatni()
{
    eksponat* pom = pierwszy;
    if( pom )
    {
        if( pom->nast )
        {
            while( pom->nast->nast ) pom = pom->nast;
            delete pom->nast;
            pom->nast = NULL;
            liczba_eksponatow--;
        }
    }
}

void usun()
{
    int id_eksponatu;
    cout<<"Podaj indeks eksponatu, ktory chcesz usunac: "<<endl;
    cin>>id_eksponatu;
    cin.ignore();
    if(id_eksponatu==pierwszy->indeks) usun_pierwszy();
    else if(id_eksponatu==ostatni->indeks) usun_ostatni();
    else
    {
        eksponat* pom=pierwszy;
        eksponat* do_usuniecia=pierwszy->nast;
        while((do_usuniecia->indeks)!=id_eksponatu)
        {
            pom=pom->nast;
            do_usuniecia=do_usuniecia->nast;
        }
        pom->nast=do_usuniecia->nast;
        delete do_usuniecia;
        liczba_eksponatow--;
    }
    zapis_do_pliku();
}

void dodaj_reczne()
{
    int numer,ile,a,licznik=0,y;
    //string wiersz;
    cout<<"Ile eksponatow chcesz dodac: "<<endl;;
    cin>>ile;
    cin.ignore();
    for(int i=1; i<=ile; i++)
    {
        eksponat *nowy = new eksponat;
        nowy->indeks=id_ostatniego_eksponatu+1;
        id_ostatniego_eksponatu++;
        liczba_eksponatow++;
        cout<<"Podaj nazwe eksponatu : "<<endl;
        getline(cin,nowy->nazwa);
        cout<<"Podaj opis eksponatu : "<<endl;
        getline(cin,nowy->opis);
        while(licznik==0)
        {
            cout<<"Wybierz numer odpowiadajacy operacji, ktora chcesz wykonac:"<<endl;
            cout<<"1. Rok powstania"<<endl;
            cout<<"2. Przedzial lat"<<endl;
            cin>>numer;
            cin.ignore();
            switch(numer)
            {
                case 1: cout<<"Podaj rok powstania : "<<endl;
                        cin>>y;
                        cin.ignore();
                        if(y<2021)
                        {
                        nowy->rok1=nowy->rok2=y;
                        licznik++;
                        }
                        else blad();
                        break;
                case 2: cout<<"Podaj rok poczatkowy : "<<endl;
                        cin>>y;
                        cin.ignore();
                        if(y<2021)
                        {
                            nowy->rok1=y;
                            cout<<"Podaj rok koncowy : "<<endl;
                            cin>>y;
                            cin.ignore();
                            if(y>(nowy->rok1) && y<2021)
                            {
                                nowy->rok2=y;
                                licznik++;
                            }
                            else blad();
                        }
                        else blad();
                        break;
            }
        }
        licznik=0;
        cout<<"Podaj wage eksponatu w kilogramach: "<<endl;
        cin>>nowy->waga;
        cin.ignore();
        while(licznik<1)
        {
            cout<<"Podaj rok dodania eksponatu do zbioru (Muzeum powstalo 01.01.1950r.) : "<<endl;
            cin>>y;
            cin.ignore();
            if(y>1949 && y<2021)
            {
                nowy->rok=y;
                licznik++;
            }
            else blad();
        }
        licznik=0;
        while(licznik<1)
        {
            cout<<"Podaj numer miesiaca, w ktorym dodano eksponat do zbioru: "<<endl;
            cin>>y;
            cin.ignore();
            if(y>=1 && y<=12)
            {
                nowy->miesiac=y;
                licznik++;
            }
            else blad();
        }
        licznik=0;
        while(licznik<1)
        {
            cout<<"Podaj dzien miesiaca, w ktorym dodano eksponat do zbioru: "<<endl;
            cin>>y;
            cin.ignore();
            if(nowy->miesiac==1 || nowy->miesiac==3 || nowy->miesiac==5 || nowy->miesiac==7 || nowy->miesiac==8 || nowy->miesiac==10 || nowy->miesiac==12)
            {
                if(y>=1 && y<=31)
                {
                    nowy->dzien=y;
                    licznik++;
                }
                else blad();
            }
            if(nowy->miesiac==4 || nowy->miesiac==6 || nowy->miesiac==9 || nowy->miesiac==11)
            {
                if(y>=1 && y<=30)
                {
                    nowy->dzien=y;
                    licznik++;
                }
                else blad();
            }
            if((nowy->miesiac==2) && ((nowy->rok%4==0 && nowy->rok%100!=0) || nowy->rok%400==0))
            {
                if(y>=1 && y<=29)
                {
                    nowy->dzien=y;
                    licznik++;
                }
                else blad();
            }
            else if(nowy->miesiac==2)
            {
                if(y>=1 && y<=28)
                {
                    nowy->dzien=y;
                    licznik++;
                }
                else blad();
            }
        }
        licznik=0;
        while(licznik<1)
        {
            cout<<"Podaj stan eksponatu ( w skali 1-5 ) : "<<endl;
            cin>>y;
            cin.ignore();
            if(y>=1 && y<=5)
            {
                nowy->stan=y;
                licznik++;
            }
            else blad();
        }
        nowy->nast=NULL;
        if(ostatni != NULL)
        {
            ostatni->nast=nowy;
        }
        else
        {
            pierwszy = nowy;
        }
        ostatni = nowy;
    }

}

void dodaj_automat()
{
    ifstream fin;
    fin.open("dane.txt");
    int ile,a;
    string wiersz;
    cout<<"Ile eksponatow chcesz dodac: "<<endl;
    cin>>ile;
    cin.ignore();
    for(int i=0; i<=id_ostatniego_eksponatu_z_bazy; i++)
    {
        for(int k=0; k<2; k++) getline(fin,wiersz);
    }
    for(int j=1; j<=ile; j++)
    {
        eksponat *nowy=new eksponat;
        nowy->indeks=id_ostatniego_eksponatu+1;
        id_ostatniego_eksponatu++;
        id_ostatniego_eksponatu_z_bazy++;
        liczba_eksponatow++;
        getline(fin,wiersz);
        nowy->nazwa=wiersz;
        getline(fin,wiersz);
        nowy->opis=wiersz;
        a=(rand()%5)+1;
        if(a==1 || a==2 || a==3)
        {
            nowy->rok1=(rand()%400)+1400;
            nowy->rok2=(rand()%80)+nowy->rok1+1;
        }
        else
        {
            nowy->rok1=nowy->rok2=(rand()%400)+1400;
        }
        nowy->waga=(float)(((rand()%200)+1.0)/10.0);
        nowy->rok=(rand()%71)+1950;
        nowy->miesiac=(rand()%12)+1;
        if(nowy->miesiac==1 || nowy->miesiac==3 || nowy->miesiac==5 || nowy->miesiac==7 ||  nowy->miesiac==8 || nowy->miesiac==10 || nowy->miesiac==12) nowy->dzien=(rand()%31)+1;
        if(nowy->miesiac==4 || nowy->miesiac==6 || nowy->miesiac==9 || nowy->miesiac==11) nowy->dzien=(rand()%30)+1;
        if((nowy->miesiac==2) && ((nowy->rok%4==0 && nowy->rok%100!=0) || nowy->rok%400==0)) nowy->dzien=(rand()%29)+1;
        else nowy->dzien=(rand()%28)+1;
        nowy->stan=a;
        nowy->nast=NULL;
        if(ostatni != NULL)
        {
            ostatni->nast=nowy;
        }
        else
        {
            pierwszy = nowy;
        }
        ostatni = nowy;
    }
}

void dodaj()
{
    int numer=0;
    cout<<"Wybierz numer odpowiadajacy operacji, ktora chcesz wykonac:"<<endl;
    cout<<"1. Dodanie reczne"<<endl;
    cout<<"2. Dodanie automatyczne"<<endl;
    cout<<"Dowolny inny klawisz. Powrot"<<endl;
    cout<<"Podaj numer operacji: ";
    cin>>numer;
    cin.ignore();
    switch(numer)
    {
        case 1: dodaj_reczne();
                break;
        case 2: dodaj_automat();
                break;
    }
    zapis_do_pliku();
}

int main()
{
    cout << "Witaj w muzeum!" << endl;
    int numer=0;
    while(numer!=13)
    {
        cout<<endl;
        cout<<"Wybierz numer odpowiadajacy operacji, ktora chcesz wykonac:"<<endl;
        cout<<"1. Wyswietlenie wszystkich eksponatow"<<endl;
        cout<<"2. Wyswietlenie posortowanej listy eksponatow"<<endl;
        cout<<"3. Dodanie eksponatow"<<endl;
        cout<<"4. Wyszykiwanie eksponatu"<<endl;
        cout<<"5. Edycja eksponatu"<<endl;
        cout<<"6. Usuniecie eksponatu"<<endl;
        cout<<"7. Utworzenie ekspozycji"<<endl;
        cout<<"8. Wyswietlenie ekspozycji"<<endl;
        cout<<"9. Dodanie eksponatu do ekspozycji"<<endl;
        cout<<"10. Usuniecie eksponatu z ekspozycji"<<endl;
        cout<<"11. Zmiana statusu ekspozycji"<<endl;
        cout<<"12. Usuniecie ekspozycji"<<endl;
        cout<<"13. Zakonczenie dzialania programu"<<endl;
        cout<<"Podaj numer operacji: ";
        cin>>numer;
        cin.ignore();
        switch(numer)
        {
            case 1: wyswietl();
                    break;
            case 2: wyswietl_sort();
                    break;
            case 3: dodaj();
                    break;
            case 4: wyszukaj();
                    break;
            case 5: edytuj();
                    break;
            case 6: usun();
                    break;
            case 7: utworz_ekspo();
                    break;
            case 8: wyswietl_ekspo();
                    break;
            case 9: dodaj_do_ekspo();
                    break;
            case 10: usun_z_ekspo();
                    break;
            case 11: status();
                    break;
            case 12: usun_ekspo();
                    break;
            case 13: break;
        }
    }
    eksponat* pom = pierwszy;
    while(pierwszy != NULL)
    {
        pom = pierwszy->nast;
        delete pierwszy;
        pierwszy = pom;
    }
    ekspozycja* pom1 = first;
    while(pom1 != NULL)
    {
        pom=first->next;
        while(first->next != NULL)
        {
            pom = first->next->nast;
            delete first->next;
            first->next = pom;
        }
        pom1=pom1->kolejny;
    }
    pom1 = first;
    while(first != NULL)
    {
        pom1 = first->kolejny;
        delete first;
        first = pom1;
    }
    return 0;
}
