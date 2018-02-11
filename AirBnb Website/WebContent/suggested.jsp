<%@ page language="java" import="dbPackage.*" import="java.util.*" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Suggested Listings</title>
</head>
<body>

	<h2>Suggested Listings</h2>

	<%
	User u = new User(Integer.parseInt(session.getAttribute("userID").toString())); 
	List<Reservation> reservations = u.UserReservations(); 
	
	for(Reservation element: reservations)
	{
		House h = new House(element.hid); 
		%>
		<b>Reservation</b><br>
		Name: <%=h.name%> <br>
		Period: <%=element.period.stringStart %> to <%=element.period.stringEnd %><br>
		People: <%=element.people %><br>
		Cost: <%=element.cost %><br><br>
		
		<b>Suggestions</b><br>
		
		<%Suggestions s = new Suggestions(u.uid, element.hid); 
		List<House> suggestions = s.GetSuggestions(); 
		
		if(suggestions.size() == 0)
		{
			%>No suggestions found.<br><br><% 
		}
		else
		{
			for(int i = 0; i < suggestions.size(); i++)
			{
				House sh = suggestions.get(i); 
			%>
				
				Name: <%=sh.name %><br>
				Address:  <%=sh.address %><br>
				Phone Number:  <%=sh.phoneNumber %><br>
				Price: <%=sh.price %><br>
				Max Residents: <%=sh.maxResidents %><br>
				Catagory: <%=sh.catagory %><br>
				
				<%if(sh.keywords.size() == 0) {%>
					Keyword: 
				<%} %>
				<%for(int j = 0; j < sh.keywords.size(); j++){ %>
					Keyword: <%=sh.keywords.get(j) %><br>
				<%} %>
				
				<%if(sh.openDates.size() == 0) {%>
					Available: 
				<%} %>
				<%for(int j = 0; j < sh.openDates.size(); j++){ %>
					Available: <%=sh.openDates.get(j).stringStart %> to <%=sh.openDates.get(j).stringEnd %><br>
				<%} %><br>
			<%}
		}
		%>	
		
		
	<%}
	
	%>
	

</body>
</html>