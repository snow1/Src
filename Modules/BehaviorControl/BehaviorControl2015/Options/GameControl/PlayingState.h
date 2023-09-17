option(PlayingState)
{
  initial_state(Demo)
  {
    transition
    {
      //if(!libDemo.parameters.isDemoActive)
      //  goto selectAction;
    }
    action
    {
      Demo();
	  //Striker();
    }
  }
}
