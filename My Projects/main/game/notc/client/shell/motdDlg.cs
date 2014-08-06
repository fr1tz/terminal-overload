// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if(!isObject(MotdConn))
{
   new HttpObject(MotdConn);
   $MOTD::Text = "";
}

//------------------------------------------------------------------------------

function MotdDlg::onAdd(%this)
{
   %this.refresh();
}

function MotdDlg::onWake(%this)
{
   %this.setMotd();
}

function MotdDlg::refresh(%this)
{
   $MOTD::Text = "";
   MotdDlg-->text.setText("--- FETCHING http://www.terminal-overload.org/motd ---\n");
   MotdConn.get("www.terminal-overload.org:80", "/motd");
}

function MotdDlg::setMotd(%this)
{
   //echo("MotdDlg::setMotd()");

   if($MOTD::Text $= "")
      return;

   MotdDlg-->text.setText($MOTD::Text);

   if(MotdDlg.isAwake())
   {
      hilightControl(MainMenuGui-->MotdButton, false);
      $Pref::MOTD::Hash = sha256($MOTD::Text);
   }
   else if(sha256($MOTD::Text) !$= $Pref::MOTD::Hash)
   {
      hilightControl(MainMenuGui-->MotdButton, true);
   }
}


//------------------------------------------------------------------------------

function MotdConn::onLine(%this, %line)
{
   //error("MotdConn::onLine()");
   $MOTD::Text = $MOTD::Text @ %line @ "\n";
}

function MotdConn::onDNSResolved(%this)
{
   //error("MotdConn::onDNSResolved()");
   MotdDlg-->text.addText("--- HOST FOUND ---\n", true);
}

function MotdConn::onDNSFailed(%this)
{
   //error("MotdConn::onDNSFailed()");
   MotdDlg-->text.addText("--- HOST NOT FOUND ---\n", true);
}

function MotdConn::onConnected(%this)
{
   //error("MotdConn::onConnected()");
   MotdDlg-->text.addText("--- BEGIN TRANSMISSION ---\n", true);
}

function MotdConn::onConnectFailed(%this)
{
   //error("MotdConn::onConnectFailed()");
   MotdDlg-->text.addText("--- CONNECTION FAILED ---\n", true);
}

function MotdConn::onDisconnect(%this)
{
   //error("MotdConn::onDisconnect()");
   if($MOTD::Text $= "")
      MotdDlg-->text.addText("\n--- TRANSMISSION EMPTY ---", true);
   else
      MotdDlg.setMotd();
}

