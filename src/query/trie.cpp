#include "trie.h"
#include <algorithm>
using namespace std;
TrieNode::TrieNode() : isEndOfWord(false), frequency(0) {}

Trie::Trie() : root(make_shared<TrieNode>()) {}

void Trie::insert(const string &word)
{
    auto node = root;
    for (char ch : word)
    {
        if (node->children.find(ch) == node->children.end())
            node->children[ch] = make_shared<TrieNode>();
        node = node->children[ch];
    }
    node->isEndOfWord = true;
    node->frequency++;
}

bool Trie::search(const string &word)
{
    auto node = root;
    for (char ch : word)
    {
        if (node->children.find(ch) == node->children.end())
            return false;
        node = node->children[ch];
    }
    return node->isEndOfWord;
}

void Trie::collectWords(shared_ptr<TrieNode> node, string prefix,
                        vector<pair<string, int>> &results)
{
    if (node->isEndOfWord)
        results.push_back({prefix, node->frequency});
    for (auto &[ch, child] : node->children)
        collectWords(child, prefix + ch, results);
}

vector<string> Trie::prefixSearch(const string &prefix, int limit)
{
    auto node = root;
    for (char ch : prefix)
    {
        if (node->children.find(ch) == node->children.end())
            return {};
        node = node->children[ch];
    }
    vector<pair<string, int>> results;
    collectWords(node, prefix, results);
    sort(results.begin(), results.end(),
         [](const auto &a, const auto &b)
         { return a.second > b.second; });
    vector<string> words;
    for (int i = 0; i < min(limit, (int)results.size()); i++)
        words.push_back(results[i].first);
    return words;
}
