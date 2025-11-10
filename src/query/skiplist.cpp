#include "skiplist.h"
#include <algorithm>
using namespace std;
template <typename T>
SkipList<T>::SkipList(int maxLvl, float prob)
    : maxLevel(maxLvl), currentLevel(1), probability(prob), rng(random_device{}())
{
    head = make_shared<SkipNode<T>>(T(), maxLevel);
}

template <typename T>
int SkipList<T>::randomLevel()
{
    int level = 1;
    uniform_real_distribution<float> dist(0.0, 1.0);
    while (dist(rng) < probability && level < maxLevel)
        level++;
    return level;
}

template <typename T>
void SkipList<T>::insert(T value)
{
    vector<shared_ptr<SkipNode<T>>> update(maxLevel);
    auto current = head;
    for (int i = currentLevel - 1; i >= 0; i--)
    {
        while (current->forward[i] && current->forward[i]->value < value)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    if (!current || current->value != value)
    {
        int newLevel = randomLevel();
        if (newLevel > currentLevel)
        {
            for (int i = currentLevel; i < newLevel; i++)
                update[i] = head;
            currentLevel = newLevel;
        }
        auto newNode = make_shared<SkipNode<T>>(value, newLevel);
        for (int i = 0; i < newLevel; i++)
        {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

template <typename T>
bool SkipList<T>::search(T value)
{
    auto current = head;
    for (int i = currentLevel - 1; i >= 0; i--)
    {
        while (current->forward[i] && current->forward[i]->value < value)
            current = current->forward[i];
    }
    current = current->forward[0];
    return current && current->value == value;
}

template <typename T>
vector<T> SkipList<T>::toVector()
{
    vector<T> result;
    auto current = head->forward[0];
    while (current)
    {
        result.push_back(current->value);
        current = current->forward[0];
    }
    return result;
}

template <typename T>
vector<T> SkipList<T>::intersect(const SkipList<T> &other)
{
    vector<T> result;
    auto curr1 = head->forward[0];
    auto curr2 = other.head->forward[0];
    while (curr1 && curr2)
    {
        if (curr1->value == curr2->value)
        {
            result.push_back(curr1->value);
            curr1 = curr1->forward[0];
            curr2 = curr2->forward[0];
        }
        else if (curr1->value < curr2->value)
            curr1 = curr1->forward[0];
        else
            curr2 = curr2->forward[0];
    }
    return result;
}

template class SkipList<int>;
template class SkipList<unsigned int>;
