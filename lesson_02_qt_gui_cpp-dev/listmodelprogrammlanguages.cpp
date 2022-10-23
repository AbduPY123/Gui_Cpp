#include "listmodelprogrammlanguages.h"

ItemProgrammLanguage::ItemProgrammLanguage(QSharedPointer<QIcon> icon,
                                           QString nameLanguage)
    :m_icon(icon),m_nameLanguage(nameLanguage)
{}
ItemProgrammLanguage::~ItemProgrammLanguage()
{}
QVariant ItemProgrammLanguage::name()
{
    return m_nameLanguage;
}
QVariant ItemProgrammLanguage::icon()
{
    return *m_icon;
}

ListViewModelProgrammLanguages::ListViewModelProgrammLanguages(
        const QVector<QSharedPointer<ItemProgrammLanguage>>& listItem,
        QObject *parent = nullptr)
    :QAbstractListModel(parent),
      m_Items(listItem)
{}
ListViewModelProgrammLanguages::~ListViewModelProgrammLanguages()
{}

QVariant ListViewModelProgrammLanguages::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return m_Items.at(index.row())->name();
        break;
    case Qt::DecorationRole:
        return m_Items.at(index.row())->icon();
        break;
    }
    return QVariant();
}
int ListViewModelProgrammLanguages::rowCount(const QModelIndex &parent) const
{
    return m_Items.size();
}

void ListViewModelProgrammLanguages::addItem(QSharedPointer<ItemProgrammLanguage>& item)
{
    if(item != nullptr)
    {
        beginResetModel();
        m_Items.push_back(item);
        endResetModel();
    }
}

void ListViewModelProgrammLanguages::deleteItem(int indexItem)
{
    if(indexItem >= 0 && indexItem < m_Items.size())
    {
        beginResetModel();
        m_Items.remove(indexItem);
        endResetModel();
    }
}

void ListViewModelProgrammLanguages::upItem(int indexItem)
{
    if(indexItem > 0 && indexItem < m_Items.size())
    {
        beginResetModel();

        auto item = m_Items.takeAt(indexItem);
        m_Items.insert(--indexItem,item);

        endResetModel();
    }
}

void ListViewModelProgrammLanguages::downItem(int indexItem)
{
    if(indexItem >= 0 && indexItem < (m_Items.size() - 1))
    {
        beginResetModel();

        auto item = m_Items.takeAt(indexItem);
        m_Items.insert(++indexItem,item);

        endResetModel();
    }
}
