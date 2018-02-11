package dbPackage;

import java.util.*;

//page that lets the user edit the houses that the own
public class HousingPage {
	
	//main housing page
	public static void HousingStart(int user_id)
	{	
		System.out.println("What would you like to do? Please select a number below.");
		System.out.println("1. Add housing");
		System.out.println("2. Edit housing");
		System.out.println("3. Go back to main page");
		
		String choice = ""; 
		try
		{
			choice = StartPage.in.readLine(); 
			
			while(!choice.equals("1")&& !choice.equals("2") && !choice.equals("3"))
			{
				System.out.println("Please choose a valid option.");
				choice = StartPage.in.readLine(); 			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		if(choice.equals("1"))
		{
			AddNewHousing(user_id); 
		}
		else if (choice.equals("2"))
		{
			EditHousing(user_id); 
		}
		else
		{
			//go back to main page
			MainPage.HomePage(user_id);
		}

	}
	
	//adds a new house to the database under the person's user_id
	public static void AddNewHousing(int user_id)
	{
		House newHouse = new House(); 
		
		newHouse.uid = user_id; 
		String tempYear = ""; 
		String tempPrice = ""; 
		String tempMax = ""; 
		String tempKeyword = ""; 
		
		try
		{
			System.out.println("Please type in the name of the place.");
			newHouse.name = StartPage.in.readLine(); 
			
			System.out.println("Please type in the address of the place.");
			System.out.println("Enter address as: address, city, state zipcode");
			System.out.println("Such as: 100 E 100 N, Salt Lake City, Utah 84012");
			newHouse.address = StartPage.in.readLine();
			
			System.out.println("Please type in the phone number.");
			System.out.println("Enter phone as: (123)456-7890");
			newHouse.phoneNumber = StartPage.in.readLine();
			
			System.out.println("Please type the year it was built.");
			tempYear = StartPage.in.readLine();
			newHouse.yearBuilt = Integer.parseInt(tempYear); 
			while(newHouse.yearBuilt < 1600 && newHouse.yearBuilt > 2017)
			{
				System.out.println("Give a valid year between 1600 and 2017."); 
				tempYear = StartPage.in.readLine();
				newHouse.yearBuilt = Integer.parseInt(tempYear); 
			}
			
			System.out.println("Please type the price per person per night.");
			tempPrice = StartPage.in.readLine(); 
			newHouse.price = Integer.parseInt(tempPrice); 
			while(newHouse.price < 0)
			{
				System.out.println("Give a valid price above $0."); 
				tempPrice = StartPage.in.readLine(); 
				newHouse.price = Integer.parseInt(tempPrice); 
			}
			
			System.out.println("Please type maximum number of people who can stay here each night.");
			tempMax = StartPage.in.readLine(); 
			newHouse.maxResidents = Integer.parseInt(tempMax); 
			while(newHouse.maxResidents < 0)
			{
				System.out.println("Give a valid number above zero"); 
				tempMax = StartPage.in.readLine(); 
				newHouse.maxResidents = Integer.parseInt(tempMax); 
			}
			
			System.out.println("Please type what catagory this place falls under.");
			System.out.println("House");
			System.out.println("Apartment");
			System.out.println("Condo");
			newHouse.catagory = StartPage.in.readLine(); 
			//check that the catagory is valid
			while(!newHouse.catagory.equals("House") && !newHouse.catagory.equals("Apartment") && !newHouse.catagory.equals("Condo"))
			{
				System.out.println("Please enter a valid type for the catagory.");
				newHouse.catagory = StartPage.in.readLine(); 
			}
			
			System.out.println("Would you like to add keywords to this listing?");
			System.out.println("Yes");
			System.out.println("No");
			tempKeyword = StartPage.in.readLine(); 
			while(!tempKeyword.equals("Yes") && !tempKeyword.equals("No"))
			{
				System.out.println("Please type a valid number.");
				tempKeyword = StartPage.in.readLine(); 
			}
			if(tempKeyword.equals("Yes"))
			{
				System.out.println("Type a keyword and press enter.  You will be able to add as many keywords as you would like.");
				System.out.println("Type it with the first letter capitilized like 'Downtown' or 'Two bedroom'");
				System.out.println("Type STOP to end adding keywords.");
				String word = ""; 
				word = StartPage.in.readLine(); 
				while(!word.equals("STOP"))
				{
					newHouse.keywords.add(word); 
					word = StartPage.in.readLine(); 
				}
			}
			
			//add available dates
			String addDate = ""; 
			System.out.println("When is this listing available? Please enter information as MM/DD/YYYY");
			while(!addDate.equals("No"))
			{
				TimePeriod tp = new TimePeriod(); 
				System.out.println("Start: ");
				tp.stringStart = StartPage.in.readLine(); 
				System.out.println("End: ");
				tp.stringEnd = StartPage.in.readLine(); 
				
				tp.StringToDate();
				
				//add to new house
				newHouse.openDates.add(tp); 
				
				System.out.println("Would you like to add more dates?"); 
				System.out.println("Yes"); 
				System.out.println("No"); 
				addDate = StartPage.in.readLine(); 
			}
			
			//confirm house
			System.out.println("\nPlease confirm the following information is correct.");
			newHouse.PrintAttributes();
			System.out.println("1. All information is correct. Create new housing.");
			System.out.println("2. Information is incorrect. Start over.");

			String decision = ""; 
			decision = StartPage.in.readLine(); 
			
			while(!decision.equals("1") && !decision.equals("2"))
			{
				System.out.println("Please enter a valid number.");
				decision = StartPage.in.readLine(); 
			}
			
			if(decision.equals("1"))
			{
				newHouse.AddToDatabase(); 
			}
			else
			{
				HousingStart(user_id); 
			}
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}	
	}
	
	//allows the user to edit their houses
	public static void EditHousing(int user_id)
	{
		//Get's owner's housings
		User u = new User(user_id); 
		List<House> listings = u.UserListings(); 
		
		if(listings.size() == 0)
		{
			System.out.println("You have no listings to edit.\n");
			HousingStart(user_id); 
		}
		
		System.out.println("Which listing would you like to edit? Please enter a number.");
		
		for(int i = 0; i < listings.size(); i++)
		{
			String name = listings.get(i).name; 
			String address = listings.get(i).address; 
			int index = i+1; 
			System.out.println(index+": "+name+", "+address);
		}
		try
		{
			//Get attributes from chosen house
			String choice = StartPage.in.readLine();
			int index = Integer.parseInt(choice); 
			index = index - 1; 
			
			House h = listings.get(index); 
			h.PrintAttributes();
			
			//choose what to edit
			System.out.println("Enter what you would like to edit.");
			String attribute = StartPage.in.readLine(); 
						
			attribute = attribute.toLowerCase(); 
			boolean result = false; 
			
			//edit an attribute
			if(attribute.equals("name")|| attribute.equals("address") || attribute.equals("phone_number")
				|| attribute.equals("year_built") || attribute.equals("price") || attribute.equals("max_residents")
				|| attribute.equals("catagory"))
			{
				System.out.println("Enter what you would like to change that to.");
				String value = StartPage.in.readLine(); 
				
				result = h.EditAttribute(attribute, value);
			}
			
			//add or delete a keyword
			else if (attribute.equals("keyword"))
			{
				System.out.println("Would you like to add or delete a keyword?"); 
				System.out.println("Add");
				System.out.println("Delete");
				
				String dec = StartPage.in.readLine(); 
				while(!dec.equals("Add") && !dec.equals("Delete"))
				{
					System.out.println("Please type in a valid answer."); 
					dec = StartPage.in.readLine(); 
				}
				
				//add a keyword
				if(dec.equals("Add"))
				{
					System.out.println("What keyword would you like to add?"); 
					String newWord = StartPage.in.readLine(); 
					h.keywords.add(newWord); 
					h.AddKeywords();
				}
				
				//delete a keyword
				else
				{
					System.out.println("What keyword would you like to delete?"); 
					for(int i = 0; i < h.keywords.size(); i++)
					{
						System.out.println("Keyword: " + h.keywords.get(i));
					}
					String deleteWord = StartPage.in.readLine(); 
					h.keywords.remove(deleteWord);  
					h.DeleteKeyword(deleteWord);
				}
			}
			
			//add or edit available dates
			else if (attribute.equals("available date"))
			{
				System.out.println("What would you like to do?");
				System.out.println("1: Add an available date");
				System.out.println("2. Delete an available date");
				
				String adChoice = StartPage.in.readLine(); 
				while(!adChoice.equals("1") && !adChoice.equals("2"))
				{
					System.out.println("Please type in a valid answer."); 
					adChoice = StartPage.in.readLine(); 
				}
				//add a new available date
				if(adChoice.equals("1"))
				{
					String adAdd = ""; 
					while(!adAdd.equals("No"))
					{
						System.out.println("Please enter information as MM/DD/YYYY"); 
						TimePeriod tp = new TimePeriod(); 
						System.out.println("Start: ");
						tp.stringStart = StartPage.in.readLine(); 
						System.out.println("End: ");
						tp.stringEnd = StartPage.in.readLine(); 
						
						tp.StringToDate();
						
						//add to new house
						h.openDates.add(tp); 
						
						System.out.println("Would you like to add more dates?"); 
						System.out.println("Yes"); 
						System.out.println("No"); 
						adAdd = StartPage.in.readLine(); 
					}
					//add date to database
					h.AddAvailableDates();
				}
				
				//delete an available date
				else
				{
					h.GetAvailableDates();
					System.out.println("Choose what date to delete. Pick a number below.");
					int adIndex;
					for(int i = 0; i < h.openDates.size(); i++)
					{
						adIndex = i + 1; 
						System.out.println(adIndex + ": "+ h.openDates.get(i).PrintDate());				
					}
					String adDecision = StartPage.in.readLine(); 
					int testDec = Integer.parseInt(adDecision); 
					
					//check that the chosen date is a valid choice
					while(!(testDec > 0) && !(testDec < h.openDates.size()))
					{
						System.out.println("Choose a valid input.");
						adDecision = StartPage.in.readLine(); 
						testDec = Integer.parseInt(adDecision); 
					}
					
					TimePeriod temp_tp = new TimePeriod(); 
					//subtract one to account for adding 1 in adIndex
			        temp_tp = h.openDates.get(testDec - 1); 
			        
			        h.DeleteDate(temp_tp); 
				}
			}
			
			else
			{
				System.out.println("Not a valid answer try again.\n");
				EditHousing(user_id); 
			}
			
			System.out.println("Here is the updated information.");
			h.PrintAttributes();
			
			System.out.println("\nWould you like to edit anything else?");
			System.out.println("Yes");
			System.out.println("No");
			
			String decision = StartPage.in.readLine(); 
			
			while(!decision.equals("Yes") && !decision.equals("No"))
			{
				System.out.println("Choose a valid answer");
				decision = StartPage.in.readLine(); 
			}
			if(decision.equals("Yes"))
			{
				EditHousing(user_id); 
			}
			else
			{
				HousingStart(user_id); 
			}			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}		
	}
}
