void main()
{
	// ONLY the Hive/Economy should be here. 
	// Do NOT put Expansion checks or Date logic in main().
	Hive ce = CreateHive();
	if (ce)
		ce.InitOffline();
}

class CustomMission: MissionServer
{
	// Note: We use the inherited m_player; do not redeclare it.

	override void OnInit()
	{
		// 1. Initialize core systems
		super.OnInit();
		
		// 2. Safely run Expansion logic here
		if (GetGame().IsServer() && GetExpansionSettings()) 
		{
			Print("Expansion Settings Loaded Successfully");
		}

		// 3. Set Date (December 2025)
		int year, month, day, hour, minute;
		GetGame().GetWorld().GetDate(year, month, day, hour, minute);
		
		if (year < 2025)
		{
			year = 2025; month = 12; day = 20;
			hour = 12; minute = 0;
			GetGame().GetWorld().SetDate(year, month, day, hour, minute);
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);

		if (m_player)
			GetGame().SelectPlayer(identity, m_player);

		return m_player;
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
