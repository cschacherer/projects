<%@ page language="java" import ="dbPackage.*" %><html>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<%-- <h1>Hello <b>
<%
	Visit v = new Visit();
	String hotel_id = (String)request.getParameter("hid");
	int hotelID = Integer.parseInt(hotel_id);
	Reservation r = new Reservation();
	r.hid = hotelID;
	v.hid = hotelID;
%>
<%= hotel_id %>
</b>!</h1> --%>
</body>
</html>