#ifndef DISPLAYWORDSDIALOG_H
#define DISPLAYWORDSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class DisplayWordsDialog;
}

class DisplayWordsDialog : public QDialog {
    Q_OBJECT
public:
    DisplayWordsDialog(QWidget *parent = 0);
    DisplayWordsDialog(QString text, QWidget *parent = 0);
    ~DisplayWordsDialog();

protected:
    void changeEvent(QEvent *e);

private slots:
    void findWord();

private:
    Ui::DisplayWordsDialog *ui;
};

#endif // DISPLAYWORDSDIALOG_H
