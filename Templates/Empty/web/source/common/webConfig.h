// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Define secure TorqueScript calls by adding them here.
// This list defines the calls that can be made by JavaScript into your game, so be very careful.

const char* gSecureScript[] = { 
    "echo",
    "testJavaScriptBridge",
    //"MyNamespace::myfunction",
    0 //SENTINEL
};

// Define the domains which are allowed to run your game via the web
// Your game plugin will refuse to run from any other domain for security reasons.
// You can turn this off during development and/or for debug builds

//#define WEBDEPLOY_DOMAIN_CHECK 
//#define WEBDEPLOY_DOMAIN_ALLOW_DEBUG

const char* gAllowedDomains[] = { 
    //"www.mydomain.com",
    //"games.myotherdomain.com",
    0 //SENTINEL
};