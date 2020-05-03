#include<iostream>
#include<string>
#include<algorithm>
#include<utility>
#include<numeric>
using namespace std;

struct BankovniRacun
{
    string ime;
    unsigned long long int id_racuna;
    double saldo;
};
struct brRacuna
{
    unsigned long long int id_racuna;
    int indeks;
};

int brKlijenata=0;

bool postoji(BankovniRacun baza[],unsigned long long int n)
{
    for(int i=0;i<brKlijenata;i++)
    {
        if(baza[i].id_racuna==n)
        {
            return true;
        }
    }
    return false;
}

void novi_racun(BankovniRacun baza[])
{
    unsigned long long int n;
    cout << "Unesite jedinstveni 10 - ero znamenkasti broj racuna: ";
    while(1)
    {
        cin >> n;
        try
        {
            if((n<=1000000000) ||( n>9999999999))
            {
                throw "Broj nema 10 znamenki";
            }
            else if (postoji(baza,n)==true)
            {
                throw "Broj racuna mora biti jedinstven";
            }
            else
            {
                break;
            }
        }
        catch (const char* msg)
        {
            cout<< msg << endl;
            cout<<"Ponovo unesite broj racuna: ";
            cin>>n;
        }
    }
    baza[brKlijenata].id_racuna = n;
    cout << "Unesite prezime i ime: ";
    cin.ignore();
    getline(cin,baza[brKlijenata].ime);
    cout<< "Unesite saldo: ";
    cin >> baza[brKlijenata].saldo;
    brKlijenata++;
}

bool negativan(double broj)
{
    if(broj<0)
        return true;
    return false;
}
bool tekuci(unsigned long long int id)
{
    if(id/1000000000 == 32)
    {
        return true;
    }
    return false;
}

void ispis_svega(BankovniRacun baza[],double saldo_temp[])
{
    cout << "Slijede racuni " << endl << "----------------------------------------" << endl << "----------------------------------------"<< endl;
    for(int i = 0; i < brKlijenata;i++)
    {
        cout << "Racun broj: " << i << endl;
        cout << "Broj racuna: " << baza[i].id_racuna << endl;
        cout << "Prezime i ime: " << baza[i].ime  << endl;
        cout << "Stanje na racunu: " << baza[i].saldo << endl;
        cout << "----------------------------------------" << endl;
    }
    cout << "Suma svih stanja racuna: " << accumulate(saldo_temp,saldo_temp+brKlijenata,0) << endl;
    cout << "Prezime i ime racuna s najvecim stanjem na racunu je: " << baza[max_element(saldo_temp,saldo_temp+brKlijenata)-saldo_temp].ime << endl;
    cout << "Broj racuna s negativnim stanjem na racunu je: " << count_if(saldo_temp,saldo_temp+brKlijenata, negativan) << endl;
    cout << "Broj racuna s tekucim racunima je: " << count_if(saldo_temp,saldo_temp+brKlijenata, tekuci) << endl;
}

bool ispis_podataka(BankovniRacun baza[],string pretraga)
{
    int broj = 0;
    for(int i = 0; i < brKlijenata; i++)
    {
        if(baza[i].ime == pretraga)
        {
            cout << "Broj racuna: " << baza[i].id_racuna << endl << "Saldo: " << baza[i].saldo << endl;
            broj++;
        }
    }
    
    if(broj == 0)
        return false;
    
    return true;
    
}

void ispis_sortirano(BankovniRacun baza[], string imena[])
{
    cout << "Racuni: " << endl;
    for(int i=0; i < brKlijenata; i++)
    {
        for(int j=0; j < brKlijenata; j++)
        {
            if(imena[i] == baza[j].ime)
            {
                cout << baza[j].ime << endl << "Broj racuna: " << baza[j].id_racuna << endl << "Saldo: " << baza[j].saldo << endl;
            }
        }
    }
}

bool binary(brRacuna temp_id[],int l,int r, unsigned long long int broj,int &indeks)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        // Check if x is present at mid
        if (temp_id[m].id_racuna == broj)
        {
            indeks = temp_id[m].indeks;
            return true;
        }
        
        if (temp_id[m].id_racuna < broj)
            l = m + 1;
        else
            r = m - 1;
    }
    return false;
}



