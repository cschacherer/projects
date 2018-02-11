<%@ page language="java" import="dbPackage.*" import="java.util.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Trusted Users</title>
</head>
<body>
<h2>Trust or Not Trust a User</h2>
<a href="mainpage.jsp">Back</a><br><br>

	<%
	Trust trustedUser = new Trust(Integer.parseInt(session.getAttribute("userID").toString())); 
	List<String> allLogins = Trust.ReturnAllLogins(); 
	%>
	
	<b> All Users</b><br>
	<%for(String element:allLogins) 
	{%>
		<%=element %><br>
	<%} %> <br>
	
	<b>Trusted Users</b><br>
	<%List<String> trusted_users = trustedUser.GetTrustedUsers(); 
	for(String element:trusted_users) 
	{%>
		<%=element %><br>
	<%} %> <br>
	
	<b>Not Trusted Users</b><br>
	<%List<String> not_trusted_users = trustedUser.GetNotTrustedUsers();  
	for(String element:not_trusted_users) 
	{%>
		<%=element %><br>
	<%} %> <br>
	
	<form name="Trust User" method=post action="trusted.jsp#setTrusted">
		Please write the name of the user you would like to set as trusted or not trusted.  
    	<br/>User:<input type="text" name="t_user">
    	<br/>Category <select name = "trusted">
			 <option value="1">Trusted</option>
			 <option value="0">Not Trusted</option>
		</select> 
        <br/><input type="submit" value="Submit">
	</form>
	
<div id = "setTrusted">
	<%
	String name = request.getParameter("t_user"); 
	String trusted = request.getParameter("trusted"); 

	Trust tu = new Trust(Integer.parseInt(session.getAttribute("userID").toString())); 
	if(name != null && trusted != null)
	{
		boolean success = tu.AddTrusted(name, Integer.parseInt(trusted)); 
		if(success)
		{
			%>Person as been added to trusted or not trusted!<%
		}
		else
		{
			%>There was an error and the person as been not been added to trusted or not trusted.<%
		}
	}
	
	%>
</div>
	
</body>
</html>