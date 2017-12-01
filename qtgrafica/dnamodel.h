#ifndef DNAMODEL_H
#define DNAMODEL_H

#include <QAbstractListModel>

class DnaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QVector<int> dna READ dna WRITE setDna NOTIFY dnaChanged)
    QVector<int> m_dna;

public:
    QVector<int> dna() const;
    void setDna(QVector<int> dna);
    explicit DnaModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
signals:
    void dnaChanged(QVector<int> dna);
};

#endif // DNAMODEL_H
