/** A test striker option without common decision */
option(demoStriker)
{
	initial_state(start)
	{
		transition
		{
			if (state_time > 1000)
			 goto searchForBall;
		}
			action
		{
			LookAtBall();
		Stand();
			//kick();
		}
	}

	state(turnToBall)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		/*if (theBallModel.estimate.position.y()< -100.f&&libCodeRelease.between(theBallModel.estimate.position.x(), 500.f, 2000.f))
		goto moveRight;
		if (theBallModel.estimate.position.y()>100.f&&libCodeRelease.between(theBallModel.estimate.position.x(), 500.f, 2000.f))
		goto moveLeft;*/
		if (std::abs(theBallModel.estimate.position.angle())<5_deg)
			goto walkToBall;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
		}
	}
	state(turnToBalls)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
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
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
			if (libCodeRelease.ballPositionCal() < 300.f&&libCodeRelease.angleToGoal>0)
				goto alignToGoalR;
			if (libCodeRelease.ballPositionCal() < 300.f&&libCodeRelease.angleToGoal<0)
				goto alignToGoalL;
			if (theBallModel.estimate.position.angle() > 15_deg)
				goto turnToBall;
			if (theBallModel.estimate.position.angle() < -15_deg)
				goto turnToBalls;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.f, 0.8f, 0.f), theBallModel.estimate.position);
		}
	}

	state(alignToGoalL)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (std::abs(libCodeRelease.angleToGoal) < 15_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
			goto alignBehindBall;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(-0.4f, 0.f, 0.8f));
		}
	}

	state(alignToGoalR)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (std::abs(libCodeRelease.angleToGoal) < 15_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
			goto alignBehindBall;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(0.4f, 0.f, -0.8f));
		}
	}


	state(alignBehindBall)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 7000)
			goto searchForBall;
		if (libCodeRelease.between(theBallModel.estimate.position.y(), 40.f, 85.f)
			&& libCodeRelease.between(theBallModel.estimate.position.x(), 170.f, 215.f)
			)
			goto kick;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.5f, 0.8f, 0.6f), Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 50.f));
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

		LookForward();
		SpecialAction(SpecialActionRequest::strongKick, true);
		}
	}

	state(searchForBall)
	{
		transition
		{

			if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;
		//if (theRoleTransformation.number == 3)
			//goto Tothearea;
		if (state_time > 5000)
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
			if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;

		}
			action
		{
			LookForward();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
		}
	}
}