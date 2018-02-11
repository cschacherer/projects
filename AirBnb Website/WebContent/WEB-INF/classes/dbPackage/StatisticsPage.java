package dbPackage;

import java.util.*;

public class StatisticsPage {
	
	public static void StatisticsStart(int user_id)
	{
		System.out.println("What would you like to do? Select a number below.");
		System.out.println("1. See most popular listings");
		System.out.println("2. See most expensive listings");
		System.out.println("3. See highest rated listings");
		System.out.println("4. Go back to home page");
		
		try
		{
			String choice = StartPage.in.readLine(); 
			
			System.out.println("How many listings would you like to see?"); 
			String stringNumber = StartPage.in.readLine(); 
			int m = Integer.parseInt(stringNumber); 
			
			//most popular
			Statistics s = new Statistics(); 
			List<House> listings = new ArrayList<House>(); 
			if(choice.equals("1"))
			{
				listings = s.GetMostPopular(); 
			}
			//most expensive
			else if (choice.equals("2"))
			{
				listings = s.GetMostExpensive(); 
			}
			//highest rated
			else if (choice.equals("3"))
			{
				
			}
			else if (choice.equals("4"))
			{
				MainPage.HomePage(user_id);
			}
			else
			{
				System.out.println("Choose a valid input.");
				StatisticsStart(user_id); 
			}
			
			//print out the listings
			int size = m; 
			if (m > listings.size())
			{
				size = listings.size(); 
			}
			for(int i = 0; i < size; i++)
			{
				listings.get(i).PrintAttributes();
				System.out.println("");
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage()); 
		}
	}
}
