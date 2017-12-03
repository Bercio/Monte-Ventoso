#include "dnamodel.h"

DnaModel::DnaModel(QObject *parent)
    : QAbstractListModel(parent)
{
}
void DnaModel::setDna(QVector<int> dna){
    if(m_data == dna) return;
    beginResetModel();
    m_data = dna;
    endResetModel();
}
int DnaModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.length();
}

QVariant DnaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::EditRole) return m_data.at(index.row());
    else return QString(QString::number(index.row(),2).rightJustified(std::log2(m_data.length()), '0') + ": " + QString::number(m_data.at(index.row())));
}

bool DnaModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        m_data[index.row()] = value.toInt();
        emit dataChanged(index, index);
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
