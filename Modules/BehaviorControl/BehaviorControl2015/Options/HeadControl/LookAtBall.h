option(LookAtBall)
{
  initial_state(look_at_estimate)
  {
     transition
    {
     // if(ball.time_since_last_seen > 2500)
      /*if(theBallModel.timeWhenLastSeen>2500)
      	goto look_active;*/
    }
    action
    {
       
	  SetHeadTargetOnGround(Vector3f(theBallModel.estimate.position.x(), theBallModel.estimate.position.y(), theFieldDimensions.ballRadius));
      /*head.mode = target_on_ground;
      head.ccmode = autoCamera;
      head.target.x() = ball.x();
      head.target.y() = ball.y();
      head.target.z() = 35;
      head.speed = 150;*/
    }
  }

 /* state(look_active)
  {
     transition
    {
      if(libCodeRelease.timeSinceBallWasSeen() > 100)
        goto look_at_estimate;
    }
    action
    {
      head.use_active_vision = true;
      head.active_vision_ball_factor = 1;
      head.speed = 150;
    }
  }*/
}
