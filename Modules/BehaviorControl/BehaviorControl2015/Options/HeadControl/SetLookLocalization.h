option(SetLookLocalization)
{
	initial_state(look_left)
	{
		transition
		{
			if (state_time > 500 && !theHeadJointRequest.moving)
				goto stop_left;
		}
			action
		{
			SetHeadPanTilt(0.5f, 0.0f, 0.9f);
		/*head.mode = pan_tilt;
		head.pan = 85;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}

	state(stop_left)
	{
		transition
		{
			if (state_time > 500)
			goto look_right;
		}
			action
		{
			SetHeadPanTilt(0.0f, 0.0f, 0.0f);
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
			if (state_time > 500)
			goto look_right;
		}
			action
		{
			SetHeadPanTilt(0.0f, 0.0f, 0.0f);
		/*head.mode = pan_tilt;
		head.pan = goal.angle_to_last_seen;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}



	state(look_right)
	{
		transition
		{
			if (state_time > 500 && !theHeadJointRequest.moving)
				goto stop_right;
		}
			action
		{
			SetHeadPanTilt(-0.5f, 0.0f, 0.9f);
		/*head.mode = pan_tilt;
		head.pan = -85;
		head.tilt = 30;
		head.speed = 100;*/
		}
	}
}
