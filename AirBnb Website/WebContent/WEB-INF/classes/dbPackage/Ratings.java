package dbPackage;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class Ratings {
	
	public int fid; 
	public int uid; 
	public int rate;

   public Ratings()
   {
	    fid = -1;
	    uid = -1;
		rate = 0;
   }
   
	//adds a rate to the database. 
	public void AddToDatabase()
	{		
		try
		{
			Connector con = new Connector();
	        
	        //add info to database
			String query = "INSERT INTO Ratings(rating_fid, rating_uid, rating) "
					+ "VALUES("+fid+","+uid+", "+rate+")"; 
			
			int insertResult = con.stmt.executeUpdate(query);
			if(insertResult > 0)
			{
				System.out.println ("Feedback added to database.");
			}
			else
			{
				System.out.println ("Feedback NOT added to database.");
			}
			
			//get rate id
//			query = "SELECT rating_fid FROM Ratings WHERE rating_uid ='"+uid; 
//			ResultSet rs = con.stmt.executeQuery(query); 
//			if(rs.next())
//			{
//				fid = rs.getInt("rating_fid"); 
//			}
			
			con.closeConnection();
					
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//Get user first name that rate a feedback
	private String GetUserName()
	{
		String n = ""; 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT login FROM Users WHERE u_id = '"+uid+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			if(rs.next())
			{
				n = rs.getString("login"); 
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return n; 
	}
	
	
	public List<House> Houses()
	{
		List<House> houses = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT * FROM Housing"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				int house_id = rs.getInt("h_id");
				House house = new House(house_id); 		
				houses.add(house); 
			}
	        con.closeConnection(); 
			
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		return houses; 
	}
	//Print rates
	public void PrintRatings()
	{
		String sName = GetUserName();
		System.out.println("User Name: " + sName);
		System.out.println("Rate: " +rate);
	}
}