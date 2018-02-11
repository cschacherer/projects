package dbPackage;

import java.util.*;
import java.util.List;

public class FeedbackPage {

	//get list of visit a user.
	//hotel user wants to give feedback for.

	public static void FeedBackStart(int user_id)
	{
		try
		{
			User u = new User(user_id);
			List<Visit> userTH =  u.UserVisits();

			for(int i = 0; i < userTH.size(); i++ )
			{
				int ind = i + 1;
				System.out.println(ind + ": ");
				userTH.get(i).PrintVisit();
				System.out.println("");
			}

			System.out.println("Choose number of hotel to leave feedback on ");
			System.out.println("Type 'BACK' to return to Homepage");
			String userInput = StartPage.in.readLine();
			if(userInput.equals("BACK"))
			{
				MainPage.HomePage(user_id);
			}

			int userInput2 = Integer.parseInt(userInput);

			System.out.println("Type 'VIEW' to see Usefullnes ratings on Feedback or 'FEEDBACK' to enter a Feedback");
			String userInput3 = StartPage.in.readLine();
			if(userInput3.equals("VIEW"))
			{
				Feedback viewfeedback = new Feedback();	

				List<Feedback> hotelFeedback = viewfeedback.GetFeedback(userTH.get(userInput2 - 1).hid); 
				for(int i = 0; i < hotelFeedback.size(); i++)
				{
					hotelFeedback.get(i).PrintFeedBacks();
					System.out.println("");
				}

			}
			if(userInput3.equals("FEEDBACK"))
			{
				CreateFeedback(userTH.get(userInput2-1), user_id);			
			}


		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}

	}

	public static void CreateFeedback(Visit v, int user_id)
	{
		try
		{
			Feedback userFeedBack = new Feedback();
			userFeedBack.uid = user_id;
			userFeedBack.hid = v.hid;
			userFeedBack.date = v.period.stringEnd;

			System.out.println("Select a number from 0-10 for Scores. With 0 being the lowest and the 10 the highest");
			System.out.println("Enter Score: ");
			String scoreEntered = StartPage.in.readLine();
			int numScore = Integer.parseInt(scoreEntered);
			userFeedBack.score = numScore;

			System.out.println("Enter Feedback under 200 characters or push 'ENTER' to skip :");
			String feedbackEntered = StartPage.in.readLine();
			userFeedBack.text = feedbackEntered;

			boolean checkInTable = userFeedBack.inFeedback(); 
			if(checkInTable)
			{
				System.out.println("Cannot leave a feedback on a hotel twice.");
			}
			else
			{
				userFeedBack.AddToDatabase();
				FeedBackStart(user_id);
			}
			

		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}

	}


}

