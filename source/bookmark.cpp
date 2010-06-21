#include <iostream>
#include "bookmark.h"

Bookmark::Bookmark(int p, QString t)
{
    pos = p;
    text = t;
}

int Bookmark::getPos()
{
    return pos;
}

QString Bookmark::getText()
{
    return text;
}

void Bookmark::setPos(int p)
{
    pos = p;
}

void Bookmark::setText(QString t)
{
    try {
        if(!t.isEmpty())
            throw 1;
    }
    catch(int) {
        std::cerr<<"Bookmark text is empty"<<std::endl;
        return;
    }

    text = t;
}
