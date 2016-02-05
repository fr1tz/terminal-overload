// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Called by the mission editor.
function TriggerData::create(%data)
{
   %obj = new Trigger()
   {
      polyhedron = "-0.5 0.5 0.0 1.0 0.0 0.0 0.0 -1.0 0.0 0.0 0.0 1.0";
      dataBlock = %data;
   };

   return %obj;
}

//-----------------------------------------------------------------------------
// DefaultTrigger is used by the mission editor.  This is also an example
// of trigger methods and callbacks.

function DefaultTrigger::onEnterTrigger(%this,%trigger,%obj)
{
   // This method is called whenever an object enters the %trigger
   // area, the object is passed as %obj.
}

function DefaultTrigger::onLeaveTrigger(%this,%trigger,%obj)
{
   // This method is called whenever an object leaves the %trigger
   // area, the object is passed as %obj.
}

function DefaultTrigger::onTickTrigger(%this,%trigger)
{
   // This method is called every tickPerioMS, as long as any
   // objects intersect the trigger.

   // You can iterate through the objects in the list by using these
   // methods:
   //    %trigger.getNumObjects();
   //    %trigger.getObject(n);
}
