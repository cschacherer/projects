package dbPackage;

import java.util.*;
import java.util.Map.Entry;
import java.sql.*; 

public class Statistics {
	
	public List<House> GetMostPopular(String searchCatagory)
	{
		List<House> popular = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT visited_hid FROM Visits, Housing WHERE visited_hid = h_id AND catagory = '"+searchCatagory+"'"; 
			ResultSet rs = con.stmt.executeQuery(query); 
			
			List<Integer> house_ids = new ArrayList<Integer>(); 
			while(rs.next())
			{
				int hid = rs.getInt("visited_hid"); 
				house_ids.add(hid); 
			}
			
			List<Integer> sorted_hids = new ArrayList<Integer>(); 
			List<Integer> sorted_freqs = new ArrayList<Integer>(); 
			while(house_ids.size() != 0)
			{
				int maxHID = 0; 
				int freqMaxHID = 0; 
				for(int i = 0; i < house_ids.size(); i++)
				{
					int freq = Collections.frequency(house_ids, house_ids.get(i)); 
					if(freq > freqMaxHID)
					{
						maxHID = house_ids.get(i); 
						freqMaxHID = freq; 
					}
				}
				sorted_hids.add(maxHID); 	
				sorted_freqs.add(freqMaxHID); 
				for(int j = 0; j < freqMaxHID; j++)
				{
					Integer m = maxHID; 
					house_ids.remove(m); 
				}
			}
			
			for(int i = 0; i < sorted_hids.size(); i++)
			{
				House h = new House(sorted_hids.get(i)); 
				h.avgScore = sorted_freqs.get(i); 
				popular.add(h); 
			}
			
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return popular; 
	}
	
	public List<House> GetMostExpensive(String searchCatagory)
	{
		List<House> expensive = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT visited_hid, num_people, cost FROM Visits, Housing WHERE visited_hid = h_id AND catagory = '"+searchCatagory+"'";
			ResultSet rs = con.stmt.executeQuery(query); 
			
			Map<Integer, List<Integer>> dict = new HashMap <Integer, List<Integer>>(); 
			while(rs.next())
			{
				int hid = rs.getInt("visited_hid"); 
				int people = rs.getInt("num_people"); 
				int cost = rs.getInt("cost"); 
				int avg = cost / people; 
				if(dict.containsKey(hid))
				{
					dict.get(hid).add(avg); 
				}
				else
				{
					List<Integer> fuckthis = new ArrayList<Integer>(); 
					fuckthis.add(avg); 
					dict.put(hid, fuckthis); 
				}
			}
			
			Map<Integer, Integer> totalAvg = new HashMap <Integer, Integer>(); 
			Iterator iterator = dict.keySet().iterator();
			while(iterator.hasNext())
			{
				Integer house_id = (Integer)iterator.next(); 
				int totalCost = 0; 
				for(int i = 0; i < dict.get(house_id).size(); i++)
				{
					totalCost += dict.get(house_id).get(i); 
				}
				totalCost = totalCost / dict.get(house_id).size(); 
				
				totalAvg.put(house_id, totalCost); 
			}
			
			while(totalAvg.size() != 0)
			{
		        int mostExpensive =(Collections.max(totalAvg.values()));
		        Integer hotel_id = 0;
		        Integer hotel_exp = 0;
		        for(Entry<Integer, Integer> hotel : totalAvg.entrySet())
		        {        	 
		        	if(hotel.getValue() == mostExpensive)
		        	{
		        		hotel_id = hotel.getKey(); 
		        		hotel_exp = mostExpensive; 		        		
		        	}	
		        }
		        House h = new House(hotel_id); 
		        h.avgScore = hotel_exp; 
        		expensive.add(h); 
	        	totalAvg.remove(hotel_id);
			}
			con.closeConnection();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return expensive; 
	}
	
	public List<House> GetHighestRated(String searchCatagory)
	{
		List<House> topRated = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			String query = "SELECT h_id, score FROM Housing, Feedback WHERE feedback_hid = h_id AND catagory = '"+searchCatagory+"'"
					+ " GROUP BY score, h_id"; 
			ResultSet rs = con.stmt.executeQuery(query); 
					
			Map<Integer, List<Integer>> hotelScores = new HashMap<Integer, List<Integer>>(); 
			while(rs.next())
			{
				int id = rs.getInt("h_id"); 
				int score = rs.getInt("score"); 
				
				if(hotelScores.containsKey(id))
				{
					hotelScores.get(id).add(score);
				}
				else
				{
					List<Integer> scoreList = new ArrayList<Integer>(); 
					scoreList.add(score); 
					hotelScores.put(id, scoreList); 
				}
			}
			
			//get averages of score of feedbacks
			Map<Integer, Integer> hotelAvg = new HashMap<Integer, Integer>(); 
			for(Entry<Integer, List<Integer>> h_score : hotelScores.entrySet())
			{
				int avgScore = 0; 
				for(int j = 0; j < h_score.getValue().size(); j++)
				{
					avgScore += h_score.getValue().get(j); 
				}
				avgScore = avgScore / h_score.getValue().size(); 
				
				hotelAvg.put(h_score.getKey(), avgScore); 
			}
			
			//find max average scores
			while(hotelAvg.size() != 0)
			{
		        int highestScore =(Collections.max(hotelAvg.values()));
		        Integer hotel_id = 0;
		        Integer hotel_score = 0; 
		        for(Entry<Integer, Integer> hotel : hotelAvg.entrySet())
		        {        	 
		        	if(hotel.getValue() == highestScore)
		        	{
		        		hotel_id = hotel.getKey(); 
		        		hotel_score = highestScore; 
		        	}	
		        }
		        House h = new House(hotel_id); 
		        h.avgScore = hotel_score; 
		        topRated.add(h); 
		        hotelAvg.remove(hotel_id);
			}
			
			con.closeConnection(); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return topRated; 
	}
}