int main()
{
    int izbor;
    BankovniRacun *baza = new BankovniRacun [1000];
    brRacuna temp_id[1000];
    while(1)
    {
        system("PAUSE");
        system("cls");
        cout << "Unesite broj kako bi odabrali neki od sljedecih izbornika"<<endl;
        cout << "---> 1 = Unos novog racuna" << endl << "---> 2 = Ispis svih podataka" << endl << "---> 3 = Pretraga prema prezimenu i imenu"<<endl;
        cout << "---> 4 = Brisanje racuna" << endl << "---> 5 = Izmjena podataka prema broju računa" << endl << "---> 6 = Ispis sortirano prema imenu i prezimenu" << endl << "---> 7 = Izlaz iz programa"<<endl;
        cout << "Unesite broj: ";
        cin >> izbor;
        
        if(izbor == 1)
        {
            cout << "Odabrali ste unos novog racuna"<<endl;
            novi_racun(baza);
        }
        else if(izbor == 2)
        {
            cout << "Odabrali ste ispis svih podataka" << endl;
            double saldo_temp[1000];
            for(int i = 0;i < brKlijenata;i++)
            {
                saldo_temp[i]=baza[i].saldo;
            }
            ispis_svega(baza,saldo_temp);
        }
        else if(izbor == 3)
        {
            cout << "Odabrali ste pretrazivanje po prezimenu i imenu" << endl;
            cout << "Unesite prezime i ime koje pretrazujete: ";
            string pretraga;
            cin.ignore();
            getline(cin, pretraga);
            if(ispis_podataka(baza,pretraga)==false)
            {
                cout << "Ne postoji racun s takvim prezimenom i imenom" << endl;
            }
        }
        else if(izbor == 4)
        {
            cout << "Odabrali ste brisanje racuna" << endl;
            unsigned long long int id_racun;
            cout << "Unesite broj racuna kojeg zelite izbrisati: ";
            cin >> id_racun;
            int i;
            for(i = 0; i < brKlijenata; i++)
            {
                if(baza[i].id_racuna == id_racun)
                {
                    for(int j = i; j < brKlijenata - 1; j++)
                    {
                        baza[j].id_racuna = baza[j+1].id_racuna;
                        baza[j].ime = baza[j+1].ime;
                        baza[j].saldo = baza[j+1].saldo;
                    }
                    brKlijenata--;
                    break;
                }
            }
            if(i==brKlijenata)
                cout << "Trazenog racuna nema." << endl;
        }
        else if(izbor == 5)
        {
            cout << "Odabrali ste mijenjanje podataka" << endl;
            cout << "Unesite broj racuna kojem zelite promijeniti podatke: ";
            unsigned long long int broj;
            cin >> broj;
            int indeks;
            for(int i = 0; i < brKlijenata; i++)
            {
                temp_id[i].id_racuna = baza[i].id_racuna;
                temp_id[i].indeks = i;
            }
            for (int i = 0; i < brKlijenata-1; i++)
                for (int j = 0; j < brKlijenata-i-1; j++)
                    if (temp_id[j].id_racuna > temp_id[j+1].id_racuna)
                    {
                        unsigned long long int temp_brracuna = temp_id[j].id_racuna;
                        int temp_indeks = temp_id[j].indeks;
                        temp_id[j].id_racuna=temp_id[j+1].id_racuna;
                        temp_id[j].indeks=temp_id[j+1].indeks;
                        temp_id[j+1].id_racuna = temp_brracuna;
                        temp_id[j+1].indeks = temp_indeks;
                    }
            if(binary(temp_id,0,brKlijenata-1,broj,indeks) == true)
            {
                cout << "Pronasli smo racun" << endl << baza[indeks].ime << endl << "Saldo: " << baza[indeks].saldo << endl;
                cout << "Za promjenu podataka racuna odaberite sto zelite promijeniti" << endl;
                cout << "---> 1 = Promjena Prezimena i Imena" << endl;
                cout << "---> 2 = Promjena Salda" << endl;
                cout << "Unesite broj: " ;
                int broj_prom;
                cin >> broj_prom;
                if(broj_prom == 1)
                {
                    cout << "Unesite novo Prezime i ime: ";
                    cin.ignore();
                    getline(cin,baza[indeks].ime);
                    cout << "Novo Prezime i ime je: " << baza[indeks].ime << endl;
                }
                else if(broj_prom == 2)
                {
                    cout << "Unesite novi saldo: ";
                    cin >> baza[indeks].saldo;
                    cout << "Novi saldo je: " << baza[indeks].saldo << endl;
                }
                else
                {
                    cout << "Krivi unos" << endl;
                    cout << "Sve sad ispocetka" << endl;
                }
            }
            else
            {
                cout << "Ne postoji racun s tim brojem" << endl;
            }
            
            
            
        }
        else if(izbor == 6)
        {
            cout << "Odabrali ste ispis svih podataka sortirano po prezimenu i imenu" << endl;
            string imena[1000];
            for(int i = 0; i < brKlijenata; i++)
            {
                imena[i] = baza[i].ime;
            }
            sort(imena,imena+brKlijenata);
            ispis_sortirano(baza,imena);
        }
        else if(izbor == 7)
        {
            cout << "Odabrali ste izlaz iz programa" << endl;
            cout << "Kako bi izasli iz programa stisnite bilo koji klik na tipkovnici" << endl;
            break;
        }
        else
        {
            cout << "Krivi unos" << endl;
        }
    }
    cout << "Dovidenja" << endl;
    return 0;
}
