#include "database.h"
#include <mysql.h>
#include <QVector>
#include <QString>
#include <QDebug>

//Database::Database(QObject* parent) : HttpRequestHandler(parent)
Database::Database()
{
    connected = false;
    isSaved = false;
    isAdmin = false;
    mysql_init(&mysql);
    //const char *myHost = host.toStdString().c_str();
    //host = "localhost";
    //host = "155.99.161.251";
    //connection = mysql_real_connect(&mysql,host,"root","root","SolarDB",0,0,0);


}
void Database::ConnectTODb(QString userName, QString passWord)
{
    connection = mysql_real_connect(&mysql,"localhost","root","root","SolarDB",0,0,0);

    qDebug() << "Database conection";
    QString command =  "SELECT * FROM Login_Info WHERE UserName = '"+userName+"' AND Password = '"+passWord+"'";

    if (connection == NULL)
    {
        qDebug() << "Connection failed " <<mysql_error(&mysql);
        mysql_close(connection);
        exit(1);
    }
    state = mysql_query(connection, command.toStdString().c_str());
    if(state!= 0)
    {
        qDebug() << "Could not execute statement(s)" ;
        mysql_close(connection);
        exit(0);
    }

    result = mysql_store_result(connection);

    if ( ( row=mysql_fetch_row(result)) != NULL )
    {
        connected = true;
        tables.push_back(row[0]);
        qDebug() << "Connected!" ;
    }
    else
    {
        connected = false;
        qDebug() << "Incorrect Info!" ;

    }
    mysql_free_result(result);
    mysql_close(connection);

}


QString Database::GetPlayerLevel(QString username)
{
//     mysql_init(&mysql);
    connection = mysql_real_connect(&mysql,"localhost","root","root","SolarDB",0,0,0);

    qDebug() << "Database username" << username;
    QString command2 =  "SELECT Level FROM Levels WHERE UserName = '"+username+"'";
    QString playerLevel = "-1";

    if (connection == NULL)
    {
        qDebug() << "Connection failed " <<mysql_error(&mysql);
        mysql_close(connection);
        exit(1);
    }
    state2 = mysql_query(connection, command2.toStdString().c_str());
    if(state2!= 0)
    {
        qDebug() << "Could not execute statement(s)" ;
        mysql_close(connection);
        exit(0);
    }

    result = mysql_store_result(connection);
    unsigned int  num_fields = mysql_num_fields(result);

    if ( ( row=mysql_fetch_row(result)) != NULL )
    {
        for(int i = 0; i < num_fields; i++)
        {
            playerLevel =row[i];
        }
    }
    else
    {
        connected = false;
        qDebug() << "Player not created!" ;
    }
    mysql_free_result(result);
    mysql_close(connection);
    return playerLevel;

}


void Database::RegisterUser(QString firstName, QString lastName, QString userName, QString passWord)
{
    connection = mysql_real_connect(&mysql,"localhost","root","root","SolarDB",0,0,0);
    int state1;

    qDebug() << "Registered";
    QString command =  "INSERT INTO Login_Info ( First_Name, Last_Name, UserName, Password) VALUE ('"+firstName+"', '"+lastName+"', '"+userName+"','"+passWord+"' )";
    QString command1 =  "INSERT INTO Levels (UserName, Level) VALUE ('"+userName+"', 1)";

//    if (connection == NULL)
//    {
//        qDebug() << "Connection failed " <<mysql_error(&mysql);
//        mysql_close(connection);
//        exit(1);
//    }
    state = mysql_query(connection, command.toStdString().c_str());
    state1 = mysql_query(connection, command1.toStdString().c_str());

    if(state!= 0 && state1!= 0)
    {
        isSaved = false;
        qDebug() << "Error: Username already in use! Try again!" ;
        mysql_close(connection);
    }
    else
    {
        isSaved = true;
        qDebug() << "You are Registered!";
    }
    mysql_free_result(result);
    mysql_close(connection);

}


void Database::DeleteUser(QString userName)
{
    connection = mysql_real_connect(&mysql,"localhost","root","root","SolarDB",0,0,0);
    qDebug() << "Delete User";
    QString command =  "DELETE Login_Info, Levels FROM Login_info, Levels WHERE Login_Info.UserName = Levels.UserName AND Levels.UserName = '"+userName+"'";

    if (connection == NULL)
    {
        qDebug() << "Connection failed " <<mysql_error(&mysql);
        mysql_close(connection);
        exit(1);
    }
    state = mysql_query(connection, command.toStdString().c_str());

    if(state!= 0)
    {
        isSaved = false;
        qDebug() << "Error: Username already in use! Try again!" ;
        mysql_close(connection);
    }
    else
    {
        qDebug() << "User Deleted!" ;
    }
    mysql_free_result(result);
    mysql_close(connection);

}

void Database::UpdateLevels(QString userName, int level)
{
    connection = mysql_real_connect(&mysql,"localhost","root","root","SolarDB",0,0,0);
    QString stringLevel = QString::number(level);
    qDebug() << "Update Levels";
    QString command =  "UPDATE Levels SET Level = '"+stringLevel+"' WHERE UserName = '"+userName+"'";

    if (connection == NULL)
    {
        qDebug() << "Connection failed " <<mysql_error(&mysql);
        mysql_close(connection);
        exit(1);
    }
    state = mysql_query(connection, command.toStdString().c_str());
    if(state!= 0)
    {
        isSaved = false;
        qDebug() << "Error: Cannot update level!" ;
        mysql_close(connection);
    }
    else
    {
        isSaved = true;
        qDebug() << "Updated!";
    }
    mysql_free_result(result);
    mysql_close(connection);
}



