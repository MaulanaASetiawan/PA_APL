#ifndef APOTEKER_H
#define APOTEKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream> 
#include <iomanip>
using namespace std;

void loadHasilDokter(); void MenuApoteker();

struct SalinanResep
{
    string NamaPasien;
    string NamaObat;
    string Satuan;
    string Expired ;
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
string Searchname;
// int indexData = 0;


void Showresep(SalinanResep list[], int counted)
{
    system("cls");
    if (counted == 0)
    {
        cout << "====================" << endl
             << "   Data Kosong    " << endl
             << "====================";getch();cout << endl;
        MenuApoteker();
    }
    cout << "Daftar :\n";
    cout << "No\tNama Pasien\t\tNama Obat\t\tSatuan\t\tExpired\t\tDosis Obat\t\tJumlah\n";
    for (int i = 0; i < counted; i++)
    {
        cout << i+1 << "\t  " << list[i].NamaPasien << "\t\t\t" 
             << list[i].NamaObat << "\t\t" << list[i].Satuan 
             << "\t\t" << list[i].Expired <<"\t\t"<< list[i].DosisObat 
             << "\t\t" << list[i].Jumlah <<endl;
    }
}

void showHasilDokter(HasilAnalisiDokter list[], int counted)
{
    system("cls");
    if (counted == 0)
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
    for (int i = 0; i < counted; i++)
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

void saveToFile(SalinanResep list[], int counted)
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
        outfile << list[i].NamaPasien << ",";
        outfile << list[i].NamaObat << ",";
        outfile << list[i].Satuan << ",";
        outfile << list[i].Expired << ",";
        outfile << list[i].Jumlah << ",";
        outfile << list[i].DosisObat << endl;
    }
}

void addTask(SalinanResep list[], int& counted)
{
    string input;
    cout << "\nNama Pasien>> "; getline(cin,list[counted].NamaPasien);
    cout << "Nama Obat>> "; getline(cin,list[counted].NamaObat);
    cout << "Satuan/Jenis Obat>> "; getline(cin, list[counted].Satuan);
    cout << "Expired Obat>> "; getline(cin, list[counted].Expired);
    cout << "Dosis Obat>> "; getline(cin, list[counted].DosisObat);
    try
    {
        cout << "Jumlah Obat>> "; getline(cin,input);
        list[counted].Jumlah = stoi(input);
        if (list[counted].Jumlah < 1)
        {
            cout << "Harga salah"; getch();cout<<endl;
            addTask(list,counted);
        }
    }
    catch(std::invalid_argument& e)
    {
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        addTask(list,counted);
    }
    counted++;
    saveToFile(list, counted);

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
    counted = 0;
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
            listResep[counted].Jumlah = stoi(Jumlah);
        }
        catch (std::invalid_argument& e)
        {
            cout << "Data pada file rusak" << endl;
            file.close();
            return;
        }

        listResep[counted].NamaPasien = NamaPasien;
        listResep[counted].Satuan = Satuan;
        listResep[counted].Expired = Expired;
        listResep[counted].NamaObat = NamaObat;
        listResep[counted].DosisObat = DosisObat;
        counted++;
        if (counted == Max_data)
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
        counted = 0;

        while (getline(file, line))
        {
            stringstream ss(line);
            string fields;

            HasilAnalisiDokter get;
            int FieldsIndex = 0; 

            while (getline(ss, fields, ','))
            {
                switch (FieldsIndex)
                {
                case 0:
                    get.nama = fields;
                    break;
                case 1:
                    get.keluhan = stoi(fields);
                    break;
                case 2:
                    get.hasil = fields;
                    break; 
                }
                FieldsIndex++;

            }
            listData[counted] = get;
            counted++;
            if (counted == Max_data)
            {
            break;
            }
        }
    }
        file.close();
}



void SelectionSort(SalinanResep list[], int counted) {
    for (int i = 0; i < counted - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < counted; j++) {
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
                    showHasilDokter(listData, counted);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                }
                else if (pilih_menu == 1)
                {
                    loadDataResep();
                    SelectionSort(listResep, counted);
                    Showresep(listResep, counted);
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
                    addTask(listResep, counted);
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