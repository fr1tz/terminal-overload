// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function OptPlayerGui::onWake(%this)
{
   OptPlayerGui-->PseudoButton.setValue(!$Pref::AIMS::Enabled);
   OptPlayerGui-->AimsButton.setValue($Pref::AIMS::Enabled);
}

