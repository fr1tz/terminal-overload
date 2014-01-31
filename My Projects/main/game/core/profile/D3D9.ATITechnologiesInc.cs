// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ATI Vendor Profile Script
//
// This script is responsible for setting global
// capability strings based on the nVidia vendor.

if(GFXCardProfiler::getVersion() < 64.44)
{
	$GFX::OutdatedDrivers = true;
	$GFX::OutdatedDriversLink = "<a:www.ati.com>You can get newer drivers here.</a>.";
}
else
{
   $GFX::OutdatedDrivers = false;
}
