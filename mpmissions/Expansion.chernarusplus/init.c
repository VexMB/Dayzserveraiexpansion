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

		// SAFE DATE RESET (Moved from main)
		int year, month, day, hour, minute;
		int reset_month = 9;
		int reset_day = 20;
		
		World world = GetGame().GetWorld();
		if (world)
		{
			world.GetDate(year, month, day, hour, minute);
			if (month != reset_month)
			{
				world.SetDate(2025, reset_month, reset_day, hour, minute);
			}
		}
	}
    // ... rest of your code
};


Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
