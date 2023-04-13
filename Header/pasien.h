#ifndef PASIEN_H
#define PASIEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <iomanip>
using namespace std;

void MenuPasien();

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
ToDo lists[max_task];
int hitung = 0;
int pilih_menu = 0;

void showTask(ToDo lists[], int hitung)
{
    system("cls");
    if (hitung == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    " << endl;
        cout << "====================";
        getch();
        cout << endl;
        MenuPasien();
    }
    cout << "Daftar Task:\n";
    cout << "No\tNama\tUmur\t\tGol.Darah\t\tGender\t\tKeluhan\t\tWaktu Temu\t\tStatus\n";
    for (int i = 0; i < hitung; i++)
    {
        cout << i + 1 << "\t" << lists[i].nama << "\t\t" << lists[i].umur << "\t\t" << lists[i].goldar << "\t\t" << lists[i].gender << "\t\t" << lists[i].keluhan << "\t\t" << lists[i].waktutemu << "\t\t" << lists[i].status << endl;
    }
}

void saveToFile(ToDo lists[], int hitung)
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
        outfile << lists[i].nama << ",";
        outfile << lists[i].umur << ",";
        outfile << lists[i].goldar << ",";
        outfile << lists[i].gender << ",";
        outfile << lists[i].keluhan << ",";
        outfile << lists[i].waktutemu << ",";
        outfile << lists[i].status << endl;
    }
}

void addTask(ToDo lists[], int &hitung)
{
    system("cls");
    string input;
    cout << "\nNama Lengkap>> ";
    getline(cin, lists[hitung].nama);
    try
    {
        cout << "Umur>> ";
        getline(cin, input);
        lists[hitung].umur = stoi(input);
        if (lists[hitung].umur < 1)
        {
            cout << "Umur salah";
            getch();
            cout << endl;
            addTask(lists, hitung);
        }
    }
    catch (invalid_argument expression)
    {
        cout << "Inputan harus Integer";
        getch();
        cout << endl;
        addTask(lists, hitung);
    }

    cout << "Golongan Darah>> ";
    getline(cin, lists[hitung].goldar);
    cout << "Gender (L/P)>> ";
    getline(cin, lists[hitung].gender);
    cout << "Keluhan>> ";
    getline(cin, lists[hitung].keluhan);
    cout << "Waktu Temu>> ";
    getline(cin, lists[hitung].waktutemu);

    lists[hitung].status = "Dijadwalkan";
    hitung++;
    saveToFile(lists, hitung);

    cout << "\nData berhasil disimpan ke dalam Database\n";
    cout << "Tekan Enter untuk kembali ke MenuPasien";
    getch();
    cout << endl;
    MenuPasien();
}

void deleteTask()
{
    if (hitung == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    " << endl;
        cout << "====================";
        getch();
        cout << endl;
        MenuPasien();
    }

    showTask(lists, hitung);
    string input;
    int index;
    cout << "\nMasukkan no Jadwal yang sudah selesai>> ";
    getline(cin, input);

    try
    {
        int index = stoi(input) - 1;
        if (index >= 0 && index < hitung && lists[index].status == "Dijadwalkan")
        {
            for (int i = index; i < hitung - 1; i++)
            {
                lists[i] = lists[i + 1];
            }
            hitung--;
            saveToFile(lists, hitung);
            cout << "Task berhasil dihapus\n";
        }
        else
        {
            cout << "Nomor task salah atau task sudah selesai\n";
        }
    }
    catch (invalid_argument expression)
    {
        cout << "Inputan harus Integer\n";
        deleteTask();
    }
    cout << "Tekan Enter untuk kembali ke MenuPasien";
    getch();
    cout << endl;
    MenuPasien();
}

