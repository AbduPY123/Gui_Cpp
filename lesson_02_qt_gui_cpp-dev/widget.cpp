#include "widget.h"
#include "ui_widget.h"
#include "QAbstractItemView"

QVector<QSharedPointer<ItemProgrammLanguage>> getVectorItemsProgrammLanguage()
{
    QVector<QSharedPointer<ItemProgrammLanguage>> items;

    QPixmap icon_cpp = QPixmap(":/icons/cpp.jpg");
    icon_cpp.scaled(40,40);
    QSharedPointer<ItemProgrammLanguage> item =
            QSharedPointer<ItemProgrammLanguage>(
                new ItemProgrammLanguage(
                        QSharedPointer<QIcon>(new QIcon(icon_cpp)),
                                              "C++"));
    items.push_back(item);

    QPixmap icon_python = QPixmap(":/icons/python.png");
    icon_python.scaled(40,40);
    item = QSharedPointer<ItemProgrammLanguage>(
               new ItemProgrammLanguage(
                        QSharedPointer<QIcon>(new QIcon(icon_python)),
                                              "Python"));
    items.push_back(item);

    QPixmap icon_java = QPixmap(":/icons/java.png");
    icon_java.scaled(40,40);
    item = QSharedPointer<ItemProgrammLanguage>(
               new ItemProgrammLanguage(
                   QSharedPointer<QIcon>(new QIcon(icon_java)),
                                         "Java"));
    items.push_back(item);

    QPixmap icon_csh = QPixmap(":/icons/csh.jpg");
    icon_csh.scaled(40,40);
    item = QSharedPointer<ItemProgrammLanguage>(
               new ItemProgrammLanguage(
                   QSharedPointer<QIcon>(new QIcon(icon_csh)),
                                         "C#"));
    items.push_back(item);

    QPixmap icon_php = QPixmap(":/icons/php.png");
    icon_php.scaled(40,40);
    item = QSharedPointer<ItemProgrammLanguage>(
               new ItemProgrammLanguage(
                   QSharedPointer<QIcon>(new QIcon(icon_php)),
                                         "PHP"));
    items.push_back(item);

    QPixmap icon_javascript = QPixmap(":/icons/javascript.png");
    icon_javascript.scaled(40,40);
    item = QSharedPointer<ItemProgrammLanguage>(
               new ItemProgrammLanguage(
                   QSharedPointer<QIcon>(new QIcon(icon_javascript)),
                                         "Javascript"));
    items.push_back(item);

    return items;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pbtn_add_language,&QPushButton::clicked,
            this,&Widget::pbtn_add_language_clicked);

    connect(ui->pbtn_delete_language,&QPushButton::clicked,
            this,&Widget::pbtn_delete_language_clicked);

    connect(ui->chckb_icon,&QPushButton::clicked,
            this,&Widget::chckb_icon_clicked);

    connect(ui->pbtn_up,&QPushButton::clicked,
            this,&Widget::pbtn_up_clicked);

    connect(ui->pbtn_down,&QPushButton::clicked,
            this,&Widget::pbtn_down_clicked);

    model = new ListViewModelProgrammLanguages(
                    getVectorItemsProgrammLanguage(),this);

    ui->lv_languages->setModel(model);
    ui->lv_languages->setSelectionMode(QAbstractItemView::SingleSelection);

    chckb_icon_clicked();

    modelpc = new TableModelPC(this);
    modelpc->add(std::make_shared<ItemTableModelPC>("PC1","192.168.0.1","fe:df:00:01:00:01"));
    modelpc->add(std::make_shared<ItemTableModelPC>("PC2","192.168.1.1","fe:df:00:01:01:01"));
    modelpc->add(std::make_shared<ItemTableModelPC>("PC3","192.168.2.1","fe:df:00:01:02:01"));

    ui->tv_pc->setModel(modelpc);
    ui->tv_pc->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(ui->pbtn_change_color,&QPushButton::clicked,
            this,&Widget::pbtn_change_color_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::pbtn_add_language_clicked()
{
    QPixmap icon = QPixmap(":/icons/programlanguage.png");
    icon.scaled(40,40);

    QSharedPointer<ItemProgrammLanguage> item =
            QSharedPointer<ItemProgrammLanguage>(
                new ItemProgrammLanguage(
                        QSharedPointer<QIcon>(
                            new QIcon(icon)),
                        ui->le_name_language->text()));
    model->addItem(item);
}

void Widget::pbtn_delete_language_clicked()
{
    QModelIndex indx = ui->lv_languages->currentIndex();
    if(indx.isValid())
    {
        model->deleteItem(indx.row());
    }
}

void Widget::chckb_icon_clicked()
{
    if(ui->chckb_icon->isChecked())
        ui->lv_languages->setViewMode(QListView::IconMode);
    else
        ui->lv_languages->setViewMode(QListView::ListMode);
}

void Widget::pbtn_up_clicked()
{
    QModelIndex indx = ui->lv_languages->currentIndex();
    if(indx.isValid())
    {
        model->upItem(indx.row());
    }
}

void Widget::pbtn_down_clicked()
{
    QModelIndex indx = ui->lv_languages->currentIndex();
    if(indx.isValid())
    {
        model->downItem(indx.row());
    }
}

void Widget::pbtn_change_color_clicked()
{
    QModelIndexList indxlist = ui->tv_pc->selectionModel()->selectedIndexes();
    for(const auto& indx : indxlist)
    {
        if(indx.isValid())
        {
            modelpc->setBackgroundColor(indx.row(),indx.column());
        }
    }
}
