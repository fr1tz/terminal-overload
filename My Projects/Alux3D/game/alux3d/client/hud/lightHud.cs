// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function LightHud::onWake(%this)
{
   TurbulenceFx.enable();
   $HDRPostFX::colorCorrectionRamp = "alux3d/client/graphics/color_ramp_1.png";
   %teamId = %this.zTeamId;
   if(%teamId == 1)
   {
      %ownSoilMat = fr1tz_alux1_shapes_soil_mat1;
      %enemySoilMat = fr1tz_alux1_shapes_soil_mat2;
   }
   else
   {
      %ownSoilMat = fr1tz_alux1_shapes_soil_mat2;
      %enemySoilMat = fr1tz_alux1_shapes_soil_mat1;
   }

   %ownSoilMat.zDiffuseColor[0] = %ownSoilMat.diffuseColor[0];
   %ownSoilMat.zEmissive = %ownSoilMat.emissive;
   %ownSoilMat.diffuseColor[0] = "0 0 1 1";
   %ownSoilMat.emissive = "1";
   %ownSoilMat.reload();
   
   %enemySoilMat.zDiffuseColor[0] = %enemySoilMat.diffuseColor[0];
   %enemySoilMat.zEmissive = %enemySoilMat.emissive;
   %enemySoilMat.diffuseColor[0] = "1 1 1 1";
   %enemySoilMat.emissive = "0";
   %enemySoilMat.reload();

   // Turn off any shell sounds...
   // sfxStop( ... );

   $enableDirectInput = "1";
   activateDirectInput();

   // Message hud dialog
   if ( isObject( MainChatHud ) )
   {
      Canvas.pushDialog( OverlayHud );
      Canvas.pushDialog( MainChatHud );
      chatHud.attach(HudMessageVector);
   }      
   
   // just update the action map here
   moveMap.push();
   
   // Start tick thread.
   %this.tickThread();

   // hack city - these controls are floating around and need to be clamped
   if ( isFunction( "refreshCenterTextCtrl" ) )
      schedule(0, 0, "refreshCenterTextCtrl");
   if ( isFunction( "refreshBottomTextCtrl" ) )
      schedule(0, 0, "refreshBottomTextCtrl");
}

function LightHud::onSleep(%this)
{
   TurbulenceFx.disable();
   $HDRPostFX::colorCorrectionRamp = "core/scripts/client/postFx/null_color_ramp.png";

   %mat[1] = fr1tz_alux1_shapes_soil_mat1;
   %mat[0] = fr1tz_alux1_shapes_soil_mat2;

   for(%i = 0; %i < 2; %i++)
   {
      %m = %mat[%i];
      %m.diffuseColor[0] = %m.zDiffuseColor[0];
      %m.emissive = %m.zEmissive;
      %m.reload();
   }

   if ( isObject( MainChatHud ) )
      Canvas.popDialog( MainChatHud );
   
   // pop the keymaps
   moveMap.pop();
}

