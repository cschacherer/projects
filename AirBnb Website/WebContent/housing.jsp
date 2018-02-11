<%@ page language="java" import="dbPackage.*" import="java.util.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Housing</title>
</head>
<body>
<h1>Housing</h1>
<a href="mainpage.jsp">Back</a><br>

	<form name="Add House" method=post action="addHouse.jsp">
       <h2>Add Listing </h2>
                Name:<input type="text" name="name">
	            <br/>Address:<input type="text" name="address">
	            (Please enter address as address, city, state zipcode. ie: 200 W 200 S, Salt Lake City, Utah 84012)
	            <br/>Phone Number:<input type="text" name="phoneNumber">
	            (Please enter phone number as (123)456-7890)
	            <br/>Year Built:<input type="text" name="yearBuilt">
	            <br/>Price:<input type="text" name="price">
	            <br/>Max Residents:<input type="text" name="maxResidents">
	            <br/>Category <select name = "catagory">
 					 <option value="Apartment">Apartment</option>
 					 <option value="Condo">Condo</option>
 					 <option value="House">House</option>
				</select> 
	            <br/>Keywords: <input type="text" name="keywords">
	            (Please separate each keyword by a comma and a space.  Only capitalize the first word, ie: Two bedroom, Downtown, Cheap)
	            <br/>Available Dates: <input type="text" name="openDates">
	            <br>(Please input it using MM/DD/YYYY and input start and end dates, separated with a comma and a space.  
	            <br>ie: 04/20/2017, 04/30/2017, 05/05/2017, 05/10/2017 would mean it was open from 04/20/2017 to 04/30/2017 and 05/05/2017 to 05/10/2017)
	            <br/><input type="submit" value="Submit">
	     </form>

<h2>Edit Listing</h2>

<%
	User u = new User(Integer.parseInt(session.getAttribute("userID").toString()));  
	List<House> houses = u.UserListings(); 
	
	for(House element: houses) { %>
		Name: <a href="editHouse.jsp?hid=<%=element.hid%>"><%=element.name %></a><br>
		Address:  <%=element.address %><br>
		Phone Number:  <%=element.phoneNumber %><br>
		Price: <%=element.price %><br>
		Max Residents: <%=element.maxResidents %><br>
		Catagory: <%=element.catagory %><br>
		
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
	<% } %>

</body>
</html>