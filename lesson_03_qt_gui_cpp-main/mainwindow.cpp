#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QToolBar"
#include "QFileDialog"
#include "QTextStream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pathDir(QDir::currentPath())
    , wdtHelp(nullptr)
{
    ui->setupUi(this);

    setWindowTitle(tr("Простой текстовый редактор"));

    QMenu* menuFile = new QMenu(tr("&Файл"),this);
    ui->menubar->addMenu(menuFile);
    QAction* actOpen = new QAction(tr("Открыть файл"),this);
    menuFile->addAction(actOpen);
    connect(actOpen, &QAction::triggered, this, &MainWindow::openFile);
    QAction* actSave = new QAction(tr("Сохранить файл"),this);
    menuFile->addAction(actSave);
    connect(actSave, &QAction::triggered, this, &MainWindow::saveFile);

    QMenu* menuHelp = new QMenu(tr("&Справка"),this);
    ui->menubar->addMenu(menuHelp);
    QAction* actCallingHelp = new QAction(tr("Вызов справки"),this);
    menuHelp->addAction(actCallingHelp);
    connect(actCallingHelp, &QAction::triggered, this, &MainWindow::callingHelp);

    connect(menuHelp, &QMenu::triggered, this, &MainWindow::callingHelp);

    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    statusLabel = new QLabel(this);
    statusBar()->addWidget(statusLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QFileDialog fileDialog;

    QString fileName = fileDialog.getOpenFileName(this,
        tr("Открыть файл"), pathDir, tr("Текстовые файлы (*.txt)"));

    if(fileName.isEmpty()) return;

    int index = fileName.indexOf(".txt");
    if(index == -1 || fileName.length() - 4 != index) return;

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::ExistingOnly)) return;

    QTextStream stream(&file);
    textEdit->setPlainText(stream.readAll());
    file.close();

    pathDir = fileDialog.directory().absolutePath();
    statusLabel->setText(fileName);
}

void MainWindow::saveFile()
{
    QFileDialog fileDialog;

    QString fileName = fileDialog.getSaveFileName(this,
        tr("Сохранить файл"), pathDir, tr("Текстовые файлы (*.txt)"));

    if(fileName.isEmpty()) return;

    int index = fileName.indexOf(".txt");
    if(index == -1 || fileName.length() - 4 != index)
    {
        fileName += ".txt";
    }

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Truncate)) return;

    QTextStream stream(&file);
    stream << textEdit->toPlainText();
    file.close();

    pathDir = fileDialog.directory().absolutePath();
    statusLabel->setText(fileName);
}

void MainWindow::callingHelp()
{
    if(wdtHelp != nullptr)
    {
        wdtHelp->show();
        return;
    }

    QFile file(":/help/help.txt");
    if(!file.open(QIODevice::OpenModeFlag::ReadOnly)) return;

    wdtHelp = new QDialog(this);
    QTextStream textStream(&file);
    QPlainTextEdit* textHelp = new QPlainTextEdit(textStream.readAll(),this);
    textHelp->setReadOnly(true);
    QVBoxLayout* vBoxLayout = new QVBoxLayout(wdtHelp);
    vBoxLayout->addWidget(textHelp);
    wdtHelp->setLayout(vBoxLayout);
    wdtHelp->setMinimumSize(QSize(200,200));
    wdtHelp->setWindowTitle(tr("Справка"));
    wdtHelp->show();
}

