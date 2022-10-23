#ifndef LISTMODELPROGRAMMLANGUAGES_H
#define LISTMODELPROGRAMMLANGUAGES_H

#include <QAbstractListModel>
#include <QIcon>
#include <QString>

class ItemProgrammLanguage
{
public:
    ItemProgrammLanguage(QSharedPointer<QIcon> icon,
                         QString nameLanguage);
    ~ItemProgrammLanguage();

    QVariant name();
    QVariant icon();
private:
    QSharedPointer<QIcon> m_icon;
    QString m_nameLanguage;
};

class ListViewModelProgrammLanguages: public QAbstractListModel
{
    Q_OBJECT
public:
    ListViewModelProgrammLanguages(
            const QVector<QSharedPointer<ItemProgrammLanguage>>& listItem,
            QObject *parent);
    ~ListViewModelProgrammLanguages();

    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void addItem(QSharedPointer<ItemProgrammLanguage>& item);
    void deleteItem(int indexItem);

    void upItem(int indexItem);
    void downItem(int indexItem);

private:
    QVector<QSharedPointer<ItemProgrammLanguage>> m_Items;
};

#endif // LISTMODELPROGRAMMLANGUAGES_H
