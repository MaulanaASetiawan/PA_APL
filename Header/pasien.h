#ifndef PASIEN.H
#define PASIEN.H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
using namespace std;

void MenuPasien();
// void interli(int count_menu, string desc_menupasien[], string header_menupasien);

struct ToDo
{
    string nama;
    int umur;
    string goldar;
    string gender;
    string keluhan;
    string waktutemu;
    string status;
};

const int max_task = 100;
ToDo list[max_task];
int hitung = 0;
int pilih_menu = 0;

void showTask(ToDo list[], int hitung)
{
    system("cls");
    if (hitung == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    " << endl;
        cout << "====================";getch();
        cout << endl;
        MenuPasien();
    }
    cout << "Daftar Task:\n";
    cout << "No\tNama\tUmur\t\tGol.Darah\t\tGender\t\tKeluhan\t\tWaktu Temu\t\tStatus\n";
    for (int i = 0; i < hitung; i++)
    {
        cout << i+1 << "\t" << list[i].nama << "\t\t" << list[i].umur << "\t\t" << list[i].goldar << "\t\t" << list[i].gender <<"\t\t"<< list[i].keluhan << "\t\t" << list[i].waktutemu << "\t\t" << list[i].status<< endl;
    }
}

void saveToFile(ToDo list[], int hitung)
{
    ofstream outfile("Database/Data_Pasien.csv");
    if (!outfile)
    {
        cout << "Gagal membuka file Data_Pasien." << endl;
        return;
    }
    
    outfile << "Nama,Umur,Gol.Darah,Gender,Keluhan,Waktu temu,Status" << endl;

    for (int i = 0; i < hitung; i++)
    {
        outfile << list[i].nama << ",";
        outfile << list[i].umur << ",";
        outfile << list[i].goldar << ",";
        outfile << list[i].gender << ",";
        outfile << list[i].keluhan << ",";
        outfile << list[i].waktutemu << ",";
        outfile << list[i].status << endl;
    }
}


void addTask(ToDo list[], int& hitung)
{
    system("cls");
    string input;
    cout << "\nNama Lengkap>> "; getline(cin,list[hitung].nama);
    try
    {
        cout << "Umur>> "; getline(cin,input);
        list[hitung].umur = stoi(input);
        if (list[hitung].umur < 1)
        {
            cout << "Umur salah"; getch();cout<<endl;
            addTask(list,hitung);
        }
    }
    catch(invalid_argument expression)
    {
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        addTask(list,hitung);
    }

    cout << "Golongan Darah>> "; getline(cin, list[hitung].goldar);
    cout << "Gender (L/P)>> "; getline(cin, list[hitung].gender);
    cout << "Keluhan>> "; getline(cin, list[hitung].keluhan);
    cout << "Waktu Temu>> "; getline(cin, list[hitung].waktutemu);

    list[hitung].status = "Dijadwalkan";
    hitung++;
    saveToFile(list, hitung);

    cout << "\nData berhasil disimpan ke dalam Database\n";
    cout << "Tekan Enter untuk kembali ke MenuPasien";getch(); cout<<endl;
    MenuPasien();
        
}

void deleteTask()
{
    if (hitung == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    "    << endl;
        cout << "====================";getch(); cout << endl;
        MenuPasien();
    }

    showTask(list, hitung);
    string input; int index;
    cout << "\nMasukkan no Jadwal yang sudah selesai>> "; getline(cin, input);
    
    try {
        int index = stoi(input) - 1;
        if (index >= 0 && index < hitung && list[index].status == "Dijadwalkan")
        {
            for (int i = index; i < hitung - 1; i++)
            {
                list[i] = list[i+1];
            }
            hitung--;
            saveToFile(list, hitung);
            cout << "Task berhasil dihapus\n";
        }
        else
        {
            cout << "Nomor task salah atau task sudah selesai\n";
        }
    }
    catch(invalid_argument expression)
    {
        cout << "Inputan harus Integer\n";
        deleteTask();
    }
    cout << "Tekan Enter untuk kembali ke MenuPasien"; getch(); cout << endl;
    MenuPasien();
}


