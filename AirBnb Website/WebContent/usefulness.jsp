<%@ page language="java"  import ="dbPackage.*"  import ="java.util.*"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Usefulness Ratings</title>
</head>
<body>
<% 
    String n = session.getAttribute("userID").toString();
	int userId = Integer.parseInt(n);
	User u = new User(userId);
	List<Visit> userTH =  u.UserVisits();	
	
	Ratings r = new Ratings();
	List<House> houseToRate = new ArrayList<House>();
	List<Feedback> feedbacks = new ArrayList<Feedback>();
	
	Feedback f = new Feedback();	
	houseToRate = r.Houses();	
	session.setAttribute("feedback", f);
	
%>
<h3 style="text-align:center">Useful Ratings</h3>
<a href="mainpage.jsp">BACK</a><br>
	<ul>
		<%for(House element: houseToRate){ %>
		<!--  <li> -->
		 Hotel name: <%= element.name %><br>
		 Address: <%= element.address %><br>
		 Phone Number: <%= element.phoneNumber %><br>
		 Year Built: <%= element.yearBuilt %><br>
		 Price: <%= element.price %><br>
		 Max Residents: <%= element.maxResidents %><br>
		 Hotel name: <%= element.catagory %><br>
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
		<%} %>
 		 <a href="usefulness.jsp?hid=<%=element.hid%>#view">VIEW ALL FEEDBACK</a><br>
 		 <a href="usefulness.jsp?hid_id=<%=element.hid%>#viewsome">VIEW LESS</a><br>					
 		 <br>
		<!-- </li>  -->
		<% 
	
		} %>
	</ul>
	
	<div id="view">
		<%
		    String house_id = request.getParameter("hid");
			int correctId = 0;
			if(house_id != null)
			{
				int converH_id = Integer.parseInt(house_id);
				for(int j = 0; j < houseToRate.size(); j++)
				{
					if(houseToRate.get(j).hid == converH_id)
					{
						correctId = j;
					}
				}
				   
					feedbacks = f.GetFeedback(Integer.parseInt(house_id));
					Collections.sort(feedbacks, Collections.reverseOrder());
					if(feedbacks.size() == 0)
					{
						
						out.println("There are no feedbacks at this time");	
						%><a href = "usefulness.jsp"> Return</a><%
					}
					else
					{
						%>
						<ul>
							<%for(Feedback element: feedbacks){ %>
							 <li>
			 					Hotel name: <%= element.GetHotelName() %><br>
								Score: <%=element.score %><br>
								Text: <%= element.text %><br>
								Date: <%= element.date %><br>
								Usefulness: <%= element.usefulness %><br><br>
							</li> 
							<% } %>
						</ul>	
						<a href = "usefulness.jsp"> Return to top</a>
						<%
					}
			}
		%>
	</div>	
	<div id="viewsome">
		<%
		    String h_id = request.getParameter("hid_id");
		    int correctId2 = 0;
			if(h_id != null)
			{
				int converH_id = Integer.parseInt(h_id);
				for(int j = 0; j < houseToRate.size(); j++)
				{
					if(houseToRate.get(j).hid == converH_id)
					{
						correctId2 = j;
					}
				}
				feedbacks = f.GetFeedback(Integer.parseInt(h_id));
				Collections.sort(feedbacks, Collections.reverseOrder());
				
				String num = request.getParameter("number");
				if(num == null )
				{
		 		 %>  
			  		<form method=post action="">
			  			Select a number of feedback/s you'd like to see
			            <br/>Enter Number:<input type="text" name="number">
			            <br/><input type="submit" >
			    	</form>	 
			  	 <%
				}
				
				else
				{
					int converH_num = Integer.parseInt(num);
					if(feedbacks.size() < converH_num)
					{
						out.println("We have only " + feedbacks.size() + " " + "Feedback/s");
						
						%>
						<ul>
							<%for(Feedback element: feedbacks){ %>
							 <li>
			 					Hotel name: <%= element.GetHotelName() %><br>
								Score: <%=element.score %><br>
								Text: <%= element.text %><br>
								Date: <%= element.date %><br>
								Usefulness: <%= element.usefulness %><br><br>
							</li> 
							<% } %>
						</ul>
					  <a href = "usefulness.jsp"> Return to top</a>
						<%
					}
					else
					{
						%> <ul><% 
						for(int i = 0; i < converH_num; i++)
						{
							%>
								<li>
								Hotel name: <%= feedbacks.get(i).GetHotelName() %><br>
								Score: <%=feedbacks.get(i).score %><br>
								Text: <%= feedbacks.get(i).text %><br>
								Date: <%= feedbacks.get(i).date %><br>
								Usefulness: <%= feedbacks.get(i).usefulness %><br><br>
								</li>
							<% 
						}
						%></ul><%
						%><a href = "usefulness.jsp"> Return to top</a><%
					}
				}
			}
		%>
	</div>	
<%
%>
</body>
</html>