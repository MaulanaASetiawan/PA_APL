#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>  
using namespace std;

void Menu(), Menupriority();
struct ToDo {
    string task;
    string deadline;
    string status;
    int priority;
};
const int max_task = 100;
ToDo list[max_task];
int count = 0;


void showTask(ToDo list[], int count) {
    system("cls");
    if (count == 0){
        cout << "=================" << endl
             << "   Task Kosong"    << endl
             << "=================";getch();cout << endl;
        Menu();
    }
    cout << "Daftar Task:\n";
    cout << "No\tPriority\tTask\t\tDeadline\tStatus\n";
    for (int i = 0; i < count; i++) {
        cout << i+1 << "\t" << list[i].priority << "\t\t" << list[i].task << "\t\t" << list[i].deadline << "\t" << list[i].status << endl;
    }
}

void saveToFile(ToDo list[], int count) {
    ofstream outfile("todolist.csv");
    if (!outfile) {
        cout << "Gagal membuka file todolist.csv." << endl;
        return;
    }

    outfile << "Priority,Task,Deadline,Status" << endl;
    for (int i = 0; i < count; i++) {
        outfile << list[i].priority << ",";
        outfile << list[i].task << ",";
        outfile << list[i].deadline << ",";
        outfile << list[i].status << endl;
    }
}


void addTask(ToDo list[], int count){
    string input;
    Menupriority();
    try{
        cout << "\nMasukkan prioritas (1-3)>> "; getline(cin,input);//cin >> list[count].priority;
        list[count].priority = stoi(input);
        if (list[count].priority > 3) {
            cout << "Priority salah"; getch();cout<<endl;
            addTask(list,count);
        }
    }catch(std::invalid_argument& e){
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        addTask(list,count);
    }
        cout << "Masukkan task baru>> "; getline(cin, list[count].task);
        cout << "Masukkan deadline (DD/MM/YYYY)>> "; getline(cin, list[count].deadline);
        list[count].status = "Belum selesai";
        count++;
        saveToFile(list, count);

        cout << "\nData berhasil disimpan ke dalam file todolist.csv\n";
        cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;
        Menu();
        
}

void deleteTask() {
    if (count == 0) {
        cout << "Belum ada task!"; getch(); cout << endl;
        Menu();
    }
    showTask(list, count);
    string input; int index;
    cout << "\nMasukkan nomor task yang sudah selesai>> "; getline(cin, input);
    try {
        int index = stoi(input) - 1;
        if (index >= 0 && index < count && list[index].status == "Belum selesai") {
            for (int i = index; i < count - 1; i++) {
                list[i] = list[i+1];
            }
            count--;
            saveToFile(list, count);
            cout << "Task berhasil dihapus\n";
        } else {
            cout << "Nomor task salah atau task sudah selesai\n";
        }
    } catch(std::invalid_argument& e) {
        cout << "Inputan harus Integer\n";
        deleteTask();
    }
    cout << "Tekan Enter untuk kembali ke menu"; getch(); cout << endl;
    Menu();
}


void updateTask(ToDo list[], int count) {
    system("cls");
    if (count == 0) {
        cout << "Belum ada task!"; getch(); cout<< endl;
        Menu();
    }
    else {
        showTask(list, count);
        int choice; string input;
        try{
        cout << "\n\nMasukkan nomor task yang ingin diubah >> "; getline(cin,input);
        choice = stoi(input);
        }catch(std::invalid_argument& e) {
            cout << "Inputan harus Integer\n";
            updateTask(list,count);
        }
        if (choice <= 0 || choice > count) {
            cout << "Nomor task tidak valid"; getch(); cout<<endl;
            updateTask(list, count);
        }
        else {
            try {
                cout << "\nUbah priority menjadi >> ";getline(cin, input);
                int priority = stoi(input);
                if (priority < 1 || priority > 3) {
                    cout << "Priority tidak valid";getch(); cout<<endl;
                    updateTask(list, count);
                }
                else {
                    list[choice-1].priority = priority;
                }
            } catch (std::invalid_argument& e){
                cout << "Inputan harus integer"; getch(); cout << endl;
                updateTask(list, count);
            }
            cout << "Task Baru>> ";getline(cin, list[choice-1].task);
            cout << "Deadline Baru>> "; getline(cin, list[choice-1].deadline);
            list[choice-1].status = "Belum Selesai";

            saveToFile(list, count);
            cout << "\nData berhasil diupdate ke dalam file todolist.csv\n";
            cout << "Tekan Enter untuk kembali ke menu";getch(); cout<<endl;
            Menu();
        }
    }
}


void loadData() {
    ifstream infile("todolist.csv");
    if (!infile.is_open()) {
        cout << "File tidak ditemukan" << endl;
        return;
    }
    string line;
    getline(infile, line); // skip header line
    count = 0;
    while (getline(infile, line)) {
        stringstream iss(line);
        string priority_str, task, deadline, status;
        getline(iss, priority_str, ',');
        getline(iss, task, ',');
        getline(iss, deadline, ',');
        getline(iss, status, ',');
        try {
            list[count].priority = stoi(priority_str);
        } catch (std::invalid_argument& e) {
            cout << "Data pada file rusak" << endl;
            infile.close();
            return;
        }
        list[count].task = task;
        list[count].deadline = deadline;
        list[count].status = status;
        count++;
        if (count == max_task) {
            break;
        }
    }
    infile.close();
}


void Menupriority(){
    system("cls");
    cout<<"========================"<<endl
        <<"     Periority List     "<<endl
        <<"========================"<<endl
        <<" [1] Sangat Penting     "<<endl
        <<" [2] Penting            "<<endl
        <<" [3] Cukup penting      "<<endl
        <<"========================"<<endl;
}

void Menu(){
    
    system("cls");
    int choice; string input;

    cout <<"===================================="<<endl
         <<"              ToDo List             "<<endl
         <<"===================================="<<endl
         <<" [1] Tambah Task                    "<<endl
         <<" [2] List Task                      "<<endl
         <<" [3] Hapus Task                     "<<endl
         <<" [4] Update Task                    "<<endl
         <<" [0] Keluar                         "<<endl
         <<"===================================="<<endl;
    try{
    cout <<">> "; getline(cin, input);
    choice = stoi(input);
        switch (choice) {
            case 1:
                addTask(list,count);
                break;
            case 2:
                loadData();
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
    }catch(std::invalid_argument& e){
        cout<<"Inputan harus Integer"; getch(); cout << endl;
        Menu();
    }
}

int main(){
    int choice;
    Menu();
return 0;
}
