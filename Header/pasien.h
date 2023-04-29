#ifndef PASIEN_H
#define PASIEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "interli.h"
using namespace std;

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

struct Dokter
{
    string nama;
    string keluhan;
    string hasil;
};

struct Resep
{
    string NamaPasien;
    string NamaObat;
    string Satuan;
    string Expired;
    string DosisObat;
    int Jumlah;
};

void MenuPasien();
void LoadData_Pasien();
void LoadData_Dokter();
void LoadData_Apoteker();
void ShellSort();
void SearchPasien(ToDo *lists, int hitung);
void FinalAnalisis(ToDo *lists, Dokter *review, Resep *Final, int hitung, int field, int counts);

const int max_task = 100;
ToDo lists[max_task];
Dokter review[max_task];
Resep final[max_task];
int hitung = 0;
int field = 0;
int counts = 0;
int pilih_menu = 0;
tm date = {}; // reminder : date value 0

void showTask(ToDo lists[], int hitung)
{
    SearchPasien(lists, hitung);
}

void Final_Decision(ToDo lists[], int hitung)
{
    FinalAnalisis(lists, review, final, hitung, field, counts);
}

void saveToFile(ToDo lists[], int hitung)
{
    ofstream outfile("Database/Data_Pasien.csv");
    if (!outfile)
    {
        cout << "Gagal membuka file Data_Pasien." << endl;
        return;
    }

    outfile << "Nama/Umur/Gol.Darah/Gender/Keluhan/Waktu temu/Status" << endl;

    for (int i = 0; i < hitung; i++)
    {
        fflush(stdin);
        outfile << lists[i].nama << "/";
        outfile << lists[i].umur << "/";
        outfile << lists[i].goldar << "/";
        outfile << lists[i].gender << "/";
        outfile << lists[i].keluhan << "/";
        outfile << lists[i].waktutemu << "/";
        outfile << lists[i].status << endl;
    }
}

void Date(tm &date, ToDo lists[], int hitung)
{
    // Mendapatkan waktu sekarang
    time_t now = time(nullptr); // nullptr bawaan cpp dia pointernull
    // Konversi waktu saat ini ke struct tm
    tm *local_now = localtime(&now);

    cout << "Masukkan tanggal (DD-MM-YYYY) >>  ";
    cin >> get_time(&date, "%d-%m-%Y");

    if (cin.fail() || mktime(&date) < now)
    {
        cin.clear();
        cout << "Format tanggal tidak valid atau tanggal tidak boleh sebelum hari ini!";
        getch();
        cout << endl;
        while (cin.get() != '\n')
            ;
        Date(date, lists, hitung);
    }
    else
    {
        time_t time = mktime(&date);
        stringstream ss;
        ss << put_time(localtime(&time), "%d %b %Y");
        lists[hitung].waktutemu = ss.str();
    }
}

void ShellSort()
{
    ToDo temp;
    for (int gap = hitung / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < hitung; i++)
        {
            temp = lists[i];
            int j;
            for (j = i; j >= gap && lists[j - gap].waktutemu > temp.waktutemu; j -= gap)
            {
                lists[j] = lists[j - gap];
            }
            lists[j] = temp;
        }
    }
}

void SearchPasien(ToDo *lists, int hitung)
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

    ShellSort();
    string input;
    cout << "------Penjadwalan---------------------------------------" << endl;
    cout << "Cari Nama--> ";
    getline(cin, input);
    string nama = input;

    bool get = false;
    for (int j = 0; j < nama.size(); j++)
    {
        nama[j] = tolower(nama[j]);
    }
    for (int i = 0; i <hitung; i++)
    {
        string temp = lists[i].nama;
        for (int j = 0; j < temp.size(); j++)
        {
        temp[j] = tolower(temp[j]);
        }

        int found = temp.find(nama);
        if (found >= 0)
        {
            get = true;
            cout << "Daftar Task:\n";
            cout << "Nama\t\t\t\tGender\t\tStatus\n";
            cout << lists[i].nama << "\t\t" << lists[i].gender << "\t\t" << lists[i].status << endl;
        }
    }
    if (!get)
    {
        cout << "Tidak ada pasien dengan nama \"" << nama << "\"." << endl;
    }
}

