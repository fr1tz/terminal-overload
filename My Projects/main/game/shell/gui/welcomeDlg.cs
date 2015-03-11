// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function WelcomeDlg::onAdd(%this)
{
   %this.zUnderstood = false;
}

function WelcomeDlg::onWake(%this)
{
   %txt = "<just:center>Welcome to Terminal Overload" SPC
          $GameVersionString @ "!<just:left><br>";

   if($GameVersionType $= "dev")
   {
      %this-->window.text = "Development Version";
      %t = "Warning: This is a development version of Terminal Overload." NL
           "Development versions can be very buggy and unfinished." NL
           "The main purpose of development versions is to collect" SPC
           "feedback about the latest changes to the game." NL
           "Once the changes are finalized, testing versions are released" SPC
           "to find and eliminate bugs until finally a public version is" SPC
           "released.";
   }
   else if($GameVersionType $= "testing")
   {
      %this-->window.text = "Testing Version";
      %t = "This is a testing version of Terminal Overload." NL
           "The main purpose of testing versions is to collect bug reports." NL
           "Once the reported bugs have been eliminated, a public" SPC
           "version is released.";
   }
   else if($GameVersionType $= "public")
   {
      %this-->window.text = "Welcome";
   }
   else
   {
      %this-->window.text = "Unknown Version";
      %t = "Unknown $GameVersionType:" SPC "'"@$GameVersionType@"'";
   }
   
   if($GameVersionFeedbackURL !$= "")
   {
      %t = %t @ "<linkcolor:ffffff><just:center>";
      %t = %t @ "<br><br>Feedback URL:  <a:"@$GameVersionFeedbackURL@">";
      %t = %t @ "http://"@$GameVersionFeedbackURL@"</a>";
   }
   
   %txt = %txt NL %t;
      
   %this-->text.setText(%txt);
}

function WelcomeDlg::understood(%this)
{
   %this.zUnderstood = true;
   Canvas.popDialog(%this);
}

function WelcomeDlg::setWelcome(%this)
{
   //echo("WelcomeDlg::setWelcome()");

   if($MOTD::Text $= "")
      return;
      
   %mtext = $MOTD::Text;
   %wc = getWordCount(%mtext);
   for(%i = 0; %i < %wc; %i++)
   {
      %word = getWord(%mtext, %i);
      if(getSubStr(%word, 0, 4) $= "http")
         %mtext = setWord(%mtext, %i, "<a:"@%word@">"@%word@"</a>");
   }

   WelcomeDlg-->text.setText(%mtext);

   if(WelcomeDlg.isAwake())
   {
      hilightControl(MainMenuGui-->WelcomeButton, false);
      $Pref::MOTD::Hash = sha256($MOTD::Text);
   }
   else if(sha256($MOTD::Text) !$= $Pref::MOTD::Hash)
   {
      hilightControl(MainMenuGui-->WelcomeButton, true);
   }
}


//------------------------------------------------------------------------------

function WelcomeConn::onLine(%this, %line)
{
   //error("WelcomeConn::onLine()");
   $MOTD::Text = $MOTD::Text @ %line @ "\n";
}

function WelcomeConn::onDNSResolved(%this)
{
   //error("WelcomeConn::onDNSResolved()");
   WelcomeDlg-->text.addText("--- HOST FOUND ---\n", true);
}

function WelcomeConn::onDNSFailed(%this)
{
   //error("WelcomeConn::onDNSFailed()");
   WelcomeDlg-->text.addText("--- HOST NOT FOUND ---\n", true);
}

function WelcomeConn::onConnected(%this)
{
   //error("WelcomeConn::onConnected()");
   WelcomeDlg-->text.addText("--- BEGIN TRANSMISSION ---\n", true);
}

function WelcomeConn::onConnectFailed(%this)
{
   //error("WelcomeConn::onConnectFailed()");
   WelcomeDlg-->text.addText("--- CONNECTION FAILED ---\n", true);
}

function WelcomeConn::onDisconnect(%this)
{
   //error("WelcomeConn::onDisconnect()");
   if($MOTD::Text $= "")
      WelcomeDlg-->text.addText("\n--- TRANSMISSION EMPTY ---", true);
   else
      WelcomeDlg.setWelcome();
}

