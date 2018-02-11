<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Registering</title>
</head>
<body>
 <h1>Register</h1>
	<div style="text-align:center">
       <form name="sign_up" method=post action="signup.jsp">
	            <br/>Username:<input type="text" name="username">
	            <br/>First Name:<input type="text" name="firstname">
	            <br/>Last Name:<input type="text" name="lastname">
	            <br/>Address:<input type="text" name="address">
	            <br/>Phone Number:<input type="tel" name="phonenumber">
	            <br/>Password:<input type="password" name="password">
	            <br/><input type="submit" value="Submit">
	     </form>
	</div>
</body>
</html>