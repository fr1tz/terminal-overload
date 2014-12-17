// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function downloadMissingFiles()
{
   PreloadGui.addText("WILL TRY TO DOWNLOAD MISSING FILES\n");

   if(!isObject($Client::Preload) || $Client::Preload.missingFiles.count() == 0)
   {
      // Nothing to do.
      onContentDownloadFinished();
      return;
   }
   
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

//------------------------------------------------------------------------------

if(!isObject(ContentDownloader))
   new notcHttpFileDownloader(ContentDownloader);

function ContentDownloader::onLine(%this, %line)
{
   //error("ContentDownloader::onLine()");
   //PreloadGui.addText(".");
}

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
   PreloadGui.addText(" CONNECTION TO FAILED\n");
   schedule(0, 0, "downloadNextMissingFile");
}

function ContentDownloader::onDisconnect(%this)
{
   //error("ContentDownloader::onDisconnect()");
   $Client::Preload.missingFiles.erase(ContentDownloader.currIndex);
   ContentDownloader.currIndex--;
   PreloadGui.addText(" DONE\n");
   schedule(0, 0, "downloadNextMissingFile");
}

