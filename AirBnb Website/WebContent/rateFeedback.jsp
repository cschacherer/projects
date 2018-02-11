<%@ page language="java"  import ="dbPackage.*"  import ="java.util.*"%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Rate Feedbacks</title>
</head>
<body>
<h3 style="text-align:center">RATE FEEDBACKS</h3>
<%
	String n = session.getAttribute("userID").toString();
	int userId = Integer.parseInt(n);
	User u = new User(userId);
	
	Feedback f = new Feedback();
	Ratings r = new Ratings();
	List<House> houseToRate = r.Houses();
	List<Feedback> feedbacks = new ArrayList<Feedback>();
%>
<a href="mainpage.jsp">BACK</a><br>
	<ul>
	<%for(House element: houseToRate){ %>
	 Hotel name: <%= element.name %><br>
	 Address: <%= element.address %><br>
	 Phone Number: <%= element.phoneNumber %><br>
	 Year Built: <%= element.yearBuilt %><br>
	 Price: <%= element.price %><br>
	 Max Residents: <%= element.maxResidents %><br>
	 Catagory: <%= element.catagory %><br>
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
		 <a href="rateFeedback.jsp?hid=<%=element.hid%>#view">VIEW</a><br>
		 <br>
	<% } %>
	
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
					session.setAttribute("feedback", feedbacks);
					if(feedbacks.size() == 0)
					{
						
						out.println("There are no feedbacks at this time");	
						%><a href = "rateFeedback.jsp"> Return to top</a><%
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
								Usefulness: <%= element.usefulness %><br>
								<a href="rateFeedback.jsp?hid_id=<%=element.hid%>#rate">RATE IT!</a><br><br>											
							</li> 
							<% } %>
						</ul>	
						<a href = "rateFeedback.jsp"> Return to top</a>
						<%
					}
			}
		%>
	</div>
	<div id="rate">
	<%
			//feedbacks = (List<Feedback>)session.getAttribute("feedback");
			
			/* out.println(feedbacks.size()); */
		    String h_id = request.getParameter("hid_id");
			
			//out.println(f_id);
		    int correctId2 = 0;
			if(h_id != null)
			{	
				int converH_id = Integer.parseInt(h_id);
				feedbacks = f.GetFeedback(converH_id);
				
				for(int j = 0; j < feedbacks.size(); j++)
				{
					if(feedbacks.get(j).hid == converH_id)
					{
						correctId2 = j;
					}
				}
				 
 				r.fid = feedbacks.get(correctId2).fid; 
 				r.uid = u.uid; 
 				if(feedbacks.size() > 0)
				{
					String num = request.getParameter("number");
					if(num == null )
					{
			 		 %>  
				  		<form method=post action="">
				  			Rate ranges from 0 to 2 with 0 being unusefull and 2 being usefull 
				            <br/>Rate: <input type="text" name="number">
				            <br/><input type="submit" >
				    	</form>	 
				  	 <%
					}
					else{
						int newRate = Integer.parseInt(num);
						r.rate = newRate;
						r.AddToDatabase();
						/* out.println(newRate); */
						%><a href = "rateFeedback.jsp"> Return to top</a><%
					}
				}
				else{
					
					out.println("There are no feedbacks at this time");	
					%><a href = "rateFeedback.jsp"> Return to top</a><%
					
				}
				
			}
	%>
	
	</div>	
</ul>
</body>
</html>