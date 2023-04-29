#ifndef MENU_H
#define MENU_H

#include <conio.h>
#include "interli.h"
#include "reglog.h"

void Menu()
{
    system("cls");
    string deskripsi_menu[3] = {"Login", "Register", "Exit"};
    string header_menu = "MENU UTAMA";
    create_menus(banyak_opsi, deskripsi_menu, header_menu);

    if (current_selection == 0)
    {
        Login();
    }
    else if (current_selection == 1)
    {
        Register();
    }
    else
    {
        exit(0);
    }

    getch();
    Menu();
}

#endif