#include <iostream>
#include "trie.h"
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;


// ��������� ����� ���� � ������� ������
TrieNode* getNewNode()
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� ��������� �������� �.�. ����� �����
void insert(TrieNode* root, string key)
{
	struct TrieNode* node = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
		{
			node->children[index] = getNewNode();
		}
		node = node->children[index];
	}
	node->isEndOfWord = true;
}
bool search(struct TrieNode* root, string key)
{
	TrieNode* node = root;
	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			return false;

		node = node->children[index];
	}

	return (node != nullptr && node->isEndOfWord);
}
bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}

void suggestionsRec(struct TrieNode* root, string curr_pref)
{
	if (root->isEndOfWord)
		cout << curr_pref << endl;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i]) {
			char child = 'a' + i;
			suggestionsRec(root->children[i],
				curr_pref + child);
		}
}

int printAutoSuggestions(TrieNode* root, const string txt)
{
	TrieNode* node = root;
	for (char c : txt) {
		int ind = CHAR_TO_INDEX(c);
		if (!node->children[ind])
			return 0;

		node = node->children[ind];
	}
	if (isLastNode(node)) {
		cout << txt << endl;
		return -1;
	}
	suggestionsRec(node, txt);
	return 1;
}
bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}
// ����������� ������� �������� ����� �� ������
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
	// ���� ������ ������
	if (!root)
		return nullptr;
	// ���� ����� �� ����� �����
	if (depth == key.size()) {
		// ���� ���� ������ �� ����� �����
		// ������� ������� �����
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		// ���� ���� �� �������� ���������, ������� ���
		if (isEmpty(root)) {
			delete (root);
			root = nullptr;
		}

		return root;
	}

	// ���� �� ����� �� ����� ����� ��� ����������, 
	// ��� ��� ��� � ������, ���������� �������� ��� �������
	// ���������������� �������
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	// ���� � ����� ��� ��������� �����
	// (������ ������ ���� ��� �������� �������),
	// � �� �� ������������� ������ ������.
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = nullptr;
	}
	// ���������� ����� ������
	return root;
}