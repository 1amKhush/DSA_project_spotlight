#include "min_heap.h"
#include <algorithm>
#include <cstdint>
using namespace std;
template <typename T>
MinHeap<T>::MinHeap(function<bool(const T &, const T &)> cmp) : compare(cmp) {}

template <typename T>
void MinHeap<T>::heapifyUp(int i)
{
    while (i > 0 && compare(heap[i], heap[parent(i)]))
    {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template <typename T>
void MinHeap<T>::heapifyDown(int i)
{
    int minIdx = i;
    int l = left(i);
    int r = right(i);
    if (l < (int)heap.size() && compare(heap[l], heap[minIdx]))
        minIdx = l;
    if (r < (int)heap.size() && compare(heap[r], heap[minIdx]))
        minIdx = r;
    if (minIdx != i)
    {
        swap(heap[i], heap[minIdx]);
        heapifyDown(minIdx);
    }
}

template <typename T>
void MinHeap<T>::push(const T &value)
{
    heap.push_back(value);
    heapifyUp((int)heap.size() - 1);
}

template <typename T>
T MinHeap<T>::pop()
{
    if (heap.empty())
        throw runtime_error("Heap is empty");
    T minVal = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
        heapifyDown(0);
    return minVal;
}

template <typename T>
const T &MinHeap<T>::top() const
{
    if (heap.empty())
        throw runtime_error("Heap is empty");
    return heap[0];
}

template <typename T>
bool MinHeap<T>::empty() const { return heap.empty(); }

template <typename T>
size_t MinHeap<T>::size() const { return heap.size(); }

template class MinHeap<pair<double, uint32_t>>;
