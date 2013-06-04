// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIGRAPHCTRL_H_
#define _GUIGRAPHCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

class GuiGraphCtrl : public GuiControl
{
   public:
   
      typedef GuiControl Parent;

      enum Constants
      {
         MaxPlots = 6,
         MaxDataPoints = 200
      };

      enum GraphType {
         Point,
         Polyline,
         Filled,
         Bar
      };

   protected:
   
      F32 mCenterY;
      StringTableEntry mAutoPlot[ MaxPlots ];
      U32 mAutoPlotDelay[ MaxPlots ];
      SimTime mAutoPlotLastDisplay[ MaxPlots ];
      ColorF mGraphColor[ MaxPlots ];
      Vector< F32 > mGraphData[ MaxPlots ];
      F32 mGraphMax[ MaxPlots ];
      GraphType mGraphType[ MaxPlots ];

      GFXStateBlockRef  mSolidSB;
      GFXStateBlockRef  mBlendSB;
      
   public:
      
      GuiGraphCtrl();

      void addDatum( S32 plotID, F32 v );
      F32  getDatum( S32 plotID, S32 samples );
      void addAutoPlot( S32 plotID, const char *variable, S32 update );
      void removeAutoPlot( S32 plotID);
      void setGraphType( S32 plotID, GraphType graphType );
      F32 getMax( S32 plotID ) const { return mGraphMax[ plotID ]; }
      void setMax( S32 plotID, F32 max ) { mGraphMax[ plotID ] = max; }

      // GuiControl.
      virtual void onRender(Point2I offset, const RectI &updateRect);

      DECLARE_CONOBJECT(GuiGraphCtrl);
      DECLARE_CATEGORY( "Gui Other" );
      DECLARE_DESCRIPTION( "A control that allows to plot curve graphs." );
      
      static void initPersistFields();
};

typedef GuiGraphCtrl::GraphType GuiGraphType;
DefineEnumType( GuiGraphType );

#endif
