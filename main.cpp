#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>  
using namespace std;

void Menu();
void Menupriority();


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
int count = 0;

void showTask(ToDo list[], int count)
{
    system("cls");
    if (count == 0)
    {
        cout << "====================" << endl;
        cout << "   Jadwal Kosong    " << endl;
        cout << "====================";getch();
        cout << endl;
        Menu();
    }
    cout << "Daftar Task:\n";
    cout << "No\tNama\tUmur\t\tGol.Darah\t\tGender\t\tKeluhan\t\tWaktu Temu\t\tStatus\n";
    for (int i = 0; i < count; i++)
    {
        cout << i+1 << "\t" << list[i].nama << "\t\t" << list[i].umur << "\t\t" << list[i].goldar << "\t\t" << list[i].gender <<"\t\t"<< list[i].keluhan << "\t\t" << list[i].waktutemu << "\t\t" << list[i].status<< endl;
    }
}

void saveToFile(ToDo list[], int count)
{
    ofstream outfile("Database/Data_Pasien.csv");
    if (!outfile)
    {
        cout << "Gagal membuka file Data_Pasien." << endl;
        return;
    }
    
    outfile << "Nama,Umur,Gol.Darah,Gender,Keluhan,Waktu temu,Status" << endl;

    for (int i = 0; i < count; i++)
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


void addTask(ToDo list[], int& count)
{
    string input;
    cout << "\nNama Lengkap>> "; getline(cin,list[count].nama);
    try
    {
        cout << "Umur>> "; getline(cin,input);
        list[count].umur = stoi(input);
        if (list[count].umur < 1)
        {
            cout << "Umur salah"; getch();cout<<endl;
            addTask(list,count);
        }
    }
    catch(std::invalid_argument& e)
    {
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        addTask(list,count);
    }

    cout << "Golongan Darah>> "; getline(cin, list[count].goldar);
    cout << "Gender (L/P)>> "; getline(cin, list[count].gender);
    cout << "Keluhan>> "; getline(cin, list[count].keluhan);
    cout << "Waktu Temu>> "; getline(cin, list[count].waktutemu);

    list[count].status = "Dijadwalkan";
    count++;
    saveToFile(list, count);

    cout << "\nData berhasil disimpan ke dalam Database\n";
    cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;
    Menu();
        
}

void deleteTask()
{
    if (count == 0)
    {
        cout << "====================" << endl
             << "   Jadwal Kosong    "    << endl
             << "====================";getch();cout << endl;
        Menu();
    }

    showTask(list, count);
    string input; int index;
    cout << "\nMasukkan no Jadwal yang sudah selesai>> "; getline(cin, input);
    
    try {
        int index = stoi(input) - 1;
        if (index >= 0 && index < count && list[index].status == "Dijadwalkan")
        {
            for (int i = index; i < count - 1; i++)
            {
                list[i] = list[i+1];
            }
            count--;
            saveToFile(list, count);
            cout << "Task berhasil dihapus\n";
        }
        else
        {
            cout << "Nomor task salah atau task sudah selesai\n";
        }
    }
    catch(std::invalid_argument& e)
    {
        cout << "Inputan harus Integer\n";
        deleteTask();
    }
    cout << "Tekan Enter untuk kembali ke menu"; getch(); cout << endl;
    Menu();
}


void updateTask(ToDo list[], int& count)
{
    system("cls");
    if (count == 0)
    {
        cout << "====================" << endl
             << "   Jadwal Kosong    "    << endl
             << "====================";getch();cout << endl;
        Menu();
    }
    else
    {
        showTask(list, count);
        int choice; string input;
        try
        {
        cout << "\n\nMasukkan nomor task yang ingin diubah >> "; getline(cin,input);
        choice = stoi(input);
        }
        catch(std::invalid_argument& e) {
            cout << "Inputan harus Integer\n";
            updateTask(list,count);
        }
        if (choice <= 0 || choice > count)
        {
            cout << "Nomor task tidak valid"; getch(); cout<<endl;
            updateTask(list, count);
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
                    updateTask(list, count);
                }
                else
                {
                    list[choice-1].umur = umur;
                }
            }
            catch (std::invalid_argument& e)
            {
                cout << "Inputan harus integer"; getch(); cout << endl;
                updateTask(list, count);
            }

            cout << "Golongan Darah>> "; getline(cin, list[choice-1].goldar);
            cout << "Gender (L/P)>> "; getline(cin, list[choice-1].gender);
            cout << "Keluhan>> "; getline(cin, list[choice-1].keluhan);
            cout << "Waktu Temu>> "; getline(cin, list[choice-1].waktutemu);
            list[choice-1].status = "Dijadwalkan";

            saveToFile(list, count);
            cout << "\nData berhasil diupdate ke dalam Database\n";
            cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;
            Menu();
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
    count = 0;
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
            list[count].umur = stoi(umur);
        }
        catch (std::invalid_argument& e)
        {
            cout << "Data pada file rusak" << endl;
            infile.close();
            return;
        }

        list[count].nama = nama;
        list[count].goldar = goldar;
        list[count].gender = gender;
        list[count].keluhan = keluhan;
        list[count].waktutemu = waktutemu;
        list[count].status = status;
        count++;
        if (count == max_task)
        {
            break;
        }
    }
    infile.close();
}


void Menupriority()
{
    system("cls");
    cout <<"========================"<<endl;
    cout <<"     Periority List     "<<endl;
    cout <<"========================"<<endl;
    cout <<" [1] Sangat Penting     "<<endl;
    cout <<" [2] Penting            "<<endl;
    cout <<" [3] Cukup penting      "<<endl;
    cout <<"========================"<<endl;
}

void Menu()
{
    system("cls");
    int choice; string input;
    cout <<"===================================="<<endl;
    cout <<"              ToDo List             "<<endl;
    cout <<"===================================="<<endl;
    cout <<" [1] Tambah Task                    "<<endl;
    cout <<" [2] List Task                      "<<endl;
    cout <<" [3] Hapus Task                     "<<endl;
    cout <<" [4] Update Task                    "<<endl;
    cout <<" [0] Keluar                         "<<endl;
    cout <<"===================================="<<endl;
    try
    {
        cout <<">> "; getline(cin, input);
        choice = stoi(input);
            switch (choice)
            {
                case 1:
                    addTask(list,count);
                    break;
                case 2:
                    showTask(list, count);
                    cout<<"\nTekan Enter untuk kembali ke menu";getch();cout<<endl;
                    Menu();
                    break;
                case 3:
                    deleteTask();
                    break;
                case 4:
                    updateTask(list,count);
                    break;
                case 0:
                cout << "Keluar dari program.\n";
                exit(0);
                default:
                    cout<<"\nMenu tidak ada, Enter untuk kembali";getch();cout<<endl;
                    Menu();
            }
    }
    catch(std::invalid_argument& e)
    {
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        Menu();
    }
}

int main()
{
    int choice;
    loadData();
    system("mkdir database");
    Menu();

return 0;
}
