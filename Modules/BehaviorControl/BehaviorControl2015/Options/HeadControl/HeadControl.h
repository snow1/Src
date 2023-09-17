option(HeadControl)
{
  common_transition
  {
    if(!theGroundContactState.contact && theGameInfo.state != STATE_INITIAL)
      goto lookForward;

    switch(theHeadControlMode)
    {
      case HeadControl::off: goto off;
      case HeadControl::lookForward: goto lookForward;
	  case HeadControl::lookUpAndDown: goto lookUpAndDown;
	  case HeadControl::lookLocalization:goto lookLocalization;
	  case HeadControl::llookLocalization:goto llookLocalization;
	  case HeadControl::rlookLocalization:goto rlookLocalization;
	  case HeadControl::LookAtBall:goto LookAtBall;
	  case HeadControl::setLookLocalization:goto SetLookLocalization;
      default: goto none;
    }
  }

  initial_state(none) {}
  state(off) {action SetHeadPanTilt(JointAngles::off, JointAngles::off, 0.f);}
  state(lookForward) {action LookForward();}
  state(lookUpAndDown) {action LookUpAndDown();}
  state(lookLocalization) {action LookLocalization();}
  state(llookLocalization) { action LLookLocalization(); }
  state(rlookLocalization) { action RLookLocalization(); }
  state(LookAtBall) { action LookAtBall(); }
  state(SetLookLocalization) { action SetLookLocalization();}
}

struct HeadControl
{
  ENUM(Mode,
  {,
    none,
    off,
    lookForward,
	lookUpAndDown,
	lookLocalization,
	llookLocalization,
	rlookLocalization,
	LookAtBall,
	setLookLocalization,
  });
};

HeadControl::Mode theHeadControlMode;
//HeadControl::Mode theHeadControlMode = HeadControl::Mode::none; /**< The head control mode executed by the option HeadControl. */
