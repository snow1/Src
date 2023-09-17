/** A test striker without common decision */
option(Keeper)
{
	initial_state(start)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 1000)
			goto searchForBall;
		if (theBallModel.estimate.position.angle()>10_deg)
			goto turnToBall;
		if (theBallModel.estimate.position.angle()<-10_deg)
			goto turnToBalls;
		/*if (theBallModel.estimate.velocity.x() < -500.f &&theBallModel.estimate.position.y() > -130.f&&theBallModel.estimate.position.y() < 130.f &&theBallModel.estimate.position.x() < 1500.f&&libCodeRelease.ballPositionCal() < 1500.f)
		goto blockBall;
		if (theBallModel.estimate.position.y() >130.f&&libCodeRelease.ballPositionCal() < 1500.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 1500.f)
		goto blockBallL;
		if (theBallModel.estimate.position.y() < -130.f&&libCodeRelease.ballPositionCal() < 1500.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 1500.f)
		goto blockBallR;*/
		}
			action
		{
			LookAtBall();
		Stand();
		//WalkAtSpeedPercentage(Pose2f(0.f, -0.99f, 0.f));
		//WalkToTarget(Pose2f(0.f, 0.5f, 0.f), theGetPoints.keeperNeedpointa);
		//WalkToFixedPosition(Pose2f(0.7f, 0.7f, 0.7f), theGetPoints.keeperNeedpoint);
		}
	}
	state(blockBall)
	{
		transition
		{
			if (action_done)
			goto stand;
		}
			action
		{
			SpecialAction(SpecialActionRequest::sitDownToBlockBall);
		}
	}
	state(blockBallL)
	{
		transition
		{
			if (action_done)
			goto stand;
		}
			action
		{
			SpecialAction(SpecialActionRequest::downToBlockBall);
		}
	}
	state(blockBallR)
	{
		transition
		{
			if (action_done)
			goto stand;
		}
			action
		{
			SpecialAction(SpecialActionRequest::FallDownToBlockBall);
		}
	}
	state(stand)
	{
		transition
		{
			if (state_time > 2000)
			goto searchForBall;
		}
			action
		{
			Stand();
		}
	}
	state(walkToBall)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (libCodeRelease.ballPositionCal() < 300.f)
			goto alignToGoal;
		if (theBallModel.estimate.position.angle() > 15_deg)
			goto turnToBall;
		if (theBallModel.estimate.position.angle() < -15_deg)
			goto turnToBalls;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.f, 0.7f, 0.f), theBallModel.estimate.position);
		}
	}

	state(alignToGoal)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (std::abs(libCodeRelease.angleToGoalkeeper) < 25_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
			goto alignBehindBall;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(-0.4f, 0.f, 0.8f));
		}
	}

	state(alignBehindBall)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (libCodeRelease.between(theBallModel.estimate.position.y(), 20, 65.f)// 5  25			//45	55
			&& libCodeRelease.between(theBallModel.estimate.position.x(), 170.f, 215.f)
			&&std::abs(libCodeRelease.angleToGoalkeeper) < 25_deg 
			//120  150	//180	195//165
																					   //&& std::abs(libCodeRelease.angleToGoal) < 2_deg
			)
			goto kick;
		}
			action
		{
			LookAtBall();
		//WalkToTarget(Pose2f(0.3f, 0.4f, 0.f), Pose2f(0, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 50.f));
		WalkToTarget(Pose2f(-0.4f, 0.7f, 0.7f), Pose2f(//libCodeRelease.angleToGoal
			libCodeRelease.angleToGoalkeeper, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 50.f));//160 50
		}
	}

	state(kick)
	{
		transition
		{
			if ( action_done)
			goto backToGoal;
		}
			action
		{
			LookAtBall();
		//InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
		InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), Pose2f(0, 0.f, 0.f));
		}
	}
	state(backToGoal)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		Pose2f relativeToRobot = Pose2f(0.f, -4400.f, 0.f) - theRobotPose;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f)
			goto searchForBall;
		if (absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() <= 500.f&&libCodeRelease.ballPositionCal() >= 300.f)
			goto walkToBall;
		}
			action
		{
			LookAtBall();
		WalkToFixedPosition(Pose2f(0.4f, 0.8f, 0.6f), Pose2f(0.f, -3900.f, 0.f));
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
			goto turnToBallnext;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));//×ó×ª
		}
	}
	state(turnToBalls)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (std::abs(theBallModel.estimate.position.angle())<5_deg)
			goto turnToBallnext;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(-0.5f, 0.f, 0.f));//ÓÒ×ª
		}
	}

	state(turnToBallnext)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		if (libCodeRelease.timeSinceBallWasSeen() > 2000)
			goto searchForBall;
		if (theBallModel.estimate.velocity.x() < -500.f &&theBallModel.estimate.position.y() > -130.f&&theBallModel.estimate.position.y() < 130.f &&theBallModel.estimate.position.x() < 1500.f&&libCodeRelease.ballPositionCal() < 1500.f)
			goto blockBall;
		if (theBallModel.estimate.position.y() >130.f&&libCodeRelease.ballPositionCal() < 1200.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 1200.f)
			goto blockBallL;
		if (theBallModel.estimate.position.y() < -130.f&&libCodeRelease.ballPositionCal() < 1200.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 1200.f)
			goto blockBallR;

		if (absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() <= 500.f&&libCodeRelease.ballPositionCal() >= 100.f)
			goto walkToBall;
		//if (theBallModel.estimate.position.angle()>15_deg || theBallModel.estimate.position.angle()<-15_deg)
			//goto goTopoint;
		}
			action
		{
			LookAtBall();
		Stand();

		}
	}

	state(goTopoint)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		Pose2f relativeToRobot = (Pose2f)theGetPoints.oneNeedpoint - theRobotPose;
		if (libCodeRelease.timeSinceBallWasSeen() > 5000)
			goto searchForBall;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 100.f && std::abs(relativeToRobot.translation.y()) < 20.f&&theBallModel.estimate.position.angle()>10_deg)
			goto turnToBall;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 100.f && std::abs(relativeToRobot.translation.y()) < 20.f&&theBallModel.estimate.position.angle()<-10_deg)
			goto turnToBalls;
		if (absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() <= 1000.f&&libCodeRelease.ballPositionCal() >= 100.f)
			goto walkToBall;



		if (theBallModel.estimate.velocity.x() < -500.f &&theBallModel.estimate.position.y() > -130.f&&theBallModel.estimate.position.y() < 130.f &&theBallModel.estimate.position.x() < 1500.f&&libCodeRelease.ballPositionCal() < 1500.f)
			goto blockBall;
		if (theBallModel.estimate.position.y() >130.f&&libCodeRelease.ballPositionCal() < 1200.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 1200.f)
			goto blockBallL;
		if (theBallModel.estimate.position.y() < -130.f&&libCodeRelease.ballPositionCal() < 1200.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 1200.f)
			goto blockBallR;
		}
			action
		{
			LookForward();
		WalkToFixedPosition(Pose2f(0.4f, 0.7f, 0.5f), theGetPoints.oneNeedpoint);
		}
	}
	state(searchForBall)
	{
		transition
		{

			//if (libCodeRelease.timeSinceBallWasSeen() < 300)
			//goto goTopoint;
			if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;
		/*if (state_time > 10000)
		{
			goto searchForBallnext;
		}*/
		}
			action
		{
			LookForward();
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
		//if (state_time > 10000)
		//goto goTopoint;
		}
			action
		{
			LookForward();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
		}
	}

}
