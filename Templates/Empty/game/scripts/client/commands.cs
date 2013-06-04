// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//----------------------------------------------------------------------------
// Game start / end events sent from the server
//----------------------------------------------------------------------------

function clientCmdGameEnd(%seq)
{
   // Stop local activity... the game will be destroyed on the server
   sfxStopAll();
}
