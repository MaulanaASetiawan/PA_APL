#ifndef APOTEKER_H
#define APOTEKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream> 
#include <windows.h>
#include <iomanip>
using namespace std;

void loadDataPasien(); void MenuApoteker();

struct SalinanResep
{
    string NamaPasien;
    string NamaObat;
    string Satuan;
    string Expired ;
    string DosisObat;
    int Jumlah;
};

struct HasilAnalisis
{
    string nama;
    string keluhan;
    string hasil;
};

const int max_task = 100;
SalinanResep listResep[max_task];
HasilAnalisis listData[max_task];
int count = 0;
string Searchname;
// int indexData = 0;


void Showresep(SalinanResep list[], int count)
{
    system("cls");
    if (count == 0)
    {
        cout << "====================" << endl
             << "   Data Kosong    " << endl
             << "====================";getch();cout << endl;
        MenuApoteker();
    }
    cout << "Daftar :\n";
    cout << "No\tNama Pasien\t\tNama Obat\t\tSatuan\t\tExpired\t\tDosis Obat\t\tJumlah\n";
    for (int i = 0; i < count; i++)
    {
        cout << i+1 << "\t  " << list[i].NamaPasien << "\t\t\t" 
             << list[i].NamaObat << "\t\t" << list[i].Satuan 
             << "\t\t" << list[i].Expired <<"\t\t"<< list[i].DosisObat 
             << "\t\t" << list[i].Jumlah <<endl;
    }
}

void showHasilDokter(HasilAnalisis list[], int count)
{
    system("cls");
    if (count == 0)
    {
    cout << "====================" << endl
         << "    Data Kosong     " << endl
         << "====================";getch();cout << endl;
    MenuApoteker();
}
    cout << " Masukkan Nama Pasien >> ";getline(cin, Searchname);
    cout << "Daftar Task:\n";
    cout << "No\tNama\t\tUmur\t\tGol.Darah\t\tGender\t\tKeluhan\t\tWaktu Temu\t\tStatus\n";
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (list[i].nama == Searchname)
        {
            cout << i+1 << "\t" << list[i].nama << "\t\t"
            << list[i].keluhan << "\t\t " << list[i].hasil << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {   
        cout << "Data Pasien Tidak Ditemukan" << endl;
    }
}

void saveToFile(SalinanResep list[], int count)
{
    ofstream outfile("Database/Dosis_Pasien.csv");
    if (!outfile)
    {
        cout << "Gagal membuka file Data_Pasien." << endl;
        return;
    }
    
    outfile << "Nama Pasien,Nama Obat,Satuan,Expired,Dosis Obat,Jumlah" << endl;

    for (int i = 0; i < count; i++)
    {
        outfile << list[i].NamaPasien << ",";
        outfile << list[i].NamaObat << ",";
        outfile << list[i].Satuan << ",";
        outfile << list[i].Expired << ",";
        outfile << list[i].Jumlah << ",";
        outfile << list[i].DosisObat << endl;
    }
}

void addTask(SalinanResep list[], int& count)
{
    string input;
    cout << "\nNama Pasien>> "; getline(cin,list[count].NamaPasien);
    cout << "Nama Obat>> "; getline(cin,list[count].NamaObat);
    cout << "Satuan/Jenis Obat>> "; getline(cin, list[count].Satuan);
    cout << "Expired Obat>> "; getline(cin, list[count].Expired);
    cout << "Dosis Obat>> "; getline(cin, list[count].DosisObat);
    try
    {
        cout << "Jumlah Obat>> "; getline(cin,input);
        list[count].Jumlah = stoi(input);
        if (list[count].Jumlah < 1)
        {
            cout << "Harga salah"; getch();cout<<endl;
            addTask(list,count);
        }
    }
    catch(std::invalid_argument& e)
    {
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        addTask(list,count);
    }
    count++;
    saveToFile(list, count);

    cout << "\nData berhasil disimpan ke dalam Database\n";
    cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;
    MenuApoteker();
        
}

void loadDataResep()
{
    ifstream file;
    file.open("Database/Dosis_Pasien.csv",ios::in);
    if (!file.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(file, line);
    count = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string NamaPasien,NamaObat,Satuan,Expired,Jumlah,DosisObat;
        getline(ss, NamaPasien, ',');
        getline(ss, NamaObat, ',');
        getline(ss, Satuan, ',');
        getline(ss, Expired, ',');
        getline(ss, Jumlah, ',');
        getline(ss, DosisObat, ',');
        
        try
        {
            listResep[count].Jumlah = stoi(Jumlah);
        }
        catch (std::invalid_argument& e)
        {
            cout << "Data pada file rusak" << endl;
            file.close();
            return;
        }

        listResep[count].NamaPasien = NamaPasien;
        listResep[count].Satuan = Satuan;
        listResep[count].Expired = Expired;
        listResep[count].NamaObat = NamaObat;
        listResep[count].DosisObat = DosisObat;
        count++;
        if (count == max_task)
        {
            break;
        }
    }
    file.close();
}

void loadHasilDokter(){
    ifstream file;
    file.open("Database/Data_Dokter.csv",ios::in);
    if (file.is_open())
    {
        string line;
        getline(file, line);
        count = 0;

        while (getline(file, line))
        {
            stringstream ss(line);
            string field;

            HasilAnalisis get;
            int fieldIndex = 0; 

            while (getline(ss, field, ','))
            {
                switch (fieldIndex)
                {
                case 0:
                    get.nama = field;
                    break;
                case 1:
                    get.keluhan = stoi(field);
                    break;
                case 2:
                    get.hasil = field;
                    break; 
                }
                fieldIndex++;

            }
            listData[count] = get;
            count++;
            if (count == max_task)
            {
            break;
            }
        }
    }
        file.close();
}



void SelectionSort(SalinanResep list[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < count; j++) {
            if (list[j].NamaPasien < list[min_index].NamaPasien) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(list[min_index], list[i]);
        }
    }
}

