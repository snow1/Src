option(Demo)
{
  common_transition
  {
    switch(libDemo.demoGameState)
      {
      case LibDemo::wavingPlinking:
        goto waving;
      case LibDemo::normal:
        goto normal;
      default:
        ASSERT(false);
        break;
    }
  }

  initial_state(normal)
  {
	  action
	  {
		  if (Global::getSettings().playerNumber == 6)
		  demoStriker();
		if (theRoleTransformation.number == 1)
		Keeper();
	if (theRoleTransformation.number == 2 || theRoleTransformation.number == 3)
		Striker();
	if (theRoleTransformation.number == 4 || theRoleTransformation.number == 5)
		Defender();
    }
  }

  state(waving)
  {
    action
    {
      LookForward();
      Waving();
    }
  }
}
