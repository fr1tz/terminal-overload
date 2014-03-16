// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$AudioTestHandle = 0;
// Description to use for playing the volume test sound.  This isn't
// played with the description of the channel that has its volume changed
// because we know nothing about the playback state of the channel.  If it
// is paused or stopped, the test sound would not play then.
$AudioTestDescription = new SFXDescription()
{
   sourceGroup = AudioChannelMaster;
};

function OptAudioGui::onWake(%this)
{
   //echo("OptAudioGui::onWake()");
   
   if($InGuiEditor)
      return;

   // Audio
   //OptAudioHardwareToggle.setStateOn($pref::SFX::useHardware);
   //OptAudioHardwareToggle.setActive( true );

   %this-->OptAudioVolumeMaster.setValue( $pref::SFX::masterVolume );
   %this-->OptAudioVolumeShell.setValue( $pref::SFX::channelVolume[ $GuiAudioType] );
   %this-->OptAudioVolumeSim.setValue( $pref::SFX::channelVolume[ $SimAudioType ] );
   %this-->OptAudioVolumeMusic.setValue( $pref::SFX::channelVolume[ $MusicAudioType ] );

   OptAudioProviderList.clear();
   %buffer = sfxGetAvailableDevices();
   %count = getRecordCount( %buffer );
   for(%i = 0; %i < %count; %i++)
   {
      %record = getRecord(%buffer, %i);
      %provider = getField(%record, 0);

      if ( OptAudioProviderList.findText( %provider ) == -1 )
            OptAudioProviderList.add( %provider, %i );
   }

   OptAudioProviderList.sort();

   %selId = OptAudioProviderList.findText($pref::SFX::provider);
	if ( %selId == -1 )
		OptAudioProviderList.setFirstSelected();
   else
	   OptAudioProviderList.setSelected( %selId );
}

function OptAudioUpdateMasterVolume( %volume )
{
   if( %volume == $pref::SFX::masterVolume )
      return;

   sfxSetMasterVolume( %volume );
   $pref::SFX::masterVolume = %volume;

   if( !isObject( $AudioTestHandle ) )
      $AudioTestHandle = sfxPlayOnce( AudioChannel, "content/xa/torque3d/3.0/sound/ui/volumeTest.wav" );
}

function OptAudioUpdateChannelVolume( %description, %volume )
{
   %channel = sfxGroupToOldChannel( %description.sourceGroup );

   if( %volume == $pref::SFX::channelVolume[ %channel ] )
      return;

   sfxSetChannelVolume( %channel, %volume );
   $pref::SFX::channelVolume[ %channel ] = %volume;

   if( !isObject( $AudioTestHandle ) )
   {
      $AudioTestDescription.volume = %volume;
      $AudioTestHandle = sfxPlayOnce( $AudioTestDescription, "content/xa/torque3d/3.0/sound/ui/volumeTest.wav" );
   }
}

function OptAudioProviderList::onSelect( %this, %id, %text )
{
   // Skip empty provider selections.
   if ( %text $= "" )
      return;

   $pref::SFX::provider = %text;
   OptAudioDeviceList.clear();

   %buffer = sfxGetAvailableDevices();
   %count = getRecordCount( %buffer );
   for(%i = 0; %i < %count; %i++)
   {
      %record = getRecord(%buffer, %i);
      %provider = getField(%record, 0);
      %device = getField(%record, 1);

      if (%provider !$= %text)
         continue;

       if ( OptAudioDeviceList.findText( %device ) == -1 )
            OptAudioDeviceList.add( %device, %i );
   }

   // Find the previous selected device.
   %selId = OptAudioDeviceList.findText($pref::SFX::device);
   if ( %selId == -1 )
      OptAudioDeviceList.setFirstSelected();
   else
   OptAudioDeviceList.setSelected( %selId );
}

function OptAudioDeviceList::onSelect( %this, %id, %text )
{
   // Skip empty selections.
   if ( %text $= "" )
      return;

   $pref::SFX::device = %text;

   if ( !sfxCreateDevice(  $pref::SFX::provider,
                           $pref::SFX::device,
                           $pref::SFX::useHardware,
                           -1 ) )
      error( "Unable to create SFX device: " @ $pref::SFX::provider
                                             SPC $pref::SFX::device
                                             SPC $pref::SFX::useHardware );
}

/*
function OptAudioHardwareToggle::onClick(%this)
{
   if (!sfxCreateDevice($pref::SFX::provider, $pref::SFX::device, $pref::SFX::useHardware, -1))
      error("Unable to create SFX device: " @ $pref::SFX::provider SPC $pref::SFX::device SPC $pref::SFX::useHardware);
}
*/

