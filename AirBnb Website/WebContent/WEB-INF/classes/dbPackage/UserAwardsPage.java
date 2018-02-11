package dbPackage;

import java.util.List;

public class UserAwardsPage {

	public static void UserAwardsStart(int user_id)
	{
		try
		{
			UserAwards userAwd = new UserAwards();
			List<User> allUsefulAwd = userAwd.UsersUsefulFeedback();
			System.out.println("View Most useful Feedbacks");
			if(allUsefulAwd.size() == 0)
			{
				System.out.println("No user has a feedback at this time");
				MainPage.HomePage(user_id);
			}
			
			System.out.println("Enter the number of users with the most useful Feedbacks you'd like to see");
			System.out.println("Type 'BACK' to go back to mainpage");
			String userInput = StartPage.in.readLine();
			if(userInput.equals("BACK"))
			{
				MainPage.HomePage(user_id);
			}		
			int numOfUsers = Integer.parseInt(userInput);
			
			if(numOfUsers > allUsefulAwd.size())
			{
				for(int i = 0; i < allUsefulAwd.size(); i++)
				{
					allUsefulAwd.get(i).PrintAttributes();
					System.out.println("");
				}
			}
			else
			{
				for(int i = 0; i < numOfUsers; i++)
				{
					allUsefulAwd.get(i).PrintAttributes();
					System.out.println("");
				}
			}
			
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
