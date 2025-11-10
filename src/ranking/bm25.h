#ifndef BM25_H
#define BM25_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstdint>
#include "../core/utils.h"
using namespace std;
const double BM25_K1 = 1.5;
const double BM25_B = 0.75;

class BM25
{
private:
    const unordered_map<string, vector<Posting>> *indexPtr;
    const map<DocID, DocumentInfo> *docsPtr;
    double avgDocLength;
    double calculateIDF(size_t docFreq, size_t totalDocs) const;
    void updateAvgDocLength();

public:
    BM25();
    void setIndex(const unordered_map<string, vector<Posting>> &index,
                  const map<DocID, DocumentInfo> &documents);
    double scoreTermInDoc(const string &term, DocID docId, double k1 = BM25_K1, double b = BM25_B) const;
    vector<pair<DocID, double>> topKForTerm(const string &term, int k = 10) const;
    vector<pair<DocID, double>> scoreMultiTerm(const vector<string> &terms, int k = 10) const;
};

#endif
