#ifndef ADDBOOKMARKDIALOG_H
#define ADDBOOKMARKDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class AddBookmarkDialog;
}

class AddBookmarkDialog : public QDialog {
    Q_OBJECT
    QString text;

public:
    AddBookmarkDialog(QWidget *parent = 0);
    AddBookmarkDialog(QString t, QWidget *parent = 0);
    ~AddBookmarkDialog();

    //берем содержимое textEdit
    QString getText();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddBookmarkDialog *ui;
};

#endif // ADDBOOKMARKDIALOG_H
