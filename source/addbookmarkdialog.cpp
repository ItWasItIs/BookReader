#include "addbookmarkdialog.h"
#include "ui_addbookmarkdialog.h"

AddBookmarkDialog::AddBookmarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookmarkDialog)
{
    ui->setupUi(this);
}

AddBookmarkDialog::AddBookmarkDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookmarkDialog)
{
    ui->setupUi(this);
    ui->textEdit->setPlainText(text);
}

AddBookmarkDialog::~AddBookmarkDialog()
{
    delete ui;
}

QString AddBookmarkDialog::getText()
{
    return ui->textEdit->toPlainText();
}

void AddBookmarkDialog::changeEvent(QEvent *e)
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
