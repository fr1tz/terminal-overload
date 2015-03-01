// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

package NotcHitSound
{
   function clientCmdGameStart(%seq)
   {
      //echo("clientCmdGameStart(): NotcHitSound");
      Parent::clientCmdGameStart(%seq);
      $NotcHitSound::Source[1] = sfxCreateSource(
         AudioGui,
         "content/xa/notc/core/sounds/healthhit1.wav"
      );
      $NotcHitSound::Source[2] = sfxCreateSource(
         AudioGui,
         "content/xa/notc/core/sounds/shieldhit1.wav"
      );
      $NotcHitSound::Source[3] = sfxCreateSource(
         AudioGui,
         "content/xa/notc/core/sounds/test1.wav"
      );
      $NotcHitSound::Source[4] = sfxCreateSource(
         AudioGui,
         "content/xa/notc/core/sounds/test2.wav"
      );
   }

   function clientCmdGameEnd()
   {
      //echo("clientCmdGameEnd(): NotcHitSound");
      Parent::clientCmdGameEnd();
      for(%i = 1; %i <= 4; %i++)
         if(isObject($NotcHitSound::Source[%i]))
            $NotcHitSound::Source[%i].delete();
   }
};

activatePackage(NotcHitSound);

function clientCmdPlayHitSound(%number, %volume, %pitch)
{
   //echo("clientCmdPlayHitSound(): number =" SPC %number SPC
   //   "volume =" SPC %volume SPC "pitch =" SPC %pitch);

   if(!isObject($NotcHitSound::Source[%number]))
      return;
      
   $NotcHitSound::Source[%number].stop();
   $NotcHitSound::Source[%number].setVolume(%volume);
   $NotcHitSound::Source[%number].setPitch(%pitch);
   $NotcHitSound::Source[%number].play();
}

