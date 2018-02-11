<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>logout</title>
</head>
<body>
<h3 style="text-align:center">Leaving so soon? Come again!<br>
<br>
<%

        session.removeAttribute("userID");
        session.removeAttribute("password");
        session.invalidate();
%>
<a href="login.jsp">Login</a>
</h3>
</body>
</html>