// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
// Mission Editor Manager
new ActionMap(EditorMap);

function EditorMap_getMouseAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * $pref::Input::LinkMouseSensitivity;
}

function mouseWheelScroll( %val )
{
   //$Camera::speedCurveTime += $Camera::scrollStepSize * ( (%val>0.0) ? 1 : -1 );
   //$Camera::speedCurveTime = mClamp( $Camera::speedCurveTime, 0.0, 1.0 );
   //calculateCameraSpeed();   
   //EditorGui-->CameraSpeedSpinner.setText( $Camera::movementSpeed );

   %rollAdj = EditorMap_getMouseAdjustAmount(%val);
   %rollAdj = mClamp(%rollAdj, -mPi()+0.01, mPi()-0.01);
   $mvRoll += %rollAdj;
}

function editorYaw(%val)
{
   %yawAdj = EditorMap_getMouseAdjustAmount(%val);

   if(ServerConnection.isControlObjectRotDampedCamera() || EWorldEditor.isMiddleMouseDown())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   if( EditorSettings.value( "Camera/invertXAxis" ) )
      %yawAdj *= -1;

   $mvYaw += %yawAdj;
}

function editorPitch(%val)
{
   %pitchAdj = EditorMap_getMouseAdjustAmount(%val);

   if(ServerConnection.isControlObjectRotDampedCamera() || EWorldEditor.isMiddleMouseDown())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   if( EditorSettings.value( "Camera/invertYAxis" ) )
      %pitchAdj *= -1;

   $mvPitch += %pitchAdj;
}

function editorWheelFadeScroll( %val )
{
   EWorldEditor.fadeIconsDist += %val * 0.1;
   if( EWorldEditor.fadeIconsDist < 0 )
      EWorldEditor.fadeIconsDist = 0;
}

EditorMap.bind( mouse, xaxis, editorYaw );
EditorMap.bind( mouse, yaxis, editorPitch );
EditorMap.bind( mouse, zaxis, mouseWheelScroll );

EditorMap.bind( mouse, "alt zaxis", editorWheelFadeScroll );
