package dbPackage;

import java.sql.*;
import java.util.*;

public class SearchListings {
	
	public static List<House> SearchByAddress(String destination)
	{
		List<House> listings = new ArrayList<House>(); 
		
		try
		{
			Connector con = new Connector(); 
			
			String query = "SELECT * FROM Housing WHERE address LIKE '%"+destination+"%'"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			while(rs.next())
			{
				House h = new House();
	        	h.hid = rs.getInt("h_id"); 
	        	h.name = rs.getString("name"); 
	        	h.address = rs.getString("address"); 
	        	h.phoneNumber = rs.getString("phone_number"); 
	        	h.yearBuilt = rs.getInt("year_built"); 
	        	h.price = rs.getInt("price");
	        	h.maxResidents = rs.getInt("max_residents"); 
	        	h.catagory = rs.getString("catagory"); 
	        	
	        	h.GetKeywords(); 
	        	h.GetAvailableDates();
	        	 
	        	listings.add(h); 
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e + ", " + e.getMessage());
		}
		
		return listings; 
	}

	public static List<House> AddressAndDate(String destination, TimePeriod tp)
	{
		List<House> listings = new ArrayList<House>(); 
		
		try
		{
			//get listings by address
			List<House> addressListings = SearchByAddress(destination); 
			
			//get listings by date
			listings = SearchByDate(addressListings, tp); 
	
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		return listings; 
	}
	
	public static List<House> SearchByDate(List<House> listings, TimePeriod tp)
	{
		List<House> dateListings = new ArrayList<House>(); 
		
		//go through each listing and check if dates are correct
		for(int i = 0; i < listings.size(); i++)
		{
			House h = listings.get(i); 
			List<TimePeriod> availableDates = new ArrayList<TimePeriod>(); 
			
			for(int j = 0; j < h.openDates.size(); j++)
			{
				TimePeriod ad = h.openDates.get(j); 

				//if TH start date is equal or before reservation start date
				if(ad.start.equals(tp.start) || ad.start.before(tp.start))
				{
					//if TH end date is equal or after reservation end date
					if(ad.end.equals(tp.end) || ad.end.after(tp.end))
					{
						availableDates.add(ad);
					}
				}
			}
			h.openDates = availableDates; 
			
			//if it has available dates, add them to the returning house list.
			if(h.openDates.size() != 0)
			{
				dateListings.add(h); 
			}
		}
		
		return dateListings; 
	}
}
