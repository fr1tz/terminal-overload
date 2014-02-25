// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
// Deafness

function hearingSetDeafness(%deafness)
{
   $Hearing::Deafness::Deafness = %deafness;
   hearingDeafnessThread();
}

function hearingSetDeafnessDt(%dt)
{
   $Hearing::Deafness::DeafnessDt = %dt;
   hearingDeafnessThread();
}

function hearingDeafnessThread()
{
   if($Hearing::Deafness::Thread !$= "")
   {
      cancel($Hearing::Deafness::Thread);
      $Hearing::Deafness::Thread = "";
   }
   $Hearing::Deafness::Thread = schedule(32, 0, "hearingDeafnessThread");

   if($Hearing::Deafness::Deafness $= "")
      $Hearing::Deafness::Deafness = 0;
   $Hearing::Deafness::Deafness += $Hearing::Deafness::DeafnessDt;
   if($Hearing::Deafness::Deafness > 1)
      $Hearing::Deafness::Deafness = 1;
   else if($Hearing::Deafness::Deafness < 0)
      $Hearing::Deafness::Deafness = 0;
   sfxSetChannelVolume(2, $Pref::SFX::channelVolume2*(1-$Hearing::Deafness::Deafness));
}

//------------------------------------------------------------------------------
// Tinnitus

function hearingSetTinnitusEnabled(%enabled)
{
   $Hearing::Tinnitus::Enabled = %enabled;
   hearingTinnitusThread();
}

function hearingSetTinnitusVolume(%vol)
{
   $Hearing::Tinnitus::Volume = %vol;
   hearingTinnitusThread();
}

function hearingSetTinnitusVolumeDt(%dt)
{
   $Hearing::Tinnitus::VolumeDt = %dt;
   hearingTinnitusThread();
}

function hearingTinnitusThread()
{
   if($Hearing::Tinnitus::Thread !$= "")
   {
      cancel($Hearing::Tinnitus::Thread);
      $Hearing::Tinnitus::Thread = "";
   }
   $Hearing::Tinnitus::Thread = schedule(32, 0, "hearingTinnitusThread");
   
   if($Hearing::Tinnitus::Enabled)
   {
      if($Hearing::Tinnitus::Source $= "")
      {
         $Hearing::Tinnitus::Source = sfxCreateSource(
            AudioGuiLoop2D,
            "content/xa/alux1/sounds/tinnitus.wav"
         );
      }
      
      if(!$Hearing::Tinnitus::Source.isPlaying())
         $Hearing::Tinnitus::Source.play();
         
      if($Hearing::Tinnitus::Volume $= "")
         $Hearing::Tinnitus::Volume = 1;
      $Hearing::Tinnitus::Volume += $Hearing::Tinnitus::VolumeDt;
      $Hearing::Tinnitus::Source.setVolume($Hearing::Tinnitus::Volume);
   }
   else
   {
      if($Hearing::Tinnitus::Source !$= "")
      {
         if($Hearing::Tinnitus::Source.isPlaying())
            $Hearing::Tinnitus::Source.stop();
      }
   }
}
