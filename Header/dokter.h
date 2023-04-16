#ifndef DOKTER_H
#define DOKTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <filesystem>
#include <cstring>
#include "interli.h"
using namespace std;
using namespace filesystem;

int indexDataDokter = 0, banyakOpsiDokter = 3;

struct Pasien
{
    string nama;
    int umur;
    string goldar;
    string gender;
    string keluhan;
    string waktutemu;
    string status;
};

struct HasilAnalisis
{
    string nama;
    string keluhan;
    string hasil;
};

HasilAnalisis hasil[100];
Pasien listPasien[100];
string nama;

void MenuReadDokter();

void fileChecker()
{
    path path = current_path();
    if (!exists(path / "Database/Data_Dokter.csv"))
    {
        ofstream DataDokter;
        DataDokter.open("Database/Data_Dokter.csv");
        DataDokter << "Nama, Keluhan, Hasil" << endl;
        DataDokter.close();
    }
}

void csvToArray()
{
    ifstream dataPasien("Database/Data_Pasien.csv");
    if (dataPasien.is_open())
    {
        string baris;
        getline(dataPasien, baris);

        while (getline(dataPasien, baris))
        {
            stringstream ss(baris);
            string field;
            int fieldIndex = 0;

            Pasien pasien;

            while (getline(ss, field, ','))
            {
                switch (fieldIndex)
                {
                case 0:
                    pasien.nama = field;
                    break;
                case 1:
                    pasien.umur = stoi(field);
                    break;
                case 2:
                    pasien.goldar = field;
                    break;
                case 3:
                    pasien.gender = field;
                    break;
                case 4:
                    pasien.keluhan = field;
                    break;
                case 5:
                    pasien.waktutemu = field;
                    break;
                case 6:
                    pasien.status = field;
                    break;
                }

                fieldIndex++;
            }

            listPasien[indexDataDokter] = pasien;
            indexDataDokter++;
        }

        dataPasien.close();
    }
}

void ReadDataPasien()
{
    int nomorData = 1;
    cout << "No\tNama\t\tUmur\t\tGol.Darah\t\tGender\t\tKeluhan\t\tWaktu Temu\t\tStatus\n";
    for (int i = 0; i < indexDataDokter; i++)
    {
        if (listPasien[i].umur != 0)
        {
            cout << 2 + i - nomorData << "\t" << listPasien[i].nama << "\t\t" << listPasien[i].umur << "\t\t" << listPasien[i].goldar << "\t\t" << listPasien[i].gender << "\t\t" << listPasien[i].keluhan << "\t\t" << listPasien[i].waktutemu << "\t\t" << listPasien[i].status << endl;
        }
        else
        {
            nomorData++;
            continue;
        }
    }

    cout << "Tekan ENTER untuk kembali.";
    memset(listPasien, 0, sizeof(listPasien));
    fflush(stdin);
    getch();
}

void CreateDokter()
{
    csvToArray();
    cout << endl;
    cout << "Masukkan nama pasien: ";
    getline(cin, nama);
    fflush(stdin);
    cout << endl;

    bool found = false;
    for (int i = 0; i < indexDataDokter; i++)
    {
        if (listPasien[i].nama == nama)
        {
            ofstream DataDokter;
            DataDokter.open("Database/Data_Dokter.csv", ios::app);
            hasil[i].nama = listPasien[i].nama;
            hasil[i].keluhan = listPasien[i].keluhan;
            cout << "Masukkan hasil analisis: ";
            getline(cin, hasil[i].hasil);
            fflush(stdin);
            DataDokter << hasil[i].nama << "," << hasil[i].keluhan << "," << hasil[i].hasil << endl;
            DataDokter.close();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Nama pasien tidak ditemukan.";
    }
}



void ReadDokter()
{
    int nomorData = 1;
    cout << "No\tNama\t\tKeluhan\t\tHasil\n";
    for (int i = 0; i < indexDataDokter; i++)
    {
        if (hasil[i].nama != "")
        {
            cout << 2 + i - nomorData << "\t" << hasil[i].nama << "\t\t" << hasil[i].keluhan << "\t\t" << hasil[i].hasil << endl;
        }
        else
        {
            nomorData++;
            continue;
        }
    }

    cout << "Tekan ENTER untuk kembali.";
    getch();
}

void MenuDokter()
{
    fileChecker();
    csvToArray();
    system("cls");
    string deskripsi_menu[3] = {"Create", "Read", "Back"};
    string header_menu = "Menu Dokter";
    create_menus(banyakOpsiDokter, deskripsi_menu, header_menu);

    if (current_selection == 0)
    {
        ReadDataPasien();
        CreateDokter();
        MenuDokter();
    }
    else if (current_selection == 1)
    {
        MenuReadDokter();
        MenuDokter();
    }
    else
    {
        exit(0);
    }

    getch();
    MenuDokter();
}

void MenuReadDokter()
{
    string deskripsiMenuDokter[3] = {"Data Pasien", "Data Hasil Analisis", "Back"};
    string headerMenuDokter = "Menu Read Dokter";
    create_menus(banyakOpsiDokter, deskripsiMenuDokter, headerMenuDokter);

    if (current_selection == 0)
    {
        ReadDataPasien();
        MenuReadDokter();
    }
    else if (current_selection == 1)
    {
        ReadDokter();
        MenuReadDokter();
    }
    else
    {
        MenuDokter();
    }
}

#endif
