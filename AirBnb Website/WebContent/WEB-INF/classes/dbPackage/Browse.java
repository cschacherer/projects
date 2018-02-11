package dbPackage;

import java.sql.*;
import java.util.*; 
import java.util.Map.Entry;

public class Browse {

	public int maxPrice; 
	public int minPrice; 
	public String location; 
	public String name; 
	public String catagory; 
	public List<String> keywords; 
	
	public Browse()
	{
		maxPrice = -1; 
		minPrice = -1; 
		location = ""; 
		name = ""; 
		catagory = ""; 
		keywords = new ArrayList<String>(); 
	}
	
	public List<House> GetSearch(String sortBy, int user_id)
	{
		List<House> browseResults = new ArrayList<House>(); 
		try
		{
			Connector con = new Connector(); 
			String whereCondition = ""; 
			
			String priceCondition = ""; 
			String locationCondition = ""; 
			String nameCondition = ""; 
			String catagoryCondition = ""; 
			
			//get where conditions depending on attributes
			if(maxPrice != -1 && minPrice != -1)
			{
				priceCondition = "price <="+maxPrice+" AND price >= "+minPrice+" "; 
				whereCondition = priceCondition; 
			}
			if(!location.equals(""))
			{
				locationCondition = "address LIKE '%"+location+"%' "; 
				if(whereCondition.equals(""))
				{
					whereCondition = locationCondition; 
				}
				else
				{
					whereCondition += "AND "+ locationCondition; 
				}
			}
			if(!name.equals(""))
			{
				nameCondition = "name LIKE '%"+name+"%' "; 
				if(whereCondition.equals(""))
				{
					whereCondition = nameCondition; 
				}
				else
				{
					whereCondition += "AND " + nameCondition; 
				}
			}
			if(!catagory.equals(""))
			{
				catagoryCondition = "catagory = '"+catagory+"' ";
				if(whereCondition.equals(""))
				{
					whereCondition = catagoryCondition; 
				}
				else
				{
					whereCondition += "AND "+ catagoryCondition; 
				}
			}
			
			//if there are not keyword attributes
			if(keywords.size() == 0)
			{
				//sort by price, no keywords
				if(sortBy.equals("price"))
				{
					String query = "SELECT h_id, price FROM Housing WHERE " + whereCondition + "GROUP BY price, h_id"; ///have to change price
					ResultSet rs = con.stmt.executeQuery(query); 
					
					while(rs.next())
					{
						int id = rs.getInt("h_id"); 
						House h = new House(id); 
						browseResults.add(h);
					}
				}
				//sort by avg score each hotel got, no keywords
				else if(sortBy.equals("ratings") || sortBy.equals("trustedRatings"))
				{
					String query = ""; 
					if(sortBy.equals("ratings"))
					{
						whereCondition += " AND h_id = feedback_hid "; 
						query = "SELECT h_id, score FROM Housing, Feedback WHERE " + whereCondition + "GROUP BY score, h_id"; 
					}
					else if(sortBy.equals("trustedRatings"))
					{
						whereCondition += " AND h_id = feedback_hid AND feedback_uid = trusted_tuid AND trusted_uid = "+user_id; 
						query = "SELECT h_id, score FROM Housing, Feedback, TrustedUser WHERE " + whereCondition + " GROUP BY score, h_id"; 
					}
					
					//System.out.println(query); 
					
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
				        h.avgScore = hotel_score; ///////////////////////////////
				        browseResults.add(h); 
				        hotelAvg.remove(hotel_id);
					}
				}
				
				con.closeConnection();
			}
			
			//keywords is an attribute of the search, need to go through and find each keyword
			else
			{
				String keywordCondition = "";
				String tableCondition = ""; 
				//join a few tables
				for(int i = 0; i < keywords.size(); i++)
				{
					int kid = House.GetKIDFromWord(keywords.get(i)); 
					if(i == 0)
					{
						tableCondition = "HasKeywords hk0 "; 
						keywordCondition = "hk0.keyword_kid = "+kid+" AND h_id = hk0.keyword_hid "; 
					}
					else
					{
						tableCondition += ", HasKeywords hk"+i; 
						keywordCondition += "AND hk"+i+".keyword_kid = "+kid+" AND h_id = hk"+i+".keyword_hid "; 
					}
				}
				
				if(whereCondition.equals(""))
				{
					whereCondition = keywordCondition; 
				}
				else
				{
					whereCondition += "AND "+keywordCondition; 
				}
				
				//sort by price, has keyword search attributes
				if(sortBy.equals("price"))
				{
					String query = "SELECT h_id, price FROM Housing, "+tableCondition+" WHERE "+whereCondition+ "GROUP BY price, h_id"; 

					System.out.println(query);

					ResultSet rs = con.stmt.executeQuery(query); ; 
					while(rs.next())
					{
						int id = rs.getInt("h_id"); 
						House h = new House(id); 
						browseResults.add(h); 
					}
				}
				
				//sort by avg score of hotel ratings, has keyword search attributes
				else if(sortBy.equals("ratings") || sortBy.equals("trustedRatings"))
				{
					String query = ""; 
					if(sortBy.equals("ratings"))
					{
						whereCondition += "AND h_id = feedback_hid "; 
						query = "SELECT h_id, score FROM Housing, Feedback, "+tableCondition+" WHERE " + whereCondition + "GROUP BY score, h_id"; 
					}
					else if(sortBy.equals("trustedRatings"))
					{
						whereCondition += " AND h_id = feedback_hid AND feedback_uid = trusted_tuid AND trusted_uid = "+user_id; 
						query = "SELECT h_id, score FROM Housing, Feedback, TrustedUser, "+tableCondition+" WHERE " + whereCondition 
								+ " GROUP BY score, h_id"; 
					}
					
					System.out.println(query); 
					
					
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
				        Integer hotel_score = 0; ///////////////////////////////////////
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
				        browseResults.add(h); 
				        hotelAvg.remove(hotel_id);
					}
				}
				
				con.closeConnection();
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		return browseResults; 
	}
}
