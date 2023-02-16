#include <iostream>
#include "trie.h"
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;


// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode()
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает вкачестве литового т.е. конец слова
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
// Рекурсивная функция удаления ключа из дерева
TrieNode* remove(TrieNode* root, string key, int depth = 0)
{
	// Если дерево пустое
	if (!root)
		return nullptr;
	// Если дошли до конца ключа
	if (depth == key.size()) {
		// Этот узел больше не конец слова
		// поэтому снимаем метку
		if (root->isEndOfWord)
			root->isEndOfWord = false;
		// Если ключ не является префиксом, удаляем его
		if (isEmpty(root)) {
			delete (root);
			root = nullptr;
		}

		return root;
	}

	// Пока не дошли до конца ключа или определили, 
	// что его нет в дереве, рекурсивно вызываем для ребенка
	// соответствующего символа
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	// Если у корня нет дочернего слова
	// (удален только один его дочерний элемент),
	// и он не заканчивается другим словом.
	if (isEmpty(root) && root->isEndOfWord == false) {
		delete (root);
		root = nullptr;
	}
	// возвращаем новый корень
	return root;
}