#include <QTextCursor>
#include <iostream>
#include "displaywordsdialog.h"
#include "ui_displaywordsdialog.h"

DisplayWordsDialog::DisplayWordsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayWordsDialog)
{
    ui->setupUi(this);
    connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(close()));
    ui->textEdit->setReadOnly(true);
}

DisplayWordsDialog::DisplayWordsDialog(QString text, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DisplayWordsDialog)
{
    ui->setupUi(this);
    ui->textEdit->setHtml(text);
    connect(ui->buttonClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->buttonFind, SIGNAL(clicked()), this, SLOT(findWord()));
    ui->textEdit->setReadOnly(true);
}

DisplayWordsDialog::~DisplayWordsDialog()
{
    delete ui;
}

void DisplayWordsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DisplayWordsDialog::findWord()
{
//    //перематываем textEdit на начало
//    QTextCursor tc;
//    tc.setPosition(0);
//    ui->textEdit->setTextCursor(tc);
    ui->textEdit->find(ui->lineEdit->text());
}
