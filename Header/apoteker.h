#ifndef APOTEKER_H
#define APOTEKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include "interli.h"

using namespace std;

void Loadhasildokter();
void MenuApoteker();
void Menureadapoteker();

struct SalinanResep
{
    string NamaPasien;
    string NamaObat;
    string Satuan;
    string Expired;
    string DosisObat;
    int Jumlah;
};

struct HasilAnalisiDokter
{
    string nama;
    string keluhan;
    string hasil;
};

const int Max_data = 100;
SalinanResep listResep[Max_data];
HasilAnalisiDokter listData[Max_data];
int counted = 0;
int Jumlah = 0;
int banyakOpsiApoteker = 3;



void Showprescription(SalinanResep listResep[], int counted)
{
    system("cls");
    if (counted == 0)
    {
        cout << "====================" << endl;
        cout << "   Data Kosong    " << endl;
        cout << "====================";
        getch();
        cout << endl;
        fflush(stdin);
        Menureadapoteker();
    }
    cout << "Daftar :\n";
    cout << "No\tNama Pasien\t\tNama Obat\t\tSatuan\t\tExpired\t\tDosis Obat\t\tJumlah\n";
    for (int i = 0; i < counted; i++)
    {
        cout << i + 1 << "\t  " << listResep[i].NamaPasien << "\t\t\t";
        cout << listResep[i].NamaObat << "\t\t" << listResep[i].Satuan;
        cout << "\t\t" << listResep[i].Expired << "\t\t" << listResep[i].DosisObat;
        cout << "\t\t" << listResep[i].Jumlah << endl;
    }
}

void Showhasildokter(HasilAnalisiDokter listData[], int Jumlah)
{
    system("cls");
    if (Jumlah == 0)
    {
        cout << "====================" << endl;
        cout << "    Data Kosong     " << endl;
        cout << "====================";
        getch();
        cout << endl;
        Menureadapoteker();
    }
    cout << "Hasil Analisis:\n";
    cout << "No\tNama\t\tKeluhan\t\t Hasil\n";
    for (int i = 0; i < Jumlah; i++)
    {
        cout << i + 1 << "\t" << listData[i].nama << "\t\t";
        cout << listData[i].keluhan << "\t\t " << listData[i].hasil << endl;
    }
}

void Savetofiles(SalinanResep listResep[], int counted)
{
    ofstream outfile("Database/Dosis_Pasien.csv");
    if (!outfile)
    {
        cout << "Gagal membuka file Data_Pasien." << endl;
        return;
    }

    outfile << "Nama Pasien,Nama Obat,Satuan,Expired,Dosis Obat,Jumlah" << endl;

    for (int i = 0; i < counted; i++)
    {
        fflush(stdin);
        outfile << listResep[i].NamaPasien << "/";
        outfile << listResep[i].NamaObat << "/";
        outfile << listResep[i].Satuan << "/";
        outfile << listResep[i].Expired << "/";
        outfile << listResep[i].DosisObat << "/";
        outfile << listResep[i].Jumlah << endl;
        fflush(stdin);
    }
}

void Date(tm &date, SalinanResep listResep[], int counted)
{
    cout << "Masukkan tanggal Expired (DD-MM-YYYY) >>  ";
    string input;
    getline(cin, input);
    istringstream ss(input);
    ss >> get_time(&date, "%d-%m-%Y");

    if (ss.fail())
    {
        cout << "Format tanggal tidak valid!";
        getch();
        cout << endl;
        fflush(stdin);
        Date(date, listResep, counted);
    }
    else
    {
        time_t time = mktime(&date);
        stringstream ss;
        ss << put_time(localtime(&time), "%d %b %Y");
        listResep[counted].Expired = ss.str();
    }
}

