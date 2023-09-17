#include "RoleChoice.h"
#include"Representations/Communication/RoleTransformation.h"
#include "Representations/BehaviorControl/Role.h"

bool three;
MAKE_MODULE(RoleChoice, communication)
RoleChoice::RoleChoice()
{
}
void RoleChoice::update(RoleTransformation& roleTransformation)
{
	if (roleTransformation.number == -1)
		roleTransformation.number = Global::getSettings().playerNumber;
	rolenumber = roleTransformation.number;
	float selfx = theBallPercept.positionOnField.x() / 10;
	float selfy = theBallPercept.positionOnField.y() / 10;
	float selftoball = pow(pow(selfx, 2) + pow(selfy, 2), 0.5);
	/*if (Ispenalty())
	{
	treatmentPenalty(roleTransformation);
	}*/
	//OUTPUT(idText, text, "name1  " << roleTransformation.number);
	if (roleTransformation.number == 2 && (!thenearest(selftoball, roleTransformation)||!three)&&false)
	{
		//OUTPUT(idText, text, "aaaaaaa   ");	
		//OUTPUT(idText, text, "name1  " << Global::getSettings().playerNumber);
		// OUTPUT(idText, text, "rolenumber  " << rolenumber);
		if (true||fieldRole())
		{
			roleTransformation.number = 3;
			rolenumber = 3;	
			three = false;
		}
		else
		{
			//OUTPUT(idText, text, "4  " << four);
			//OUTPUT(idText, text, "5  " << five);
			//OUTPUT(idText, text, "key  " << key);
			roleTransformation.number = key;
			rolenumber = key;
		}
	}
	if (roleTransformation.number == 3&&false)
	{
		if (thenearest(selftoball, roleTransformation))
		{
			//OUTPUT(idText, text, "name2  " << Global::getSettings().playerNumber);
			roleTransformation.number = 2;
			rolenumber = 2;
			//OUTPUT(idText, text, "rolenumber  " << rolenumber);
		}
		else
		{
			if (fieldRole()&&false)
			{
				roleTransformation.number = key;
				rolenumber = key;
			}
		}
	}
	if (roleTransformation.number == 4 && thenearest(selftoball, roleTransformation) && (defenderTostriker(selftoball, 2) || defenderTostriker(selftoball, 3))&&false)
	{
		roleTransformation.number = 2;
		rolenumber = 2;
	}
	if (roleTransformation.number == 5 && thenearest(selftoball, roleTransformation) && (defenderTostriker(selftoball, 2) || defenderTostriker(selftoball, 3))&&false)
	{
		roleTransformation.number = 2;
		rolenumber = 2;
	}

	//roleTransformation.number = 2;	

}
bool RoleChoice::thenearest(float selftoball, RoleTransformation& roleTransformation)
{
	//验证得 TeammatesData中只存放队员的信息
	for (const Teammate& a : theTeammateData.teammates)
	{
		if (a.rolenumber == 3)
			three = true;
		float teammatetoball = pow(pow(a.ball.estimate.position.x() / 10, 2) + pow(a.ball.estimate.position.y() / 10, 2), 0.5);
		/*OUTPUT(idText, text, "name  " << Global::getSettings().playerNumber);
		OUTPUT(idText, text, "num   " << roleTransformation.number);
		OUTPUT(idText, text, "selftoball   " << selftoball);
		OUTPUT(idText, text, "teammatetoball   "<< teammatetoball);*/
		if (min > teammatetoball&&teammatetoball != 0)
		{
			min = teammatetoball;
			roleTransformation.theNearestRobotnum = a.rolenumber;
		}
	}
	//OUTPUT(idText, text, "num  " << roleTransformation.number);
	//OUTPUT(idText, text, "theNearestRobotnum  " << theNearestRobotnum);
	//OUTPUT(idText, text, "mmmmmmmmmmmm   "<<min);
	if (selftoball < min)
	{
		/*OUTPUT(idText, text, "name1  " << Global::getSettings().playerNumber);
		OUTPUT(idText, text, "111  "<<theNearestRobotnum);*/
		roleTransformation.theNearestRobotnum = rolenumber;
		min = 99999;
		//OUTPUT(idText, text, "theNearestRobotnums   " << theNearestRobotnum);
		return true;
	}
	else
	{
		/*OUTPUT(idText, text, "name2  " << Global::getSettings().playerNumber);
		OUTPUT(idText, text, "222  " << theNearestRobotnum);*/
		//OUTPUT(idText, text, "theNearestRobotnum   " << theNearestRobotnum);
		min = 99999;
		return false;

	}
}
bool RoleChoice::defenderTostriker(float selftoball, int robot2)
{
	float selfx = theRobotPose.translation.x();
	float selfy = theRobotPose.translation.y();
	bool b=false;
	for (const Teammate& a : theTeammateData.teammates)
	{
		if (a.rolenumber == 2)
			b = true;
	}
	if(!b)
		return true;
	for (const Teammate& a : theTeammateData.teammates)
	{
		if (a.rolenumber == robot2)
		{
			float robot2x = a.pose.translation.x();
			float robot2y = a.pose.translation.y();
			float twoRobotdistance = pow(pow((selfx - robot2x) / 10, 2) + pow((selfy - robot2y) / 10, 2), 0.5);
			if (selftoball > twoRobotdistance)
				return true;
			else
				return false;
		}
	}
}
bool RoleChoice::strikerTodefender(int robot2)
{
	float selfx = theRobotPose.translation.x();
	float selfy = theRobotPose.translation.y();
	float twoRobotdistance;
	float minn = 99999;
	if (robot2 == 4)
		twoRobotdistance = pow(pow((selfx - (-2608)) / 10, 2) + pow((selfy - (-754)) / 10, 2), 0.5);
	if (robot2 == 5)
		twoRobotdistance = pow(pow((selfx - (-2608)) / 10, 2) + pow((selfy - 754) / 10, 2), 0.5);
	for (const Teammate& a : theTeammateData.teammates)
	{
		float teammatetoball = pow(pow(a.ball.estimate.position.x() / 10, 2) + pow(a.ball.estimate.position.y() / 10, 2), 0.5);
		if (minn > teammatetoball&&teammatetoball != 0)
			minn = teammatetoball;
	}
	if (twoRobotdistance<minn)
		return true;
	else
		return false;
	/*for (const Teammate& a : theTeammateData.teammates)
	{
	if (a.role.rolenumber == robot2)
	{
	float robot2x = a.pose.translation.x();
	float robot2y = a.pose.translation.y();
	float robot2toball= pow(pow(a.ball.estimate.position.x() / 10, 2) + pow(a.ball.estimate.position.y() / 10, 2), 0.5);
	float twoRobotdistance = pow(pow((selfx - robot2x) / 10, 2) + pow((selfy - robot2y) / 10, 2), 0.5);
	if (robot2toball > twoRobotdistance)
	return true;
	else
	return false;
	}
	}*/
}
bool RoleChoice::Ispenalty()
{
	for (const Teammate& a : theTeammateData.teammates)
	{
		if (a.isPenalized)
		{
			Ispenaltyednum[a.teammateRoles.rolenumber] = true;
			penaltyedRobotnum++;
		}
		else
		Ispenaltyednum[a.teammateRoles.rolenumber] = false;
	}
	for (int i = 1; i < 6; i++)
		if (Ispenaltyednum[i])
			return true;
	return false;
}
void RoleChoice::treatmentPenalty(RoleTransformation& roleTransformation)
{
	switch (penaltyedRobotnum)
	{
	case 1:if (Ispenaltyednum[4] || Ispenaltyednum[5])//defender 被判罚
	{
		//扩大在场地上的后卫的活动范围
	}break;
	case 2:if (Ispenaltyednum[2] && Ispenaltyednum[3])
	{
		if (roleTransformation.number == 4)
			roleTransformation.number = 2;
	}
		   if (Ispenaltyednum[4] && Ispenaltyednum[5])
		   {
			   if (roleTransformation.number == 3)
				   roleTransformation.number = 4;
		   }break;
	}
}
bool RoleChoice::fieldRole()
{
	//OUTPUT(idText, text, "bbbb  ");
	for (const Teammate& a : theTeammateData.teammates)
	{
		//OUTPUT(idText, text, "aaaa  "<< a.role.rolenumber);
		if (a.rolenumber == 4)
		{
			//OUTPUT(idText, text, "111  ");
			four = true;
		}
		if (a.rolenumber == 5)
		{ 
			//OUTPUT(idText, text, "222  ");
			five = true;
		}
	}
	if (!four)
	{
		//OUTPUT(idText, text, "aaa  ");
		key = 4;
		return false;
	}
	else
	{
		if (!five)
		{
			//OUTPUT(idText, text, "ccc  ");
			key = 5;
			return false;
		}
		else
		{
			//OUTPUT(idText, text, "ddd  ");
			five = false;
			four = false;
			return true;
		}
	}
}
void RoleChoice::update(TeammateRoles& Roles)
{
	//RoleType roleType;
	if (rolenumber == 1)
	{
		//Roles.role = Role::RoleType::keeper;
		Roles.rolenumber = 1;
		Roles.rolenumbers = Global::getSettings().playerNumber;
	}
	if (rolenumber == 2)
	{
		//Roles.role = Role::RoleType::striker;
		Roles.rolenumber = 2;
		Roles.rolenumbers = Global::getSettings().playerNumber;
	}
	if (rolenumber == 3)
	{
		//Roles.role = Role::RoleType::supporter;
		Roles.rolenumber = 3;
		Roles.rolenumbers = Global::getSettings().playerNumber;
	}
	if (rolenumber == 4)
	{
		//Roles.role = Role::RoleType::defender;
		Roles.rolenumber = 4;
		Roles.rolenumbers = Global::getSettings().playerNumber;
	}
	if (rolenumber == 5)
	{
		//Roles.role = Role::RoleType::defender;
		Roles.rolenumber = 5;
		Roles.rolenumbers = Global::getSettings().playerNumber;
	}
}