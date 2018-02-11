#ifndef STARTUP_H
#define STARTUP_H

#include <mysql.h>
#include "httprequesthandler.h"

class StartUp: public HttpRequestHandler
{
    Q_OBJECT
public:
    StartUp(QObject* parent=0);

    void service(HttpRequest &request, HttpResponse &response);

private:

    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL *connection, mysql;
    int state;

};

#endif // STARTUP_H
