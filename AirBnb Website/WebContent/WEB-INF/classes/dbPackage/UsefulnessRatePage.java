package dbPackage;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class UsefulnessRatePage {
	public static Ratings r = new Ratings();
	public static List<House> houseToRate = new ArrayList<House>();
	public static List<Feedback> Feedbacks = new ArrayList<Feedback>();
	public static void usefullStart(int user_id)
	{
		try
		{
			Feedback f = new Feedback();	
			houseToRate = r.Houses();

			for(int i = 0; i < houseToRate.size(); i++ )
			{
				int ind = i + 1;
				System.out.println(ind + ": ");
				houseToRate.get(i).PrintAttributes();
				System.out.println("");

			}
			
			System.out.println("Select the number of hotel to view its most useful feedbacks");
			System.out.println("Type 'BACK' to return to homepage" );
			String userInput = StartPage.in.readLine(); 
			if(userInput.equals("BACK"))
			{
				MainPage.HomePage(user_id);
			}
			int userInput2 = Integer.parseInt(userInput);
			int hotelID = houseToRate.get(userInput2-1).hid; 			
			Feedbacks = f.GetFeedback(hotelID); 	
			if(Feedbacks.size() == 0)
			{
				
				System.out.println("There are no feedbacks at this time");
				usefullStart(user_id);
					
			}
			System.out.println("Type 'VIEW' to see all Feedbacks  in order of usefulness OR  ");
			System.out.println("Enter the number of the most useful feedback you would like to see");
			String userInput3 = StartPage.in.readLine();
			if(userInput3.equals("VIEW"))
			{
				//System.out.println("test");
				GetNumberofFeedback(Feedbacks.size());
			}
			else
			{
				int numberOfFeedback = Integer.parseInt(userInput3);
				if(Feedbacks.size() < numberOfFeedback)
				{
					System.out.println("We have only " + Feedbacks.size() + " " + "Feedbacks");
					GetNumberofFeedback(Feedbacks.size());
				}
				else
				{
					GetNumberofFeedback(numberOfFeedback);
				}
			}		
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	public static void GetNumberofFeedback(int num)
	{
		Collections.sort(Feedbacks, Collections.reverseOrder());
		for(int i = 0; i < num; i++)
		{
			Feedbacks.get(i).PrintFeedBacks();
			System.out.println("");
			//usefullStart(user_id);

		}
	}

}
