option(RLookLocalization)
{
	initial_state(look_left_stop_at_goal)
	{
		transition
		{
			if (state_time > 200 && !theHeadJointRequest.moving)
			goto look_right_stop_at_goal;
			//else if (theGoalPercept.timeWhenGoalPostLastSeen == 0)
				//goto stop_left;
		}
			action
		{
			SetHeadPanTilt(0.f, 0.0f, 1.3f);
		/*head.mode = pan_tilt;
		head.pan = 85;//85
		head.tilt = 20;//40,30,24;
		head.speed = 100;*/
		}
	}

	state(look_right_stop_at_goal)
	{
		transition
		{
			if (state_time > 200 && !theHeadJointRequest.moving)
			goto look_left_stop_at_goal;
			//else if (theGoalPercept.timeWhenGoalPostLastSeen == 0)
				//goto stop_right;
		}
			action
		{
			SetHeadPanTilt(-2.1f, 0.0f, 1.3f);
		/*head.mode = pan_tilt;
		head.pan = -120;
		head.tilt = 20;
		head.speed = 100;*/
		}
	}

	state(stop_left)
	{
		transition
		{
			if (state_time > 1000)
			goto look_left;
		}
			action
		{
			SetHeadPanTilt(0.f, 0.0f, 0.8f);
		/*head.mode = pan_tilt;
		head.pan = goal.angle_to_last_seen;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}

	state(stop_right)
	{
		transition
		{
			if (state_time > 1000)
			goto look_right;
		}
			action
		{
			SetHeadPanTilt(-2.f, 0.0f, 0.8f);
		/*head.mode = pan_tilt;
		head.pan = goal.angle_to_last_seen;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}

	state(look_left)
	{
		transition
		{
			if (state_time > 200 && !theHeadJointRequest.moving)
			goto look_right_stop_at_goal;
		}
			action
		{
			SetHeadPanTilt(0.f, 0.0f, 0.8f);
		/*head.mode = pan_tilt;
		head.pan = 85;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}

	state(look_right)
	{
		transition
		{
			if (state_time > 200 && !theHeadJointRequest.moving)
			goto look_left_stop_at_goal;
		}
			action
		{
			SetHeadPanTilt(-1.5f, 0.0f, 0.8f);
		/*head.mode = pan_tilt;
		head.pan = -85;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}
}
