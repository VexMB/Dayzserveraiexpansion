void main()
{
	// 1. INIT WEATHER (Required to prevent memory access violations during Hive init)
	Weather weather = GetGame().GetWeather();
	weather.MissionWeather(false);

	// 2. INIT ECONOMY
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	// 3. DATE RESET (September 20th, 2025)
	int year, month, day, hour, minute;
	int reset_month = 9;
	int reset_day = 20;
	
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	// Simplified check: If not September or October, or if too early/late in those months, reset.
	if (month != reset_month && month != (reset_month + 1))
	{
		GetGame().GetWorld().SetDate(2025, reset_month, reset_day, hour, minute);
	}
	else if (month == reset_month && day < reset_day)
	{
		GetGame().GetWorld().SetDate(2025, reset_month, reset_day, hour, minute);
	}
	else if (month == (reset_month + 1) && day > reset_day)
	{
		GetGame().GetWorld().SetDate(2025, reset_month, reset_day, hour, minute);
	}
}

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// Safely initialize Expansion systems
		if (GetGame().IsServer() && GetExpansionSettings()) 
		{
			Print("Expansion Settings Loaded Successfully");
		}
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		player.RemoveAllItems();
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
