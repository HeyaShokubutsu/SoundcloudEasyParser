#ifndef MAINPARSERWINDOW_H
#define MAINPARSERWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include "netmanager.h"

namespace Ui {
class MainParserWindow;
}

class MainParserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainParserWindow(QWidget *parent = 0);
    ~MainParserWindow();

private slots:

    void on_OK_clicked();

    void on_CANCEL_clicked();

    void on_RequestLineEdit_editingFinished();

    void on_CLEAR_clicked();

    void on_FindPath_clicked();

    void on_DISPLAY_clicked();

private:
    Ui::MainParserWindow *ui;
    QFileDialog *FileDialog;
    NetManager *NetMngr;
};

#endif // MAINPARSERWINDOW_H
