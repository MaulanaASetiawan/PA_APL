#ifndef REGISTRASI_H
#define REGISTRASI_H

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <chrono>
#include <thread>
#include <filesystem>
#include "rot13.h"
#include "interli.h"
#include "pasien.h"
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace filesystem;

int pilihan, indexData = 0;
string inputUsername, inputPassword;
int banyak_opsi = 3;
bool isLogin = false;

struct User
{
    string nama;
    string username;
    string password;
    string akses;
};

User users[100];

void Menu();

void DirChecker()
{
    path path = current_path();
    if (!exists(path / "Database"))
    {
        create_directory(path / "Database");
    }

    if (!exists(path / "Database/Data_User.csv"))
    {
        ofstream DataUser;
        DataUser.open("Database/Data_User.csv");
        DataUser << "Nama, Username, Password, Akses" << endl;
        DataUser.close();
    }
}

void ReadData()
{
    ifstream dataUser("Database/Data_User.csv");
    if (dataUser.is_open())
    {
        string baris;
        getline(dataUser, baris);

        while (getline(dataUser, baris))
        {
            stringstream ss(baris);
            string field;
            int fieldIndex = 0;

            User user;

            while (getline(ss, field, ','))
            {
                switch (fieldIndex)
                {
                case 0:
                    user.nama = Rot13(field);
                    break;
                case 1:
                    user.username = Rot13(field);
                    break;
                case 2:
                    user.password = Rot13(field);
                    break;
                case 3:
                    user.akses = Rot13(field);
                    break;
                }

                fieldIndex++;
            }

            users[indexData] = user;
            indexData++;
        }

        dataUser.close();
    }
}

void Input()
{
    cout << "Nama: ";
    cin >> users->nama;
    cout << "Username: ";
    cin >> users->username;
    cout << "Password: ";
    cin >> users->password;
}

void Register()
{
    system("cls");
    string deskripsi_menu[3] = {"Dokter", "Apoteker", "Pasien"};
    string header_menu = "Registrasi";
    create_menus(banyak_opsi, deskripsi_menu, header_menu);

    ofstream dataUser("Database/Data_User.csv", ios::app);
    if (current_selection == 0)
    {
        users->akses = "dokter";
        Input();
        dataUser << Rot13(users->nama) << ",";
        dataUser << Rot13(users->username) << ",";
        dataUser << Rot13(users->password) << ",";
        dataUser << Rot13(users->akses) << endl;
        dataUser.close();
        Menu();
    }
    else if (current_selection == 1)
    {
        users->akses = "apoteker";
        Input();
        dataUser << Rot13(users->nama) << ",";
        dataUser << Rot13(users->username) << ",";
        dataUser << Rot13(users->password) << ",";
        dataUser << Rot13(users->akses) << endl;
        dataUser.close();
        Menu();
    }
    else
    {
        users->akses = "pasien";
        Input();
        dataUser << Rot13(users->nama) << ",";
        dataUser << Rot13(users->username) << ",";
        dataUser << Rot13(users->password) << ",";
        dataUser << Rot13(users->akses) << endl;
        dataUser.close();
        Menu();
    }

    getch();
    Register();
}

void Login()
{
    ReadData();
    system("cls");
    cout << "Username: ";
    cin >> inputUsername;
    cout << "Password: ";
    cin >> inputPassword;
    for (int i = 0; i < indexData; i++)
    {
        if (users[i].username == inputUsername && users[i].password == inputPassword)
        {
            cout << "Login Berhasil" << endl;
            isLogin = true;
            system("cls");
            if ((users[i].akses) == "dokter")
            {
                cout << "Selamat datang, " << users[i].nama << endl;
                sleep_for(seconds(2));
                system("cls");
                // MenuDokter();
            }
            else if ((users[i].akses) == "apoteker")
            {
                cout << "Selamat datang, " << users[i].nama << endl;
                sleep_for(seconds(2));
                system("cls");
                // MenuApoteker();
            }
            else
            {
                cout << "Selamat datang, " << users[i].nama << endl;
                sleep_for(seconds(2));
                system("cls");
                MenuPasien();
            }
        }
        else
        {
            continue;
        }
    }
}

#endif