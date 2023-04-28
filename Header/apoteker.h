#ifndef APOTEKER_H
#define APOTEKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream> 
#include <iomanip>

using namespace std;

void Loadhasildokter(); void MenuApoteker(); void Menushow();

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
int Jumlah = 0;
// string Searchname;


void Showprescription(SalinanResep listResep[], int counted)
{
    system("cls");
    if (counted == 0)
    {
        cout << "====================" << endl
             << "   Data Kosong    " << endl
             << "====================";getch();cout << endl;fflush(stdin);
        Menushow();
    }
    cout << "Daftar :\n";
    cout << "No\tNama Pasien\t\tNama Obat\t\tSatuan\t\tExpired\t\tDosis Obat\t\tJumlah\n";
    for (int i = 0; i < counted; i++)
    {
        cout << i+1 << "\t  " << listResep[i].NamaPasien << "\t\t\t" 
             << listResep[i].NamaObat << "\t\t" << listResep[i].Satuan 
             << "\t\t" << listResep[i].Expired <<"\t\t"<< listResep[i].DosisObat 
             << "\t\t" << listResep[i].Jumlah <<endl;
    }
}

void Showhasildokter(HasilAnalisiDokter listData[], int Jumlah)
{
    system("cls");
    if (Jumlah == 0)
    {
    cout << "====================" << endl
         << "    Data Kosong     " << endl
         << "====================";getch();cout << endl;
    Menushow();
    }
    cout << "Hasil Analisis:\n";
    cout << "No\tNama\t\tKeluhan\t\t Hasil\n";
    for (int i = 0; i < Jumlah; i++)
     {
        cout << i+1 << "\t" << listData[i].nama << "\t\t"
        << listData[i].keluhan << "\t\t " << listData[i].hasil << endl;
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
        outfile << listResep[i].NamaPasien << ",";
        outfile << listResep[i].NamaObat << ",";
        outfile << listResep[i].Satuan << ",";
        outfile << listResep[i].Expired << ",";
        outfile << listResep[i].DosisObat << ",";
        outfile << listResep[i].Jumlah << endl;
        fflush(stdin);
    }
}

void Date(tm &date, SalinanResep listResep[], int counted)
{
    cout << "Masukkan tanggal (DD-MM-YYYY) >>  ";
    string input;
    getline(cin, input);
    istringstream ss(input);
    ss >> get_time(&date, "%d-%m-%Y");

    if (ss.fail()) 
    {
        cout << "Format tanggal tidak valid!"; getch(); cout << endl;fflush(stdin);
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

void Searchnamepasien(HasilAnalisiDokter listData[], int Jumlah){
    string Searchname;
    cout << "\nMasukkan Nama Pasien >> ";getline(cin, Searchname);
    fflush(stdin);
    cout << "Daftar Task:\n";
    cout << "No\tNama\t\tKeluhan\t\tHasil\n";
    bool found = false;
    for (int i = 0; i < Jumlah; i++)
    {
        if (listData[i].nama == Searchname)
        {
            cout << i+1 << "\t" << listData[i].nama << "\t\t"
            << listData[i].keluhan << "\t\t " << listData[i].hasil << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {   
        cout << "Data Pasien Tidak Ditemukan" << endl;
        cout<<"Kembali Ke Menu APoteker(Tekan Enter)"; getch(); cout << endl;
        fflush(stdin);
        MenuApoteker();
    }
    fflush(stdin);

}

void Addprescription(SalinanResep listResep[], HasilAnalisiDokter listData[], int counted, int Jumlah)
{
    string input;
    system("cls");
    Searchnamepasien(listData,Jumlah);
    cout << endl;
    cout << "Salinan Resep Obat:"<< endl;
    cout << "\nNama Pasien>> "; getline(cin,listResep[counted].NamaPasien);
    // listResep[counted].NamaPasien =  listData[Jumlah].nama;
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
    files.open("Database/Dosis_Pasien.csv",ios::in);
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
    file.open("Database/Data_Dokter.csv",ios::in);
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
        getline(ss, Namapasien, ',');
        getline(ss, Keluhan, ',');
        getline(ss, Hasil, ',');
        

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


void SelectionSort(SalinanResep listResep[], int counted) {
    for (int i = 0; i < counted - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < counted; j++) {
            if (listResep[j].NamaPasien < listResep[min_index].NamaPasien) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(listResep[min_index], listResep[i]);
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
                    Showhasildokter(listData, Jumlah);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                }
                else if (pilih_menu == 1)
                {
                    Loaddataresep();
                    SelectionSort(listResep, counted);
                    Showprescription(listResep, counted);
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
                    Addprescription(listResep, listData , counted, Jumlah);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    MenuApoteker();
                }
                else if (pilih_menu == 1)
                {
                    Menushow();
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
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