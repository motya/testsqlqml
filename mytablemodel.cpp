#include "mytablemodel.hpp"
#include <QtQml>
#include <QSqlRecord>
MyTableModel::MyTableModel(QObject *parent) :
    QSqlTableModel(parent)
{
    qmlRegisterType<MyTableModel>("com.matasoft.tablemodel", 1, 0, "MyTableModel");

}

namespace {
//QHash<int, QByteArray> makeRoleNames()
//{
//    QHash<int, QByteArray> roles;
//    roles.insert(0, "id");
//    roles.insert(1, "firstName");
//    roles.insert(2, "lastName");
//    return roles;
//}
const char* COLUMN_NAMES[] = {
 "id",
 "firstName",
 "lastName",
 NULL
};
QHash<int, QByteArray> makeRoleNames()
{
    int idx = 0;
    QHash<int, QByteArray> roleNames;
    while( COLUMN_NAMES[idx]) {
            roleNames[Qt::UserRole + idx + 1] = COLUMN_NAMES[idx];
            idx++;
    }
    return roleNames;
}
}

QHash<int, QByteArray> MyTableModel::roleNames() const
{
    static const QHash<int, QByteArray> roleNames = makeRoleNames();
    return roleNames;
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlTableModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlTableModel::data(index, role);
    }
    else
    {
        const int column = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), column);
        value = QSqlTableModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}



