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
	int rolenumber;// ��teammatedate���������ֻ����˵Ľ�ɫ
	float min = 99999;//��Ż����˵�����С����
	int theNearestRobotnum;//��ŵ�����С����Ļ����˵ĺ���
	int penaltyedRobotnum=0;//��¼�з������˵ĸ���
	bool Ispenaltyednum[6];//�ж��ĸ���ɫ���з�
	bool four;
	bool five;
	RoleChoice();
	void update(RoleTransformation& roleTransformation);
	void update(TeammateRoles& Roles);
	bool thenearest(float selftoball, RoleTransformation& roleTransformation);//���������
	bool defenderTostriker(float selftoball, int robot2);
	bool strikerTodefender(int robot2);
	bool Ispenalty();//�Ƿ��з�
	void treatmentPenalty(RoleTransformation& roleTransformation);//���������ϳ����з������
	bool fieldRole();//�жϳ����Ƿ��к���
};

