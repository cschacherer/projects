package dbPackage;

import java.util.*;
import java.sql.*;

public class Suggestions {

	public int uid; 
	public int hid; 
	
	public Suggestions(int UID, int HID)
	{
		uid = UID; 
		hid = HID; 
	}
	
	public List<House> GetSuggestions()
	{
		List<House> suggested = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT visited_uid FROM Visits WHERE visited_hid ="+hid+" AND visited_uid != "+uid; 
			ResultSet users_rs = con.stmt.executeQuery(query); 
			
			List<Integer> visitor_ids = new ArrayList<Integer>(); 
			while(users_rs.next())
			{
				int v_id = users_rs.getInt("visited_uid"); 
				visitor_ids.add(v_id); 
			}
			//System.out.println("visitors: " + visitor_ids.size() + ", " + visitor_ids.get(0));

			
			List<Integer> housing_ids = new ArrayList<Integer>(); 
			for(int i = 0; i < visitor_ids.size(); i++)
			{
				query = "SELECT visited_hid FROM Visits WHERE visited_uid = "+visitor_ids.get(i)+ " AND visited_hid != "+hid; 
				ResultSet house_rs = con.stmt.executeQuery(query); 
				
				while(house_rs.next())
				{
					int h_id = house_rs.getInt("visited_hid"); 
					housing_ids.add(h_id); 
				}
			}
			
			List<Integer> sorted_hids = new ArrayList<Integer>(); 
			while(housing_ids.size() != 0)
			{
				int maxHID = 0; 
				int freqMaxHID = 0; 
				for(int i = 0; i < housing_ids.size(); i++)
				{
					int freq = Collections.frequency(housing_ids, housing_ids.get(i)); 
					if(freq > freqMaxHID)
					{
						maxHID = housing_ids.get(i); 
						freqMaxHID = freq; 
					}
				}
				sorted_hids.add(maxHID); 				
				for(int j = 0; j < freqMaxHID; j++)
				{
					Integer m = maxHID; 
					housing_ids.remove(m); 
				}
			}

			con.closeConnection();
			for(int j = 0; j < sorted_hids.size(); j++)
			{
				House h = new House(sorted_hids.get(j)); 
				suggested.add(h); 
			}
			
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return suggested; 
	}
}
