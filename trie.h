#pragma once
#define ALPHABET_SIZE 26

#include<string>
using namespace std;

struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	// isEndOfWord - true, если ключ является концом слова
	bool isEndOfWord;
};
TrieNode* getNewNode();
void insert(TrieNode* root, string key);
bool search(struct TrieNode* root, string key);
bool isEmpty(TrieNode* root);
TrieNode* remove(TrieNode* root, string key, int depth);
void suggestionsRec(struct TrieNode* root, string curr_pref);
int printAutoSuggestions(TrieNode* root, const string txt);