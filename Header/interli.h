#ifndef INTERLI_H
#define INTERLI_H

#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

int current_selection = 0;

void create_menus(int number_of_options, string description_of_options[], string menu_header)
{
    while (true)
    {
        system("cls || clear");
        cout << setw((80 - menu_header.size()) / 2) << "";
        cout << "======= " << menu_header << " =======" << setw((80 - menu_header.size()) / 2) << "" << endl;

        for (int i = 0; i < number_of_options; i++)
        {
            cout << setw((80 - description_of_options[i].size()) / 2) << "" << (current_selection == i ? ">>" : "  ") << "      " << description_of_options[i] << "     " << (current_selection == i ? "<<" : " ") << setw((80 - description_of_options[i].size() - 6) / 2) << "" << endl;
        }

        cout << setw((80 - 10) / 2) << "";
        cout << "==========================" << setw((80 - 10) / 2) << "" << endl;

        char key = getch();

        if (key == 72)
        { /*arrow up*/
            current_selection = (current_selection == 0 ? number_of_options - 1 : current_selection - 1);
        }
        else if (key == 80)
        { /*arrow down*/
            current_selection = (current_selection == number_of_options - 1 ? 0 : current_selection + 1);
        }
        else if (key == 13)
        { /*enter*/
            system("cls || clear");
            break;
        }
    }
}

#endif