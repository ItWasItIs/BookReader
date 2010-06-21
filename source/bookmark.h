#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QString>

class Bookmark
{
    int pos;
    QString text;

public:
    Bookmark(int p, QString t = "");

    int getPos();
    QString getText();

    void setPos(int p);
    void setText(QString t);
};

#endif // BOOKMARK_H
