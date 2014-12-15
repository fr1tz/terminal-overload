// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function PreloadGui::onAdd(%this)
{

}

function PreloadGui::onWake(%this)
{

}

function PreloadGui::onSleep(%this)
{

}

function PreloadGui::clearText(%this)
{
   %this-->text.setText("");
}

function PreloadGui::addText(%this, %text)
{
   echo("PL:" SPC %line);
   %this-->text.addText(%text);
   %this-->scroll.scrollToBottom();
}

