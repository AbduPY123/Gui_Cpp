#include "widget.h"
#include "ui_widget.h"
#include "cmath"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->le_a->setValidator(new QDoubleValidator(ui->le_a));
    ui->le_b->setValidator(new QDoubleValidator(ui->le_b));
    ui->le_c->setValidator(new QDoubleValidator(ui->le_c));

    ui->le_corner->setValidator(new QDoubleValidator(ui->le_corner));
    ui->le_side1->setValidator(new QDoubleValidator(ui->le_side1));
    ui->le_side2->setValidator(new QDoubleValidator(ui->le_side2));

    connect(ui->pbtn_decision_of_an_equation,&QPushButton::clicked,
            this,&Widget::pbtn_decision_of_an_equation_clicked);

    connect(ui->pbtn_calculate_the_third_party,&QPushButton::clicked,
            this,&Widget::pbtn_calculate_the_third_party_clicked);

    connect(ui->pbtn_add_text,&QPushButton::clicked,
            this,&Widget::pbtn_add_text_clicked);
    connect(ui->pbtn_change_text,&QPushButton::clicked,
            this,&Widget::pbtn_change_text_clicked);
    connect(ui->pbtn_add_html,&QPushButton::clicked,
            this,&Widget::pbtn_add_html_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::pbtn_add_text_clicked()
{
    ui->pte_Rezults->appendPlainText(
                ui->te_Text->toPlainText());
}
void Widget::pbtn_change_text_clicked()
{
    ui->pte_Rezults->clear();
    ui->pte_Rezults->appendPlainText(
                ui->te_Text->toPlainText());

}
void Widget::pbtn_add_html_clicked()
{
    ui->pte_Rezults->clear();
    ui->te_Text->clear();

    ui->pte_Rezults->appendPlainText("<font color='red'>Hello</font>");
    ui->te_Text->setHtml("<font color='red'>Hello</font>");
}

void Widget::pbtn_calculate_the_third_party_clicked()
{
    ui->pte_Rezults->clear();

    double side1 = ui->le_side1->text().toDouble();
    double side2 = ui->le_side2->text().toDouble();
    double corner = ui->le_corner->text().toDouble();

    if(side1 == 0 || side2 == 0 || corner == 0)
    {
        ui->pte_Rezults->appendPlainText("Исходные данные не заданы.");
        return;
    }

    if(ui->rbtn_radians->isChecked())
        corner *= 180/M_PI;

    if(corner >= 180)
    {
        ui->pte_Rezults->appendPlainText("Введите корректное значение угла треугольника.");
        return;
    }

    double side3 = std::sqrt(side1*side1 + side2*side2 - 2*side1*side2*std::cos(corner));
    ui->pte_Rezults->appendPlainText("Исходные данные:");
    ui->pte_Rezults->appendPlainText("Длина первой стороны треугольника: " + QString::number(side1));
    ui->pte_Rezults->appendPlainText("Длина второй стороны треугольника: " + QString::number(side2));
    ui->pte_Rezults->appendPlainText("Значение угла треугольника в градусах: " + QString::number(corner));
    ui->pte_Rezults->appendPlainText("Расчетная длина третьей стороны треугольника: " + QString::number(side3));
}
void Widget::pbtn_decision_of_an_equation_clicked()
{
    ui->pte_Rezults->clear();

    double a = ui->le_a->text().toDouble();
    double b = ui->le_b->text().toDouble();
    double c = ui->le_c->text().toDouble();

    if(a == 0 && b == 0 && c == 0)
    {
        ui->pte_Rezults->appendPlainText("Решением уравнения является все множество действительных чисел.");
        return;
    }

    if(a == 0 && b == 0)
    {
        ui->pte_Rezults->appendPlainText("Уравнение не имеет решения.");
        return;
    }

    if(a == 0)
    {
        QString s = QString::number(-1*c/b);
        ui->pte_Rezults->appendPlainText("Уравнение имеет один действительный корень: " + s);
        return;
    }

    double d = b*b - 4*a*c;

    if(d == 0)
    {
        QString s = QString::number(-1*b/(2*a));
        ui->pte_Rezults->appendPlainText("Уравнение имеет один действительный корень: " + s);
    }
    else if(d > 0)
    {
        QString s1 = QString::number((-1*b + std::sqrt(d)) / (2*a));
        QString s2 = QString::number((-1*b - std::sqrt(d)) / (2*a));
        ui->pte_Rezults->appendPlainText("Уравнение имеет два действительных корня: x1 = " + s1 + " x2 = " + s2);
    }
    else if(d < 0)
    {
        QString re_s = QString::number((-1*b) / (2*a));
        QString im_s = QString::number(std::sqrt(std::fabs(d)) / (2*a));
        ui->pte_Rezults->appendPlainText("Уравнение имеет два комплексных корня: \nx1 = " + re_s + " + i*" + im_s +
                                         "\nx2 = " + re_s + " - i*" + im_s);
    }
}
