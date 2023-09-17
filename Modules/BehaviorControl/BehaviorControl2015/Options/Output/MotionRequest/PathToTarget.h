/** Sets all members of the MotionRequest representation for executing a PathMode-WalkRequest
 *  (i.e. Plan path to a \c target at a \c speed)
 *  @param speed Walking speeds, in percentage.
 *  @param target Walking target, in mm and radians, in field coordinates.
 option(PathToTarget, (float)speed, (const Pose2f&)target)
 */
option(PathToTarget, (const Pose2f&) speed, (const Pose2f&) target)
{
  const bool avoidOwnPenaltyArea = (theRole.role != Role::keeper);

  /** Set the motion request. */
  initial_state(setRequest)
  {
    transition
    {
      if(theMotionInfo.motion == MotionRequest::walk)
        goto requestIsExecuted;
    }
    action
    {
      theMotionRequest.motion = MotionRequest::walk;
      theMotionRequest.walkRequest.mode = avoidOwnPenaltyArea ? WalkRequest::pathModeAvoidingOwnPenaltyArea : WalkRequest::pathMode;
      theMotionRequest.walkRequest.target = target;
   // theMotionRequest.walkRequest.speed = Pose2f(speed, speed, speed);
	//  theMotionRequest.walkRequest.speed = Pose2f(1.f, 1.f, 1.f);
	  theMotionRequest.walkRequest.speed = speed;
      theMotionRequest.walkRequest.walkKickRequest = WalkRequest::WalkKickRequest();
    }
  }

  /** The motion process has started executing the request. */
  target_state(requestIsExecuted)
  {
    transition
    {
      if(theMotionInfo.motion != MotionRequest::walk)
        goto setRequest;
    }
    action
    {
      theMotionRequest.motion = MotionRequest::walk;
      theMotionRequest.walkRequest.mode = avoidOwnPenaltyArea ? WalkRequest::pathModeAvoidingOwnPenaltyArea : WalkRequest::pathMode;
      theMotionRequest.walkRequest.target = target;
	  theMotionRequest.walkRequest.speed = speed;
   // theMotionRequest.walkRequest.speed = Pose2f(speed, speed, speed);
	 // theMotionRequest.walkRequest.speed = Pose2f(1.f, 1.f, 1.f);
      //theMotionRequest.walkRequest.kickType = WalkRequest::none;
	  theMotionRequest.walkRequest.walkKickRequest = WalkRequest::WalkKickRequest();
    }
  }
}
