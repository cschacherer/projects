package dbPackage;

public class DegreeSeparationPage {

	public static void SeparationStart(int user_id)
	{
		System.out.println("Here is a list of usernames: "); 
		Trust.PrintAllLogins(); 
		
		try
		{
			System.out.println("Please enter two user names to find the degree of separation.");
			System.out.println("Name 1: "); 
			String name1 = StartPage.in.readLine(); 
			System.out.println("Name 2: ");
			String name2 = StartPage.in.readLine();
			
			DegreeSeparation ds = new DegreeSeparation(); 
			int degree = ds.FindDegree(name1, name2); 
			
			if(degree == 1)
			{
				System.out.println("There is 1 degree of separation.\n");
			}
			else
			{
				System.out.println("There is more than 1 degree of separation.\n"); 
			}
			
			MainPage.HomePage(user_id);
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
