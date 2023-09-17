/**
* @file LibCodeRelease.cpp
*/

#include "../LibraryBase.h"

namespace Behavior2015
{
  #include "LibCodeRelease.h"
  
  LibCodeRelease::LibCodeRelease():
    angleToGoal(0.f)
  {}
  
  void LibCodeRelease::preProcess()
  {
    angleToGoal = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, 0.f)).angle();
	angleToGoalkeeper = (theRobotPose.inversePose * Vector2f(0.f, 0.f)).angle();
	angleToGoaldefender= (theRobotPose.inversePose * Vector2f(2000.f, 0.f)).angle();
	angleToGoalstriker = (theRobotPose.inversePose * Vector2f(4500.f, 0.f)).angle();
  }

  void LibCodeRelease::postProcess()
  {
  }
  
  int LibCodeRelease::timeSinceBallWasSeen()
  {
    return theFrameInfo.getTimeSince(theBallModel.timeWhenLastSeen);
  }
  
  bool LibCodeRelease::between(float value, float min, float max)
  {
    return value >= min && value <= max;
  } 
  float LibCodeRelease::ballPositionCal()
  {
	  return (std::sqrt(theBallModel.estimate.position.x()*theBallModel.estimate.position.x() + theBallModel.estimate.position.y()*theBallModel.estimate.position.y()));
  }
}