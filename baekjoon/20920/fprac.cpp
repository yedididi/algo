#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

typedef struct s_node
{
    string word;
    unsigned long wordLen;
    int wordAppearNum;
} t_node;

int n, m;
vector<t_node> dictionary;

bool compare(const t_node &a, const t_node &b)
{
    if (a.wordAppearNum != b.wordAppearNum)
        return (a.wordAppearNum > b.wordAppearNum);
    
    if (a.wordLen != b.wordLen)
        return (a.wordLen > b.wordLen);
    
    int compareNum = a.word.compare(b.word);
    return (compareNum != 0);
}

int main(void)
{
    cin.tie(NULL);
    // sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;

        if (tmp.size() >= m)
        {    
            auto itr = find(dictionary.begin(), dictionary.end(), tmp);
            if (itr == dictionary.end())
            {
                t_node newNode = {tmp, tmp.size(), 1};
                dictionary.push_back(newNode);
            }
            else
                itr->wordAppearNum++;
        }
    }

    sort(dictionary.begin(), dictionary.end(), compare);

    for (auto itr = dictionary.begin(); itr != dictionary.end(); itr++)
        cout << itr->word << "\n";
}