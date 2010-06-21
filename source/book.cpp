#include <QTextStream>
#include "book.h"

void Book::loadTranslatedWords()
{
    QFile file(db_path);

    try {
        //если файла нет - создаем
        if(!file.exists())
        {
            if(!file.open(QIODevice::WriteOnly))
                throw 1;
            file.close();
        }
        if(!file.open(QIODevice::ReadWrite))
            throw 2;
    }
    catch(int x) {
        if(x == 1)
        {
            std::cerr<<"Cannot open file \""<<db_path.toLocal8Bit().data()
                    <<"\" for writing"<<std::endl;
            return;
        }
        file.close();

        if(x == 2)
        {
            std::cerr<<"Cannot open file \""<<db_path.toLocal8Bit().data()
                    <<"\" for reading and writing"<<std::endl;
            return;
        }
    }

    QTextStream ts(&file);
    QString tmp = ts.readLine();
    partsp psp;

    //считывание файла
    while(!ts.atEnd())
    {
        listWords.append(*new TranslatedWord(tmp));

        tmp = ts.readLine();
        //пока строка начинается с 2х пробелов это часть речи
        while(tmp.startsWith("  ") && !ts.atEnd())
        {
            if(!tmp.compare("  verb:"))
            {
                listWords.last().listTranslation.append(*new Translation(VERB, ""));
                psp = VERB;
            }
            else if(!tmp.compare("  noun:"))
            {
                listWords.last().listTranslation.append(*new Translation(NOUN, ""));
                psp = NOUN;
            }
            else if(!tmp.compare("  adjective:"))
            {
                listWords.last().listTranslation.append(*new Translation(ADJECTIVE, ""));
                psp = ADJECTIVE;
            }
            else if(!tmp.compare("  adverb:"))
            {
                listWords.last().listTranslation.append(*new Translation(ADVERB, ""));
                psp = ADVERB;
            }
            else if(!tmp.compare("  pronoun:"))
            {
                listWords.last().listTranslation.append(*new Translation(PRONOUN, ""));
                psp = PRONOUN;
            }
            else if(!tmp.compare("  preposition:"))
            {
                listWords.last().listTranslation.append(*new Translation(PREPOSITION, ""));
                psp = PREPOSITION;
            }
            else if(!tmp.compare("  conjuction:"))
            {
                listWords.last().listTranslation.append(*new Translation(CONJUCTION, ""));
                psp = CONJUCTION;
            }
            else if(!tmp.compare("  interjection:"))
            {
                listWords.last().listTranslation.append(*new Translation(INTERJECTION, ""));
                psp = INTERJECTION;
            }


            tmp = ts.readLine();
            listWords.last().listTranslation.last().text = tmp.trimmed();
            tmp = ts.readLine();
            //пока строка начинается с 4х пробелов это перевод
            while(tmp.startsWith("    ") && !ts.atEnd())
            {
                listWords.last().listTranslation.append(*new Translation(psp, tmp.trimmed()));
                tmp = ts.readLine();
            }
        }
    }

    file.close();

//    int i;
//    int j;
//    for(i = 0; i < listWords.size(); i++)
//    {
//        tmp = listWords.at(i).word;
//        std::cout<<i<<" "<<tmp.toStdString()<<std::endl;
//
//        for(j = 0; j < listWords.at(i).listTranslation.size(); j++)
//            std::cout<<"  "<<j<<" "<<listWords.at(i).listTranslation.at(j)
//            .text.toLocal8Bit().data()<<std::endl;
//    }
}

void Book::addTranslatedWordToDB(const QString &word, const Translation &trans)
{
    QFile file(db_path);
    try {
        if(!file.open(QIODevice::ReadWrite))
            throw 1;
    }
    catch(int) {
        std::cerr<<"Cannot open file \""<<db_path.toLocal8Bit().data()
                <<"\" for reading and writing"<<std::endl;
        return;
    }

    QTextStream ts(&file);

    ts.seek(file.size() - 1);
    ts<<word<<"\n";
    if(trans.type == NOUN)
        ts<<"  noun:\n";
    if(trans.type == VERB)
        ts<<"  verb:\n";
    ts<<"    "<<trans.text<<"\n";
    ts<<"\n";

    file.close();
}

void Book::loadBookmarks()
{
    QFile file(bookmarks_db_path);

    try {
        //если файла нет - создаем
        if(!file.exists())
        {
            if(!file.open(QIODevice::WriteOnly))
                throw 1;
            file.close();
        }
        if(!file.open(QIODevice::ReadWrite))
            throw 2;
    }
    catch(int x) {
        if(x == 1)
        {
            std::cerr<<"Cannot open file \""<<bookmarks_db_path.toLocal8Bit().data()
                    <<"\" for writing"<<std::endl;
            return;
        }
        file.close();

        if(x == 2)
        {
            std::cerr<<"Cannot open file \""<<bookmarks_db_path.toLocal8Bit().data()
                    <<"\" for reading and writing"<<std::endl;
            return;
        }
    }

//    if(!file.exists())
//    {
//        if(!file.open(QIODevice::WriteOnly))
//        {
//            std::cerr<<"Cannot open file \""<<db_path.toLocal8Bit().data()
//                    <<"\" for writing"<<std::endl;
//            return;
//        }
//        file.close();
//    }
//    if(!file.open(QIODevice::ReadWrite))
//    {
//        std::cerr<<"Cannot open file \""<<db_path.toLocal8Bit().data()
//                <<"\" for reading and writing"<<std::endl;
//        return;
//    }

    QTextStream ts(&file);
    QString tmp = ts.readLine();

    while(!ts.atEnd())
    {
        listBookmarks.append(*new Bookmark(tmp.toInt()));
        tmp = ts.readLine();
        listBookmarks.last().setText(tmp);
        tmp = ts.readLine();
    }
}

