#include "addtranslatedialog.h"
#include "ui_addtranslatedialog.h"

AddTranslateDialog::AddTranslateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTranslateDialog)
{
    ui->setupUi(this);
}

AddTranslateDialog::AddTranslateDialog(QString word, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTranslateDialog)
{
    ui->setupUi(this);
    ui->lineEditWord->setText(word);
    ui->rbVerb->setChecked(true);   //RadioButton по умолчанию
}

AddTranslateDialog::~AddTranslateDialog()
{
    delete ui;
}

QString AddTranslateDialog::getWord()
{
    return ui->lineEditWord->text();
}

Translation AddTranslateDialog::getTranslation()
{
    QString word;
    QString tr;
    partsp ps;

    word = ui->lineEditWord->text();
    tr = ui->lineEditTranslate->text();
    if(ui->rbNoun->isChecked())
        ps = NOUN;
    if(ui->rbVerb->isChecked())
        ps = VERB;
    if(ui->rbAdjective->isChecked())
        ps = ADJECTIVE;
    if(ui->rbAdverb->isChecked())
        ps = ADVERB;
    if(ui->rbConjuction->isChecked())
        ps = CONJUCTION;
    if(ui->rbInterjection->isChecked())
        ps = INTERJECTION;
    if(ui->rbPreposition->isChecked())
        ps = PREPOSITION;
    if(ui->rbPronoun->isChecked())
        ps = PRONOUN;

    return Translation(ps, tr);
}

void AddTranslateDialog::changeEvent(QEvent *e)
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
