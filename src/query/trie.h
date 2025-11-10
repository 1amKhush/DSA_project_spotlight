#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;
class TrieNode
{
public:
    unordered_map<char, shared_ptr<TrieNode>> children;
    bool isEndOfWord;
    int frequency;
    TrieNode();
};

class Trie
{
private:
    shared_ptr<TrieNode> root;
    void collectWords(shared_ptr<TrieNode> node, string prefix,
                      vector<pair<string, int>> &results);

public:
    Trie();
    void insert(const string &word);
    bool search(const string &word);
    vector<string> prefixSearch(const string &prefix, int limit = 10);
};

#endif
