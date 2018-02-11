package dbPackage;

import java.sql.ResultSet;

//class that holds all the relevent information on visits
public class Visit {
	public int hid; 
	public int uid; 
	public TimePeriod period;
	public int people; 
	public int cost; 
	
	//constructor
	public Visit()
	{
		hid = -1; 
		uid = -1; 
		period = new TimePeriod(); 
		people = -1; 
		cost = -1; 
	}
	public Visit(int hID)
	{
		try
		{
			Connector con = new Connector();
			String query = "SELECT * FROM Feedback WHERE visited_hid = '"+hID+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 

			while(rs.next())
			{
				hid = rs.getInt("visited_hid"); 
				uid = rs.getInt("visited_uid");
				
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	//adds the visit to the database
	public boolean AddToDatabase()
	{
		try
		{
			Connector con = new Connector(); 
			String query = "INSERT INTO Visits(visited_hid, visited_uid, startDate, endDate, num_people, cost) "
					+ "VALUE("+hid+", "+uid+", '"+period.stringStart+"', '"+period.stringEnd+"', "+people+", "+cost+")"; 
			
			int result = con.stmt.executeUpdate(query);
			con.closeConnection();
			if(result > 0)
			{
				return true; 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return false; 
	}

	//easy way to print the visits
	public void PrintVisit()
	{
		String name = GetName(); 
		System.out.println("Name: " + name);
		System.out.println("Date: "+period.PrintDate());
		System.out.println("Number of People: "+people);
		System.out.println("Cost: "+cost);
	}
	
	//gets the name from the visit hid so it is easier to print out the visit
	public String GetName()
	{
		String n = ""; 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT name FROM Housing WHERE h_id = "+hid; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			if(rs.next())
			{
				n = rs.getString("name"); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return n; 
	}
}
