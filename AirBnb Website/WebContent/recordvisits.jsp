<%@ page language="java" import = "java.util.concurrent.TimeUnit" import ="dbPackage.*" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

<title>Recorded Visits</title>


<script type="text/javascript">
</script>
</head>
<body>

<h3 style="text-align:center">Record a Visit</h3>
<a href="mainpage.jsp">BACK</a><br>

<%!
	public java.util.List<Reservation> VisitStart(int user_id)
	{
		User u = new User(user_id);
		java.util.List<Reservation> res = u.UserReservations(); 

		return res;
	}

%>
<%

  String n = session.getAttribute("userID").toString();
  int ID = Integer.parseInt(n);
  java.util.List<Reservation> hotels = VisitStart(ID);
%>

<%

	if(hotels.size() == 0)
	{
		%><h5>You have not reserved a room anywhere.</h5><% 
	}
	
	else{
%>



<ul>

  <% for(Reservation element: hotels) { %>


    Hotel name:<%=element.GetName() %><br>  
    People: <%=element.people %><br>
    Cost: $ <%= element.cost %><br>
    Time Period: <%=element.period.PrintDate() %><br>
    <a href="recordvisits.jsp?hid=<%=element.hid%>#form">RECORD VISIT</a><br>
    <br>	   

  <% }

  %> 

</ul> 



  <h3 id="form">

  <%

  Reservation r = new Reservation();
  Visit v = new Visit();
  int h_id;
  String hotel_id = (String)request.getParameter("hid");
  if(hotel_id != null){
		h_id = Integer.parseInt(hotel_id); 	
		for(int j = 0; j < hotels.size(); j++)
		{
			if(hotels.get(j).hid == h_id)
			{
				r = hotels.get(j);
			}
		}
		v.hid = r.hid;
		v.uid = r.uid; 

		%>
    	Your reservation says your stay was from <%= r.period.PrintDate() %> <br/>
		<% 

		String userFirstVisit = request.getParameter("firstVisit");
		String userLastVisit = request.getParameter("lastVisit");
		String numPeople = request.getParameter("numberOfPeople");

 	  	if( userFirstVisit == null && userLastVisit == null &&  numPeople == null){ %>  
 			<form name="changedates" method=post action="">
	            <br/>First day of your visit:<input type="text" name="firstVisit">
	            <br/>Last day of your visit:<input type="text" name="lastVisit">
	            <br/>Number of people that stayed:<input type="text" name="numberOfPeople">
	            <br/><input type="submit" >
    		</form>
 	  <% }
 	  else
 	  {
			v.period.stringStart = userFirstVisit;
			v.period.stringEnd = userLastVisit;
			v.period.StringToDate();
			v.people = Integer.parseInt(numPeople);
			long vDiff = v.period.end.getTime() - v.period.start.getTime(); 
		    long vNumDays = TimeUnit.DAYS.convert(vDiff, TimeUnit.MILLISECONDS); 

    		House h = new House(r.hid); 

			int totalCost = h.price * v.people * (int)vNumDays; 
			v.cost = totalCost; 
			int sunum = v.people;
			session.setAttribute("nump", sunum);
			session.setAttribute("fv", userFirstVisit);
			session.setAttribute("lv", userLastVisit);
			session.setAttribute("cost", totalCost);
			session.setAttribute("vhid", v.hid);
			session.setAttribute("vuid", v.uid);
 
			%>Here is your visit information: <br>
			Name: <%= v.GetName() %><br>
			Number of people: <%= v.people %><br>		
			Dates: <%= v.period.PrintDate() %> <br>
			Cost: <%= v.cost%> <br>
			
			<form name="confirmDates" method=post action="recordvisits.jsp#confirmVisit">
				</br><input type= "hidden" name="confirm" value = "ConfirmValue">
            	<br/><input type="submit" value="Confirm" >
    		</form>
	<% } 
	  }
 	} %>
</h3>
  
<div id = "confirmVisit">
<%
String userFirstVisit = request.getParameter("firstVisit");
String userLastVisit = request.getParameter("lastVisit");
String numPeople = request.getParameter("numberOfPeople");
String cVar = request.getParameter("confirm"); 
Visit v = new Visit(); 

if(cVar != null){ 
{
	
	String hid = session.getAttribute("vhid").toString();

	String uid = session.getAttribute("vuid").toString();

	v.hid = Integer.parseInt(hid);

	v.uid =  Integer.parseInt(uid);

	v.period.stringStart = session.getAttribute("fv").toString();

	v.period.stringEnd = session.getAttribute("lv").toString();

	v.period.StringToDate();

	String un = session.getAttribute("nump").toString();
	
	v.people = Integer.parseInt(un);
	
	long vDiff = v.period.end.getTime() - v.period.start.getTime(); 

    long vNumDays = TimeUnit.DAYS.convert(vDiff, TimeUnit.MILLISECONDS); 

   

    House h = new House(v.hid); 

	int totalCost = h.price * v.people * (int)vNumDays;  
	
	String c = session.getAttribute("cost").toString();
	
	v.cost = Integer.parseInt(c);  

    boolean result = v.AddToDatabase(); 

	if (result)

	{
	
		out.println("Visit added!\n"); 
	
	}
	
	else
	
	{
	
		out.println("There was an error, try again.\n"); 
	
	}  
}
}
%>
</div>


</body>

</html>