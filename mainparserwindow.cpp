#include "mainparserwindow.h"
#include "ui_mainparserwindow.h"

MainParserWindow::MainParserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainParserWindow),
    FileDialog(new QFileDialog),
    NetMngr(new NetManager)
{
    ui->setupUi(this);
}

MainParserWindow::~MainParserWindow()
{
    delete ui;
    delete FileDialog;
    delete NetMngr;
}

void MainParserWindow::on_CANCEL_clicked()
{
    QApplication::quit();
}

void MainParserWindow::on_OK_clicked()
{
    QUrl url("https://soundcloud.com/search?q=" + ui->RequestLineEdit->text());
    qDebug() << url;
    NetMngr->getData(url);
    NetMngr->parseSource(ui->PathLineEdit->text());
}

void MainParserWindow::on_RequestLineEdit_editingFinished()
{
    //ui->debugSpace->append(ui->UrlLineEdit->text());
}

void MainParserWindow::on_CLEAR_clicked()
{
    ui->debugSpace->clear();

    //Just an experiment, downloads math archive from kantiana.ru
    /*QUrl url(ui->RequestLineEdit->text());
    QString site1 = "https://www.kantiana.ru/mathematics/umk/analis";
    QString site2 = ".pdf";
    for(qint8 i = 1; i <= 74; i++)
    {
        if(i == 57){continue;}
        QFile output("C:\\Users\\<Username>\\Downloads\\MATAN_IMK\\lecture" + QString::number(i) + ".pdf");
        output.open(QIODevice::WriteOnly);
        QUrl url = site1 + (i <= 9 ? ("0" + QString::number(i)) : QString::number(i)) + site2;
        output.write(NetMngr->getData(url));
        output.close();
    }*/
}

void MainParserWindow::on_FindPath_clicked()
{
    ui->PathLineEdit->clear();
    ui->PathLineEdit->insert(FileDialog->getExistingDirectory(this, "Save as"));
}

void MainParserWindow::on_DISPLAY_clicked()
{
    ui->debugSpace->insertHtml(QString::fromUtf8(NetMngr->gotData));
}
