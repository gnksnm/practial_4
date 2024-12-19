#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <windows.h>
using namespace std;

bool isrulower(char c) {
    return (c >= '�') && (c <= '�');
}
bool isruupper(char c) {
    return (c >= '�') && (c <= '�');
}
int strsize(char a[]) {
    int i = 0;
    while (*(a+i) != '\0') {
        i++;
           }
    i++;
    return(i);
}
char plusch(char a[], char b[]) {
    int al = strsize(a) + strsize(b);
    char c[10*10];
    int i = 0;
    while (a[i] != '\0') {
        c[i] = a[i];
        i++;
    }
    int j = 0;
    while (b[j] != '\0') {
        c[i] = b[j];
        i++;
        j++;
    }
    c[i] = '\0';
    cout << c;
    return('0');
}
vector<int> prfx(string pat) {
    int n = pat.length();
    vector<int> lps(n, 0);
    int i = 1;
    int len = 0;
    while (i < n) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return(lps);
}
vector<int> kmp(string str, string pstr) {
    vector <int> occur;
    vector<int> lps(prfx(pstr));
    int n = str.length();
    int m = pstr.length();
    int i = 0;
    int j = 0;
    while (i < n) {
        if (str[i] == pstr[j]) {
            i++;
            j++;
        }
        if (j == m) {
            occur.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && str[i] != pstr[j]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return (occur);
}
int linsearch(string str, string pstr) {
    int n = str.length();
    int m = pstr.length();
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (str[i + j] != pstr[j])
                break;
        }

        if (j == m)
            return i;
    }

    return -1;
}


string task2(string S) {
    vector<int> spaces = kmp(S, "  ");
    int k = 0;
    for (int i : spaces) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> dots = kmp(S, "..");
    vector<int> rdots = kmp(S, "...");
    k = 0;
    for (int i : dots) {
        for (int j : rdots) {
            if (i == j) {
                dots.erase(find(dots.begin(), dots.end(), i));
                dots.erase(find(dots.begin(), dots.end(), i + 1));
                k++;
            }
        }
    }
    k = 0;
    for (int i : dots) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> comma = kmp(S, ",,");
    k = 0;
    for (int i : comma) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> excl = kmp(S, "!!");
    k = 0;
    for (int i : excl) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> quest = kmp(S, "??");
    k = 0;
    for (int i : quest) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> dash = kmp(S, "--");
    k = 0;
    for (int i : dash) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> colon = kmp(S, "::");
    k = 0;
    for (int i : colon) {
        S.erase(i - k, 1);
        k++;
    }
    vector<int> semicolon = kmp(S, ";;");
    k = 0;
    for (int i : semicolon) {
        S.erase(i - k, 1);
        k++;
    }
   /* for (int i = 0; i < S.length(); i++) {
        if ((isruupper(S[i]) && isruupper(S[i + 1])) || (isrulower(S[i]) && isruupper(S[i + 1]))) {
            S[i + 1] = tolower(S[i + 1]);
        }
    }*/
    for (int i = 0; i < S.length(); i++) {
        if ((isupper(S[i]) && isupper(S[i + 1])) || (islower(S[i]) && isupper(S[i + 1]))) {
            S[i + 1] = tolower(S[i + 1]);
        }
    }
    return(S);
}
void task3(string S) {

    int m[3] = { 0,0,0 };
    int kr = 0;
    int figure = 0;
    int letter = 0;
    for (int i = 0; i < S.length(); i++) {
        if ((S[i] == ' ') || (S[i] == '.') || (S[i] == ',') || (S[i] == '?') || (S[i] == '!') || (S[i] == '-') || (S[i] == ':') || (S[i] == ';')) {
            if (figure && letter) {
                kr = 1;
                m[2] += 1;
            }
            else if (figure) {
                m[1] += 1;
            }

            else if (letter) {
                m[0] += 1;
            }
            letter = 0;
            figure = 0;
        }
        else if ('0' <= S[i] && S[i] <= '9') {
            figure = 1;
        }
        else {
            letter = 1;
        }

    }
    cout << "���������� ����, ��������� ������ �� ����: " << m[0] << endl;
    cout << "���������� ����, ��������� ������ �� ����: " << m[1] << endl;
    cout << "���������� ����, ��������� ��� �� ����, ��� � �� ����: " << m[2] << endl;
}
string task4(string S) {
    char n;
    char l;
    for (int i = 0; i < S.length(); i++) {
        n = S[i];
        l = n;
        switch (n) {
        case('0'):
            l = 'a';
            break;
        case('1'):
            l = 'b';
            break;
        case('2'):
            l = 'c';
            break;
        case('3'):
            l = 'd';
            break;
        case('4'):
            l = 'e';
            break;
        case('5'):
            l = 'f';
            break;
        case('6'):
            l = 'g';
            break;
        case('7'):
            l = 'h';
            break;
        case('8'):
            l = 'i';
            break;
        case('9'):
            l = 'j';
            break;
        }
        S[i] = l;
    }
    return(S);
}
void task5(string S) {
    cout << endl << "������� 5:" << endl;
    char n = '2';
    string s;
    int result;
    vector<int>occur;
    while (n != '0') {
        do {
            cout << "���� ������ ����� ���������, ������� 1, ����� 0." << endl;
            cin >> n;
        } while (n != '1' && n != '0');
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        switch (n) {
        case('1'):
            cout << "������� ���������, ������� ������ �����." << endl;
            getline(cin, s);
            cout << endl << "�������� ��������� ������:" << endl;
            result = linsearch(S, s);
            if (result == -1)
                cout << "��������� ��� � ������." << endl;
            else
                cout << "��������� ������� � ������ �� �������: " << result << endl;
            cout << endl << "�������� �����-������-������:" << endl;
            occur = kmp(S, s);
            if (occur.empty()) {
                cout << "��������� ��� � ������." << endl << endl;
            }
            else {
                cout << "��������� ������� � ������ �� ��������: ";
                for (int i : occur) {
                    cout << i << " ";
                }
                cout << endl << endl;
            }

            break;
        case('0'):
            break;
        }

    }
}


int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int l;
    char a[] = { "fox  jumps  over the  lazy dog a"};
    char b[] = { "the  lazy dog " };
    plusch(a, b);
    l=strsize(a);
    cout << l<<endl;
    string S2, S3;
    cout << "�������� ������ ����� ������:" << endl;
    cout << "1. � ����������" << endl;
    cout << "2. �� �����" << endl;
    int ans = -1;
    do {
        cout << "��� �����: ";
        cin >> ans;
    } while (ans != 1 && ans != 2);

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');


    string S;
    if (ans == 1) {
        cout << "������� �����" << endl;
        getline(cin, S);
    }
    else {
        cout << "������� ���� �� ����� � �������: ";
        string path;
        getline(cin, path);
        fstream file(path, ios_base::in);
        if (!file.is_open()) {
            cout << "�� ������� ������� ����, �������� ����������.";
            return 1;
        }
        getline(file, S);
        file.close();
    }
    cout << endl << "������� 3:" << endl;
    task3(S);
    cout << endl << "������� 2:" << endl;
    S2 = task2(S);
    cout << S2 << endl;
    cout << endl << "������� 4:" << endl;
    S3 = task4(S2);
    cout << S3 << endl;
    task5(S3);
}