#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>

//Part of speech
enum partsp {
    VERB,
    NOUN,
    ADJECTIVE,
    ADVERB,
    PRONOUN,
    PREPOSITION,
    CONJUCTION,
    INTERJECTION
};

class Translation
{
public:
    QString text;
    partsp type;

    Translation();
    Translation(partsp tp, QString txt);
    Translation(const Translation &other);

    void setText(QString other);
    void setType(partsp other);
};

#endif // TRANSLATION_H
