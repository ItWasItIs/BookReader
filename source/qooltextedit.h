#ifndef QOOLTEXTEDIT_H
#define QOOLTEXTEDIT_H

#include <QtGui/QTextEdit>
#include <QtGui/QMenu>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QAction>

namespace Ui {
    class QOolTextEdit;
}

class QOolTextEdit : public QTextEdit {
    Q_OBJECT
    Q_DISABLE_COPY(QOolTextEdit)

public:
    QOolTextEdit(QWidget *parent = 0);
    ~QOolTextEdit();

    QAction *actionAdd;
    QAction *actionAddBookmark;

protected:
    void changeEvent(QEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void mouseMoved(QMouseEvent *e);

public slots:
    void setActionsChecked(bool b);

private:
    Ui::QOolTextEdit *ui;

//    void mouseMoveEvent(QMouseEvent *);
};

#endif // QOOLTEXTEDIT_H
