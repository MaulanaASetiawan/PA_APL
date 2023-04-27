#ifndef APOTEKER_H
#define APOTEKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream> 
#include <iomanip>

using namespace std;

void Loadhasildokter(); void MenuApoteker();

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


void Showrecipe(SalinanResep list[], int counted)
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

void Showhasildokter(HasilAnalisiDokter listed[], int counted)
{
    system("cls");
    if (counted == 0)
    {
    cout << "====================" << endl
         << "    Data Kosong     " << endl
         << "====================";getch();cout << endl;
    MenuApoteker();
    }
    cout << "Hasil Analisis:\n";
    cout << "No\tNama\t\tKeluhan\t\tHasil\n";
    for (int i = 0; i < counted; i++)
     {
        cout << i+1 << "\t" << listed[i].nama << "\t"
        << listed[i].keluhan << "\t " << listed[i].hasil << endl;
     }
}

void Savetofiles(SalinanResep list[], int counted)
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
        outfile << list[i].DosisObat << ",";
        outfile << list[i].Jumlah << endl;
    }
}

void Date(tm &date, SalinanResep list[], int counted)
{
    cout << "Masukkan tanggal (DD-MM-YYYY) >>  ";
    string input;
    getline(cin, input);
    istringstream ss(input);
    ss >> get_time(&date, "%d-%m-%Y");

    if (ss.fail()) 
    {
        cout << "Format tanggal tidak valid!"; getch(); cout << endl;
        Date(date, list, counted);
    }
    else
    {
        time_t time = mktime(&date);
        stringstream ss;
        ss << put_time(localtime(&time), "%d %b %Y");
        list[counted].Expired = ss.str();
    }
}

void Addprescription(SalinanResep list[], HasilAnalisiDokter listed[], int& counted)
{
    system("cls");
    cout << "Salinan Resep Obat:"<< endl;
    string input;
    cout << "\nMasukkan Nama Pasien >> ";getline(cin, Searchname);
    cout << "Daftar Task:\n";
    cout << "No\tNama\t\tKeluhan\t\tHasil\n";
    bool found = false;
    for (int i = 0; i < counted; i++)
    {
        if (listed[i].nama == Searchname)
        {
            cout << i+1 << "\t" << listed[i].nama << "\t\t"
            << listed[i].keluhan << "\t\t " << listed[i].hasil << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {   
        cout << "Data Pasien Tidak Ditemukan" << endl;
        cout<<"Kembali Ke Menu APoteker(Tekan Enter)"; getch(); cout << endl;
        MenuApoteker();
    }

    cout << "\nNama Pasien>> "; getline(cin,list[counted].NamaPasien);
    cout << "Nama Obat>> "; getline(cin,list[counted].NamaObat);
    // cout << "Satuan/Jenis Obat>> "; getline(cin, list[counted].Satuan);
    cout << "Jenis Obat (Tablet/Kapsul/Pil/Serbuk/ObatCair)>> ";
    getline(cin, input);
    if (input != "Tablet" && input != "tablet" && input != "Kapsul" && input != "kapsul" 
        && input !="Pil" && input != "pil" && input != "Serbuk" && input != "serbuk" && input != "ObatCair" && input != "obatcair")
    {
        cout << "Masukkan Jenis Obat yang benar!(Tekan Enter)";
        getch();cout << endl;
        Addprescription(list,listed,counted);
    }
    list[counted].Satuan = input;
    Date(date,list,counted);
    cout << "Dosis Obat>> "; getline(cin, list[counted].DosisObat);
    try
    {
        cout << "Jumlah Obat>> "; getline(cin,input);
        list[counted].Jumlah = stoi(input);
        if (list[counted].Jumlah < 1)
        {
            cout << "Jumlah salah"; getch();cout<<endl;
            Addprescription(list,listed,counted);
        }
    }
    catch(std::invalid_argument& e)
    {
        cout<<"Inputan harus Integer(Tekan Enter)"; getch(); cout << endl;
        Addprescription(list,listed,counted);
    }
    counted++;
    Savetofiles(list, counted);

    cout << "\nData berhasil disimpan ke dalam Database\n";
    cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;
    MenuApoteker();
        
}

void Loaddataresep()
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
        string Pasien,Obat,Satuan,Expired,Jumlah,Dosis;
        getline(ss, Pasien, ',');
        getline(ss, Obat, ',');
        getline(ss, Satuan, ',');
        getline(ss, Expired, ',');
        getline(ss, Dosis, ',');
        getline(ss, Jumlah, ',');
        

        listResep[counted].NamaPasien = Pasien;
        listResep[counted].NamaObat = Obat;
        listResep[counted].Satuan = Satuan;
        listResep[counted].Expired = Expired;
        listResep[counted].DosisObat = Dosis;
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
        counted++;
        if (counted == Max_data)
        {
            break;
        }
    }
    file.close();
}
void Loadhasildokter()
{
    ifstream file;
    file.open("Database/Data_Dokter.csv",ios::in);
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
        string Namapasien,Keluhan,Hasil;
        getline(ss, Namapasien, ',');
        getline(ss, Keluhan, ',');
        getline(ss, Hasil, ',');
        

        listData[counted].nama = Namapasien;
        listData[counted].keluhan = Keluhan;
        listData[counted].hasil = Hasil;
        counted++;
        if (counted == Max_data)
        {
            break;
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

void Menushow()
{
    fflush(stdin);
    int pilih_menu = 0;
    int count_menu = 3;
    string desc_MenuShow[3] = {"[1] List Hasil Analisis Dokter","[2] List Salinan Resep","[0] Kembali"};
    string header_MenuShow = "Menu Show";

    while (true)
    {
        system("cls");
        cout << setw((80 - header_MenuShow.size()) / 2) << "" << "========================================" << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
        cout << setw((80 - header_MenuShow.size()) / 2) << "";
        cout << "-------------- " << header_MenuShow << " ---------------" << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
        cout << setw((80 - header_MenuShow.size()) / 2) << "" << "========================================" << setw((80 - header_MenuShow.size()) / 2) << "" << endl;
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
                    Loadhasildokter();
                    Showhasildokter(listData, counted);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                }
                else if (pilih_menu == 1)
                {
                    Loaddataresep();
                    SelectionSort(listResep, counted);
                    Showrecipe(listResep, counted);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                }
                else if (pilih_menu == 2)
                {
                    cout<<"Kembali ke Menu Apoteker, Enter untuk kembali";getch();cout<<endl;
                    MenuApoteker();
                    break;
                }
                else{
                    cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                    Menushow();
                }
            }
            catch (invalid_argument exception)
            {
                cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                Menushow();
            }
        }
    }
}

void MenuApoteker()
{
    Loaddataresep();
    Loadhasildokter();
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
                    Addprescription(listResep, listData , counted);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    break;
                    MenuApoteker();
                }
                else if (pilih_menu == 1)
                {
                    Menushow();
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    break;
                    MenuApoteker();
                }
                else if (pilih_menu == 2)
                {
                    cout << "Keluar dari program.\n";
                    exit(0);
                    break;
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