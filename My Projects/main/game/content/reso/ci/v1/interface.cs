// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmd_ResoMessageToController(%address, %msg)
{
   if(isObject(ResoControllerInterface))
      ResoControllerInterface.sendMsgTo(%address, %msg);
}

//------------------------------------------------------------------------------

function ResoEnableControllerInterface()
{
   ResoDisableControllerInterface();  
   %ci = new vitcPacketReceiveNotificationObject(ResoControllerInterface);
}

function ResoDisableControllerInterface()
{ 
   if(isObject(ResoControllerInterface))
      ResoControllerInterface.delete();
}

//------------------------------------------------------------------------------

function ResoControllerInterface::onAdd(%this)
{
   echo("ResoControllerInterface::onAdd()");	
   %this.heartbeatThread();
}

function ResoControllerInterface::onRemove(%this)
{
   echo("ResoControllerInterface::onRemove()");	
}

function ResoControllerInterface::onPacketReceive(%this, %address, %data)
{
   echo("ResoControllerInterface::onPacketReceive()");
   
   echo(" Packet from" SPC %address @ ":" SPC %data);
   
   %bstream = new vitcBitStreamObject();
   %bstream.initBufferFromBase64(%data);
   //error("BitStream size:" SPC %bstream.getStreamSize());
   %int1 = %bstream.readU32();
   %int2 = %bstream.readU32();
   //echo(%int1 SPC %int2);
   if(%int1 == 25 && %int2 == 1)
   {
      %msgLen = %bstream.readU32();
      %msg = %bstream.read(%msgLen);
      %this.processControllerMsg(%address, %msg);
   }
   %bstream.delete();
}

function ResoControllerInterface::heartbeatThread(%this)
{
   //echo("ResoControllerInterface::heartbeatThread()");	

   if(%this.zTickThread !$= "")
   {
      cancel(%this.zTickThread);
      %this.zTickThread = "";
   }
   %this.zTickThread = %this.schedule(640, "heartbeatThread");
   
   //%this.sendMsgTo("IP:BROADCAST:27999", "HEARTBEAT");
   //%this.sendMsgTo("IP:192.168.43.255:27999", "HEARTBEAT");
}

function ResoControllerInterface::sendMsgTo(%this, %address, %msg)
{
   //echo("ResoControllerInterface::sendMsg() [" @ %address @ "] " @ %msg);	
   %bstream = new vitcBitStreamObject();
   %bstream.initBuffer(1024);
   %bstream.writeU32(4);
   %bstream.writeU32(strlen(%msg));
   %bstream.write(%msg);
   vitcSendPacket(%address, %bstream.getBase64());
   %bstream.delete();   
}

function ResoControllerInterface::processControllerMsg(%this, %address, %msg)
{
   echo("ResoControllerInterface::processControllerMsg() [" @ %address @ "] " @ %msg);
   if(ServerConnection.getAddress() $= "local")
   	  serverCmdMessageFromController(LocalClientConnection, %address, %msg); 
   else
      commandToServer('MessageFromController', %address, %msg);
}

