<%@ page language="java" import="dbPackage.*" import="java.util.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Browse Listings</title>
</head>
<body>
<h2>Browse Listings</h2>
<a href="mainpage.jsp">Back</a><br><br>

<form name="InputBrowse" method=post action="browse.jsp#search">
	Enter what attributes you'd like to browse by. Leave the others blank.  
	<br><b>Price</b><br>
	Min Price: <input type="text" name="minPrice"><br>
	Max Price: <input type="text" name="maxPrice"><br><br>
	
	<b>Location</b><br>
	City or State: <input type="text" name="location"><br>
	Use proper capitalization (ie: Salt Lake City or Utah)<br><br>
	
	<b>Name of Hotel</b><br>
	<input type="text" name="name"><br><br>
	
	<b>Keywords</b><br>
	<input type="text" name="keywords"><br>
	Please have multiple keywords separated by a comma and a space<br>
	and only capitalize the first word (ie: Two bedroom, Cheap)<br><br>
	
	<b>Catagory</b><br>
	<select name = "catagory">
		<option value="Empty"> </option>
 		<option value="Apartment">Apartment</option>
 		<option value="Condo">Condo</option>
 		<option value="House">House</option>
	</select> <br><br>
	
	<b>Sort search results by</b><br>
	<select name = "sort">
 		<option value="price">Price</option>
 		<option value="ratings">Highest Ratings</option>
 		<option value="trustedRatings">Trusted User Ratings</option>
	</select> <br><br>
	
	<input type="submit" value="Submit">
</form>

<div id = "search">
	<%
	String minPrice = request.getParameter("minPrice"); 
	String maxPrice = request.getParameter("maxPrice"); 
	String location = request.getParameter("location"); 
	String name = request.getParameter("name"); 
	String keywords = request.getParameter("keywords"); 
	String catagory = request.getParameter("catagory"); 
	String sortBy = request.getParameter("sort"); 
	Browse b = new Browse(); 
	
	if(minPrice == null && maxPrice == null && location == null &&
			name == null && keywords == null && catagory == null)
	{
		
	}
	else
	{
		if(!minPrice.equals("") && !maxPrice.equals(""))
		{
			b.minPrice = Integer.parseInt(minPrice); 
			b.maxPrice = Integer.parseInt(maxPrice); 
		}
		if(!location.equals(""))
		{
			b.location = location; 
		}
		if(!name.equals(""))
		{
			b.name = name; 
		}
		if(!keywords.equals(""))
		{
			String[] words = keywords.split(", "); 
			for(int i = 0; i < words.length; i++)
			{
				b.keywords.add(words[i]); 
			}
		}
		if(!catagory.equals("Empty"))
		{
			b.catagory = catagory; 
		}
		
		int user_id = Integer.parseInt(session.getAttribute("userID").toString()); 
		List<House> searchResults = b.GetSearch(sortBy, user_id); 
		
		if(searchResults.size() == 0)
		{
			%>Nothing matches your search. Try again.<%
		}
		else
		{
			%><br><h3>Search Results</h3><%
			for(House element: searchResults) { %>
				Name: <%=element.name%><br>
				Address:  <%=element.address %><br>
				Phone Number:  <%=element.phoneNumber %><br>
				Price: <%=element.price %><br>
				Max Residents: <%=element.maxResidents %><br>
				Catagory: <%=element.catagory %><br>
				
				<%if(!sortBy.equals("price")) {%>
					Rating: <%=element.avgScore %><br>
				<%} %>
				<%if(element.keywords.size() == 0) {%>
					Keyword: <br>
				<%} %>
				<%for(int i = 0; i < element.keywords.size(); i++){ %>
					Keyword: <%=element.keywords.get(i) %><br>
				<%} %>
		
				<%if(element.openDates.size() == 0) {%>
					Available: <br>
				<%} %>
				<%for(int i = 0; i < element.openDates.size(); i++){ %>
					Available: <%=element.openDates.get(i).stringStart %> to <%=element.openDates.get(i).stringEnd %><br>
				<%} %><br>
				
			<%}
		}
	
	}
	%>
</div>


</body>
</html>