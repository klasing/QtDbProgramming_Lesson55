#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // setup a database connection
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=(localdb)\\Projects;Database=test");
    db.setUserName("odbc");
    db.setPassword("odbc");
    db.setDatabaseName(dsn);

    if (!db.open()) qDebug() << db.lastError().text();

    this->model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM [test].[dbo].[people]");

    ui->tableView->setModel(model);
}

Dialog::~Dialog()
{
    db.close();
    delete ui;
}
