// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function shellAddStartServerGui(%ctrl)
{
   //echo("shellAddStartServerGui():" SPC %ctrl);

   if(!isObject(%ctrl))
      return;

   if(strstr($Shell::StartServerGuis, %ctrl @ " ") != -1)
      return;

   $Shell::StartServerGuis = $Shell::StartServerGuis @ %ctrl @ " ";
}

function shellSetStartServerArgs(%gameType, %args)
{
   StartServerArgsText.setText(%gameType SPC %args);
}

function shellStartServer()
{
   //echo("ChooseLevelDlgGoBtn::onMouseUp()");

   // So we can't fire the button when loading is in progress.
   if ( isObject( ServerGroup ) )
      return;

   %gameType = getWord(StartServerArgsText.text, 0);
   %args = getWords(StartServerArgsText.text, 1, -1);

   //echo("Game type:" SPC %gameType);
   //echo("Args:" SPC %args);

   // Launch the chosen level with the editor open?
   if(ChooseLevelDlg.launchInEditor)
   {
      activatePackage("BootEditor");
      ChooseLevelDlg.launchInEditor = false;
   }

   startAndConnectToLocalServer(%gameType, %args);
}
   
//----------------------------------------

function ChooseLevelWindow::onWake(%this)
{
   //echo("ChooseLevelWindow::onWake()");

   if($InGuiEditor)
      return;

   %this.updateStartServerGuiList();

   if(%this-->ContentContainer.getCount() == 0)
      StartServerGuiList.setFirstSelected();
}

function ChooseLevelWindow::setContent(%this, %ctrl)
{
   //echo("ChooseLevelWindow::setContent():" SPC %ctrl);

   if(%this.zContent $= %ctrl)
      return;

   // Clean content container.
   if(isObject(%this.zContent) && isObject(%this.zContentOriginalParent))
      %this.zContentOriginalParent.add(%this.zContent);
   %this-->ContentContainer.clear();

   %content = %ctrl;
   %contentOriginalParent = %ctrl.getParent();

   if(isObject(%content))
   {
      %this-->ContentContainer.add(%content);
      %content.setPosition(0, 0);
      %extent = %this-->ContentContainer.getExtent();
      %w = getWord(%extent, 0);
      %h = getWord(%extent, 1);
      %extent = %w SPC %h;
      %content.setExtent(%extent);
      %this.zContent = %content;
      %this.zContentOriginalParent = %contentOriginalParent;
   }
}

function ChooseLevelWindow::updateStartServerGuiList(%this)
{
   //echo("ChooseLevelWindow::updateStartServerGuiList()");

   %popup = StartServerGuiList;
   %popup.clear();

   %numEditors = getWordCount($Shell::StartServerGuis);
   for(%i = 0; %i < %numEditors; %i++)
   {
      %ssg = getWord($Shell::StartServerGuis, %i);
      %string = %ssg.gameType;
      if(%string $= "")
         %string = %ssg;
      %popup.add(%string, %ssg.getId());
   }
}

function StartServerGuiList::onSelect(%this, %id, %text)
{
   //echo("StartServerGuiList::onSelect()");
   ChooseLevelWindow.setContent(%id);
}

