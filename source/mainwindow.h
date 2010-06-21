#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMouseEvent>
#include "book.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    Book *bptr;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void open();
    void addTranslate();
    void addBookmark();
    void chooseBookmark();
    void deleteBookmark(int p, QString str);
    void displayWords();
    void displayTooltip(QMouseEvent *e);
    void about();

private:
    Ui::MainWindow *ui;

    void customizeActions();
};

#endif // MAINWINDOW_H
