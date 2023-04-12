#include <iostream>
#include <string>
using namespace std;

string Rot13(string kata)
{
    string hasil;
    for (int i = 0; i < kata.length(); i++)
    {
        if (kata[i] >= 'A' && kata[i] <= 'Z' || kata[i] >= 'a' && kata[i] <= 'z')
        {
            if (kata[i] >= 'A' && kata[i] <= 'Z')
            {
                hasil += (kata[i] - 'A' + 13) % 26 + 'A';
            }
            else
            {
                hasil += (kata[i] - 'a' + 13) % 26 + 'a';
            }
        }
        else
        {
            hasil += kata[i];
        }
    }
    return hasil;
}