#include <QtGui/QGuiApplication>
#include <QtWidgets>
#include <QtSql>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "../connection.h"
#include "mytablemodel.hpp"

void initializeModel(QSqlTableModel *model)
{
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("firstName"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

QTableView *createView(QSqlTableModel *model, const QString &title = "")
{
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setWindowTitle(title);
    return view;
}

int main(int argc, char *argv[])
{
    if (!createConnection())
        return 1;
    QApplication app(argc, argv);

    MyTableModel model;

    initializeModel(&model);
    QSqlRecord record;
    record.append(QSqlField("ID", QVariant::Int));
    record.append(QSqlField("firstname", QVariant::String));
    record.append(QSqlField("lastname", QVariant::String));
    record.setValue("ID", 8);
    record.setValue("firstname", "Gubert");
    record.setValue("lastname", "Bugert");
    model.insertRecord(-1, record);
    qDebug() << model.lastError().text();

    QTableView *view1 = createView(&model, QObject::tr("Table Model (View 1)"));
    QTableView *view2 = createView(&model, QObject::tr("Table Model (View 2)"));
    view1->show();
    view2->move(view1->x() + view1->width() + 20, view1->y());
    view2->show();

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("MyTableModel", &model);
  //  viewer.rootContext()->setContextProperty("firstName",);
    viewer.setMainQmlFile(QStringLiteral("qml/untitled/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
