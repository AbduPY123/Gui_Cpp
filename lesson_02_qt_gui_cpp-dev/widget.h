#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
#include <listmodelprogrammlanguages.h>
#include <tablemodelpc.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    ListViewModelProgrammLanguages* model;
    TableModelPC* modelpc;

private slots:
    void pbtn_add_language_clicked();
    void pbtn_delete_language_clicked();
    void chckb_icon_clicked();
    void pbtn_up_clicked();
    void pbtn_down_clicked();
    void pbtn_change_color_clicked();
};
#endif // WIDGET_H
