// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function PreloadGui::onAdd(%this)
{

}

function PreloadGui::onWake(%this)
{

}

function PreloadGui::onSleep(%this)
{

}

function PreloadGui::clearText(%this)
{
   %this-->text.setText("");
}

function PreloadGui::addText(%this, %text)
{
   %this-->text.addText(%text);
   %this-->scroll.scrollToBottom();
}

function PreloadGui::preloadFailed(%this)
{
   %c = $Client::Preload.missingFiles.count();
   if(%c == 0)
   {
      %this.abort();
      return;
   }
   
   %totalsize = 0;
   for(%i = 0; %i < %c; %i++)
      %totalsize += getWord($Client::Preload.missingFiles.getValue(%i), 0);
   %totalsizeMB = mFloatLength(%totalsize/1000000, 2);

   MessageBoxYesNo(
      "Missing Content",
      "The game is missing content required by this server!\n" @
      "(" @ %c SPC "files," SPC %totalsizeMB SPC "MB total)\n" @
      "Try to download missing content automatically?",
      "PreloadGui.downloadMissingFiles();",
      "PreloadGui.abort();");
}

function PreloadGui::downloadMissingFiles()
{
   downloadMissingFiles();
}

function PreloadGui::abort()
{
   if(isObject($Client::Preload))
      $Client::Preload.delete();
   disconnect();
}

