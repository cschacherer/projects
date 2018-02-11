package dbPackage;

import java.sql.*;
import java.util.*;

public class House {

	public int hid; 
	public String name; 
	public String address;
	public String phoneNumber; 
	public int yearBuilt; 
	public int price; 
	public int uid; 
	public int maxResidents; 
	public String catagory; 
	public List<String> keywords; 
	public List<TimePeriod> openDates; 
	
	public int avgScore = 0; 
	
	
	//regular house constructor
	public House()
	{
		hid = -1; 
		name = ""; 
		address = ""; 
		phoneNumber = ""; 
		yearBuilt = -1;
		price = -1; 
		uid = -1; 
		maxResidents = -1; 
		catagory = ""; 
		keywords = new ArrayList<String>(); 
		openDates = new ArrayList<TimePeriod>(); 
	}
	
	//creates a house from the hid
	public House(int HID)
	{
		try
		{
			Connector con = new Connector();
	        
	        String query = "SELECT * FROM Housing WHERE h_id = '"+HID+"'"; 
	        ResultSet rs = con.stmt.executeQuery(query); 
	        
	        while(rs.next())
	        {
	        	hid = rs.getInt("h_id"); 
	        	name = rs.getString("name"); 
	        	address = rs.getString("address"); 
	        	phoneNumber = rs.getString("phone_number"); 
	        	yearBuilt = rs.getInt("year_built"); 
	        	price = rs.getInt("price");
	        	uid = rs.getInt("housing_uid"); 
	        	maxResidents = rs.getInt("max_residents"); 
	        	catagory = rs.getString("catagory"); 
	        	
	        	GetKeywords(); 
	        	GetAvailableDates();
	        }
	        
	        con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
	}
	
	//gets a list of the keywords from the database
	public List<String> GetKeywords()
	{
		List<String> words = new ArrayList<String>(); 
		try
		{
			Connector con = new Connector();
	        
	        String query = "SELECT keyword_kid FROM HasKeywords WHERE keyword_hid = '"+hid+"'"; 
	        ResultSet rs = con.stmt.executeQuery(query); 
	        
	        List<Integer> k_ids = new ArrayList<Integer>(); 
	        while(rs.next())
	        {
	        	int new_id = rs.getInt("keyword_kid"); 
	        	k_ids.add(new_id); 
	        }
	        
	        for(int i = 0; i < k_ids.size(); i++)
	        {
	        	query = "SELECT word FROM Keywords WHERE k_id = '"+k_ids.get(i)+"'"; 
	        	rs = con.stmt.executeQuery(query); 
	        	while(rs.next())
	        	{
	        		String kw = rs.getString("word"); 
	        		words.add(kw); 
	        	}
	        }
	        
	        con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		keywords = words; 
		return keywords; 
	}
	
	//adds the house to the database. 
	public boolean AddToDatabase()
	{
		try
		{
			Connector con = new Connector();
	        
	        //add info to database
			String query = "INSERT INTO Housing(name, address, phone_number, year_built, price, housing_uid, "
					+ "max_residents, catagory) "
					+ "VALUES('"+name+"', '"+address+"', '"+phoneNumber+"', '"+yearBuilt+"', '"+price+"', "
					+ "'"+uid+"', '"+maxResidents+"', '"+catagory+"')"; 
			
			int insertResult = con.stmt.executeUpdate(query);
			if(insertResult > 0)
			{
				System.out.println ("Housing added to database.");
			}
			else
			{
				System.out.println ("Housing NOT added to database.");
			}
			
			//get housing id
			query = "SELECT h_id FROM Housing WHERE name ='"+name+"' AND address ='"+address+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			if(rs.next())
			{
				hid = rs.getInt("h_id"); 
			}
			
			con.closeConnection();
			
			//set up keywords
			if (keywords.size() > 0)
			{
				AddKeywords(); 
			}
			
			if(openDates.size() > 0)
			{
				AddAvailableDates(); 
			}
			
			return true; 
		
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return false;
	}

	//gets the keyword id from a housing id
	private List<Integer> GetKIDSFromHID(int housing_id)
	{
		List<Integer> h_kids = new ArrayList<Integer>(); 
		try
		{
			Connector con = new Connector();
			String query = "SELECT keyword_kid FROM HasKeywords WHERE keyword_hid = '"+housing_id+"'"; 
			ResultSet inTable = con.stmt.executeQuery(query); 
			
			//keyword is already in table, get kid of word
			while(inTable.next())
			{
				int kid = inTable.getInt("keyword_kid"); 
				h_kids.add(kid); 
			} 
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return h_kids; 
	}
	
	//gets a housing id from the keyword id
	private List<Integer> GetHIDSFromKID(int kid)
	{
		List<Integer> hids = new ArrayList<Integer>(); 
		try
		{
			Connector con = new Connector();
			String query = "SELECT keyword_hid FROM HasKeywords WHERE keyword_kid = '"+kid+"'"; 
			ResultSet inTable = con.stmt.executeQuery(query); 
			
			//keyword is already in table, get kid of word
			while(inTable.next())
			{
				int hid = inTable.getInt("keyword_hid"); 
				hids.add(hid); 
			} 
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return hids; 
	}
	
	//gets the keyword id from the keyword
	public static int GetKIDFromWord(String word)
	{
		int kid = -1; 
		try
		{
			Connector con = new Connector();
			String query = "SELECT k_id FROM Keywords WHERE word = '"+word+"'"; 
			ResultSet inTable = con.stmt.executeQuery(query); 
			
			//keyword is already in table, get kid of word
			if(inTable.next())
			{
				kid = inTable.getInt("k_id"); 
			} 
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return kid; 
	}
	
	//gets the keyword from a keyword id
	private String GetWordFromKID(int kid)
	{
		String word = ""; 
		try
		{
			Connector con = new Connector();
			String query = "SELECT word FROM Keywords WHERE k_id = '"+kid+"'"; 
			ResultSet inTable = con.stmt.executeQuery(query); 
			
			//keyword is already in table, get kid of word
			if(inTable.next())
			{
				word = inTable.getString("word"); 
			} 
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
		return word; 
	}
	
	//adds keywords to the database
	public void AddKeywords()
	{
		try
		{
			Connector con = new Connector();
			String query; 
			
			for(int i = 0; i < keywords.size(); i++)
			{
				String keyword = keywords.get(i); 
				
				int kid = GetKIDFromWord(keyword); 
				
				//word is not already in table
				if(kid == -1)
				{
					//insert word into Keywords 
					System.out.println("test"); 
					query = "INSERT INTO Keywords(word) VALUE ('"+keyword+"')"; 
			    	int intoTable = con.stmt.executeUpdate(query); 
			    	
			    	//able to put it in the table
			    	if(intoTable > 0)
			    	{
			    		//insert into HasKeywords
				    	kid = GetKIDFromWord(keyword); 
						query = "INSERT INTO HasKeywords(keyword_hid, keyword_kid) VALUE('"+hid+"', '"+kid+"')";
				    	int hasKey = con.stmt.executeUpdate(query); 
			    	}
				}
				
				//word is already in table
				else
				{
					List<Integer> hkCheck = GetHIDSFromKID(kid);
					
					boolean inHKTable = false; 
					for(int j = 0; j < hkCheck.size(); j++)
					{
						if(hkCheck.get(j) == hid)
						{
							inHKTable = true; 
							break; 
						}
					}
					if(inHKTable == false)
					{
						query = "INSERT INTO HasKeywords(keyword_hid, keyword_kid) VALUE('"+hid+"', '"+kid+"')";
				    	int hasKey = con.stmt.executeUpdate(query); 
					}					
				}
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//edits an attribute in the database.  
	public boolean EditAttribute(String attribute, String newValue)
	{
		try
		{
			Connector con = new Connector();
			String query; 
			
			query = "UPDATE Housing SET "+attribute+" = '"+newValue+"' WHERE h_id = "+hid; 
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
	
	//deletes a keyword from the database.  
	public boolean DeleteKeyword(String value)
	{
		try
		{
			Connector con = new Connector();
			
			int kid = GetKIDFromWord(value); 
			String query = "DELETE FROM HasKeywords WHERE keyword_hid = '"+hid+"' AND keyword_kid = '"+kid+"'"; 
			int result = con.stmt.executeUpdate(query); 	
			con.closeConnection();
			if(result > 0)
			{
				keywords.remove(value); 
				return true; 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return false; 
	}
	
	//checks to see if the date is already in the database
	private boolean CheckAvailableDate(TimePeriod tp)
	{
		try
		{
			Connector con = new Connector();
			String query = "SELECT * FROM Available WHERE available_hid = '"+hid+"' AND "+
							"startDate = '"+tp.stringStart+"' AND endDate = '"+tp.stringEnd+"'"; 
			
			ResultSet rs = con.stmt.executeQuery(query); 
			
			con.closeConnection();
			if(rs.next())
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
	
	//adds all the dates in openDates list to the database.  
	public void AddAvailableDates()
	{
		try
		{
			Connector con = new Connector();
			String query; 
			
			for(int i = 0; i < openDates.size(); i++)
			{
				boolean inTable = CheckAvailableDate(openDates.get(i)); 
				if(inTable == false)
				{
					query = "INSERT INTO Available(available_hid, price_per_night, startDate, endDate)"
							+" VALUE("+hid+", "+price+", '"+openDates.get(i).stringStart+"', '"+openDates.get(i).stringEnd+"')";
					int result = con.stmt.executeUpdate(query); 
				}
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//deletes a date from the Available database.  
	public boolean DeleteDate(TimePeriod tp)
	{
		try
		{
			Connector con = new Connector();
			
			String query = "DELETE FROM Available WHERE available_hid = '"+hid+"' AND startDate = '"+tp.stringStart+"'"
					+ " AND endDate = '"+tp.stringEnd+"'"; 
			int result = con.stmt.executeUpdate(query); 	
			
			if(result > 0)
			{
				int index = -1; 
				System.out.println(openDates.size()); 
				for(int k = 0; k < openDates.size(); k++)
				{		
					if(openDates.get(k).stringStart.equals(tp.stringStart) && openDates.get(k).stringEnd.equals(tp.stringEnd))
					{
						index = k; 
					}
					
				}
				openDates.remove(index); 
				
				con.closeConnection();
				return true; 
			}
			con.closeConnection(); 
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return false; 
	}
	
	//pulls the available dates from the database.  
	public void GetAvailableDates()
	{
		openDates = new ArrayList<TimePeriod>(); 
		
		try
		{
			Connector con = new Connector();
			
			String query = "SELECT startDate, endDate FROM Available WHERE available_hid = '"+hid+"'"; 
			ResultSet rs = con.stmt.executeQuery(query);
			
			while(rs.next())
			{
				TimePeriod tp = new TimePeriod(); 
				tp.stringStart = rs.getString("startDate"); 
				tp.stringEnd = rs.getString("endDate"); 
				tp.StringToDate();
				
				openDates.add(tp); 
			}
			con.closeConnection(); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	
	//easy way to print out the houses attributes
	public void PrintAttributes()
	{
		System.out.println("Name: "+ name);
		System.out.println("Address: "+ address);
		System.out.println("Phone_Number: "+ phoneNumber);
		System.out.println("Year_Built: "+ yearBuilt);
		System.out.println("Price: "+ price);
		System.out.println("Max_Residents: "+ maxResidents);
		System.out.println("Catagory: "+ catagory);
		
		//GetKeywords(); 
		if(keywords.size() == 0)
		{
			System.out.println("No Keywords");
		}
		else
		{
			for(int i = 0; i < keywords.size(); i++)
			{
				System.out.println("Keyword: " + keywords.get(i));
			}
		}
		
		//GetAvailableDates(); 
		if(openDates.size() == 0)
		{
			System.out.println("No Available Date");
		}
		for(int j = 0; j < openDates.size(); j++)
		{
			System.out.println("Available Date: "+openDates.get(j).PrintDate());
		}
	}

}
