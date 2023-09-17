/** Pun intended. Looks straight ahead in a way that the Nao V4's cameras cover the area in front of its feet as well as everything else in front of the robot.*/
option(LookUpAndDown)
{

  /** Simply sets the necessary angles */
  initial_state(lookForward)
  {
	  transition
	  {
		 if(action_done)
		 {
				goto raiseHead;
		 }  
	   }
       action
       {
         SetHeadPanTilt(0.f, -0.38f, 150_deg);
	   }
  }
  
  state(raiseHead)
  {
	  transition
	  {
		 if(action_done)
		 {
			goto lookForward;
	      }
	   }
	   action
	   {
		    SetHeadPanTilt(0.f, 0.19f, 150_deg);
		}
  }

}
