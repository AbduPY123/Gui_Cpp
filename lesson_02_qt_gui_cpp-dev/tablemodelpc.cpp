#include "tablemodelpc.h"

ItemTableModelPC::ItemTableModelPC(QString aNamePC,QString aIP, QString aMAC)
    :namePC(aNamePC),ip(aIP),mac(aMAC)
{
    for(int i = 0; i < ItemTableModelPC::COLUMN_SIZE; ++i)
        color[i] = QBrush(QColor(255,255,255));
}

QBrush ItemTableModelPC::getColor(int column) const
{
    if(column < 0 || column >= ItemTableModelPC::COLUMN_SIZE) return QBrush();

    return color[column];
}
void ItemTableModelPC::setColor(int column, QBrush& brush)
{
    color[column] = brush;
}

TableModelPC::TableModelPC(QObject *parent)
    :QAbstractTableModel(parent)
{
}

void TableModelPC::add(std::shared_ptr<ItemTableModelPC> aItem)
{
    m_Items.push_back(aItem);
}

int TableModelPC::columnCount(const QModelIndex &parent) const
{
    return ItemTableModelPC::COLUMN_SIZE;
}

int TableModelPC::rowCount(const QModelIndex &parent) const
{
    return m_Items.size();
}

QVariant TableModelPC::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            return index.row()+1;
        case 1:
            return m_Items.at(index.row())->getNamePC();
        case 2:
            return m_Items.at(index.row())->getIP();
        case 3:
            return m_Items.at(index.row())->getMAC();
        }
    case Qt::BackgroundRole:
        return m_Items.at(index.row())->getColor(index.column());
    }
    return QVariant();
}

QVariant TableModelPC::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal) return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        switch(section)
        {
        case 0:
            return "Номер";
            break;
        case 1:
            return "Имя ПК";
            break;
        case 2:
            return "IP адрес";
            break;
        case 3:
            return "MAC адрес";
            break;
        }
    }
    return QVariant();
}

void TableModelPC::setBackgroundColor(size_t row, size_t column)
{
    if(column >= ItemTableModelPC::COLUMN_SIZE) return;
    if(row >= m_Items.size()) return;
    QColor color(127, 255, 212);
    QBrush brush(color);
    m_Items.at(row)->setColor(column,brush);
}
