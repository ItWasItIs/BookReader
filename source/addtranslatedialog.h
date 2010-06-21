#ifndef ADDTRANSLATEDIALOG_H
#define ADDTRANSLATEDIALOG_H

#include <QDialog>
#include <QString>
#include "book.h"

namespace Ui {
    class AddTranslateDialog;
}

class AddTranslateDialog : public QDialog {
    Q_OBJECT
public:
    AddTranslateDialog(QWidget *parent = 0);
    AddTranslateDialog(QString word, QWidget *parent = 0);
    ~AddTranslateDialog();

    QString getWord();
    Translation getTranslation();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddTranslateDialog *ui;
};

#endif // ADDTRANSLATEDIALOG_H
