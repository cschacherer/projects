<%@ page language="java" import="dbPackage.*" import="java.util.*" import="java.util.concurrent.TimeUnit" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Reserve a room</title>
</head>
<body>
<h2>Reserve a Room</h2>

<a href="mainpage.jsp">Back</a><br><br>

	<form name="Reserve Room" method=post action="reserve.jsp?#reserveRoom">
		Where are you going? Please type in a city or state (Use proper capitalization)
        <br/>Address:<input type="text" name="address"><br><br>
        
        When are you going? Please type use MM/DD/YYYY format.  
        <br/>Start Date:<input type="text" name="startDate">
        <br/>End Date:<input type="text" name="endDate"><br>
        
        <br/><input type="submit" value="Submit"><br>
    </form>

<div id = "reserveRoom">
	<%
	String where = request.getParameter("address"); 
	String start = request.getParameter("startDate"); 
	String end = request.getParameter("endDate");
	List<House> searchResults = new ArrayList<House>();
	
	if(where != null && start != null && end != null)
	{
		session.setAttribute("reserveAddress", where); 
		session.setAttribute("reserveStart", start); 
		session.setAttribute("reserveEnd", end); 
		
		TimePeriod tp = new TimePeriod(); 
		tp.stringStart = start; 
		tp.stringEnd = end; 
		tp.StringToDate();   
		
		searchResults = SearchListings.AddressAndDate(where, tp); 
		
		if(searchResults.size() == 0)
		{%>
			<br>No hotels matched your search.  Try again.
		<%}
		else
		{%>
			<br><b>Hotels: </b><br>
			<%for(House element: searchResults) { %>
				House ID: <%=element.hid %><br>
				Name: <%=element.name %><br>
				Address: <%=element.address %><br>
				Phone Number:  <%=element.phoneNumber %><br>
				Price: <%=element.price %><br>
				Max Residents: <%=element.maxResidents %><br>
				Catagory: <%=element.catagory %><br>
				
				<%if(element.keywords.size() == 0) {%>
					Keyword: 
				<%} %>
				<%for(int i = 0; i < element.keywords.size(); i++){ %>
					Keyword: <%=element.keywords.get(i) %><br>
				<%} %>
				
				<%if(element.openDates.size() == 0) {%>
					Available: 
				<%} %>
				<%for(int i = 0; i < element.openDates.size(); i++){ %>
					Available: <%=element.openDates.get(i).stringStart %> to <%=element.openDates.get(i).stringEnd %><br>
				<%} %><br>
			<%} %><br>
			
			<form name="Reserve Hotel" method=post action="reserve.jsp?#confirmReservation">
				Please type in the Hotel ID of the place you would like to reserve.  
		        <br/>Hotel ID:<input type="text" name="h_id"><br><br>
		        
		        When would you like to reserve this room.  Please type use MM/DD/YYYY format.  
		        <br/>Start Date:<input type="text" name="start_date">
		        <br/>End Date:<input type="text" name="end_date"><br><br>
		        
		        How many people will be staying there? 
		        <br/>People:<input type="text" name="residents">
		        
		        <br/><input type="submit" value="Reserve"><br>
		    </form>
		    <%} %>
	<%}	%>
</div>

<div id="confirmReservation">
	<%
	String hotel_id = request.getParameter("h_id"); 
	String s_date = request.getParameter("start_date"); 
	String e_date = request.getParameter("end_date"); 
	String people = request.getParameter("residents"); 
	Reservation r = new Reservation(); 
	
	if(hotel_id == null && s_date == null && e_date == null && people == null)
	{
		
	}
	else
	{
		TimePeriod confirmTime = new TimePeriod(); 
		confirmTime.stringStart = (String)session.getAttribute("reserveStart"); 
		confirmTime.stringEnd = (String)session.getAttribute("reserveEnd"); 
		confirmTime.StringToDate(); 
		
		searchResults = SearchListings.AddressAndDate((String)session.getAttribute("reserveAddress"), confirmTime); 
		
		r.hid = Integer.parseInt(hotel_id);
		r.uid = Integer.parseInt(session.getAttribute("userID").toString()); 
		
		TimePeriod tp = new TimePeriod(); 
		tp.stringStart = s_date; 
		tp.stringEnd = e_date; 
		tp.StringToDate(); 
		r.period = tp; 
		
		r.people = Integer.parseInt(people); 
		
		House h = new House(r.hid); 
		long diff = tp.end.getTime() - tp.start.getTime(); 
	    long numDays = TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS); 
		int totalCost = h.price * r.people * (int)numDays; 
		r.cost = totalCost; 	
		
		//find original times
		String originalStartDate = ""; 
		String originalEndDate = ""; 
		
		for(int i = 0; i < searchResults.size(); i++)
		{
			if(r.hid == searchResults.get(i).hid)
			{
				originalStartDate = searchResults.get(i).openDates.get(0).stringStart; 
				originalEndDate = searchResults.get(i).openDates.get(0).stringEnd; 
			}
		}%>
		
		<%session.setAttribute("reservation", r); %>
		
		<br><b>Confirm Reservation</b><br>
		Hotel ID: <%=r.hid %><br>
		Name: <%=h.name %><br>
		Time Period: <%=r.period.stringStart %> to <%=r.period.stringEnd %><br>
		Number of People: <%=r.people %><br>
		Cost: <%=r.cost %><br><br>
		
		<form name="Confirm Reservation" method=post action="reserve.jsp?sd=<%=originalStartDate%>&ed=<%=originalEndDate %>#finalConfirm">
            <br/><input type="submit" value="Confirm">
	    </form>
		
	<%}	%>
	
</div>

<div id = "finalConfirm">
	<%
	String sd = request.getParameter("sd"); 
	String ed = request.getParameter("ed"); 
	
	if(sd != null && ed != null)
	{
		//pass in the original date of the available house
		TimePeriod original_tp = new TimePeriod(); 
		original_tp.stringStart = sd; 
		original_tp.stringEnd = ed; 
		original_tp.StringToDate(); 
		
		Reservation nr = (Reservation)session.getAttribute("reservation"); 
		boolean result = nr.AddToDatabase(original_tp); 
		if(result) { %>
			Your reservation has been added!
		<% }
		else {%>
			There was an error, the reservation did not go through
		<%} 
	    
	}%> 
	
	

</div>


</body>
</html>