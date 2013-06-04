// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Some state presets.


/// Return the first active SFXState in the given SimSet/SimGroup.
function sfxGetActiveStateInGroup( %group )
{
   %count = %group.getCount();
   for( %i = 0; %i < %count; %i ++ )
   {
      %obj = %group.getObject( %i );
      if( !%obj.isMemberOfClass( "SFXState" ) )
         continue;
         
      if( %obj.isActive() )
         return %obj;
   }
   
   return 0;
}


//-----------------------------------------------------------------------------
// Special audio state that will always and only be active when no other
// state is active.  Useful for letting slots apply specifically when no
// other slot in a list applies.

singleton SFXState( AudioStateNone ) {};

AudioStateNone.activate();

function SFXState::onActivate( %this )
{
   if( %this.getId() != AudioStateNone.getId() )
      AudioStateNone.disable();
}

function SFXState::onDeactivate( %this )
{
   if( %this.getId() != AudioStateNone.getId() )
      AudioStateNone.enable();
}

//-----------------------------------------------------------------------------
// AudioStateExclusive class.
//
// Automatically deactivates sibling SFXStates in its parent SimGroup
// when activated.

function AudioStateExclusive::onActivate( %this )
{
   Parent::onActivate( %this );
   
   %group = %this.parentGroup;
   %count = %group.getCount();
   
   for( %i = 0; %i < %count; %i ++ )
   {
      %obj = %group.getObject( %i );

      if( %obj != %this && %obj.isMemberOfClass( "SFXState" ) && %obj.isActive() )
         %obj.deactivate();
   }
}

//-----------------------------------------------------------------------------
// Location-dependent states.

singleton SimGroup( AudioLocation );

/// State when the listener is outside.
singleton SFXState( AudioLocationOutside )
{
   parentGroup = AudioLocation;
   className = "AudioStateExclusive";
};

/// State when the listener is submerged.
singleton SFXState( AudioLocationUnderwater )
{
   parentGroup = AudioLocation;
   className = "AudioStateExclusive";
};

/// State when the listener is indoors.
singleton SFXState( AudioLocationInside )
{
   parentGroup = AudioLocation;
   className = "AudioStateExclusive";
};

/// Return the currently active SFXState in AudioLocation.
function sfxGetLocation()
{
   return sfxGetActiveStateInGroup( AudioLocation );
}

//-----------------------------------------------------------------------------
// Mood-dependent states.

singleton SimGroup( AudioMood );

singleton SFXState( AudioMoodNeutral )
{
   parentGroup = AudioMood;
   className = "AudioStateExclusive";
};

singleton SFXState( AudioMoodAggressive )
{
   parentGroup = AudioMood;
   className = "AudioStateExclusive";
};

singleton SFXState( AudioMoodTense )
{
   parentGroup = AudioMood;
   className = "AudioStateExclusive";
};

singleton SFXState( AudioMoodVictory )
{
   parentGroup = AudioMood;
   className = "AudioStateExclusive";
};

singleton SFXState( AudioMoodCalm )
{
   parentGroup = AudioMood;
   className = "AudioStateExclusive";
};

/// Return the currently active SFXState in AudioMood.
function sfxGetMood()
{
   return sfxGetActiveStateInGroup( AudioMood );
}
