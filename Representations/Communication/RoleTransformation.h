#pragma once
#include<iostream>
#include "Platform/BHAssert.h"
#include "Tools/Streams/AutoStreamable.h"
#include "Tools/Streams/Enum.h"
STREAMABLE(RoleTransformation,
{
	int number=-1,//number ȡֵ��ΧΪ1-5 �ֱ���� ����Ա ����ǰ�� �� ����
	(int) theNearestRobotnum = -1,
	//int theNearestRobotnum;//��ŵ�����С����Ļ����˵ĺ���
});