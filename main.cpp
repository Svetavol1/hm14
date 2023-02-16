#include<iostream>
#include "trie.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    TrieNode* root = getNewNode();
    insert(root, "hello");
    insert(root, "dog");
    insert(root, "hell");
    insert(root, "cat");
    string input;
    cin >> input;
    int res = printAutoSuggestions(root, input);

    if (res == 0)
        cout << "Ничего не найдено!\n";

    return 0;
}