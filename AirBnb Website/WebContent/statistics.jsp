<%@ page language="java" import="dbPackage.*" import="java.util.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Statistics</title>
</head>
<body>
<h2>Statistics</h2>
<a href="mainpage.jsp">Back</a><br><br>

<form name="Stats" method=post action="statistics.jsp#showStats">
	Sort Listings: <select name = "sort">
		<option value="visited">Most Visited</option>
		<option value="expensive">Most Expensive</option>
		<option value="rating">Highest Rated</option>
	</select> <br>
	
	<br/>Catagory: <select name = "catagory">
		<option value="Apartment">Apartment</option>
		<option value="Condo">Condo</option>
		<option value="House">House</option>
	</select> <br>
	
	</br>Number of Listings:<input type="text" name="numListings"><br>
	
	<br/><input type="submit" value="Submit">
</form>

<div id = "showStats">
	<%
	String sortBy = request.getParameter("sort"); 
	String catagory = request.getParameter("catagory"); 
	String numListings = request.getParameter("numListings"); 
	
	if(sortBy != null && catagory != null && numListings != null)
	{
		Statistics s = new Statistics(); 
		List<House> listings = new ArrayList<House>(); 
		
		if(sortBy.equals("visited"))
		{
			listings = s.GetMostPopular(catagory); 
		}
		else if(sortBy.equals("expensive"))
		{
			listings = s.GetMostExpensive(catagory); 
		}
		else if(sortBy.equals("rating"))
		{
			listings = s.GetHighestRated(catagory); 
		}
		
		int chosenSize = Integer.parseInt(numListings); 
		
		%><br><h2>Statistics Results</h2><%
		
		if(chosenSize > listings.size())
		{
			chosenSize = listings.size(); 
			%>There are only <%=chosenSize %> results. <br><br><%
		}
		for(int i = 0; i < chosenSize; i++)
		{
			House h = listings.get(i); %>
			
			Name: <%=h.name%><br>
			Address:  <%=h.address %><br>
			Phone Number:  <%=h.phoneNumber %><br>
			Price: <%=h.price %><br>
			Max Residents: <%=h.maxResidents %><br>
			Catagory: <%=h.catagory %><br>
			
			<%if(sortBy.equals("visited")) {%>
				Total Visits: <%=h.avgScore %><br>
			<%} %>
			<%if(sortBy.equals("expensive")) {%>
				Average Price Per Person: <%=h.avgScore %><br>
			<%} %>
			<%if(sortBy.equals("rating")) {%>
				Average Rating: <%=h.avgScore %><br>
			<%} %>
			<%if(h.keywords.size() == 0) {%>
				Keyword: 
			<%} %>
			<%for(int j = 0; j < h.keywords.size(); j++){ %>
				Keyword: <%=h.keywords.get(j) %><br>
			<%} %>
	
			<%if(h.openDates.size() == 0) {%>
				Available: 
			<%} %>
			<%for(int j = 0; j < h.openDates.size(); j++){ %>
				Available: <%=h.openDates.get(j).stringStart %> to <%=h.openDates.get(j).stringEnd %><br>
			<%} %><br>
				
		<%}
	}
	%>
</div>
</body>
</html>