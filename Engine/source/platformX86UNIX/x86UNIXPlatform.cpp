#include "platform/platform.h"
#include "console/console.h"
#include "core/strings/stringFunctions.h"

#include <unistd.h> 

bool Platform::openWebBrowser( const char* webAddress )
{
   if(!webAddress || dStrlen(webAddress) == 0)
      return false;

   const char* browser = Con::getVariable("Pref::Unix::WebBrowser");
   if(dStrlen(browser) == 0)
      browser = NULL;

   pid_t pid = fork();
   if(pid == -1)
   {
      Con::printf("Platform::openWebBrowser(): fork() failed");
      return false;
   }
   else if(pid != 0)
   {
      // In parent process
      //if(Video::isFullScreen())
      //   Video::toggleFullScreen();
      return true;
   }
   else if(pid == 0)
   {
      // In child process
      char* argv[3];
      argv[0] = "";
      argv[1] = const_cast<char*>(webAddress);
      argv[2] = 0;
      // if execvp returns, it means it couldn't execute the program
      if(browser != NULL)
         execvp(browser, argv);
      execvp("firefox", argv);
      execvp("google-chrome", argv);
      execvp("konqueror", argv);
      execvp("mozilla", argv);
      execvp("netscape", argv);
      dPrintf("Platform::openWebBrowser(): Couldn't launch a web browser\n");
      _exit(-1);
      return false;
   }
}