void FinalAnalisis(ToDo *lists, Dokter *review, Resep *Final, int hitung, int  field, int counts)
{
    system("cls");

    ShellSort();
    string input;
    cout << "------Hasil Analisis---------------------------------------" << endl;
    cout << "Cari Nama--> ";
    getline(cin, input);
    string nama = input;

    bool get = false;
    for (int j = 0; j < nama.size(); j++)
    {
        nama[j] = tolower(nama[j]);
    }

    for (int i = 0; i < hitung; i++)
    {
        string temp = lists[i].nama ;
        for (int j = 0; j < temp.size(); j++)
        {
        temp[j] = tolower(temp[j]);
        }

        int found = temp.find(nama);
        if (found >= 0)
        {
            get = true;
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            cout << "No\tNama\t\t\tGender\t\tStatus\n";
            cout << lists[i].nama << "\t\t" << lists[i].gender << "\t\t" << lists[i].status << endl;
        }
    }
    if (!get)
    {
        cout << "Tidak ada pasien dengan nama \"" << nama << "\"." << endl;
        return;
    }

    if (hitung > 0)
    {
        bool foundDokter = false;
        for (int i = 0; i < field; i++)
        {
            string temp = review[i].nama ;
            for (int j = 0; j < temp.size(); j++)
            {
            temp[j] = tolower(temp[j]);
            }

            int found = temp.find(nama);
            if (found >= 0)
            {
                foundDokter = true;
                cout << "-------------------------------------------------------------------------------------------------" << endl;
                cout << "Nama\t\t\t\tKeluhan\t\t\tHasil\n";
                cout << review[i].nama << "\t\t" << review[i].keluhan << "\t\t" << review[i].hasil << endl;
            }
        }
        if(!foundDokter)
        {
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            cout << "Mohon menunggu hingga dokter selesai Menganalisa" << endl;
        }

        bool foundApoteker = false;
        for (int i = 0; i < counts; i++)
        {
            string temp = final[i].NamaPasien ;
            for (int j = 0; j < temp.size(); j++)
            {
            temp[j] = tolower(temp[j]);
            }

            int found = temp.find(nama);
            if (found >= 0)
            {
                foundApoteker = true;
                cout << "-------------------------------------------------------------------------------------------------" << endl;
                cout << "Nama Pasien\t\tNama Obat\t\tSatuan\t\tExpired\t\tDosis Obat\t\tJumlah\n";
                cout << final[i].NamaPasien << "\t\t\t" 
                        << final[i].NamaObat << "\t\t" << final[i].Satuan 
                        << "\t\t" << final[i].Expired <<"\t\t"<< final[i].DosisObat 
                        << "\t\t" << final[i].Jumlah <<endl;
                cout << "-------------------------------------------------------------------------------------------------" << endl;
            }
        }
        if (!foundApoteker)
        {
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            cout << "Resep sedang dibuat, Mohon ditunggu" << endl;
            cout << "-------------------------------------------------------------------------------------------------" << endl;
        }
    }
    else
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    " << endl;
        cout << "====================";
        getch();
        cout << endl;
        MenuPasien();
    }
}

