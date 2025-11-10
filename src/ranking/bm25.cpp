#include "bm25.h"
#include "../ranking/min_heap.h"
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <unordered_set>
using namespace std;
BM25::BM25() : indexPtr(nullptr), docsPtr(nullptr), avgDocLength(0.0) {}

void BM25::setIndex(const unordered_map<string, vector<Posting>> &index,
                    const map<DocID, DocumentInfo> &documents)
{
    indexPtr = &index;
    docsPtr = &documents;
    updateAvgDocLength();
}

double BM25::calculateIDF(size_t docFreq, size_t totalDocs) const
{
    return log(((double)totalDocs - (double)docFreq + 0.5) / ((double)docFreq + 0.5) + 1.0);
}

void BM25::updateAvgDocLength()
{
    if (!docsPtr || docsPtr->empty())
    {
        avgDocLength = 0.0;
        return;
    }
    double sum = 0.0;
    for (const auto &p : *docsPtr)
        sum += p.second.termCount;
    avgDocLength = sum / docsPtr->size();
}

double BM25::scoreTermInDoc(const string &term, DocID docId, double k1, double b) const
{
    if (!indexPtr || !docsPtr || avgDocLength <= 0.0)
        return 0.0;
    auto it = indexPtr->find(term);
    if (it == indexPtr->end())
        return 0.0;
    int termFreq = 0;
    for (const auto &posting : it->second)
    {
        if (posting.docId == docId)
        {
            termFreq = (int)posting.positions.size();
            break;
        }
    }
    if (termFreq == 0)
        return 0.0;
    auto docIt = docsPtr->find(docId);
    if (docIt == docsPtr->end())
        return 0.0;
    double docLength = (double)docIt->second.termCount;
    size_t docFreq = it->second.size();
    double idf = calculateIDF(docFreq, docsPtr->size());
    double numerator = termFreq * (k1 + 1.0);
    double denominator = termFreq + k1 * (1.0 - b + b * (docLength / avgDocLength));
    return idf * (numerator / denominator);
}

vector<pair<DocID, double>> BM25::topKForTerm(const string &term, int k) const
{
    if (!indexPtr || !docsPtr)
        return {};
    auto it = indexPtr->find(term);
    if (it == indexPtr->end())
        return {};
    MinHeap<pair<double, DocID>> heap([](const auto &a, const auto &b)
                                      { return a.first < b.first; });
    for (const auto &posting : it->second)
    {
        double s = scoreTermInDoc(term, posting.docId);
        if ((int)heap.size() < k)
            heap.push({s, posting.docId});
        else if (s > heap.top().first)
        {
            heap.pop();
            heap.push({s, posting.docId});
        }
    }
    vector<pair<DocID, double>> res;
    while (!heap.empty())
    {
        auto p = heap.pop();
        res.push_back({p.second, p.first});
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<pair<DocID, double>> BM25::scoreMultiTerm(const vector<string> &terms, int k) const
{
    if (!indexPtr || !docsPtr || terms.empty())
        return {};
    unordered_set<DocID> candidates;
    for (const auto &t : terms)
    {
        auto it = indexPtr->find(t);
        if (it != indexPtr->end())
        {
            for (const auto &p : it->second)
                candidates.insert(p.docId);
        }
    }
    vector<pair<double, DocID>> scores;
    for (DocID id : candidates)
    {
        double total = 0.0;
        for (const auto &t : terms)
            total += scoreTermInDoc(t, id);
        scores.push_back({total, id});
    }
    sort(scores.begin(), scores.end(), [](const auto &a, const auto &b)
         { return a.first > b.first; });
    vector<pair<DocID, double>> results;
    for (int i = 0; i < min((int)scores.size(), k); ++i)
        results.push_back({scores[i].second, scores[i].first});
    return results;
}
