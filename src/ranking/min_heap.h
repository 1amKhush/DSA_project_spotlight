#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>
#include <functional>
#include <stdexcept>
using namespace std;
template <typename T>
class MinHeap
{
private:
    vector<T> heap;
    function<bool(const T &, const T &)> compare;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }
    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    MinHeap(function<bool(const T &, const T &)> cmp = less<T>());
    void push(const T &value);
    T pop();
    const T &top() const;
    bool empty() const;
    size_t size() const;
};

#endif
