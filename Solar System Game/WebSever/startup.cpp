#include "startup.h"

StartUp::StartUp(QObject* parent)
    : HttpRequestHandler(parent) {

        mysql_init(&mysql);
}

void StartUp::service(HttpRequest &request, HttpResponse &response)
{
        connection = mysql_real_connect(&mysql,"localhost","admin","password","SolarDB",0,0,0);
        qDebug() << "Browser";
        QString command =  "SELECT a.First_Name, a.Last_Name, b.UserName, b.Level FROM Login_Info a, Levels b WHERE a.UserName = b.UserName ORDER BY b.UserName";

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
        unsigned int num_fields;
        unsigned int i;
        num_fields = mysql_num_fields(result);

        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css' integrity='sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7' crossorigin='anonymous'>");
        response.write("<head><title>Teachers Information</title><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'> <link rel='stylesheet' href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css'> <script src='https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js'></script> <script src='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js'></script></head>");
        response.write("<style>.bg-1 { background-image: url('https://ucare.timepad.ru/3b2162e1-91f9-4892-b95c-0d02e56ef5d9/poster_event_280510.png');}");
        response.write("body {background-image: url('https://scontent.fsnc1-1.fna.fbcdn.net/hphotos-xta1/t31.0-8/13072714_858539884257026_311452036398901605_o.jpg');}  p {text-indent: 50px;}</style>");
        response.write("");
        response.write("");
        response.write("");
        response.write("<div class = 'container-fluid bg-1 text-center'><h1><font color = 'white'>Soaring Through Outer Space</font></h1></div><body> <p><table class='table table-hover'> <thead><tr>");
        response.write("<html><body>");
        response.write("<table class='table table-hover'>");
        response.write("<thead>");
        response.write("<tr>");
        response.write("<th>First Name</th>");
        response.write("<th>Last Name</th>");
        response.write("<th>Username</th>");
        response.write("<th>Level</th>");
        response.write("</tr>");
        response.write("</thead>");

        while (( (row=mysql_fetch_row(result))))
        {

            qDebug() << "Success!" ;
            response.write("<tbody>");
            response.write("<tr>");
            qDebug() << "Success!" ;
            for(i = 0; i < mysql_num_fields(result); i++)
            {
                QString s = QString::number(i);
                qDebug() <<  "print row " <<row[i] ;
                QString name= row[i];
                response.write("<td>");
                response.write(name.toLatin1());
                response.write("</td>");
            }

            response.write("</tr>\n");
            response.write("</tbody>");
        }

        response.write("</table>");
        response.write("</body></html>",true);
        mysql_free_result(result);
        mysql_close(connection);

 }
