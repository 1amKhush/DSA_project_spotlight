#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>
#include <memory>
#include <random>
using namespace std;
template <typename T>
class SkipNode
{
public:
    T value;
    vector<shared_ptr<SkipNode<T>>> forward;
    SkipNode(T val, int level) : value(val), forward(level, nullptr) {}
};

template <typename T>
class SkipList
{
private:
    shared_ptr<SkipNode<T>> head;
    int maxLevel;
    int currentLevel;
    float probability;
    mt19937 rng;
    int randomLevel();

public:
    SkipList(int maxLvl = 16, float prob = 0.5);
    void insert(T value);
    bool search(T value);
    vector<T> toVector();
    vector<T> intersect(const SkipList<T> &other);
};

#endif
