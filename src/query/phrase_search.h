#ifndef PHRASE_SEARCH_H
#define PHRASE_SEARCH_H

#include <vector>
#include <string>
#include <unordered_map>
#include "../core/utils.h"
using namespace std;
class PhraseSearch
{
public:
    static bool containsPhrase(
        DocID docId,
        const vector<string> &terms,
        const unordered_map<string, vector<Posting>> &index);
    static vector<DocID> searchPhrase(
        const vector<string> &terms,
        const unordered_map<string, vector<Posting>> &index);
};

#endif
