#include <iostream>
#include <fstream>
#include <ctime>
#include<string>
#include <windows.h>
#define M 32 

using namespace std;

bool isalpha(char ch) {
    if(ch>='А' && ch<='Я' || ch>='а' && ch<='я' || ch>='0' && ch<='9')
        return true;
    else return false;
}
void printToFile(ofstream& fout, string* a, int n) {  
    for (int i = 0; i < n; i++)
        fout << a[i] << endl;
}

void bubble_sort(string* a, int n) {
    string tmp;
    bool flag = true;
    for (int step = 1; flag == true && step <= n - 1; step++) {
        flag = false;
        for (int i = n - 1; i >= step; i--)

            if (a[i] < a[i - 1]) {
                tmp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = tmp;
                flag = true;
            }
    }
}

string filstr(ifstream& fin, int& n) {
    string source = "";
    char ch;
    n = 1;
    while (!fin.eof()) {
        fin.get(ch);
        if (ch == ' ' || ch == '\t' || ch == '\n')
            n++;
        if (!fin.eof())
            source.push_back(ch);

    }
    return source;
}
string* massalpha(string source, int& j,int n, int let[], int digit[])
{

    string* a = new string[100000];
    j = 0;
    for (int i = 0; i < source.size(); ) {
        while (isalpha(source[i]))
            a[j].push_back(source[i++]);
        if (a[j][0] >= 'а' && a[j][0] <= 'я')
            let[int(a[j][0]) - int('а')] ++;
        else if (a[j][0] >= 'А' && a[j][0] <= 'Я')
            let[int(a[j][0]) - int('А')] ++;
        else if (a[j][0] >= '0' && a[j][0] <= '9')
            digit[int(a[j][0]) - int('0')] ++;
        while (i < source.size() && !isalpha(source[i])) i++;
        j++;
    }
    return a;
}

void print_analysis(string source, int j, int t1, int t2, int let[], int  digit[]) {
    ofstream fout("analysis.txt");
    fout << "Введенный текст:" << endl;
    fout << source << endl;
    fout << "Вариант 1: Кириллица, По алфавиту, По возрастания, Учитывать числа, Сортировка Пузырьком" << endl;
    fout << "Количество слов: " << j << endl;
    fout << "Время сортировки: " << double(t2 - t1) / CLOCKS_PER_SEC << " sec" << endl;
    fout << "Статистика( количество слов на каждую букву алфавита):" << endl;
    for (int i = 0; i < M; i++)
        fout << char(i + int('а')) << " : " << let[i] << endl;
    for (int i = 0; i < 10; i++)
        fout << char(i + int('0')) << " : " << digit[i] << endl;
    fout.close();
}

int main() {
    int let[M]{ 0 };
    int digit[10]{ 0 };

    SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

    string path = "original.txt";
    cout<<"Enter name of input file: ";
    cin>>path;
    ifstream fin(path+".txt");
    while (!fin.is_open()) {
        cout << "Error opening file!";
        cout << "Enter name of input file: ";
        cin >> path;
        fin.open(path+".txt");
    }
    int n,j;
    string source = filstr( fin,n);
   
    fin.close();
    string* a = massalpha(source,j,n, let, digit);
    
    
    clock_t t1 = clock();
    
    bubble_sort(a, j);
    int t2 = clock();

    ofstream fout("result.txt");
    printToFile(fout, a, j);
    fout.close();

    print_analysis(source, j, t1, t2, let, digit);
    
}
