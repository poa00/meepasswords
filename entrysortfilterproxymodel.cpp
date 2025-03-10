#include "entrysortfilterproxymodel.h"

EntrySortFilterProxyModel::EntrySortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(EntryListModel::NameRole);
    setDynamicSortFilter(true);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    sort(0, Qt::AscendingOrder);
}

// First sort by category. Inside cateogries sort by name
bool EntrySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QAbstractItemModel *model = sourceModel();

    QVariant leftCategory = model->data(left, EntryListModel::CategoryRole);
    QVariant righCategory = model->data(right, EntryListModel::CategoryRole);

    // If both are in the same category sort by name
    if (leftCategory == righCategory) {
        QVariant leftName = model->data(left, EntryListModel::NameRole);
        QVariant righName = model->data(right, EntryListModel::NameRole);
        return QString::localeAwareCompare(leftName.toString(), righName.toString()) < 0;
    }

    // Else sort by category
    return QString::localeAwareCompare(leftCategory.toString(), righCategory.toString()) < 0;
}

QStringList EntrySortFilterProxyModel::getItemNames() const
{
    return ((EntryListModel*)sourceModel())->getItemNames();
}

void EntrySortFilterProxyModel::addOrUpdateEntry(QString name, QString category, QString userName, QString password, QString notes, int id)
{
    return ((EntryListModel*)sourceModel())->addOrUpdateEntry(name, category, userName, password, notes, id);
}

void EntrySortFilterProxyModel::clear()
{
    ((EntryListModel*)sourceModel())->clear();
}

bool EntrySortFilterProxyModel::containsUuid(QString uuid) {
    return ((EntryListModel*)sourceModel())->containsUuid(uuid);
}

QStringList EntrySortFilterProxyModel::deletedUuids() {
    return ((EntryListModel*)sourceModel())->deletedUuids();
}

int EntrySortFilterProxyModel::indexOfUuid(QString uuid) {
    return ((EntryListModel*)sourceModel())->indexOfUuid(uuid);
}

void EntrySortFilterProxyModel::removeAt(int index)
{
    QModelIndex idx = this->index(index, 0);
    QModelIndex srcIdx = mapToSource(idx);
    ((EntryListModel*)sourceModel())->removeAt(srcIdx.row());
}

void EntrySortFilterProxyModel::removeById(int id)
{
    ((EntryListModel*)sourceModel())->removeById(id);
}

void EntrySortFilterProxyModel::removeByUuid(QString uuid)
{
    ((EntryListModel*)sourceModel())->removeByUuid(uuid);
}

Entry* EntrySortFilterProxyModel::get(int index){
    QModelIndex idx = this->index(index, 0);
    QModelIndex srcIdx = mapToSource(idx);

    return (srcIdx.row() >= 0 && srcIdx.row() < sourceModel()->rowCount())
            ? ((EntryListModel*) sourceModel())->get(srcIdx.row())
            : ((EntryListModel*) sourceModel())->get(index);
}

void EntrySortFilterProxyModel::updateEntryAt(int index, QString name, QString category, QString userName, QString password, QString notes) {
    ((EntryListModel*)sourceModel())->updateEntryAt(index, name, category, userName, password, notes);
}

void EntrySortFilterProxyModel::addEntry(QString name, QString category, QString userName, QString password, QString notes, QString uuid) {
    ((EntryListModel*)sourceModel())->addEntry(name, category, userName, password, notes, uuid);
}
