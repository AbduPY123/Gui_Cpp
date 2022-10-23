#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString pathDir;
    QDialog* wdtHelp;

    QTextEdit* textEdit;
    QLabel* statusLabel;

private slots:
    void openFile();
    void saveFile();

    void callingHelp();
};
#endif // MAINWINDOW_H
