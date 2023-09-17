#include "Tools/Module/Module.h"
#include "Tools/Math/Eigen.h"
#include "Representations/Communication/TeammateData.h"
#include "Representations/Communication/getpoint.h"
#include "Representations/Modeling/TeamBallModel.h"
#include "Representations/Perception/BallPercepts/BallPercept.h"
#include "Representations/BehaviorControl/Role.h"
#include "Representations/Modeling/RobotPose.h"
#include <queue>
MODULE(GetPoint,
{ ,
REQUIRES(TeammateData),
REQUIRES(RobotPose),
REQUIRES(BallPercept),
REQUIRES(TeamBallModel),
PROVIDES(GetPoints),
});

class GetPoint : public GetPointBase
{
public:
	float ballTopointk;
	float pointTokeeperk;
	float fourpointTokeeperk;
	float fivepointTokeeperk;
	//float y;
	GetPoint();
	void update(GetPoints& Getpoints);
	void getkeeperpoint(GetPoints& Getpoints, float y);
	void getdefenderpoint(GetPoints& Getpoints, float y);
};

