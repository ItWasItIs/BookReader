#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <QList>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QHash>
#include <QTextStream>
#include "translatedword.h"
#include "translation.h"
#include "bookmark.h"

class Book
{
    QStringList listStr;
    QString path;
    QString db_path;
    QString bookmarks_db_path;
    QString lang;
    QList<TranslatedWord> listWords;
    QList<Bookmark> listBookmarks;
    int pos;

    void loadTranslatedWords();
    void addTranslatedWordToDB(const QString &word,const Translation &trans);
    void loadBookmarks();

public:
    Book(QString fileName = "", QString l = "eng");

    QString getText();
    QList<TranslatedWord> getListWords();
    QList<Bookmark> getListBookmarks();
    QString getBookPath();
    QString wordsToString() const;

    void addTranslatedWord(QString word, Translation trans);
    void addBookmark(const Bookmark &bm);
    void addBookmark(int pos, QString text);
    void deleteBookmark(int pos, QString text);
};

#endif // BOOK_H
