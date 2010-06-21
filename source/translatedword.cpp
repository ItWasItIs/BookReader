#include "translatedword.h"

TranslatedWord::TranslatedWord(QString w)
{
    word = w;
}

const QString TranslatedWord::toString() const
{
    QString *pstr = new QString();
    QTextStream ts(pstr);
    int i;
    ts<<word<<"\n";
    for(i = 0; i < listTranslation.size() - 1; i++)
    {
        ts<<"    "<<listTranslation.at(i).text<<"\n";
    }
    ts<<"    "<<listTranslation.at(i).text;
    return *pstr;
}
