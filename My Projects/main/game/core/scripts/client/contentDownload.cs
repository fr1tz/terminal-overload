// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function downloadMissingFiles()
{
   if(!isObject($Client::Preload) || $Client::Preload.missingFiles.count() == 0)
   {
      // Nothing to do.
      onContentDownloadFinished();
      return;
   }
   
   PreloadGui.addText("WILL TRY TO DOWNLOAD MISSING FILES\n");
   ContentDownloader.currIndex = -1;
   downloadNextMissingFile();
}

function downloadNextMissingFile()
{
   ContentDownloader.currIndex++;
   
   if(ContentDownloader.currIndex >= $Client::Preload.missingFiles.count())
   {
      onContentDownloadFinished();
      return;
   }
   
   %file = $Client::Preload.missingFiles.getKey(ContentDownloader.currIndex);
   
   if(getSubStr(%file, 0, 10) !$= "content/o/")
   {
      PreloadGui.addText("UNABLE TO DOWNLOAD" SPC %file @ ": UNKNOWN REPO\n");
      schedule(0, 0, "downloadNextMissingFile");
      return;
   }
   %path = "/o/" @ getSubStr(%file, 10);
   
   if(!ContentDownloader.download("www.terminal-overload.org:80", %path, %file))
   {
      PreloadGui.addText("UNABLE TO OPEN" SPC %file SPC "FOR WRITING\n");
      schedule(0, 0, "downloadNextMissingFile");
      return;
   }

   PreloadGui.addText("DOWNLOADING" SPC %file);
}

function onContentDownloadFinished()
{
   if($Client::Preload.missingFiles.count() > 0)
   {
      MessageBoxOK("Content Download Failed",
         "Not all required files could be downloaded.",
         "PreloadGui.abort();");
      return;
   }

   if($Client::Preload.serverAddress $= "local")
   {
      PreloadGui.addText("PLEASE ABORT & RESTART SERVER");
   }
   else
   {
      PreloadGui.addText("RECONNECTING TO SERVER");
      connect($Client::Preload.serverAddress);
   }
}

//------------------------------------------------------------------------------

if(!isObject(ContentDownloader))
   new notcHttpFileDownloader(ContentDownloader);

function ContentDownloader::onDNSResolved(%this)
{
   //error("ContentDownloader::onDNSResolved()");
}

function ContentDownloader::onDNSFailed(%this)
{
   //error("ContentDownloader::onDNSFailed()");
   PreloadGui.addText(" DNS LOOKUP FAILED\n");
   onContentDownloadFinished();
}

function ContentDownloader::onConnected(%this)
{
   //error("ContentDownloader::onConnected()");
   PreloadGui.addText(" CONNECTED");
}

function ContentDownloader::onConnectFailed(%this)
{
   //error("ContentDownloader::onConnectFailed()");
   PreloadGui.addText(" CONNECTION FAILED\n");
   schedule(0, 0, "downloadNextMissingFile");
}

function ContentDownloader::onDisconnect(%this)
{
   //error("ContentDownloader::onDisconnect()");
   %this.onDownloadComplete();
}

function ContentDownloader::onDownloadComplete(%this)
{
   //error("ContentDownloader::onDownloadComplete()");
   %idx = ContentDownloader.currIndex;
   %file = $Client::Preload.missingFiles.getKey(%idx);
   %crc = getWord($Client::Preload.missingFiles.getValue(%idx), 1);
   if(getFileCRC(%file) $= %crc)
   {
      $Client::Preload.missingFiles.erase(ContentDownloader.currIndex);
      ContentDownloader.currIndex--;
      PreloadGui.addText(" SUCCESS\n");
   }
   else
      PreloadGui.addText(" CRC FAILED\n");
   schedule(0, 0, "downloadNextMissingFile");
}

