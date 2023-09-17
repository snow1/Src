/** A test striker without common decision */
option(Defender)
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
		}
			action
		{
			LookAtBall();
		Stand();
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
			SpecialAction(SpecialActionRequest::defenderDownToBlockBall,true);
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
			SpecialAction(SpecialActionRequest::defenderDownToBlockBall);
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
			if (libCodeRelease.timeSinceBallWasSeen() > 4500)
			goto searchForBall;
		if (libCodeRelease.ballPositionCal() < 300.f)
			goto alignToGoal;
		if (theBallModel.estimate.position.angle()>15_deg)
			goto turnToBall;
		if (theBallModel.estimate.position.angle()<-15_deg)
			goto turnToBalls;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.f, 0.65f, 0.f), theBallModel.estimate.position);
		}
	}

	state(alignToGoal)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (std::abs(libCodeRelease.angleToGoaldefender) < 25_deg)
			goto alignBehindBall;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(-0.25f, 0.f, 0.5f));
		}
	}

	state(alignBehindBall)
	{
		transition
		{
			if (libCodeRelease.timeSinceBallWasSeen() > 3000)
			goto searchForBall;
		if (libCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 60.f)
			&& libCodeRelease.between(theBallModel.estimate.position.x(), 160.f, 215.f)
			)
			goto kick;
		}
			action
		{
			LookAtBall();
		WalkToTarget(Pose2f(0.2f, 0.45f, 0.35f), Pose2f(0, theBallModel.estimate.position.x() - 185.f, theBallModel.estimate.position.y() - 50.f));
		}
	}

	state(kick)
	{
		transition
		{
			if (state_time > 3000 || (state_time > 10 && action_done))
			goto turnToBall;
			/*if (libCodeRelease.timeSinceBallWasSeen() < 300 && theRoleTransformation.number == 4)
			goto goTopointfour;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theRoleTransformation.number == 5)
			goto goTopointfive;*/
		}
			action
		{
			LookAtBall();
		//InWalkKick(WalkRequest::left, Pose2f(libCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
		SpecialAction(SpecialActionRequest::strongKick,true);
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
			goto turnToBallnext;
		}
			action
		{
			LookAtBall();
		WalkAtSpeedPercentage(Pose2f(-0.5f, 0.f, 0.f));
		}
	}
	state(turnToBallnext)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		if (libCodeRelease.timeSinceBallWasSeen() > 5000)
			goto searchForBall;
		if (theBallModel.estimate.velocity.x() < -500.f &&theBallModel.estimate.position.y() > -180.f&&theBallModel.estimate.position.y() < 180.f &&theBallModel.estimate.position.x() < 1500.f&&libCodeRelease.ballPositionCal() < 1500.f)
			goto blockBall;
		if (theBallModel.estimate.position.y() >180.f&&libCodeRelease.ballPositionCal() < 2200.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 2200.f)
			goto blockBallL;
		if (theBallModel.estimate.position.y() < -180.f&&libCodeRelease.ballPositionCal() < 2200.f&&theBallModel.estimate.velocity.x() < -500.f&&theBallModel.estimate.position.x() < 2200.f)
			goto blockBallR;
		if (absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() <= 2000.f&&libCodeRelease.ballPositionCal() >= 100.f)
			goto walkToBall;

		/*if ((theBallModel.estimate.position.angle()>10_deg || theBallModel.estimate.position.angle()<-10_deg)&& theRoleTransformation.number == 4)
			goto goTopointfour;
		if ((theBallModel.estimate.position.angle()>10_deg || theBallModel.estimate.position.angle()<-10_deg)&& theRoleTransformation.number == 5)
			goto goTopointfive;*/
		}
			action
		{
			LookAtBall();
		Stand();

		}
	}

	state(goTopointfour)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		Pose2f relativeToRobot = (Pose2f)theGetPoints.fourNeedpoint - theRobotPose;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f&&theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f&&theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;
		if (absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() <= 1000.f&&libCodeRelease.ballPositionCal() >= 100.f)
			goto walkToBall;
		}
			action
		{
			LookAtBall();
		WalkToFixedPosition(Pose2f(0.35f, 0.7f, 0.4f), theGetPoints.fourNeedpoint);
		//Stand();
		}
	}
	state(goTopointfive)
	{
		transition
		{
			Vector2f absoluteBallPosition = theRobotPose * theBallPercept.positionOnField;
		Pose2f relativeToRobot = (Pose2f)theGetPoints.fiveNeedpoint - theRobotPose;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f&&theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f&&theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;
		if (absoluteBallPosition.x() < 0.f && libCodeRelease.ballPositionCal() <= 1000.f&&libCodeRelease.ballPositionCal() >= 100.f)
			goto walkToBall;
		}
			action
		{
			LookAtBall();
		WalkToFixedPosition(Pose2f(0.35f, 0.7f, 0.4f), theGetPoints.fiveNeedpoint);
		//Stand();
		}
	}
	state(searchForBall)
	{
		transition
		{
			if (state_time > 5000)
			goto searchForBallnext;
			/*if (libCodeRelease.timeSinceBallWasSeen() < 300&& theRoleTransformation.number == 4)
			goto goTopointfour;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theRoleTransformation.number == 5)
			goto goTopointfive;*/
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;
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
			/*if (libCodeRelease.timeSinceBallWasSeen() < 300 && theRoleTransformation.number == 4)
			goto goTopointfour;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theRoleTransformation.number == 5)
			goto goTopointfive;*/
			if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()>0_deg)
			goto turnToBall;
		if (libCodeRelease.timeSinceBallWasSeen() < 300 && theBallModel.estimate.position.angle()<0_deg)
			goto turnToBalls;
		if (state_time > 5000)
			goto searchForBall;
		}
			action
		{
			LookForward();
		WalkAtSpeedPercentage(Pose2f(0.5f, 0.f, 0.f));
		}
	}

}
