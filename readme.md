Search Engine (C++ • BM25 • Inverted Index)
A fast C++ search engine with inverted indexing, BM25 ranking, autocomplete, and support for text/code/PDF/image documents.

Features

Inverted index with term positions
BM25 scoring for ranked search
Boolean AND/OR queries
Phrase search
Trie-based autocomplete
Optional PDF parsing (Poppler)
Optional OCR for images (Tesseract)

Requirements
C++17 compiler
(Optional) Poppler for PDF
(Optional) Tesseract for OCR

Installation
Clone:
git clone https://github.com/1amKhush/DSA_project_spotlight.git
cd bm25-search-engine

Optional dependencies:
macOS
xcode-select --install
brew install poppler tesseract

Ubuntu
sudo apt update
sudo apt install clang

sudo apt install poppler-utils tesseract-ocr

compile manually:
For mac/linux:
clang++ -std=c++17 \
 src/index/dependency_checker.cpp \
 src/index/file_reader.cpp \
 src/index/tokenizer.cpp \
 src/index/bloom_filter.cpp \
 src/core/inverted_index.cpp \
 src/core/utils.cpp \
 src/query/trie.cpp \
 src/query/skiplist.cpp \
 src/query/phrase_search.cpp \
 src/ranking/bm25.cpp \
 src/ranking/min_heap.cpp \
 src/clustering/clustering.cpp \
 src/clustering/disjoint_set.cpp \
 src/clustering/avl_tree.cpp \
 main.cpp \
 -o search_engine

For Windows:
g++ -std=c++17 -m64 -static-libgcc -static-libstdc++ src/index/dependency_checker.cpp src/index/file_reader.cpp src/index/tokenizer.cpp src/index/bloom_filter.cpp src/core/inverted_index.cpp src/core/utils.cpp src/query/trie.cpp src/query/skiplist.cpp src/query/phrase_search.cpp src/ranking/bm25.cpp src/ranking/min_heap.cpp src/clustering/clustering.cpp src/clustering/disjoint_set.cpp src/clustering/avl_tree.cpp main.cpp -o search_engine.exe

Usage
Run:
For mac/liux:
./search_engine

For Windows:
.\search_engine.exe

Steps:
Engine checks for Poppler/Tesseract
You provide directory path
It indexes documents
Choose search operation from menu
Supports:
Term search
Boolean AND/OR
Phrase search
Autocomplete
BM25 Top-K
Multi-term search
Document clustering

Project Structure
src/
core/ Inverted index + utilities
index/ Tokenizer, bloom filter, file reader
query/ Trie, skiplist, phrase search
ranking/ BM25, min-heap
clustering/ Cosine similarity + union-find
main.cpp CLI interface
Makefile

Algorithms Used
Inverted Index
Bloom Filter
Trie
Skiplist
BM25 Ranking
Cosine Similarity + Union-Find

Example (CLI)
Enter directory to index: ./docs
Documents indexed: 42
Unique terms: 1337

1. Search
2. AND Search
3. OR Search
4. Phrase Search
5. Autocomplete
6. Top-K BM25
7. Multi-term BM25
8. Cluster Documents

Data Structures & Time Complexities
Your search engine uses a full parade of classical and advanced DSA pieces. Here’s the full list with their roles and complexities:

1. Inverted Index
   Structure:
   Hash map → term → posting list (sorted vector of {docID, positions})
   Operations:
   Insert term: O(1) average
   Append position: O(1)
   Lookup term: O(1) average
   Posting traversal: O(m) where m = list size

2. Posting Lists (Vectors)
   Sorted arrays of docID -> positions.
   Operations:
   Binary search in list: O(log m)
   Merge/intersect two sorted lists: O(m + n)

3. Bloom Filter
   Fixed-size bit array + 3 hash functions.
   Operations:
   Insert: O(k) (k = num hash functions → 3 here)
   Query: O(k)
   Space: O(1) (constant 10KB)
   False positives: possible
   False negatives: impossible

4. Trie (Autocomplete)
   Each node stores map<char, child> + frequency.
   Operations:
   Insert word: O(L)
   Prefix search: O(P + K)
   P = prefix length
   K = number of returned suggestions
   Memory: O(total characters)

5. Skip List (Boolean Query Intersection)
   Multi-level linked structure.
   Operations:
   Search: O(log n) expected
   Intersection: O(m log n)
   Insert/delete: O(log n)
   Space: O(n)

6. AVL Tree (Clustering helper)
   Balanced BST storing doc vectors or metadata.
   Operations:
   Search: O(log n)
   Insert/delete: O(log n)
   Rotations: O(1)

7. Disjoint Set / Union-Find (Clustering)
   With path compression + union by rank.
   Operations:
   Find: α(n) ≈ almost constant
   Union: α(n)
   Space: O(n)
   (α(n) = inverse Ackermann, basically 1 for all real use cases.)

8. Min-Heap (Top-K BM25)
   Binary heap storing the current Top K docs.
   Operations:
   Insert: O(log K)
   Pop min: O(log K)
   K extractions: O(K log K)

9. Cosine Similarity (Clustering)
   TF-vector dot product.
   Complexity:
   One comparison: O(L) (L = terms in vector)
   Full clustering: O(n² · L)

10. Tokenizer
    Lowercasing, stopword removal, stemming.
    Complexity:
    Tokenizing one document: O(N) (N = characters)
    Stemming a word: O(length of word)

11. Hash Maps Throughout
    Used for:
    Term → postings
    Term → autocomplete frequency
    Stopwords
    Document metadata
    Operations:
    Insert: O(1) average
    Lookup: O(1) average

12. Vector-Based Position Lists
    Used for phrase search.
    Phrase Matching:
    Consecutive position check: O(m + n)
