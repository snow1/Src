#pragma once
#include<iostream>
#include "Platform/BHAssert.h"
#include "Tools/Streams/AutoStreamable.h"
#include "Tools/Streams/Enum.h"
STREAMABLE(RoleTransformation,
{
	int number=-1,//number 取值范围为1-5 分别代表 守门员 两个前锋 和 后卫
	(int) theNearestRobotnum = -1,
	//int theNearestRobotnum;//存放到球最小距离的机器人的号码
});