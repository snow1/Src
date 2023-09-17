/** A test striker option without common decision */
option(Striker)
{
	initial_state(start)
	{
		transition
		{
			//if (state_time > 1000)
			//goto searchForBall;
		}
			action
		{
			OUTPUT(idText, text, "angleToGoalstriker  " << libCodeRelease.angleToGoalstriker);
			//LookForward();
		//Stand();
		WalkAtSpeedPercentage(Pose2f(0.f, -0.8f, 0.f));
		}
	}

	state(turnToBall)
	{
		transition
		{
		if (libCodeRelease.timeSinceBallWasSeen() > 7000)
			goto searchForBall;
		if (std::abs(theBallModel.estimate.position.angle())<5_deg)
			goto walkToBall;

		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.5f, 0.f, 0.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
		}
	}

	state(turnToBalls)
	{
		transition
		{
	
		if (libCodeRelease.timeSinceBallWasSeen() > 7000)
			goto searchForBall;
		if (std::abs(theBallModel.estimate.position.angle())<5_deg)
			goto walkToBall;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(-0.5f, 0.f, 0.f));
		}
	}

	state(walkToBall)
	{
		transition
		{
			
		if (libCodeRelease.timeSinceBallWasSeen() > 5000)
			goto searchForBall;
		if (theBallModel.estimate.position.norm() < 400.f)
			goto WOsolywalkToBall;
		if (theBallModel.estimate.position.angle()>15_deg)
			goto turnToBall;
		if (theBallModel.estimate.position.angle()<-15_deg)
			goto turnToBalls;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.f, 0.8f, 0.f), theBallModel.estimate.position);
		}
	}

	state(WOsolywalkToBall)
	{
		transition
		{
		if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (theBallModel.estimate.position.norm() < 300.f)
			goto alignToGoal;
		if (theBallModel.estimate.position.angle()>15_deg)
			goto turnToBall;
		if (theBallModel.estimate.position.angle()<-15_deg)
			goto turnToBalls;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.f, 0.4f, 0.f), theBallModel.estimate.position);
		}
	}
	/*state(Tothearea)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		Pose2f relativeToRobot = Pose2f(0.f, 2700.f, 1000.f) - theRobotPose;
		if (theRoleTransformation.number == 2)
			goto turnToBall;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f)
			goto searchForBall;
		}
			action
		{
			LookLocalization();
		WalkToFixedPosition(Pose2f(0.f, 0.45f, 0.35f), Pose2f(0.f, 2700.f, 1000.f));
		}
	}*/
	state(alignToGoal)
	{
		transition
		{
			
		if (libCodeRelease.timeSinceBallWasSeen() > 5000)
			goto searchForBall;
		if (std::abs(libCodeRelease.angleToGoalstriker) < 0.5)
			goto alignBehindBall;
		}
			action
		{
			LookForward();
		WalkAtSpeedPercentage(Pose2f(-0.25f, 0.f, 0.5f));
		}
	}


	state(alignBehindBall)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
			
		if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (libCodeRelease.between(theBallModel.estimate.position.y(), 40.f, 65.f)
			&& libCodeRelease.between(theBallModel.estimate.position.x(), 160.f, 215.f)
			//&& std::abs(libCodeRelease.angleToGoal) < 5_deg
			)
			goto kick;
		if(absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() >= 200.f&&libCodeRelease.ballPositionCal() >= 100.f)
			goto walkToBall;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.1f, 0.45f, 0.3f), Pose2f(0, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 50.f));
		//InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), Pose2f(0, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 50.f));
		}
	}

	state(kick)
	{
		transition
		{
			if (state_time > 3000 || (state_time > 10 && action_done))
			goto turnToBall;
		}
			action
		{
			//Annotation("Alive and Kickin'");
			LookForward();
		InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), Pose2f(0, 0.f, 0.f));
		//SpecialAction(SpecialActionRequest::strongKick, true);
		//InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 130.f, theBallModel.estimate.position.y() - 55.f));
		}
	}
	state(sideKickLeft)//≤‡Ãﬂ
	{
		transition
		{
			if (action_done)
			goto turnToBall;
		}
			action
		{
			theHeadControlMode = HeadControl::lookForward;
		SpecialAction(SpecialActionRequest::lightKick, true);
		}
	}
	state(sideKickRight)//”“≤‡Ãﬂ
	{
		transition
		{
			if (action_done)
			goto turnToBall;
		}
			action
		{
			theHeadControlMode = HeadControl::lookForward;
		SpecialAction(SpecialActionRequest::lightKick);
		}
	}

	state(searchForBall)
	{
		transition
		{

			if (libCodeRelease.timeSinceBallWasSeen() < 300)
			goto turnToBall;
		if (state_time > 10000)
			goto searchForBallnext;
		}
			action
		{
			LookLocalization();
		Stand();
		}
	}
	state(searchForBallnext)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() < 300 )
			goto turnToBall;
		//if (theRoleTransformation.number == 3)
			//goto Tothearea;
		//if (state_time > 20000)
			//goto zhixing;
		}
			action
		{
			LookForward();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
		}
	}
	state(zhixing)
	{
		transition
		{
		if (state_time > 5000)
			goto searchForBall;
		}
			action
		{
			LookLocalization();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
		}
	}
}