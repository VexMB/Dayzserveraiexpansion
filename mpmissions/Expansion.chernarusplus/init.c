void main()
{
	// --- ECONOMY INITIALIZATION ---
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	// --- DATE AND TIME (DECEMBER 2025) ---
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

	if ( year < 2025 )
	{
		year = 2025;
		month = 12;
		day = 20;
		hour = 12;
		minute = 0;
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}


}

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);

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
	// FIXED: Removed (path) from the constructor call to fix the "too many parameters" error
	return new CustomMission(); 
}
