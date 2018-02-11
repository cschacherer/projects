<%@ page language="java" import="dbPackage.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Account</title>
</head>
<body>
<h1>Account Information</h1>
<a href="mainpage.jsp">Back</a><br><br>
	<%
	String id = session.getAttribute("userID").toString(); 
	int intID = Integer.parseInt(id); 
	User u = new User(intID); 
	%>
	
	<b>Name:</b> <%=u.firstName%> <%=u.lastName%> <br>
	<b>Login: </b> <%=u.login%> <br>
	<b>Password: </b> <%=u.password%> <br>
	<b>Address: </b> <%=u.address%> <br>
	<b>Phone Number: </b> <%=u.phoneNumber%> <br><br>
	
	
	
</body>
</html>