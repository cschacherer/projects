<%@ page language="java" import ="dbPackage.*" %><html>
<head>
<script LANGUAGE="javascript">
</script>
<title>sign up</title>
</head>
<body>
<%
	String username = request.getParameter("username");
	String firstname = request.getParameter("firstname");
	String lastname = request.getParameter("lastname");
	String phonenumber = request.getParameter("phonenumber");
	String address = request.getParameter("address");
	String password=request.getParameter("password");
	//Connector connector = new Connector();
	User user = new User();
	user.firstName = firstname;
	user.lastName = lastname;
	user.login = username;
	user.phoneNumber = phonenumber;
	user.password = password;
	user.address = address;

	boolean success = user.AddToDatabase();
	if(success == false)
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