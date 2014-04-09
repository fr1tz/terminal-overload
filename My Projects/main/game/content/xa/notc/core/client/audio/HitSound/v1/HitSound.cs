// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

package XaNotcHitSound
{
   function clientCmdGameStart(%seq)
   {
      echo("clientCmdGameStart(): XaNotcHitSound");
      Parent::clientCmdGameStart(%seq);
      $XaNotcHitSound::Source1 = sfxCreateSource(
         AudioGui,
         "content/xa/rotc/p.5.4/sounds/rotc/damage1.wav"
      );
   }


   function clientCmdGameEnd()
   {
      Parent::clientCmdGameEnd();
      if(isObject($XaNotcHitSound::Source1))
         $XaNotcHitSound::Source1.delete();
   }
};

activatePackage(XaNotcHitSound);

function clientCmdPlayHitSound(%pitch)
{
   echo("clientCmdPlayHitSound(): pitch =" SPC %pitch);

   if(!isObject($XaNotcHitSound::Source1))
      return;
      
   $XaNotcHitSound::Source1.setPitch(%pitch);
   $XaNotcHitSound::Source1.play();
}

