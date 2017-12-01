#include "dnamodel.h"

DnaModel::DnaModel(QObject *parent)
    : QAbstractListModel(parent)
{
}
QVector<int> DnaModel::dna() const{return m_dna;}
void DnaModel::setDna(QVector<int> dna){
    if(m_dna == dna) return;
    m_dna= dna;
    emit dnaChanged(dna);
}
int DnaModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return dna().length();
}

QVariant DnaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return int();

    return dna().at(index.row());
}

bool DnaModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        m_dna[index.row()] = value.toInt();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DnaModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}
