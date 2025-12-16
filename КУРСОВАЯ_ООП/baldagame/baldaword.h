#ifndef BALDAWORD_H
#define BALDAWORD_H

#include <QString>
#include <QSet>

class BaldaWord
{
public:
    BaldaWord();

    void loadDictionary(const QSet<QString>& dict);
    bool exists(const QString& word) const;
    bool wasUsed(const QString& word) const;
    void addUsed(const QString& word);

private:
    QSet<QString> dictionary;
    QSet<QString> usedWords;
};

#endif // BALDAWORD_H
