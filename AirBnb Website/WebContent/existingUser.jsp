<%@ page language="java" import ="dbPackage.*" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>user login</title>
</head>
<body>
<%

	String username = request.getParameter("username");
	String password=request.getParameter("password");
	//Connector connector = new Connector();
	User user = new User();
	user.login = username;
	user.password = password;
	
	boolean loginSuccess = user.LoginUser(); 
	if(loginSuccess == false)
	{
		 response.sendRedirect("error.jsp");
	}
	else
	{
		session.setAttribute("userID", user.uid);
		response.sendRedirect("mainpage.jsp");
	}

%>
</body>
</html>