void Searchnamepasien(HasilAnalisiDokter listData[], int Jumlah)
{
    string Searchname;
    cout << "\nMasukkan Nama Pasien >> ";
    getline(cin, Searchname);
    fflush(stdin);
    cout << "Daftar Task:\n";
    cout << "No\tNama\t\tKeluhan\t\tHasil\n";
    bool found = false;
    for (int i = 0; i < Jumlah; i++)
    {
        if (listData[i].nama == Searchname)
        {
            cout << i + 1 << "\t" << listData[i].nama << "\t\t";
            cout << listData[i].keluhan << "\t\t " << listData[i].hasil << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Data Pasien Tidak Ditemukan" << endl;
        cout << "Kembali Ke Menu APoteker(Tekan Enter)";
        getch();
        cout << endl;
        fflush(stdin);
        MenuApoteker();
    }
    fflush(stdin);
}

void Addprescription(SalinanResep listResep[], HasilAnalisiDokter listData[], int counted, int Jumlah)
{
    string input;
    system("cls");
    fflush(stdin);
    Searchnamepasien(listData,Jumlah);
    cout << endl;
    cout << "Salinan Resep Obat:"<< endl;
    cout << "\nNama Pasien>> "; getline(cin,listResep[counted].NamaPasien);
    cout << "Nama Obat>> "; getline(cin,listResep[counted].NamaObat);
    cout << "Jenis Obat (Tablet/Kapsul/Pil/Serbuk/ObatCair)>> ";getline(cin, input);
    if (input != "Tablet" && input != "tablet" && input != "Kapsul" && input != "kapsul" 
        && input !="Pil" && input != "pil" && input != "Serbuk" && input != "serbuk" && input != "ObatCair" && input != "obatcair")
    {
        cout << "Masukkan Jenis Obat yang benar!(Tekan Enter)";
        getch();cout << endl;
        fflush(stdin);
        Addprescription(listResep,listData,counted, Jumlah);
    }
    listResep[counted].Satuan = input;
    Date(date,listResep,counted);
    cout << "Dosis Obat>> "; getline(cin, listResep[counted].DosisObat);
    try
    {
        cout << "Jumlah Obat>> "; getline(cin,input);
        listResep[counted].Jumlah = stoi(input);
        if (listResep[counted].Jumlah < 1)
        {
            cout << "Jumlah salah"; getch();cout<<endl;fflush(stdin);
            Addprescription(listResep,listData,counted, Jumlah);
        }
    }
    catch(std::invalid_argument& e)
    {
        cout<<"Inputan harus Integer(Tekan Enter)"; getch(); cout << endl;fflush(stdin);
        Addprescription(listResep,listData,counted, Jumlah);
    }
    fflush(stdin);
    counted++;
    Savetofiles(listResep, counted);

    cout << "\nData berhasil disimpan ke dalam Database\n";
    cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;fflush(stdin);
    MenuApoteker();
        
}


void Loaddataresep()
{
    ifstream files;
    files.open("Database/Dosis_Pasien.csv", ios::in);
    if (!files.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string lines;
    getline(files, lines);
    counted = 0;
    while (getline(files, lines))
    {
        stringstream ss(lines);
        string Pasien,Obat,Satuan,Expired,Jumlah,Dosis;
        getline(ss, Pasien, '/');
        getline(ss, Obat, '/');
        getline(ss, Satuan, '/');
        getline(ss, Expired, '/');
        getline(ss, Dosis, '/');
        getline(ss, Jumlah, '/');
        

        listResep[counted].NamaPasien = Pasien;
        listResep[counted].NamaObat = Obat;
        listResep[counted].Satuan = Satuan;
        listResep[counted].Expired = Expired;
        listResep[counted].DosisObat = Dosis;
        try
        {
            listResep[counted].Jumlah = stoi(Jumlah);
        }
        catch (std::invalid_argument &e)
        {
            cout << "Data pada file rusak" << endl;
            files.close();
            return;
        }
        counted++;
        if (counted == Max_data)
        {
            break;
        }
    }
    files.close();
}

void Loadhasildokter()
{
    ifstream file;
    file.open("Database/Data_Dokter.csv", ios::in);
    if (!file.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(file, line);
    Jumlah = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string Namapasien,Keluhan,Hasil;
        getline(ss, Namapasien, '/');
        getline(ss, Keluhan, '/');
        getline(ss, Hasil, '/');
        

        listData[Jumlah].nama = Namapasien;
        listData[Jumlah].keluhan = Keluhan;
        listData[Jumlah].hasil = Hasil;
        Jumlah++;
        if (Jumlah == Max_data)
        {
            break;
        }
    }
    file.close();
}

void SelectionSort(SalinanResep listResep[], int counted)
{
    for (int i = 0; i < counted - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < counted; j++)
        {
            if (listResep[j].NamaPasien < listResep[min_index].NamaPasien)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(listResep[min_index], listResep[i]);
        }
    }
}

void MenuApoteker()
{
    Loaddataresep();
    Loadhasildokter();
    system("cls");
    string deskripsi_menu[3] = {"Tambah Salinan Resep","List","Exit"};
    string header_menu = "Menu Apoteker";
    create_menus(banyakOpsiApoteker, deskripsi_menu, header_menu);

    if (current_selection == 0)
    {
        Addprescription(listResep, listData , counted, Jumlah);
        MenuApoteker();  
    }
    else if (current_selection == 1)
    {
        Menureadapoteker();
        MenuApoteker();
    }
    else
    {
        cout << "Keluar dari program.\n";
        exit(0);
    }
}

void Menureadapoteker()
{
    system("cls");
    string deskripsi_menu[3] = {"Hasil Analisis Dokter","List Salinan Resep","Kembali"};
    string header_menu = "Menu Read";
    create_menus(banyakOpsiApoteker, deskripsi_menu, header_menu);

    if (current_selection == 0)
    {
        Showhasildokter(listData, Jumlah);
        cout<<"Kembali ke Menu Read, Enter untuk kembali";getch();cout<<endl;
        Menureadapoteker();
    }
    else if (current_selection == 1)
    {
        SelectionSort(listResep, counted);
        Showprescription(listResep, counted);
        cout<<"Kembali ke Menu Read, Enter untuk kembali";getch();cout<<endl;
        Menureadapoteker();
    }
    else 
    {
        MenuApoteker();
    }
}

#endif