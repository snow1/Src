#include "getpoint.h"
#include"Representations/Communication/getpoint.h"


MAKE_MODULE(GetPoint, communication)
GetPoint::GetPoint()
{
}
void GetPoint::update(GetPoints& Getpoint)
{

	//Getpoint.keeperNeedpoint=Vector2f(static_cast<float>(1000), static_cast<float>(0));
	//Getpoint.keeperNeedpointa = Vector2f(static_cast<float>(1000), static_cast<float>(0));
	//Getpoint.oneNeedpoint = Vector2f(static_cast<float>(2), static_cast<float>(2));
	//Getpoint.fiveNeedpoint = Vector2f(static_cast<float>(3), static_cast<float>(3));
	for (float y = 750; y >= (0 - 750); y -= 15)
		getkeeperpoint(Getpoint, y);
	for (float y = 2000; y >= (0 - 2000); y -= 30)
		getdefenderpoint(Getpoint, y);
}
void GetPoint::getkeeperpoint(GetPoints& Getpoint, float y)
{

	//if (y>0)
	//OUTPUT(idText, text, "y  " << y);
	if (theTeamBallModel.position.x() < -4000 && theTeamBallModel.position.y() > 750)
	{
		Getpoint.oneNeedpoint = Vector2f(static_cast<float>(-4200), static_cast<float>(750));
	}
	else
	{
		if (theTeamBallModel.position.x() < -4000 && theTeamBallModel.position.y() < -750)
			Getpoint.oneNeedpoint = Vector2f(static_cast<float>(-4200), static_cast<float>(-750));
		else
		{
			if (((int)theTeamBallModel.position.y() - y) != 0)
			{
				ballTopointk = (theTeamBallModel.position.x() + 4000) / (theTeamBallModel.position.y() - y);
				//OUTPUT(idText, text, "ballTopointk  " << ballTopointk);
				//OUTPUT(idText, text, "y  " << y);
			}
			else
			{
				ballTopointk = 0;
				//OUTPUT(idText, text, "ballTopointk0  " << ballTopointk);
			}
			if (y != 0)
			{
				pointTokeeperk = (float)(-4000 + 4400) / y;
				//OUTPUT(idText, text, "pointTokeeperk  " << pointTokeeperk);
			}
			else
			{
				pointTokeeperk = 0;
				//OUTPUT(idText, text, "pointTokeeperk0  " << pointTokeeperk);
			}
			if ((ballTopointk == 0 && pointTokeeperk == 0) || (ballTopointk / pointTokeeperk) <= 1.1 && (ballTopointk / pointTokeeperk) >= 0.9)
			{
				//OUTPUT(idText, text, "ballTopointk  " << ballTopointk);
				//OUTPUT(idText, text, "pointTokeeperk  " << pointTokeeperk);
				Getpoint.oneNeedpoint = Vector2f(static_cast<float>(-4000), static_cast<float>(y));
				//OUTPUT(idText, text, "aaaaaaaaaaaaaaa  "<<y);
			}
		}
	}
}
void GetPoint::getdefenderpoint(GetPoints& Getpoint, float y)
{

	//if (y>0)
	//OUTPUT(idText, text, "y  " << y);
	if (theTeamBallModel.position.x() < -4000)
	{
		Getpoint.fourNeedpoint = Vector2f(static_cast<float>(-2000), static_cast<float>(1100));
		Getpoint.fiveNeedpoint = Vector2f(static_cast<float>(-2000), static_cast<float>(-1100));
	}
	else
	{
		if (((int)theTeamBallModel.position.y() - y) != 0)
		{
			ballTopointk = (theTeamBallModel.position.x() + 2000) / (theTeamBallModel.position.y() - y);
			//OUTPUT(idText, text, "ballTopointk  " << ballTopointk);
			//OUTPUT(idText, text, "y  " << y);
		}
		else
		{
			ballTopointk = 0;
			//OUTPUT(idText, text, "ballTopointk0  " << ballTopointk);
		}
		if (y != 400 || y != (-400))
		{
			fourpointTokeeperk = (float)(-2000 + 4400) / (y - 400);
			fivepointTokeeperk = (float)(-2000 + 4400) / (y + 400);
			//OUTPUT(idText, text, "pointTokeeperk  " << pointTokeeperk);
		}
		else
		{
			fourpointTokeeperk = 0;
			fivepointTokeeperk = 0;
			//OUTPUT(idText, text, "pointTokeeperk0  " << pointTokeeperk);
		}
		if ((ballTopointk == 0 && fourpointTokeeperk == 0) || ((fourpointTokeeperk != 0) && (ballTopointk / fourpointTokeeperk) <= 1.1 && (ballTopointk / fourpointTokeeperk) >= 0.8))
		{
			//OUTPUT(idText, text, "ballTopointk  " << ballTopointk);
			//OUTPUT(idText, text, "pointTokeeperk  " << pointTokeeperk);
			Getpoint.fourNeedpoint = Vector2f(static_cast<float>(-2000), static_cast<float>(y));
			//OUTPUT(idText, text, "aaaaaaaaaaaaaaa  " << y);
		}
		if ((ballTopointk == 0 && fivepointTokeeperk == 0) || ((fivepointTokeeperk!=0)&&(ballTopointk / fivepointTokeeperk) <= 1.1 && (ballTopointk / fivepointTokeeperk) >= 0.8))
		{
			//OUTPUT(idText, text, "ballTopointk  " << ballTopointk);
			//OUTPUT(idText, text, "pointTokeeperk  " << pointTokeeperk);
			Getpoint.fiveNeedpoint = Vector2f(static_cast<float>(-2000), static_cast<float>(y));
			//OUTPUT(idText, text, "aaaaaaaaaaaaaaa  " << y);
		}
	}

}