#ifndef TRANSLATEDWORD_H
#define TRANSLATEDWORD_H

#include <QList>
#include <QString>
#include <QFile>
#include <QHash>
#include <QTextStream>
#include "translation.h"

class TranslatedWord
{
public:
    QString word;
    QList<Translation> listTranslation;

    TranslatedWord(QString w);

    const QString toString() const;
    bool operator==(TranslatedWord &other);
};

#endif // TRANSLATEDWORD_H
