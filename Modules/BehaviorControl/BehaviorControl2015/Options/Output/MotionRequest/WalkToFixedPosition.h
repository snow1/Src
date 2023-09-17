/** Walk to a \c target in the filed at a \c speed
 *  @param speed Walking speeds, in percentage.
 *  @param target Walking target, in mm and radians, relative to the field.
 */
option(WalkToFixedPosition, (const Pose2f&) speed, (const Pose2f&) target)
{
    initial_state(start)
    {
        transition
        {
            Pose2f relativeToRobot = target - theRobotPose;
            if(std::abs(relativeToRobot.rotation) < 5_deg && std::abs(relativeToRobot.translation.x()) < 50.f && std::abs(relativeToRobot.translation.y()) < 10.f)
                goto finish;
        }
        action
        {
            theHeadControlMode = HeadControl::lookForward;
            Pose2f relativeToRobot = target - theRobotPose;
            WalkToTarget(speed, relativeToRobot); //pose2D rotation, translation.x, translation.y 
        }
    }

    state(finish)
    {       
        action
        {
            Stand();
        }
    }
};