Book::Book(QString fileName, QString l)
{
    path = "";
    lang = l;
    db_path = l + ".dat";
    if(fileName.isEmpty())
        return;
    bookmarks_db_path = fileName + QString(".bm");

    path = fileName;
    QFile file(fileName);
    try {
        if(!file.open(QIODevice::ReadOnly))
            throw 1;
    }
    catch(int) {
        std::cerr<<"Cannot open file \""<<path.toLocal8Bit().data()
                <<"\" for reading"<<std::endl;
        return;
    }

    loadTranslatedWords();
    loadBookmarks();

    QString tmp;
    QTextStream ts(&file);

    int i;
    //        std::cout<<listWords.size()<<std::endl;
    while(!ts.atEnd())
    {
        tmp = ts.readLine();
        for(i = 0; i < listWords.size(); i++)
        {
            if(tmp.contains(listWords.at(i).word, Qt::CaseInsensitive))
            {
                //подчеркиваем слова из словаря
                tmp.replace(listWords.at(i).word,
                            QString("<u>" +listWords.at(i).word + "</u>"), Qt::CaseInsensitive);
            }
        }
        listStr.append(tmp);
    }
}

QString Book::getText()
{
    return listStr.join("<br />");
}

QList<TranslatedWord> Book::getListWords()
{
    return listWords;
}

QList<Bookmark> Book::getListBookmarks()
{
    return listBookmarks;
}

QString Book::getBookPath()
{
    return path;
}

QString Book::wordsToString() const
{
    QString tmp;
    QTextStream ts(&tmp);

    QList<TranslatedWord> list(listWords);
    QStringList listStr;
    int i, j, k;

    //сортировка :-[
    for(i = 0; i < list.size(); i++)
    {
        listStr<<listWords[i].word;
    }
    listStr.sort();
    for(i = 0; i < listStr.size(); i++)
    {
        for(j = 0; j < list.size(); j++)
        {
            if(listStr.at(i) == list.at(j).word)
            {
                ts<<QString("<p><b>" + listStr.at(i) + "</b></p><br />");
                for(k = 0; k < list[j].listTranslation.size(); k++)
                {
                    ts<<""<<list[j].listTranslation[k].text<<"<br />";
                }
            }
        }
    }

    return tmp;
}

void Book::addTranslatedWord(QString word, Translation trans)
{
    if(word.isEmpty())
        return;
    word = word.toLower();
    trans.text = trans.text.toLower();
    for(int i = 0; i < listWords.size(); i++)
    {
        if(listWords.at(i).word == word)
        {
            listWords[i].listTranslation.append(*new Translation(trans));
            addTranslatedWordToDB(word, trans);
            return;
        }
    }
    listWords.append(*new TranslatedWord(word));
    listWords.last().listTranslation.append(*new Translation(trans));
    addTranslatedWordToDB(word, trans);
}

void Book::addBookmark(int pos, QString text)
{
    listBookmarks.append(*new Bookmark(pos, text));

    QFile file(bookmarks_db_path);
    try {
        if(!file.open(QIODevice::ReadWrite))
            throw 1;
    }
    catch(int) {
        std::cerr<<"Cannot open file \""<<bookmarks_db_path.toLocal8Bit().data()
                <<"\" for reading and writing"<<std::endl;
        return;
    }

    QTextStream ts(&file);
    ts.seek(file.size() - 1);
    ts<<pos<<"\n";
    ts<<text<<"\n\n";
}

void Book::deleteBookmark(int pos, QString text)
{
    QFile file(bookmarks_db_path);
    try {
        if(!file.open(QIODevice::ReadWrite))
            throw 1;
    }
    catch(int) {
        std::cerr<<"Cannot open file \""<<bookmarks_db_path.toLocal8Bit().data()
                <<"\" for reading and writing"<<std::endl;
        return;
    }

    QTextStream ts(&file);

    QString str = ts.readAll();
    str.replace(QString(QString::number(pos) + "\n"), "");
    str.replace(QString(text + "\n"), "");
    file.remove();
    file.open(QIODevice::ReadWrite);
    ts<<str;

    for(int i = 0; i < listBookmarks.size(); i++)
    {
        if(listBookmarks[i].getText() == text)
            listBookmarks.removeAt(i);
    }
}
