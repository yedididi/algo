#include <iostream>

using namespace std;

int n;
int secNum = 0;
int subSecNum = 0;
int subSubSecNum = 0;

int main(void)
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string command, text;
        cin >> command >> text;

        if (command == "section")
        {
            secNum++;
            cout << secNum << " " << text << "\n";
            subSecNum = 0;
            subSubSecNum = 0;
        }
        else if (command == "subsection")
        {
            subSecNum++;
            cout << secNum << "." << subSecNum << " " << text << "\n";
            subSubSecNum = 0;
        }
        else if (command == "subsubsection")
        {
            subSubSecNum++;
            cout << secNum << "." << subSecNum << "." << subSubSecNum << " " << text << "\n";
        }
    }

}