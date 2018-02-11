<%@ page language="java"  import ="dbPackage.*"  import ="java.util.*"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Feedback</title>
</head>
<body>
<h3 style="text-align:center">FEEDBACK</h3>

<a href="mainpage.jsp">HOME</a><br>
<% 
    String n = session.getAttribute("userID").toString();
	int userId = Integer.parseInt(n);
	User u = new User(userId);
	java.util.List<Visit> userTH =  u.UserVisits();	
%>	
<ul>
<%for(Visit element: userTH){ %>

 	Hotel name: <%= element.GetName() %><br>
	People: <%=element.people %><br>
	Cost: $ <%= element.cost %><br>
	Time Period: <%=element.period.PrintDate() %><br>
	<a href="feedback.jsp?hid=<%=element.hid%>#view">VIEW FEEDBACKS</a><br>
	<a href="feedback.jsp?hid_id=<%=element.hid%>#give">GIVE FEEDBACK</a><br><br>

	 <% } %>  
</ul>

<div id ="view">
<%
	Feedback viewfeedback = new Feedback();	
    int correctId = 0;
	String hotel_id = (String)request.getParameter("hid");
	if(hotel_id != null)
	{
		int h_id = Integer.parseInt(hotel_id); 
		for(int j = 0; j < userTH.size(); j++)
		{
			if(userTH.get(j).hid == h_id)
			{
				//viewfeedback.GetFeedback(userTH.get(j).hid);
				correctId = j;
			}
		}
		List<Feedback> hotelFeedback = viewfeedback.GetFeedback(userTH.get(correctId).hid); 
		
		if(hotelFeedback.size()!= 0)
		{
			%>
			<ul>
				<%for(Feedback element: hotelFeedback){ 
					House h = new House(element.hid); %>
				 <li>
 					Hotel name: <%= h.name %><br>
					Score: <%=element.score %><br>
					Text: <%= element.text %><br>
					Date: <%= element.date %><br>
					Usefulness: <%= element.usefulness %><br><br>
				</li> 
				<% } %>
			</ul>
			<a href = "feedback.jsp"> Return to top</a>
			<%
			
		}
		else
		{
			out.println("There no feedback");
			%><a href = "feedback.jsp"> Return to top</a><%
		}

	}
	
	
%>
</div>
<div id="give">
	
<%
	String hotel_id2 = (String)request.getParameter("hid_id");
	int num = 0;
	if(hotel_id2 != null)
	{
		int hid = Integer.parseInt(hotel_id2);
		for(int j = 0; j < userTH.size(); j++)
		{
			if(userTH.get(j).hid == hid)
			{
				//viewfeedback.GetFeedback(userTH.get(j).hid);
				num = j;
			}
		}
		 
		Feedback userFeedBack = new Feedback();
		userFeedBack.uid = u.uid;
		userFeedBack.hid = userTH.get(num).hid;
		userFeedBack.date = userTH.get(num).period.stringEnd;
		
	
		String s = request.getParameter("score");
		String sn = request.getParameter("scorenum");
		if (s == null && sn == null)
		{
 		 %>  
	  		<form method=post action="">
	  			Select a number from 0-10 for Scores. With 0 being the lowest and the 10 the highest
	            <br/>Enter Score:<input type="text" name="score">
	            <br/>Enter Feedback under 200 characters:<input type="text" name="scorenum">
	            <br/><input type="submit" >
	    	</form>	 
	  	 <%
		}
		else{
			int numScore = Integer.parseInt(s);
			userFeedBack.score = numScore;
			userFeedBack.text = sn;
			boolean checkInTable = userFeedBack.inFeedback(); 
			if(checkInTable)
			{
				out.println("Cannot leave a feedback on a hotel twice.");
				%><a href = "feedback.jsp"> Return to top</a><%
			}
			else
			{
				//feedback.jsp?hid=<%=element.hid
				userFeedBack.AddToDatabase();
				out.println("feedback added");
				%><a href = "feedback.jsp"> Return to top</a><%
			}
		}
	}
%>
</div>
</body>
</html>