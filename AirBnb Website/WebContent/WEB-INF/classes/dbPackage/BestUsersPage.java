package dbPackage;

public class BestUsersPage {

	public static void BestUsersStart(int user_id)
	{
		System.out.println("What would you like to do?");
		System.out.println("1. See most trusted users");
		System.out.println("2. See most useful users");
		System.out.println("3. Go back to home page");
		
		try
		{
			String choice = StartPage.in.readLine(); 
			System.out.println("How many users would you like to see?");
			String stringNum = StartPage.in.readLine(); 
			int numUsers = Integer.parseInt(stringNum); 
			
			BestUsers bs = new BestUsers(); 
			if (choice.equals("1"))
			{
				
			}
			else if (choice.equals("2"))
			{
				
			}
			else if (choice.equals("3"))
			{
				MainPage.HomePage(user_id);
			}
			else
			{
				System.out.println("Choose a valid input.");
			}
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
