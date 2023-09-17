#include "Tools/Module/Module.h"
#include "Tools/Math/Eigen.h"
#include "Representations/Communication/TeammateData.h"
#include "Representations/Communication/RoleTransformation.h"
#include "Representations/Perception/BallPercepts/BallPercept.h"
#include "Representations/BehaviorControl/Role.h"
#include "Representations/Modeling/RobotPose.h"
#include <queue>
MODULE(RoleChoice,
{,
REQUIRES(TeammateData),
REQUIRES(RobotPose),
REQUIRES(BallPercept),
PROVIDES(RoleTransformation),
PROVIDES(TeammateRoles),
});

class RoleChoice : public RoleChoiceBase
{
public:
	int key=0;
	int rolenumber;// 在teammatedate中用于区分机器人的角色
	float min = 99999;//存放机器人到球最小距离
	int theNearestRobotnum;//存放到球最小距离的机器人的号码
	int penaltyedRobotnum=0;//记录判罚机器人的个数
	bool Ispenaltyednum[6];//判断哪个角色被判罚
	bool four;
	bool five;
	RoleChoice();
	void update(RoleTransformation& roleTransformation);
	void update(TeammateRoles& Roles);
	bool thenearest(float selftoball, RoleTransformation& roleTransformation);//求最近距离
	bool defenderTostriker(float selftoball, int robot2);
	bool strikerTodefender(int robot2);
	bool Ispenalty();//是否被判罚
	void treatmentPenalty(RoleTransformation& roleTransformation);//解决如果场上出现判罚的情况
	bool fieldRole();//判断场上是否有后卫
};

