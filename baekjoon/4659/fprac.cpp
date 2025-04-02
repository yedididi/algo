#include <iostream>
#include <string>

using namespace std;

bool isVowel(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return (true);
    return (false);
}

bool passwordable(string password)
{
    int vowel = 0;
    int dup = 0;
    char beforeLetter = 0;

    for (int i = 0; password[i]; i++)
    {
        if (isVowel(password[i]))
        {
            vowel++;
            if (isVowel(beforeLetter))
                dup++;
            else
                dup = 1;
        }
        else
        {
            if (isVowel(beforeLetter))
                dup = 1;
            else
                dup++;
        }
        
        // cout << "current letter:" << password[i] << ", dup:" << dup << ", vowel:" << vowel << endl; 

        if (dup == 3)
            return (false);
        
        if (beforeLetter == password[i])
        {
            if (!(beforeLetter == 'e' || beforeLetter == 'o'))
                return (false);
        }

        beforeLetter = password[i];
    }

    if (vowel)
        return (true);
    else
        return (false);
}

int main(void)
{
    while (1)
    {
        string tmp;
        cin >> tmp;

        if (tmp == "end")
            break;
        
        if (passwordable(tmp))
            cout << "<" << tmp << "> is acceptable.\n";
        else
            cout << "<" << tmp << "> is not acceptable.\n";

    }
}