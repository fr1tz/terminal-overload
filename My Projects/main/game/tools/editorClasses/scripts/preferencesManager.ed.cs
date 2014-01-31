// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//*** Initializes the Preferences Manager
function initPreferencesManager()
{
   // FIXME TGEA doesnt currently have these due to the way it's built
   return;
   
   //*** Create the Preferences Manager singleton
   %pm = new PreferencesManager(pref);
   registerPreferencesManager(%pm.getId());
}
