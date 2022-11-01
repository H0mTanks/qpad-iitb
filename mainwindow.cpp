#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    _filename = "";
    ui->textEdit->setPlainText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");

    if (!file.isEmpty()) {
        QFile str_file(file);
        if (str_file.open(QFile::ReadOnly | QFile::Text)) {
            _filename = file;
            QTextStream input(&str_file);
            QString text = input.readAll();
            str_file.close();

            ui->textEdit->setPlainText(text);
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    if (_filename == "") {
        on_actionSave_As_triggered();
    }
    QFile str_file(_filename);
    if (str_file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream output(&str_file);

        output << ui->textEdit->toPlainText();

        str_file.flush();
        str_file.close();
    }
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save a file");

    if (!file.isEmpty()) {
        _filename = file;
        on_actionSave_triggered();
    }
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionBold_triggered()
{
    ui->textEdit->setFontWeight(QFont::Bold);
}


void MainWindow::on_actionUnbold_triggered()
{
    ui->textEdit->setFontWeight(QFont::Normal);
}


void MainWindow::on_actionSubscript_triggered()
{
    QString s = ui->textEdit->textCursor().selectedText();
    QTextCharFormat format;
    QString sformat = "<sub>" + s + "</sub>";
    ui->textEdit->textCursor().insertHtml(sformat);
}


void MainWindow::on_actionSuperscript_triggered()
{
    QString s = ui->textEdit->textCursor().selectedText();
    QTextCharFormat format;
    QString sformat = "<sup>" + s + "</sup>";
    ui->textEdit->textCursor().insertHtml(sformat);
}


void MainWindow::on_actionRegular_triggered()
{
    QString s = ui->textEdit->textCursor().selectedText();
    ui->textEdit->insertPlainText(s);
}


void MainWindow::on_actionAbout_Me_triggered()
{
    Dialog* dialog = new Dialog(this);
    dialog->show();
}

