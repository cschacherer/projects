<%@ page language="java" import="dbPackage.*" import="java.util.*" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Edit Listing</title>

</head>
<body>
<%
	House edit_h = new House(Integer.parseInt(request.getParameter("hid"))); 
%>

	<h2>Edit House</h2>
	<a href="housing.jsp">Back</a><br><br>
	
	Name: <%=edit_h.name%><br>
	Address: <%=edit_h.address%><br>
	Phone Number: <%=edit_h.phoneNumber%><br>
	Price: <%=edit_h.price %><br>
	Max Residents: <%=edit_h.maxResidents%></a><br>
	Catagory:</a> <%=edit_h.catagory%></a><br>
	
	<%if(edit_h.keywords.size() == 0) {%>
			Keyword: <br>
		<%} %>
	<%for(int i = 0; i < edit_h.keywords.size(); i++){ %>
		Keyword: <%=edit_h.keywords.get(i) %><br>
	<%} %>

	<%if(edit_h.openDates.size() == 0) {%>
			Available: <br>
		<%} %>
	<%for(int i = 0; i < edit_h.openDates.size(); i++){ %>
		Available: <%=edit_h.openDates.get(i).stringStart %> to <%=edit_h.openDates.get(i).stringEnd %><br>
	<%} %><br>

<div id="editAttribute">
	<form name="Edit Attribute" method=post action="editHouse.jsp?hid=<%=edit_h.hid%>#editDatabase">
        <br/><b>Name of Attribute:</b><input type="text" name="attribute"><br>
        Please enter attribute name as above, unless there is a space, then use an underscore instead. ie: Name or Phone_Number
        <br/><b>New Value:</b><input type="text" name="value"><br>
        If you are changing Catagory, please enter either Apartment, Condo, or House
        </br>If you are changing Keyword, please separate each keyword by a comma and a space.  Only capitalize the first word, ie: "Two bedroom, Downtown, Cheap"
        </br>If you are changing Available, please input the dates as MM/DD/YYYY, separated with a comma and a space.  
	    </br>ie: "04/20/2017, 04/30/2017, 05/05/2017, 05/10/2017" would mean it was open from 04/20/2017 to 04/30/2017 and 05/05/2017 to 05/10/2017)
        </br><br/><input type="submit" value="Submit">
    </form>
</div>

<div id="editDatabase">
	<%
	String attribute = request.getParameter("attribute"); 
	String newValue = request.getParameter("value"); 
	
	if(attribute == null && newValue == null)
	{
		
	}
	else if (attribute.equals("Keyword"))
	{
		//delete previous keywords
		int length = edit_h.keywords.size(); 
		for(int i = 0; i < length; i++)
		{
			edit_h.DeleteKeyword(edit_h.keywords.get(0)); 
		}
		
		//add new ones 
		String listKeys = request.getParameter("value"); 
		String[] keyArray = listKeys.split(", "); 
		for(int i = 0; i < keyArray.length; i++)
		{
			edit_h.keywords.add(keyArray[i]); 
		}
		
		edit_h.AddKeywords(); 
		
		House newHouse = new House(edit_h.hid); %>
		
		<br><br><b>Edited House</b> <br>
		Name: <%=newHouse.name%><br>
		Address: <%=newHouse.address%><br>
		Phone Number: <%=newHouse.phoneNumber%><br>
		Price: <%=newHouse.price %><br>
		Max Residents: <%=newHouse.maxResidents%><br>
		Catagory:<%=newHouse.catagory%><br>
		
		<%for(int i = 0; i < newHouse.keywords.size(); i++){ %>
			Keyword: <%=newHouse.keywords.get(i) %><br>
		<%} %>

		<%for(int i = 0; i < newHouse.openDates.size(); i++){ %>
			Available: <%=newHouse.openDates.get(i).stringStart %> to <%=newHouse.openDates.get(i).stringEnd %><br>
		<%} %><br>
	<%}
	else if (attribute.equals("Available"))
	{
		//delete old periods
		int length = edit_h.openDates.size(); 
		for(int i = 0; i < length; i++)
		{
			edit_h.DeleteDate(edit_h.openDates.get(0)); 
		}
		
		//add new dates
		String listDates = request.getParameter("value"); 
		String[] dateArray = listDates.split(", "); 
		
		for(int i = 0; i < dateArray.length; i+=2)
		{
			TimePeriod tp = new TimePeriod(); 
			tp.stringStart = dateArray[i]; 
			tp.stringEnd = dateArray[i+1]; 
			tp.StringToDate(); 
			edit_h.openDates.add(tp); 
		}
		
		edit_h.AddAvailableDates(); 
		
		House newHouse = new House(edit_h.hid); %>
		
		<br><br><b>Edited House</b> <br>
		Name: <%=newHouse.name%><br>
		Address: <%=newHouse.address%><br>
		Phone Number: <%=newHouse.phoneNumber%><br>
		Price: <%=newHouse.price %><br>
		Max Residents: <%=newHouse.maxResidents%><br>
		Catagory:<%=newHouse.catagory%><br>
		
		<%for(int i = 0; i < newHouse.keywords.size(); i++){ %>
			Keyword: <%=newHouse.keywords.get(i) %><br>
		<%} %>

		<%for(int i = 0; i < newHouse.openDates.size(); i++){ %>
			Available: <%=newHouse.openDates.get(i).stringStart %> to <%=newHouse.openDates.get(i).stringEnd %><br>
		<%} %><br>
		
	<%}
	else 
	{
		edit_h.EditAttribute(attribute, newValue); 
		
		House newHouse = new House(edit_h.hid); %>
		
		<br><br><b>Edited House</b> <br>
		Name: <%=newHouse.name%><br>
		Address: <%=newHouse.address%><br>
		Phone Number: <%=newHouse.phoneNumber%><br>
		Price: <%=newHouse.price %><br>
		Max Residents: <%=newHouse.maxResidents%><br>
		Catagory:<%=newHouse.catagory%><br>
		
		<%for(int i = 0; i < newHouse.keywords.size(); i++){ %>
			Keyword: <%=newHouse.keywords.get(i) %><br>
		<%} %>

		<%for(int i = 0; i < newHouse.openDates.size(); i++){ %>
			Available: <%=newHouse.openDates.get(i).stringStart %> to <%=newHouse.openDates.get(i).stringEnd %><br>
		<%} %><br>
	<%}	%>
	

	


</div>
</body>
</html>