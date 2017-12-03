#ifndef DNAMODEL_H
#define DNAMODEL_H

#include <QAbstractListModel>
#include <cmath>

class DnaModel : public QAbstractListModel
{
    Q_OBJECT
    QVector<int> m_data;

public:
   Q_INVOKABLE void setDna(QVector<int> dna);
    explicit DnaModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
signals:
    void dataChanged(const QModelIndex& top, const QModelIndex& bottom, const QVector<int> &roles =QVector<int> ());
};

#endif // DNAMODEL_H
