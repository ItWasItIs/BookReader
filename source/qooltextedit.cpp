#include <QToolTip>
#include <iostream>
#include <sstream>
#include "qooltextedit.h"
#include "ui_qooltextedit.h"

QOolTextEdit::QOolTextEdit(QWidget *parent) :
    QTextEdit(parent),
    ui(new Ui::QOolTextEdit)
{
    ui->setupUi(this);
    setMouseTracking(true);
    setReadOnly(true);

    actionAdd = new QAction(this);
    actionAdd->setText(tr("Add translate"));
    actionAdd->setIcon(QIcon(":/images/pencil.png"));
    actionAdd->setDisabled(true);

    actionAddBookmark = new QAction(this);
    actionAddBookmark->setText(tr("Add bookmark"));
    actionAddBookmark->setIcon(QIcon::fromTheme("bookmark",
                                          QIcon(":/images/bookmark.png")));
    actionAddBookmark->setDisabled(true);

    connect(this, SIGNAL(copyAvailable(bool)), this,
            SLOT(setActionsChecked(bool)));
}

QOolTextEdit::~QOolTextEdit()
{
    delete ui;
}

void QOolTextEdit::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QOolTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu *menu = createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(actionAdd);
    menu->addAction(actionAddBookmark);
    menu->exec(e->globalPos());
}

void QOolTextEdit::mouseMoveEvent(QMouseEvent *e)
{
    mouseMoved(e);
}

void QOolTextEdit::setActionsChecked(bool b)
{
    if(b)
    {
        actionAdd->setEnabled(true);
    }
    else
    {
        actionAdd->setDisabled(true);
    }
}
