#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef struct s_node
{
    string word;
    unsigned long wordLen;
    int wordAppearNum;
} t_node;

bool compare(const t_node &a, const t_node &b)
{
    if (a.wordAppearNum != b.wordAppearNum)
        return (a.wordAppearNum > b.wordAppearNum);

    if (a.wordLen != b.wordLen)
        return (a.wordLen > b.wordLen);

    return (a.word.compare(b.word) < 0); // 사전순 오름차순
}

int main(void)
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false); // sync_with_stdio(false) 대신 권장되는 방식

    int n, m;
    cin >> n >> m;

    unordered_map<string, int> wordCount;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        if (tmp.size() >= m)
        {
            wordCount[tmp]++;
        }
    }

    vector<t_node> dictionary;
    for (auto const& [word, count] : wordCount)
    {
        dictionary.push_back({word, word.size(), count});
    }

    sort(dictionary.begin(), dictionary.end(), compare);

    for (const auto& node : dictionary)
    {
        cout << node.word << "\n";
    }

    return 0;
}