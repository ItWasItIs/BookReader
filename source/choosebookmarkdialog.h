#ifndef CHOOSEBOOKMARKDIALOG_H
#define CHOOSEBOOKMARKDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class ChooseBookmarkDialog;
}

class ChooseBookmarkDialog : public QDialog {
    Q_OBJECT
public:
    ChooseBookmarkDialog(QWidget *parent = 0);
    ChooseBookmarkDialog(QStringList listStr,QList<int> listInt,
                         QWidget *parent = 0);
    ~ChooseBookmarkDialog();

    int getPosition();

protected:
    void changeEvent(QEvent *e);

private slots:
    void deleteBookmark();

private:
    Ui::ChooseBookmarkDialog *ui;

signals:
    void bookmarkDeleted(int pos, QString str);
};

#endif // CHOOSEBOOKMARKDIALOG_H
