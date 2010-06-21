#include "translation.h"

Translation::Translation(partsp tp, QString txt)
{
    text = txt;
    type = tp;
}

Translation::Translation(const Translation &other)
{
    text = other.text;
    type = other.type;
}

void Translation::setText(QString other)
{
    text = other;
}

void Translation::setType(partsp other)
{
    type = other;
}
