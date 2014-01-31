// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


function imposterMetricsCallback()
{
   return "  | IMPOSTER |" @ 
          "   Rendered: " @ $ImposterStats::rendered @
          "   Batches: " @ $ImposterStats::batches @
          "   DrawCalls: " @ $ImposterStats::drawCalls @
          "   Polys: " @ $ImposterStats::polyCount @
          "   RtChanges: " @ $ImposterStats::rtChanges;
}