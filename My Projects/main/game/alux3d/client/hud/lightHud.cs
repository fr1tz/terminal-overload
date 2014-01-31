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
      %friendlyMaterials[0] = fr1tz_alux1_shapes_brick_mat1;
      %friendlyMaterials[1] = Mat_Team1_Soldier_Main;
      %enemyMaterials[0] = fr1tz_alux1_shapes_brick_mat2;
      %enemyMaterials[1] = Mat_Team2_Soldier_Main;
   }
   else
   {
      %ownSoilMat = fr1tz_alux1_shapes_soil_mat2;
      %enemySoilMat = fr1tz_alux1_shapes_soil_mat1;
      %friendlyMaterials[0] = fr1tz_alux1_shapes_brick_mat2;
      %friendlyMaterials[1] = Mat_Team2_Soldier_Main;
      %enemyMaterials[0] = fr1tz_alux1_shapes_brick_mat1;
      %enemyMaterials[1] = Mat_Team1_Soldier_Main;
   }
   
   for(%i = 0; %i < 2; %i++)
   {
      %fmat = %friendlyMaterials[%i];
      %emat = %enemyMaterials[%i];
   
      %fmat.zDiffuseColor[0] = %fmat.diffuseColor[0];
      %fmat.zEmissive = %fmat.emissive;
      %fmat.diffuseColor[0] = "0.5 0 0 1";
      %fmat.emissive = "1";
      %fmat.reload();

      %emat.zDiffuseColor[0] = %emat.diffuseColor[0];
      %emat.zEmissive = %emat.emissive;
      %emat.diffuseColor[0] = "1 1 1 1";
      %emat.emissive = "0";
      %emat.reload();
   }

   %ownSoilMat.zDiffuseColor[0] = %ownSoilMat.diffuseColor[0];
   %ownSoilMat.zEmissive = %ownSoilMat.emissive;
   %ownSoilMat.diffuseColor[0] = "0.5 0.5 0 1";
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
   if (isObject( MainChatHud ) )
   {
      Canvas.pushDialog( OverlayHud );
      //Canvas.pushDialog( MainChatHud );
      //chatHud.attach(HudMessageVector);
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

   %mat[0] = fr1tz_alux1_shapes_soil_mat1;
   %mat[1] = fr1tz_alux1_shapes_soil_mat2;
   %mat[2] = fr1tz_alux1_shapes_brick_mat1;
   %mat[3] = fr1tz_alux1_shapes_brick_mat2;
   %mat[4] = Mat_Team1_Soldier_Main;
   %mat[5] = Mat_Team2_Soldier_Main;
   
   for(%i = 0; %i < 6; %i++)
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

