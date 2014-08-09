// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

exec("core/scripts/server/defaults.cs");

// Game information used to query the master server
$Client::GameTypeQuery = $appName;
$Client::MissionTypeQuery = "Any";

function print_attrib(%attrib, %val)
{
	echo($prefix SPC %attrib SPC strreplace(%val, "\n", " "));
}

function printServers()
{
	%sc = getServerCount();
	for (%i = 0; %i < %sc; %i++) {
		setServerInfo(%i);
		$prefix = "#server" SPC $ServerInfo::Address;
		print_attrib("name", $ServerInfo::Name);
		print_attrib("type", $ServerInfo::MissionType);
		print_attrib("map", $ServerInfo::MissionName);
		print_attrib("ping", $ServerInfo::Ping);
		print_attrib("players", $ServerInfo::PlayerCount @ " of " @ $ServerInfo::MaxPlayers);
		for(%l = 0; %l < getRecordCount($ServerInfo::Info); %l++)
			print_attrib("info", getRecord($ServerInfo::Info, %l));
	}
}

function queryServers()
{
	if($lan)
	{
		queryLANServers(
			28000,		// lanPort for local queries
			0,			 // Query flags
			$Client::GameTypeQuery,		 // gameTypes
			$Client::MissionTypeQuery,	 // missionType
			0,			 // minPlayers
			100,		  // maxPlayers
			0,			 // maxBots
			2,			 // regionMask
			0,			 // maxPing
			100,		  // minCPU
			0			  // filterFlags
		);
	}
	else
	{
		queryMasterServer(
			0,			 // Query flags
			$Client::GameTypeQuery,		 // gameTypes
			$Client::MissionTypeQuery,	 // missionType
			0,			 // minPlayers
			100,		  // maxPlayers
			0,			 // maxBots
			2,			 // regionMask
			0,			 // maxPing
			100,		  // minCPU
			0			  // filterFlags
		);
	}
}

function onServerQueryStatus(%status, %msg, %value)
{
    if(%status $= "done")
    {
        printServers();
        quit();
    }
}

package ServerList {

function displayHelp() {
	Parent::displayHelp();
	error(
		"Serverlist Mod options:\n"@
		"  -lan                Query lan servers\n"
	);
}

function parseArgs()
{
	Parent::parseArgs();

	$lan = false;

	for (%i = 1; %i < $Game::argc ; %i++)
	{
		%arg = $Game::argv[%i];
		%nextArg = $Game::argv[%i+1];
		%hasNextArg = $Game::argc - %i > 1;
	
		switch$ (%arg)
		{
			case "-lan":
				$lan = true;
		}
	}
}

function onStart()
{
    enableWinConsole(true);
    setNetPort(0);
    schedule(0, 0, queryServers);
}

function onExit()
{

}

}; // Client package

activatePackage(ServerList);
