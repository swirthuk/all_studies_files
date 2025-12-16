#include "baldaword.h"

BaldaWord::BaldaWord()
{
}

void BaldaWord::loadDictionary(const QSet<QString>& dict)
{
    dictionary = dict;
}

bool BaldaWord::exists(const QString& word) const
{
    return dictionary.contains(word);
}

bool BaldaWord::wasUsed(const QString& word) const
{
    return usedWords.contains(word);
}

void BaldaWord::addUsed(const QString& word)
{
    usedWords.insert(word);
}
