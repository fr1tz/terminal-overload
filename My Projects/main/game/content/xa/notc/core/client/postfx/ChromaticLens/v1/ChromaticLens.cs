// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

package ChromaticLens
{
   function clientCmdEnableChromaticLens(%max, %mode, %dt, %rnd)
   {
      Parent::clientCmdEnableChromaticLens(%max, %mode, %dt, %rnd);
      ChromaticLens.start(%max, %mode, %dt, %rnd);
   }
};

activatePackage(ChromaticLens);

if(isObject(ChromaticLens))
   ChromaticLens.delete();
new ScriptObject(ChromaticLens);

function ChromaticLens::start(%this, %max, %mode, %dt, %rnd)
{
   //echo("ChromaticLens::start():" SPC %max SPC %mode SPC %dt SPC %rnd);

   %this.max[0] = getWord(%max, 0);
   %this.max[1] = getWord(%max, 1);
   %this.max[2] = getWord(%max, 2);

   %this.mode[0] = getWord(%mode, 0);
   %this.mode[1] = getWord(%mode, 1);
   %this.mode[2] = getWord(%mode, 2);
      
   %this.dt[0] = getWord(%dt, 0);
   %this.dt[1] = getWord(%dt, 1);
   %this.dt[2] = getWord(%dt, 2);
   
   %this.rnd[0] = getWord(%rnd, 0);
   %this.rnd[1] = getWord(%rnd, 1);
   %this.rnd[2] = getWord(%rnd, 2);

   if(%this.mode[0] == 0)
      %this.value[0] = %this.max[0];
   else
      %this.value[0] = 0;

   if(%this.mode[1] == 0)
      %this.value[1] = %this.max[1];
   else
      %this.value[1] = 0;
      
   if(%this.mode[2] == 0)
      %this.value[2] = %this.max[2];
   else
      %this.value[2] = 0;

   %this.updateThread();
}

function ChromaticLens::updateThread(%this)
{
   //echo("ChromaticLens::updateThread()");

   if(%this.zUpdateThread !$= "")
   {
      cancel(%this.zUpdateThread);
      %this.zUpdateThread = "";
   }
   
   for(%i = 0; %i < 3; %i++)
   {
      if(%this.mode[%i] == 0)
      {
         if(%this.max[%i] < 0)
         {
            %this.value[%i] += %this.dt[%i];
            %this.value[%i] = mClamp(%this.value[%i], -1, 0);
         }
         else
         {
            %this.value[%i] -= %this.dt[%i];
            %this.value[%i] = mClamp(%this.value[%i], 0,1);
         }
      }
      if(%this.mode[%i] == 1)
      {
         if(%this.max[%i] < 0)
         {
            %this.value[%i] -= %this.dt[%i];
            if(%this.value[%i] < %this.max[%i]*2)
            {
               %this.value[%i] = 0;
               %this.dt[%i] = 0;
            }
         }
         else
         {
            %this.value[%i] += %this.dt[%i];
            if(%this.value[%i] > %this.max[%i]*2)
            {
               %this.value[%i] = 0;
               %this.dt[%i] = 0;
            }
         }
      }
   }
   

//   if(%this.factor[0] + %this.factor[1] + %this.factor[2] == 0)
//   {
     // if(ChromaticLensPostFX.isEnabled())
     //    ChromaticLensPostFX.disable();
     //return;
//   }
      
   if(!ChromaticLensPostFX.isEnabled())
      ChromaticLensPostFX.enable();
      
   for(%i = 0; %i < 3; %i++)
   {
      %max = %this.max[%i];
      %mode = %this.mode[%i];
      %value = %this.value[%i];
   
      if(%mode == 1 && mAbs(%value) > mAbs(%max))
         %value = %max - (%value-%max);

      %c[%i] = %value;
   }
   
   if(!(%c[0] == 0 && %c[1] == 0 && %c[2] == 0))
   {
      for(%i = 0; %i < 3; %i++)
         %c[%i] += getRandom()*%this.rnd[%i];
   }

   $CAPostFx::colorDistortionFactor = %c[0] SPC %c[1] SPC %c[2];
                                      
   //echo($CAPostFx::colorDistortionFactor);

   %this.zUpdateThread = %this.schedule(32, "updateThread");
}

