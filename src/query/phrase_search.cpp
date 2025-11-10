#include "phrase_search.h"
#include <algorithm>
#include <unordered_set>
using namespace std;
bool PhraseSearch::containsPhrase(DocID docId, const vector<string> &terms,
                                  const unordered_map<string, vector<Posting>> &index)
{
    if (terms.empty())
        return false;
    auto it = index.find(terms[0]);
    if (it == index.end())
        return false;
    vector<unsigned int> first;
    for (const auto &p : it->second)
        if (p.docId == docId)
            first = p.positions;
    for (unsigned int pos : first)
    {
        bool found = true;
        for (size_t i = 1; i < terms.size(); i++)
        {
            auto it2 = index.find(terms[i]);
            if (it2 == index.end())
            {
                found = false;
                break;
            }
            vector<unsigned int> positions;
            for (const auto &p : it2->second)
                if (p.docId == docId)
                    positions = p.positions;
            if (find(positions.begin(), positions.end(), pos + i) == positions.end())
            {
                found = false;
                break;
            }
        }
        if (found)
            return true;
    }
    return false;
}

vector<DocID> PhraseSearch::searchPhrase(const vector<string> &terms,
                                         const unordered_map<string, vector<Posting>> &index)
{
    vector<DocID> res;
    if (terms.empty())
        return res;
    unordered_set<DocID> docs;
    for (const auto &[term, posts] : index)
        for (const auto &p : posts)
            docs.insert(p.docId);
    for (auto id : docs)
        if (containsPhrase(id, terms, index))
            res.push_back(id);
    return res;
}
