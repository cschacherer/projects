package dbPackage;

import java.io.IOException;
import java.util.*; 

public class BrowsingPage {

	public static void BrowsingStart(int user_id)
	{
		System.out.println("Enter what attributes you'd like to browse by.");
		System.out.println("1. Price");
		System.out.println("2. Location (City or State)");
		System.out.println("3. Name");
		System.out.println("4. Keywords");
		System.out.println("5. Catagory");
		System.out.println("6. Go back to homepage");
		System.out.println("Type your response as '1 3 4' to browse by Price, Name, and Keywords.");

		
		List<String> attributes = new ArrayList<String>(); 
		try
		{
			String choice = StartPage.in.readLine(); 
			if(choice.equals("6"))
			{
				MainPage.HomePage(user_id);
			}
			else
			{
				BrowseByAttribute(user_id, choice); 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	public static void BrowseByAttribute(int user_id, String user_input) 
	{
		String[] attributes = user_input.split("\\s+");
		
		Browse b = new Browse(); 
		
		try
		{
			for(int i = 0; i < attributes.length; i ++)
			{
				//search by price
				if(attributes[i].equals("1"))
				{
					System.out.println("Enter a minimum price: ");
					String stringMin = StartPage.in.readLine(); 
					b.minPrice = Integer.parseInt(stringMin); 
					
					System.out.println("Enter a maximum price: ");
					String stringMax = StartPage.in.readLine(); 
					b.maxPrice = Integer.parseInt(stringMax); 
				}
				
				//search by location
				else if (attributes[i].equals("2"))
				{
					System.out.println("Enter a destination (Either city or state): ");
					b.location = StartPage.in.readLine(); 
				}
				
				//search by name of listing
				else if (attributes[i].equals("3"))
				{
					System.out.println("Enter a name to search by: ");
					b.name = StartPage.in.readLine(); 
				}
				
				//search by keywords
				else if(attributes[i].equals("4"))
				{
					String choice = "Yes"; 
					while(choice.equals("Yes"))
					{
						System.out.println("Enter a keyword (Type it with the first letter capitilized like 'Downtown' or 'Two bedroom'");
						String word = StartPage.in.readLine(); 
						b.keywords.add(word); 
						
						System.out.println("Would you like to add a another keyword?");
						System.out.println("Yes");
						System.out.println("No");
						choice = StartPage.in.readLine(); 
					}
				}
				
				//search by catagory
				else if (attributes[i].equals("5"))
				{
					System.out.println("Choose a catagory.");
					System.out.println("House");
					System.out.println("Apartment");
					System.out.println("Condo");
					b.catagory = StartPage.in.readLine(); 
				}
			}
			
			System.out.println("How would you like to sort the results?");
			System.out.println("1. Price");
			System.out.println("2. Housing ratings");
			System.out.println("3. Housing ratings from trusted users");
			String sortChoice = StartPage.in.readLine(); 
			while(!sortChoice.equals("1") && !sortChoice.equals("2") &&!sortChoice.equals("3"))
			{
				System.out.println("Enter a valid choice");
				sortChoice = StartPage.in.readLine(); 
			}
			
			String sortBy = ""; 
			if(sortChoice.equals("1"))
			{
				sortBy = "price"; 
			}
			else if(sortChoice.equals("2"))
			{
				sortBy = "ratings";
			}
			else if(sortChoice.equals("2"))
			{
				sortBy = "trusted_ratings";
			}
			List<House> results = b.GetSearch(sortBy, user_id); 
			
			if(results.size() == 0)
			{
				System.out.println("Nothing matches your search. Try again.\n");
				BrowsingStart(user_id); 
			}
			for(int i = 0; i < results.size(); i++)
			{
				results.get(i).PrintAttributes(); 
				System.out.println("");
			}
			BrowsingStart(user_id); 
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
	}
}
