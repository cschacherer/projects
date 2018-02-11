#ifndef DATABASE_H
#define DATABASE_H
#include <QVector>
#include <QString>
#include <mysql.h>
//#include "httprequesthandler.h"

#include "player.h"

class Database //: public HttpRequestHandler
{
    //Q_OBJECT
public:
    //Database(QObject* parent=0);
    Database();
    void ConnectTODb(QString userName, QString passWord);
    void RegisterUser(QString firstName, QString lastName, QString userName, QString passWord);
    void DeleteUser(QString userName);
    void UpdateLevels(QString userName, int level);
    QString GetPlayerLevel(QString username);
    //void service(HttpRequest &request, HttpResponse &response);
    bool connected;
    bool isSaved;
    const char *host;
    const char *username;
    const char *password;


private:
    QVector<QString> tables;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL *connection, mysql;
    int state;
    int state2;
    bool isAdmin;
};

#endif // DATABASE_H
