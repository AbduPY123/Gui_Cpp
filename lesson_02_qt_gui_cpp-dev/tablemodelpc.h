#ifndef TABLEMODELPC_H
#define TABLEMODELPC_H

#include <QAbstractTableModel>
#include <QBrush>
#include <vector>
#include <memory>

class ItemTableModelPC
{
public:
    ItemTableModelPC(QString aNamePC,QString aIP, QString aMAC);
    ~ItemTableModelPC(){}

    static const int COLUMN_SIZE = 4;

    QString getNamePC() const {return namePC;}
    QString getIP() const {return ip;}
    QString getMAC() const {return mac;}
    QBrush getColor(int column) const;
    void setColor(int column, QBrush& brush);
private:
    QString namePC;
    QString ip;
    QString mac;
    QBrush color[COLUMN_SIZE];
};

class TableModelPC: public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModelPC(QObject *parent = nullptr);
    void add(std::shared_ptr<ItemTableModelPC> aItem);
    void setBackgroundColor(size_t row, size_t column);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<std::shared_ptr<ItemTableModelPC>> m_Items;
};

#endif // TABLEMODELPC_H