void updateTask(ToDo list[], int& hitung)
{
    system("cls");
    if (hitung == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    "    << endl;
        cout << "====================";getch(); cout << endl;
        MenuPasien();
    }
    else
    {
        showTask(list, hitung);
        int choice; string input;
        try
        {
        cout << "\n\nMasukkan nomor task yang ingin diubah >> "; getline(cin,input);
        choice = stoi(input);
        }
        catch(invalid_argument expression) {
            cout << "Inputan harus Integer\n";
            updateTask(list,hitung);
        }
        if (choice <= 0 || choice > hitung)
        {
            cout << "Nomor task tidak valid"; getch(); cout<<endl;
            updateTask(list, hitung);
        }
        else
        {
            cout << "Nama Baru>> "; getline(cin,list[choice-1].nama);
            try
            {
                cout << "Umur Baru>> ";getline(cin, input);
                int umur = stoi(input);
                if (umur < 1)
                {
                    cout << "Umur tidak valid";getch(); cout<<endl;
                    updateTask(list, hitung);
                }
                else
                {
                    list[choice-1].umur = umur;
                }
            }
            catch (invalid_argument expression)
            {
                cout << "Inputan harus integer"; getch(); cout << endl;
                updateTask(list, hitung);
            }

            cout << "Golongan Darah>> "; getline(cin, list[choice-1].goldar);
            cout << "Gender (L/P)>> "; getline(cin, list[choice-1].gender);
            cout << "Keluhan>> "; getline(cin, list[choice-1].keluhan);
            cout << "Waktu Temu>> "; getline(cin, list[choice-1].waktutemu);
            list[choice-1].status = "Dijadwalkan";

            saveToFile(list, hitung);
            cout << "\nData berhasil diupdate ke dalam Database\n";
            cout << "Tekan Enter untuk kembali ke MenuPasien";getch(); cout<<endl;
            MenuPasien();
        }
    }
}


void loadData()
{
    ifstream infile("database/Data_Pasien.csv");
    if (!infile.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(infile, line);
    hitung = 0;
    while (getline(infile, line))
    {
        stringstream iss(line);
        string nama,umur,goldar,gender,keluhan,waktutemu,status;
        getline(iss, nama, ',');
        getline(iss, umur, ',');
        getline(iss, goldar, ',');
        getline(iss, gender, ',');
        getline(iss, keluhan, ',');
        getline(iss, waktutemu, ',');
        getline(iss, status, ',');

        try
        {
            list[hitung].umur = stoi(umur);
        }
        catch (invalid_argument expression)
        {
            cout << "Data pada file rusak" << endl;
            infile.close();
            return;
        }

        list[hitung].nama = nama;
        list[hitung].goldar = goldar;
        list[hitung].gender = gender;
        list[hitung].keluhan = keluhan;
        list[hitung].waktutemu = waktutemu;
        list[hitung].status = status;
        hitung++;
        if (hitung == max_task)
        {
            break;
        }
    }
    infile.close();
}

void MenuPasien()
{
    fflush(stdin);
    int pilih_menu = 0;
    int count_menu = 5;
    string desc_menupasien[5] = {"[1] Create Task","[2] List task", "[3] Delete Data", "[4] Update Task","[0] Exit"};
    string header_menupasien = "Pharma-10";

    while (true)
    {
        system("cls");
        cout << setw((80 - header_menupasien.size()) / 2) << "" << "===============================" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        cout << setw((80 - header_menupasien.size()) / 2) << "";
        cout << "---------- " << header_menupasien << " ----------" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        cout << setw((80 - header_menupasien.size()) / 2) << "" << "===============================" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
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
                    addTask(list, hitung);
                    break;
                }
                else if (pilih_menu == 1)
                {
                    showTask(list, hitung);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    MenuPasien();
                    break;
                }
                else if (pilih_menu == 2)
                {
                    deleteTask();
                    break;
                }
                else if (pilih_menu == 3)
                {
                    updateTask(list, hitung);
                    break;
                }
                else if (pilih_menu == 4)
                {
                    cout << "Keluar dari program.\n";
                    exit(0);
                }
                else{
                    cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                    MenuPasien();
                }
            }
            catch (invalid_argument exception)
            {
                cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                MenuPasien();
            }
        }
    }
}

#endif