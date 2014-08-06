// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function startUpdateHilightedGuiControlsThread()
{
	%set = HilightedGuiControlsSet;
	if(%set.updateThread $= "")
	{
		%set.updateThread = schedule(200, HilightedGuiControlsSet,
			"updateHilightedGuiControlsThread");
	}
}

function stopUpdateHilightedGuiControlsThread()
{
	%set = HilightedGuiControlsSet;
	if(%set.updateThread !$= "")
	{
		cancel(%set.updateThread);
		%set.updateThread = "";
	}
}

function updateHilightedGuiControlsThread()
{
	//echo("updateHilightedGuiControlsThread()");

	stopUpdateHilightedGuiControlsThread();

	%set = HilightedGuiControlsSet;
	if(%set.hilightState $= "")
		%set.hilightState = true;
	else
		%set.hilightState = "";

	for(%i = 0; %i < %set.getCount(); %i++)
	{
		%control = %set.getObject(%i);
		if(%set.hilightState == true)
      {
         if(%control.zText !$= "")
            %control.setText(%control.zText);
      }
		else
      {
         %control.zText = %control.getText();
			%control.setText("");
      }

	}

	startUpdateHilightedGuiControlsThread();
}

function hilightControl(%control, %hilight)
{
   if(!isObject(HilightedGuiControlsSet))
      new SimSet(HilightedGuiControlsSet);

	if(%hilight)
	{
      if(HilightedGuiControlsSet.getCount() == 0)
         startUpdateHilightedGuiControlsThread();
		HilightedGuiControlsSet.add(%control);
	}
	else
	{
		HilightedGuiControlsSet.remove(%control);
      if(%control.zText !$= "")
         %control.setText(%control.zText);
      if(HilightedGuiControlsSet.getCount() == 0)
         stopUpdateHilightedGuiControlsThread();
	}
}

