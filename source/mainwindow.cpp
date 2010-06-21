#include <QKeySequence>
#include <QMouseEvent>
#include <QToolTip>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "book.h"
#include "addtranslatedialog.h"
#include "addbookmarkdialog.h"
#include "choosebookmarkdialog.h"
#include "displaywordsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    bptr = NULL;
    ui->setupUi(this);
    customizeActions();
    setWindowIcon(QIcon(":/images/mainwindow-icon.svg"));
    connect(ui->textEdit, SIGNAL(mouseMoved(QMouseEvent*)), this,
            SLOT(displayTooltip(QMouseEvent*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Text File"),
                                    QDir::homePath(), tr("Plain Text (*.txt)"));
    //Если пользователь ничего не выбрал, то сам себе злой буратино - уходим
    if(fileName.isEmpty())
        return;

    if(bptr != NULL)
        delete bptr;

    bptr = new Book(fileName);

    ui->textEdit->setHtml(QString(bptr->getText()));
    ui->statusBar->showMessage(fileName);
    ui->actionAddBookmark->setEnabled(true);
    ui->actionChooseBookmark->setEnabled(true);
    ui->actionDisplayWords->setEnabled(true);
    ui->textEdit->actionAddBookmark->setEnabled(true);
}

void MainWindow::addTranslate()
{
    QString word = ui->textEdit->textCursor().selectedText();

    AddTranslateDialog die_log(word, this);
    if(die_log.exec())
    {
        word = die_log.getWord();
        //если поля со словом и перевода не пустые
        if(!word.isEmpty() && !die_log.getTranslation().text.isEmpty())
        {
            bptr->addTranslatedWord(word, die_log.getTranslation());
        }
    }
}

void MainWindow::addBookmark()
{
    QString text = ui->textEdit->textCursor().selectedText();

    AddBookmarkDialog die_toster(text, this);
    if(die_toster.exec())
    {
        text = die_toster.getText().replace("\n", " ");
        if(!text.isEmpty()) {
            bptr->addBookmark(ui->textEdit->textCursor().position(), text);
        }
        else
            std::cerr<<"Bookmark text is empty"<<std::endl;
    }
}

void MainWindow::chooseBookmark()
{
    QStringList listStr;
    QList<int> listInt;

    for(int i = 0; i < bptr->getListBookmarks().size(); i++)
    {
        listStr<<bptr->getListBookmarks()[i].getText();
        listInt<<bptr->getListBookmarks()[i].getPos();
    }
    ChooseBookmarkDialog dialog(listStr, listInt, this);

    connect(&dialog, SIGNAL(bookmarkDeleted(int,QString)), this,
            SLOT(deleteBookmark(int, QString)));

    if(dialog.exec())
    {
        //Товарищи, просматривающие этот код в пол-второго ночи
        //непосредственно перед сдачей курсовой, помните:
        //QTextEdit::textCursor() возвращает копию
        QTextCursor tc = ui->textEdit->textCursor();
        tc.setPosition(dialog.getPosition());
        ui->textEdit->setTextCursor(tc);
    }
}

void MainWindow::deleteBookmark(int p, QString str)
{
    bptr->deleteBookmark(p, str);
}

void MainWindow::displayWords()
{
    DisplayWordsDialog dialog(bptr->wordsToString(), this);

    dialog.exec();
}

void MainWindow::displayTooltip(QMouseEvent *e)
{
    static bool isFirstTime = true;
    static int selectionStart;
    static QString selectedText;
    static bool isExisted = false; //мы выделяли существующее в словаре?
    bool isExist = false;
    int i;

    QPoint p = e->pos();

    QTextCursor tc = ui->textEdit->cursorForPosition(p);
    tc.select(QTextCursor::WordUnderCursor);

    if (selectionStart != tc.selectionStart()) {

        //проверяем, есть ли слово в словаре
        for(i = 0; i < bptr->getListWords().size(); i++)
        {
            if(!bptr->getListWords().at(i).word.compare(tc.selectedText(), Qt::CaseInsensitive))
            {
                isExist = true;
                break;
            }
            if(!bptr->getListWords().at(i).word.compare(selectedText, Qt::CaseInsensitive))
            {
                isExisted = true;
            }
        }

        if (!isFirstTime)
        {
            QToolTip::hideText();   //скрываем предыдущий тултип
            //Надо удалить выделение предыдущего слова
            QTextCursor tc(ui->textEdit->document());
            tc.setPosition(selectionStart);
            tc.select(QTextCursor::WordUnderCursor);

            if(isExisted)
                tc.insertHtml(QString("<u>" + selectedText + "</b>"));
            else
            {
                tc.insertHtml(QString(selectedText));
            }
            isExisted = false;
        }
        selectionStart = tc.selectionStart();
        selectedText = tc.selectedText();

        if (tc.selectedText().length() > 0 && isExist)
        {
//            QToolTip::showText(e->globalPos(), bptr->getListWords().at(i).toString(),
//                               ui->textEdit, ui->textEdit->cursorRect());
            QToolTip::showText(e->globalPos(), bptr->getListWords().at(i).toString(),
                               ui->textEdit, ui->textEdit->cursorRect(tc));
            isFirstTime = false;
            tc.insertHtml(QString("<b>" + tc.selectedText() + "</b>"));
        }
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Book Reader"),
                       tr("<h2>Book Reader 0.1</h2>"
                          "<p>Copyright &copy; 2010 vse.umrut@gmail.com"
                          "<p>The program is provided AS IS with NO WARRANTY"
                          "OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, "
                          "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE."
                               ));
}

void MainWindow::customizeActions()
{
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open",
                                QIcon(":/images/document-open.svg")));
    ui->actionOpen->setShortcut(QKeySequence("CTRL+O"));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));

    ui->actionExit->setIcon(QIcon::fromTheme("application-exit",
                                QIcon(":/images/application-exit.svg")));
    ui->actionExit->setShortcut(QKeySequence("CTRL+Q"));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    ui->actionAddBookmark->setIcon(QIcon::fromTheme("bookmark",
                                          QIcon(":/images/bookmark.png")));
    ui->actionAddBookmark->setShortcut(QKeySequence("CTRL+B"));
    connect(ui->actionAddBookmark, SIGNAL(triggered()), this, SLOT(addBookmark()));

    ui->actionChooseBookmark->setIcon(QIcon(":/images/emblem-choose.svg"));
    ui->actionChooseBookmark->setShortcut(QKeySequence("CTRL+C"));
    connect(ui->actionChooseBookmark, SIGNAL(triggered()), this, SLOT(chooseBookmark()));

    ui->actionDisplayWords->setIcon(QIcon(":/images/list.svg"));
    ui->actionDisplayWords->setShortcut(QKeySequence("CTRL+L"));
    connect(ui->actionDisplayWords, SIGNAL(triggered()), this, SLOT(displayWords()));

    ui->actionAboutQt->setIcon(QIcon(":/images/qt-logo.png"));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    ui->actionAboutProgram->setIcon(QIcon(":/images/mainwindow-icon.svg"));
    connect(ui->actionAboutProgram, SIGNAL(triggered()), this, SLOT(about()));

    connect(ui->textEdit->actionAdd, SIGNAL(triggered(bool)), this,
            SLOT(addTranslate()));
    connect(ui->textEdit->actionAddBookmark, SIGNAL(triggered(bool)), this,
            SLOT(addBookmark()));

    ui->mainToolBar->addAction(ui->actionOpen);
    ui->mainToolBar->addAction(ui->actionAddBookmark);
    ui->mainToolBar->addAction(ui->actionChooseBookmark);
    ui->mainToolBar->addAction(ui->actionDisplayWords);
}
