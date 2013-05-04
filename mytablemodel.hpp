#ifndef MYTABLEMODEL_HPP
#define MYTABLEMODEL_HPP

#include <QSqlTableModel>

class MyTableModel : public QSqlTableModel
{
    Q_OBJECT
public:

    explicit MyTableModel(QObject *parent = 0);
    virtual QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;

signals:
    
public slots:
    
};

#endif // MYTABLEMODEL_HPP
