void main()
{
    // 1. INIT ECONOMY FIRST (Ensures the Hive is ready before scripts touch it)
    Hive ce = CreateHive();
    if ( ce )
    {
        ce.InitOffline();
    }

    // 2. INIT WEATHER SAFELY (Only if GetGame() is ready)
    if ( GetGame() )
    {
        Weather weather = GetGame().GetWeather();
        if ( weather )
        {
            weather.MissionWeather(false);
        }
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
