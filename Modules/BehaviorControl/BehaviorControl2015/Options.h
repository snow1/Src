/** All option files that belong to the current behavior have to be included by this file. */

#include "Options/Soccer.h"
#include "Options/GameControl/HandleGameState.h"
#include "Options/GameControl/HandlePenaltyState.h"
#include "Options/GameControl/PlayingState.h"
#include "Options/GameControl/ReadyState.h"

#include "Options/HeadControl/LookForward.h"

#include "Options/Output/ArmMotionRequest/PointAt.h"

#include "Options/Output/HeadMotionRequest/SetHeadPanTilt.h"

#include "Options/Output/MotionRequest/SpecialAction.h"
#include "Options/Output/MotionRequest/Stand.h"
#include "Options/Output/MotionRequest/WalkAtSpeedPercentage.h"
#include "Options/Output/MotionRequest/kick.h"
#include "Options/Output/MotionRequest/WalkToTarget.h"
#include "Options/Output/MotionRequest/InWalkKick.h"
#include "Options/Output/MotionRequest/PathToTarget.h"
#include "Options/Output/MotionRequest/GetUpEngine.h"

#include "Options/Output/PlaySound.h"
#include "Options/Output/PlaySamples.h"


#include "Options/Skills/GetUp.h"

#include "Options/Roles/Striker.h"

#include "Options/DemoOptions/Demo.h"
#include "Options/DemoOptions/Waving.h"

#include "Options/Tools/ButtonPressedAndReleased.h"

//*************************************************************

#include "Options/HeadControl/HeadControl.h"
#include "Options/HeadControl/LookUpAndDown.h"
#include "Options/HeadControl/LookLocalization.h"
#include "Options/HeadControl/LLookLocalization.h"
#include "Options/HeadControl/RLookLocalization.h"
#include "Options/HeadControl/LookAtBall.h"
#include "Options/HeadControl/SetLookLocalization.h"
#include "Options/Roles/Defender.h"
#include "Options/Roles/Keeper.h"
#include "Options/Roles/demoStriker.h"
#include "Options/Output/MotionRequest/WalkToFixedPosition.h"
#include "Options/Output/HeadMotionRequest/SetHeadTargetOnGround.h"



