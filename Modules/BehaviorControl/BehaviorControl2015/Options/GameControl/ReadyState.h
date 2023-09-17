option(ReadyState)
{
	initial_state(look_localization)
	{
		transition
		{
			if (state_time>1000)
			goto  decide_pose;
		}
			action
		{
			theHeadControlMode = HeadControl::lookLocalization;
		Stand();
		}
	}
	state(decide_pose)
	{
		transition
		{
			if (theGameInfo.kickOffTeam == theGameInfo.dropInTeam)
			{
				if (Global::getSettings().playerNumber == 1)
					goto pose1;
				if (Global::getSettings().playerNumber == 2)
					goto pose2;
				else if (Global::getSettings().playerNumber == 3)
					goto pose3;
				else if (Global::getSettings().playerNumber == 4)
					goto pose4;
				else if (Global::getSettings().playerNumber == 5)
					goto pose5;
			}
			else
			{
				if (Global::getSettings().playerNumber == 1)
					goto pose1;
				if (Global::getSettings().playerNumber == 2)
					goto pose2;
				else if (Global::getSettings().playerNumber == 3)
					goto pose3;
				else if (Global::getSettings().playerNumber == 4)
					goto pose4;
				else if (Global::getSettings().playerNumber == 5)
					goto pose5;
			}
		}
			action
		{
			theHeadControlMode = HeadControl::lookLocalization;
		Stand();
		}
	}
	// using relative distance from initial stand point
	state(pose1)
	{//improve localisation
		transition
		{

		}
			action
		{
			//WalkToPose1(-4200.f,0.f,0.f);
			LookForward();
		//WalkToTarget(Pose2f(0.4f, 0.7f, 0.f),Pose2f(0.f, 3500.f, 0.f));//3500走到场中央
		WalkToFixedPosition(Pose2f(0.1f, 0.45f, 0.35f), Pose2f(0.f, -4350.f, 0.f));													   //WalkToTarget(Pose2f(0.4f, 0.7f, 0.f), Pose2f(0.f, 2100.f, 0.f));//走到禁区边缘
		//WalkAtSpeedPercentage(Pose2f(0.f, 0.6f, 0.f));
		}
	}
	state(pose2)
	{
		transition
		{
		
		}
			action
		{
			RLookLocalization();
		WalkToFixedPosition(Pose2f(0.1f, 0.8f, 0.6f), Pose2f(3.14f, -750.f, 0.f));
		}
	}
	state(pose3)
	{
		action
		{
			LLookLocalization();
		WalkToFixedPosition(Pose2f(0.1f, 0.5f, 0.3f), Pose2f(0.f, -750.f, 1000.f));
		}
	}

	state(pose4)
	{
			action
		{
			LLookLocalization();
		WalkToFixedPosition(Pose2f(0.1f, 0.5f, 0.3f), Pose2f(0.f, -2000.f, 750.f));
		}
	}

	state(pose5)
	{
			action
		{
				RLookLocalization();
			WalkToFixedPosition(Pose2f(0.1f, 0.5f, 0.3f), Pose2f(0.f, -2000.f, 750.f));
		}
	}


	
}