void MenuShow()
{
    fflush(stdin);
    int pilih_menu = 0;
    int count_menu = 3;
    string desc_MenuShow[3] = {"[1] List Data Pasien","[2] List Salinan Resep","[0] Kembali"};
    string header_MenuShow = "Menu Show";

    while (true)
    {
        system("cls");
        cout << setw((80 - header_MenuShow.size()) / 2) << "" << "===============================" << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
        cout << setw((80 - header_MenuShow.size()) / 2) << "";
        cout << "---------- " << header_MenuShow << " ----------" << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
        cout << setw((80 - header_MenuShow.size()) / 2) << "" << "===============================" << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
        for(int i = 0; i < count_menu; i++)
        {
            if (i == pilih_menu)
            {
                cout << setw((80 - header_MenuShow.size()) / 2) << "";
                cout << ">>" << "  " << desc_MenuShow[i] << "  " << " <<"; 
                cout << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
            }
            else
            {
                cout << setw((80 - header_MenuShow.size()) / 2) << "";
                cout << "  " << "  " << desc_MenuShow[i] << "  " << "  "; 
                cout << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
            }
        }

        char keys = getch();
        if (keys == 80)
        {
            if(pilih_menu < count_menu -1)
            {
                pilih_menu++;
            }
            else
            {
                pilih_menu = 0;
            }
        }
        else if (keys == 72)
        {
            if (pilih_menu > 0)
            {
                pilih_menu--;
            }
            else
            {
                pilih_menu = count_menu-1;
            }
        }
        else if(keys == 13)
        {
            try
            {
                if (pilih_menu == 0)
                {
                    loadHasilDokter();
                    showHasilDokter(listData, count);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                }
                else if (pilih_menu == 1)
                {
                    loadDataResep();
                    SelectionSort(listResep, count);
                    Showresep(listResep, count);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                }
                else if (pilih_menu == 2)
                {
                    cout<<"Kembali ke Menu Apoteker, Enter untuk kembali";getch();cout<<endl;
                    MenuApoteker();
                }
                else{
                    cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                    MenuShow();
                }
            }
            catch (invalid_argument exception)
            {
                cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                MenuShow();
            }
        }
    }
}

void MenuApoteker()
{
    fflush(stdin);
    int pilih_menu = 0;
    int count_menu = 3;
    string desc_menupasien[5] = {"[1] Tambah Salinan Resep","[2] List","[0] Exit"};
    string header_menupasien = "Menu Salinan Resep Obat";

    while (true)
    {
        system("cls");
        cout << setw((80 - header_menupasien.size()) / 2) << "" << "=======================================" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        cout << setw((80 - header_menupasien.size()) / 2) << "";
        cout << "------- " << header_menupasien << " -------" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        cout << setw((80 - header_menupasien.size()) / 2) << "" << "=======================================" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        for(int i = 0; i < count_menu; i++)
        {
            if (i == pilih_menu)
            {
                cout << setw((80 - header_menupasien.size()) / 2) << "";
                cout << ">>" << "  " << desc_menupasien[i] << "  " << " <<"; 
                cout << setw((80 - header_menupasien.size()) / 2) << "" << endl;
            }
            else
            {
                cout << setw((80 - header_menupasien.size()) / 2) << "";
                cout << "  " << "  " << desc_menupasien[i] << "  " << "  "; 
                cout << setw((80 - header_menupasien.size()) / 2) << "" << endl;
            }
        }

        char keys = getch();
        if (keys == 80)
        {
            if(pilih_menu < count_menu -1)
            {
                pilih_menu++;
            }
            else
            {
                pilih_menu = 0;
            }
        }
        else if (keys == 72)
        {
            if (pilih_menu > 0)
            {
                pilih_menu--;
            }
            else
            {
                pilih_menu = count_menu-1;
            }
        }
        else if(keys == 13)
        {
            try
            {
                if (pilih_menu == 0)
                {
                    addTask(listResep, count);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    MenuApoteker();
                    break;
                }
                else if (pilih_menu == 1)
                {
                    MenuShow();
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    MenuApoteker();
                    break;
                }
                else if (pilih_menu == 2)
                {
                    cout << "Keluar dari program.\n";
                    exit(0);
                }
                else{
                    cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                    MenuApoteker();
                }
            }
            catch (invalid_argument exception)
            {
                cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                MenuApoteker();
            }
        }
    }
}

#endif