void updateTask(ToDo lists[], int &hitung)
{
    system("cls");
    if (hitung == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    " << endl;
        cout << "====================";
        getch();
        cout << endl;
        MenuPasien();
    }
    else
    {
        showTask(lists, hitung);
        int choice;
        string input;
        try
        {
            cout << "\n\nMasukkan nomor task yang ingin diubah >> ";
            getline(cin, input);
            choice = stoi(input);
        }
        catch (invalid_argument expression)
        {
            cout << "Inputan harus Integer\n";
            updateTask(lists, hitung);
        }
        if (choice <= 0 || choice > hitung)
        {
            cout << "Nomor task tidak valid";
            getch();
            cout << endl;
            updateTask(lists, hitung);
        }
        else
        {
            cout << "Nama Baru>> ";
            getline(cin, lists[choice - 1].nama);
            try
            {
                cout << "Umur Baru>> ";
                getline(cin, input);
                int umur = stoi(input);
                if (umur < 1)
                {
                    cout << "Umur tidak valid";
                    getch();
                    cout << endl;
                    updateTask(lists, hitung);
                }
                else
                {
                    lists[choice - 1].umur = umur;
                }
            }
            catch (invalid_argument expression)
            {
                cout << "Inputan harus integer";
                getch();
                cout << endl;
                updateTask(lists, hitung);
            }

            cout << "Golongan Darah>> ";
            getline(cin, lists[choice - 1].goldar);
            cout << "Gender (L/P)>> ";
            getline(cin, lists[choice - 1].gender);
            cout << "Keluhan>> ";
            getline(cin, lists[choice - 1].keluhan);
            cout << "Waktu Temu>> ";
            getline(cin, lists[choice - 1].waktutemu);
            lists[choice - 1].status = "Dijadwalkan";

            saveToFile(lists, hitung);
            cout << "\nData berhasil diupdate ke dalam Database\n";
            cout << "Tekan Enter untuk kembali ke MenuPasien";
            getch();
            cout << endl;
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
        string nama, umur, goldar, gender, keluhan, waktutemu, status;
        getline(iss, nama, ',');
        getline(iss, umur, ',');
        getline(iss, goldar, ',');
        getline(iss, gender, ',');
        getline(iss, keluhan, ',');
        getline(iss, waktutemu, ',');
        getline(iss, status, ',');

        try
        {
            lists[hitung].umur = stoi(umur);
        }
        catch (invalid_argument expression)
        {
            cout << "Data pada file rusak" << endl;
            infile.close();
            return;
        }

        lists[hitung].nama = nama;
        lists[hitung].goldar = goldar;
        lists[hitung].gender = gender;
        lists[hitung].keluhan = keluhan;
        lists[hitung].waktutemu = waktutemu;
        lists[hitung].status = status;
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
    string desc_menupasien[5] = {"[1] Create Task", "[2] lists task", "[3] Delete Data", "[4] Update Task", "[0] Exit"};
    string header_menupasien = "Pharma-10";

    while (true)
    {
        system("cls");
        cout << setw((80 - header_menupasien.size()) / 2) << "";
        cout << "===============================" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        cout << setw((80 - header_menupasien.size()) / 2) << "";
        cout << "---------- " << header_menupasien << " ----------" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        cout << setw((80 - header_menupasien.size()) / 2) << "";
        cout << "===============================" << setw((80 - header_menupasien.size()) / 2) << "" << endl;
        for (int i = 0; i < count_menu; i++)
        {
            if (i == pilih_menu)
            {
                cout << setw((80 - header_menupasien.size()) / 2) << "";
                cout << ">>";
                cout << "  " << desc_menupasien[i] << "  ";
                cout << " <<";
                cout << setw((80 - header_menupasien.size()) / 2) << "" << endl;
            }
            else
            {
                cout << setw((80 - header_menupasien.size()) / 2) << "";
                cout << "  ";
                cout << "  " << desc_menupasien[i] << "  ";
                cout << "  ";
                cout << setw((80 - header_menupasien.size()) / 2) << "" << endl;
            }
        }

        char keys = getch();
        if (keys == 80)
        {
            if (pilih_menu < count_menu - 1)
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
                pilih_menu = count_menu - 1;
            }
        }
        else if (keys == 13)
        {
            try
            {
                if (pilih_menu == 0)
                {
                    addTask(lists, hitung);
                    break;
                }
                else if (pilih_menu == 1)
                {
                    showTask(lists, hitung);
                    cout << "\nTekan Enter untuk kembali ke menu";
                    getch();
                    cout << endl;
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
                    updateTask(lists, hitung);
                    break;
                }
                else if (pilih_menu == 4)
                {
                    cout << "Keluar dari program.\n";
                    exit(0);
                }
                else
                {
                    cout << "\nMenu tidak ada, Enter untuk kembali";
                    getch();
                    cout << endl;
                    MenuPasien();
                }
            }
            catch (invalid_argument exception)
            {
                cout << "\nMenu tidak ada, Enter untuk kembali";
                getch();
                cout << endl;
                MenuPasien();
            }
        }
    }
}

#endif
