<%@ page language="java" import="dbPackage.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Add House</title>
</head>
<body>
<h1>Confirm House</h1>
<a href="mainpage.jsp">Back</a><br>
<%
	House h = new House(); 
	h.uid = Integer.parseInt(session.getAttribute("userID").toString()); 
	h.name = request.getParameter("name"); 
	h.address = request.getParameter("address"); 
	h.phoneNumber = request.getParameter("phoneNumber"); 
	h.yearBuilt = Integer.parseInt(request.getParameter("yearBuilt")); 
	h.price = Integer.parseInt(request.getParameter("price")); 
	h.maxResidents = Integer.parseInt(request.getParameter("maxResidents")); 
	h.catagory = request.getParameter("catagory"); 

	String listKeys = request.getParameter("keywords"); 
	String[] keyArray = listKeys.split(", "); 
	
	for(int i = 0; i < keyArray.length; i++)
	{
		h.keywords.add(keyArray[i]); 
	}
	
	String listDates = request.getParameter("openDates"); 
	String[] dateArray = listDates.split(", "); 
	
	for(int i = 0; i < dateArray.length; i+=2)
	{
		TimePeriod tp = new TimePeriod(); 
		tp.stringStart = dateArray[i]; 
		tp.stringEnd = dateArray[i+1]; 
		tp.StringToDate(); 
		h.openDates.add(tp); 
	}
	
	
	boolean success = h.AddToDatabase(); 
	if(success == false)
	{
		response.sendRedirect("error.jsp"); 
	}
	else
	{
		response.sendRedirect("housing.jsp"); 
	}
%>

	Name: <%=h.name %><br>
	Address:  <%=h.address %><br>
	Phone Number:  <%=h.phoneNumber %><br>
	Price: <%=h.price %><br>
	Maximum Residents: <%=h.maxResidents%><br>
	Catagory: <%=h.catagory %><br>
	
	<%if(h.keywords.size() == 0) {%>
			Keyword: 
		<%} %>
	<%for(int i = 0; i < h.keywords.size(); i++){ %>
		Keyword: <%=h.keywords.get(i) %><br>
	<%} %>
	
	<%if(h.openDates.size() == 0) {%>
			Available: 
	<%} %>
	<%for(int i = 0; i < h.openDates.size(); i++){ %>
			Available: <%=h.openDates.get(i).stringStart %> to <%=h.openDates.get(i).stringEnd %><br>
		<%} %><br>
	
	<button type="button" onclick="javascript:AddHouseToDatabase(h);">Confirm</button> 
	
	
</body>
</html>