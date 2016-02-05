// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ActionWidget::onAdd(%this)
{
   echo("ActionWidget::onAdd()");
   %this.mode = 0;
}

function ActionWidget::getDescription(%this)
{
   return "Action Widget";
}

function ActionWidget::getType(%this)
{
   return "reso/1";	
}

function ActionWidget::getGridSizeN(%this)
{
   return "8 8";	
}

function ActionWidget::update(%this, %args)
{
   %mode = getWord(%args, 0);
   echo("ActionWidget:" SPC %mode);   
   
   %controller = %this.moduleObj;
   %client = %controller.client;
   
   %player = %controller.player;
   %obj = %player;
   echo(%player.getClassName());
   
   if(%mode == 0 && VectorLen(%player.getVelocity()) < 0.01)
   {
	   	   
   	   %vec = getWord(%args, 1) SPC -getWord(%args, 2) SPC "0";
   	   %impulse = VectorScale(%vec, 80);
   	   echo("vec:" SPC %vec SPC "impulse:" SPC %impulse);
   	   %player.setVelocity("0 0 0");
   	   %player.applyImpulse(%player.getPosition(), %impulse);
   }

}

