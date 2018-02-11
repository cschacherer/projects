package dbPackage;

import java.util.*;

public class TrustingPage {
	
	public static void TrustingStart(int user_id)
	{
		System.out.println("Here is a list of users: ");
		Trust.PrintAllLogins(); 
		
		try
		{
			System.out.println("Please type in the login name that you would like to set as trusted or not trusted."); 
			String chosenUser = StartPage.in.readLine(); 
			
			System.out.println("Would you like to set a user as: ");
			System.out.println("1. Trusted");
			System.out.println("2. Not trusted");
			System.out.println("3. Go back to home page");
			String choice = StartPage.in.readLine(); 
			
			Trust t = new Trust(user_id); 
			//trust a user
			if(choice.equals("1"))
			{
				boolean result = t.AddTrusted(chosenUser, 1); 
				if(result)
				{
					System.out.println(chosenUser + " is now trusted!");
				}
				else
				{
					System.out.println("There was an error.  Try again.");
				}
				List<String> trusted = t.GetTrustedUsers(); 
				if(trusted.size() == 0)
				{
					System.out.println("You don't have any trusted users at this time.\n"); 
				}
				else
				{
					System.out.println("Here is a list of all of your trusted users: ");
					for(int i = 0; i < trusted.size(); i++)
					{
						System.out.println(trusted.get(i));
					}
					System.out.println("");
				}
				TrustingStart(user_id); 
				
			}
			//set a user as not trusted
			else if (choice.equals("2"))
			{
				boolean res = t.AddTrusted(chosenUser, 0);
				if(res)
				{
					System.out.println(chosenUser + " is now not trusted!");
				}
				List<String> notTrusted = t.GetNotTrustedUsers(); 
				if(notTrusted.size() == 0)
				{
					System.out.println("You don't have any trusted users at this time.\n"); 
				}
				else
				{
					System.out.println("Here is a list of all of your not trusted users: ");
					for(int i = 0; i < notTrusted.size(); i++)
					{
						System.out.println(notTrusted.get(i));
					}
					System.out.println("");
				}
				TrustingStart(user_id); 
				
			}
			//go back to homepage
			else if (choice.equals("3"))
			{
				MainPage.HomePage(user_id);
			}
			else
			{
				TrustingStart(user_id); 
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
