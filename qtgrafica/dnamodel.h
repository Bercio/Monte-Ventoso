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
};

#endif // DNAMODEL_H
