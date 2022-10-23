#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDoubleValidator>

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
    QDoubleValidator m_doubleValidator;

private slots:
    void pbtn_decision_of_an_equation_clicked();
    void pbtn_calculate_the_third_party_clicked();

    void pbtn_add_text_clicked();
    void pbtn_change_text_clicked();
    void pbtn_add_html_clicked();

};
#endif // WIDGET_H
