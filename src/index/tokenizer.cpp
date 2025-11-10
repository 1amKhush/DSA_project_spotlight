#include "tokenizer.h"
#include <cctype>
#include <algorithm>
using namespace std;
const unordered_set<string> Tokenizer::STOPWORDS = {
    "the", "is", "at", "which", "on", "a", "an", "and", "or", "but",
    "in", "with", "to", "for", "of", "as", "by", "that", "this", "it",
    "from", "be", "are", "was", "were", "been", "have", "has", "had"};

string Tokenizer::stem(const string &word)
{
    if (word.length() <= 3)
        return word;
    string result = word;
    if (endsWith(result, "ing") && result.length() > 5)
        result = result.substr(0, result.length() - 3);
    else if (endsWith(result, "ed") && result.length() > 4)
        result = result.substr(0, result.length() - 2);
    else if (endsWith(result, "ly") && result.length() > 4)
        result = result.substr(0, result.length() - 2);
    else if (endsWith(result, "s") && result.length() > 3 && !endsWith(result, "ss"))
        result = result.substr(0, result.length() - 1);
    return result;
}

bool Tokenizer::endsWith(const string &str, const string &suffix)
{
    if (str.length() < suffix.length())
        return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

vector<string> Tokenizer::tokenize(const string &text)
{
    vector<string> tokens;
    string word;
    for (char c : text)
    {
        if (isalnum(static_cast<unsigned char>(c)))
            word += tolower(static_cast<unsigned char>(c));
        else if (!word.empty())
        {
            if (STOPWORDS.find(word) == STOPWORDS.end())
                tokens.push_back(stem(word));
            word.clear();
        }
    }
    if (!word.empty() && STOPWORDS.find(word) == STOPWORDS.end())
        tokens.push_back(stem(word));
    return tokens;
}