void addTask(ToDo lists[], int &hitung)
{
    system("cls");
    string input, inputNama;
    cout << "\nNama Lengkap>> ";
    getline(cin, inputNama);
    for(int i = 0; i < hitung; i++)
    {
        if(inputNama == lists[i].nama)
        {
            cout << "\nData telah terdaftar\n";
            cout << "Silahkan Pergi ke Menu Update";
            getch();MenuPasien();
        }
    }
    lists[hitung].nama = inputNama;
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
    getline(cin, input);
    if (input != "A" && input != "B" && input != "AB" && input != "O")
    {
        cout << "Masukkan Goldar dengan benar!-(A/B/AB/O)";
        getch(); cout << endl;
        addTask(lists,hitung);
    }
    lists[hitung].goldar = input;
    cout << "Gender (L/P)>> ";
    getline(cin, input);
    if (input != "L" && input != "P")
    {
        cout << "Masukkan Gender dengan benar!-(L/P)";
        getch();cout << endl;
        addTask(lists, hitung);
    }
    lists[hitung].gender = input;
    cout << "Keluhan>> ";
    getline(cin, lists[hitung].keluhan);
    Date(date,lists,hitung);
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
    cout << "\nMasukkan no sesuai tabel>> ";
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

void updateTask(ToDo *lists, int hitung)
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

    string input;
    cout << "------Update Data---------------------------------------" << endl;
    cout << "Cari Nama--> ";
    getline(cin, input);
    string nama = input;

    bool get = false;
    for (int j = 0; j < nama.size(); j++)
    {
        nama[j] = tolower(nama[j]);
    }

    int name_search = 0;
    int choice = 0;
    cout << "+--------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|-------------------------------------------------  BIODATA PASIEN  -------------------------------------------------------------------------|" << endl;
    cout << "+--------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|Nama\t\t\t\tUmur\tGoldar\tGender\tKeluhan\t\t\t\tWaktu Temu\t\t\tStatus            |" << endl;
    cout << "+--------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    for (int i = 0; i < hitung; i++)
    {
        string temp = lists[i].nama;
        for (int j = 0; j < temp.size(); j++)
        {
            temp[j] = tolower(temp[j]);
        }
        int found = temp.find(nama);
        if (found >= 0)
        {
            get = true;
            cout << "|" << setw(25) << left << lists[i].nama << setw(10) << right << lists[i].umur << "\t" << setw(6) << left << lists[i].goldar << "\t" << setw(6) << left << lists[i].gender << "\t" << setw(25) << left << lists[i].keluhan << "\t" << setw(24) << left << lists[i].waktutemu << "\t" << setw(13) << left << lists[i].status << "|" << endl;
            cout << "+--------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            name_search++;

            choice = i + 1;
            break;
        }
    }
    if (!get)
    {
        cout << "\nTidak ada pasien dengan nama \"" << nama << "\".";
        getch();cout<<endl;
        MenuPasien();
    }

    if (name_search > 0)
    {
        cout << "\nNama Lengkap>> ";
        getline(cin, lists[choice - 1].nama);
        try
        {
            cout << "Umur>> ";
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
        getline(cin, input);
        if (input != "A" && input != "B" && input != "AB" && input != "O")
        {
            cout << "Masukkan Goldar dengan benar!-(A/B/AB/O)";
            getch();
            cout << endl;
            addTask(lists, hitung);
        }
        lists[choice - 1].goldar = input;
        cout << "Gender (L/P)>> ";
        getline(cin, input);
        if (input != "L" && input != "P")
        {
            cout << "Masukkan Gender dengan benar!-(L/P)";
            getch();
            cout << endl;
            updateTask(lists, hitung);
        }
        lists[choice - 1].gender = input;
        cout << "Keluhan>> ";
        getline(cin, lists[choice - 1].keluhan);
        Date(date, lists, choice - 1);
        lists[choice - 1].status = "Dijadwalkan";
        saveToFile(lists, hitung);
        cout << "\nData berhasil diupdate ke dalam Database\n";
        cout << "Tekan Enter untuk kembali ke MenuPasien";
        getch();
        cout << endl;
        MenuPasien();
    }
    counts = counts + name_search;
}

void LoadData_Pasien()
{
    ifstream infile_pasien("database/Data_Pasien.csv");
    if (!infile_pasien.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(infile_pasien, line);
    hitung = 0;
    while (getline(infile_pasien, line))
    {
        stringstream iss(line);
        string nama, umur, goldar, gender, keluhan, waktutemu, status;
        getline(iss, nama, '/');
        getline(iss, umur, '/');
        getline(iss, goldar, '/');
        getline(iss, gender, '/');
        getline(iss, keluhan, '/');
        getline(iss, waktutemu, '/');
        getline(iss, status, '/');

        try
        {
            lists[hitung].umur = stoi(umur);
        }
        catch (invalid_argument expression)
        {
            cout << "Data pada file rusak" << endl;
            infile_pasien.close();
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
    infile_pasien.close();
}

void LoadData_Dokter()
{
    ifstream infile_dokter("database/Data_Dokter.csv");
    if (!infile_dokter.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(infile_dokter, line);
    field = 0;
    while (getline(infile_dokter, line))
    {
        stringstream iss(line);
        string nama, keluhan, hasil;
        getline(iss, nama, '/');
        getline(iss, keluhan, '/');
        getline(iss, hasil, '/');

        review[field].nama = nama;
        review[field].keluhan = keluhan;
        review[field].hasil = hasil;
        field++;
        if (field == max_task)
        {
            break;
        }
    }
    infile_dokter.close();
}

void LoadData_Apoteker()
{
    ifstream infile_apoteker("database/Dosis_Pasien.csv");
    if (!infile_apoteker.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(infile_apoteker, line);
    counts = 0;
    while (getline(infile_apoteker, line))
    {
        stringstream iss(line);
        string nama_pasien, nama_obat, satuan, expired, dosis, jumlah_obat;
        getline(iss, nama_pasien, '/');
        getline(iss, nama_obat, '/');
        getline(iss, satuan, '/');
        getline(iss, expired, '/');
        getline(iss, dosis, '/');
        getline(iss, jumlah_obat, '/');

        try
        {
            final[counts].Jumlah = stoi(jumlah_obat);
        }
        catch (invalid_argument expression)
        {
            cout << "Data pada file rusak" << endl;
            infile_apoteker.close();
            return;
        }

        final[counts].NamaPasien = nama_pasien;
        final[counts].NamaObat = nama_obat;
        final[counts].Satuan = satuan;
        final[counts].Expired = expired;
        final[counts].DosisObat = dosis;
        counts++;
        if (counts == max_task)
        {
            break;
        }
    }
    infile_apoteker.close();
}

void MenuPasien()
{
    LoadData_Pasien();
    LoadData_Dokter();
    LoadData_Apoteker();
    fflush(stdin);
    int count_menu = 6;
    string desc_menupasien[6] = {"Create Data", "Lists Penjadwalan", "Delete Data", "Update Data", "Hasil Analisis", "Exit"};
    string header_menupasien = "Pharma-10";
    create_menus(count_menu, desc_menupasien, header_menupasien);

    if (current_selection == 0)
    {
        addTask(lists, hitung);
    }
    else if (current_selection == 1)
    {
        showTask(lists, hitung);
        cout << "\nTekan Enter untuk kembali ke menu";
        getch();
        cout << endl;
        MenuPasien();
    }
    else if (current_selection == 2)
    {
        deleteTask();
    }
    else if (current_selection == 3)
    {
        updateTask(lists, hitung);
    }
    else if (current_selection == 4)
    {
        Final_Decision(lists, hitung);
        cout << "\nTekan Enter untuk kembali ke menu";
        getch();
        cout << endl;
        MenuPasien();
    }
    else if (current_selection == 5)
    {
        exit(0);
    }
}

#endif