<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Main page</title>
<style type="text/css">
.dropbtn {
	padding: 16x;
	border: none;
	cursor: pointer;
}
.dropdown {
	position: relative;
	display: inline_block;
}

.menu_list {
	display: none;
	position: absolute;
	background-color: #f9f9f9
	box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
	min-width:160px;
	z-index: 1;
}
.menu_list a {
	color: black;
	padding: 12px 16px;
	text-decoration: none;
	display: block;
}
.dropdown:hover .menu_list {
	display: block;
}
.dropdown:hover .dropbtn {
	background-color: pink;
}
.menu_list a:hover {
	background-color: #f1f1f1;
}
</style>
</head>
<body>
<h1>HOME PAGE</h1>
 <div class= "dropdown">
 	<button class ="dropbtn">MENU</button>
 	<div class="menu_list">
 		<a href="account.jsp">Account</a>
 		<a href="housing.jsp">Listings</a> 
 		<a href="reserve.jsp">Reserve a room</a>
 		<a href="recordvisits.jsp">Record a visit</a>
 		<a href="favouriteListing.jsp">Favorite listing</a>
 		<a href="feedback.jsp">Give feedback</a>
 		<a href="rateFeedback.jsp">Rate feedback</a>
 		<a href="usefulness.jsp">Listing's feedbacks</a>
 		<a href="trusted.jsp">Trusted/Not trusted user</a>
 		<a href="browse.jsp">Browse listings</a>
 		<a href="suggested.jsp">Suggested Listings</a>
 		<a href="statistics.jsp">Statistics</a>
 		<a href="logout.jsp">Logout</a>
 	</div>
 </div>
 
 <%
   String n = session.getAttribute("userID").toString();
 %>
</body>
</html>