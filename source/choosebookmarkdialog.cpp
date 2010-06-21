#include <QString>
#include <QStringList>
#include <iostream>
#include "choosebookmarkdialog.h"
#include "ui_choosebookmarkdialog.h"

ChooseBookmarkDialog::ChooseBookmarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseBookmarkDialog)
{
    ui->setupUi(this);
}

ChooseBookmarkDialog::ChooseBookmarkDialog(QStringList listStr,
                                           QList<int>listInt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseBookmarkDialog)
{
    ui->setupUi(this);
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteBookmark()));
    for(int i = 0; i < listStr.size(); i++)
    {
        //храним название закладки и абсолютное значение
        ui->comboBox->addItem(listStr[i], QVariant(listInt[i]));
    }
}

ChooseBookmarkDialog::~ChooseBookmarkDialog()
{
    delete ui;
}

int ChooseBookmarkDialog::getPosition()
{
    return ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
}

void ChooseBookmarkDialog::changeEvent(QEvent *e)
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

void ChooseBookmarkDialog::deleteBookmark()
{
    if(ui->comboBox->count())
    {
        //отдаем событию позицию в тексте удаленной закладки
        emit bookmarkDeleted(ui->comboBox->itemData(
                ui->comboBox->currentIndex()).toInt(), ui->comboBox->currentText());
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
    }
}
