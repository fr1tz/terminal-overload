#ifndef GFX_PROFILER_H
#define GFX_PROFILER_H

/*
// Is necessary to implement a class with the following interface for each graphic API.
class Timer
{
public:      

   void begin();
   void end();

   F64 getTime();   

   class Data:
   typedef Data DataType;

    Timer(GFXDevice *device, Data &data);
    Timer();

    Timer& operator=(const Timer &b);

    StringTableEntry mName; 
};
*/


template<class TYPE>
class GFXProfiler
{
public:
   
   void PrintQueriesTimes();
   F64 getQueryTime(StringTableEntry name);
   void onEndFrame(bool start);
   void enterDebugEvent(ColorI color, const char *_name);
   void leaveDebugEvent();
   void reset();

   bool enable_Profiler;   

   typedef Map<StringTableEntry, Vector<TYPE> > TimerMap;  

   GFXProfiler() : printTimes(false), timers(0), enable_Profiler(false) {}
   bool printTimes;
protected:
   TYPE getQueryTimer(GFXDevice* d, const StringTableEntry name);   

   Vector<TYPE> timeQueries;
   Vector<TYPE> freetimeQueries;
   TimerMap queryMap;
   
   Vector<TYPE> timerStack;
   Vector<StringTableEntry> activeTimers;
   S32 timers;
   typename TYPE::DataType mData;

   Map<StringTableEntry, F64> mCampturesTimes;
   U32 mCapturedFrames;
};


template<class TYPE>
inline TYPE GFXProfiler<TYPE>::getQueryTimer(GFXDevice* d, const StringTableEntry name)
{
   if(!freetimeQueries.size())
   {
      const int size = 100;
      timeQueries.reserve( timeQueries.capacity() + size );
      freetimeQueries.reserve( freetimeQueries.capacity() + size );
      for(int i = 0; i < size; ++i)
      {
         TYPE timer(GFX, mData);
         timeQueries.push_back(timer);
         freetimeQueries.push_back(timer);
      }
   }

   TimerMap::Iterator itr;
   itr = queryMap.find(name);
   if(itr == queryMap.end())
      queryMap[name] = Vector<TYPE>();

   TYPE queryID = freetimeQueries.last();
   freetimeQueries.pop_back();
   queryMap[name].push_back(queryID);

   return queryID;
}

template<class TYPE>
inline F64 GFXProfiler<TYPE>::getQueryTime(StringTableEntry name)
{
   F64 timeTotal = 0.0;
   TimerMap::Iterator itr = queryMap.find(name);
   if(itr != queryMap.end())
   {
      for(auto i : itr->value)
      {            
         timeTotal += i.getTime();
      }      
   }

   return timeTotal;
}

template<class TYPE>
inline void GFXProfiler<TYPE>::PrintQueriesTimes()
{
   Con::printf("");
   F64 allTimers = 0;
   for(int i = 0; i < activeTimers.size(); ++i)
   {
      StringTableEntry name = activeTimers[i];
      F64 time = mCampturesTimes[name]/mCapturedFrames;

      if(time >= 0.1f)
         Con::printf("%s : %f", name, time);
      allTimers += time;      
   }

   Con::printf("All timers Total : %f\n", allTimers);
}

template<class TYPE>
inline void GFXProfiler<TYPE>::reset()
{
   mCapturedFrames = 0;
   mCampturesTimes.clear();
}

template<class TYPE>
inline void GFXProfiler<TYPE>::onEndFrame(bool start)
{
   if(start)
   {     
      if(printTimes && !enable_Profiler)
         enable_Profiler = true;
         
      if(!enable_Profiler)
         return;

      mData.onBeginFrame();
      GFXDEBUGEVENT_START(RENDER_FRAME, ColorI::RED); //CanvasPreRender
      return;
   }

   if(!enable_Profiler)
      return;

   AssertFatal(timerStack.size() == 1, avar("GFXDEBUGEVENT not ended :%s", timerStack[1].mName) );
   AssertFatal(timerStack[0].mName == StringTable->insert("RENDER_FRAME"), avar("GFXDEBUGEVENT not ended :%s", timerStack[0].mName));
   GFXDEBUGEVENT_END(); //RENDER_FRAME
   mData.onEndFrame();

   AssertFatal(timerStack.size() == 0, "");
   AssertFatal(timers == 0, "");


   ++mCapturedFrames;
   for(int i = 0; i<activeTimers.size(); ++i )
   {
      StringTableEntry name = activeTimers[i];
      F64 totalTime = mCampturesTimes[name];
      mCampturesTimes[name] = totalTime + getQueryTime(name);
   }

   if(printTimes && mCapturedFrames == 30)
   {      
      PrintQueriesTimes();      
      reset();

      printTimes = false;
      enable_Profiler = false;
   }
   activeTimers.clear();
   freetimeQueries = timeQueries;
   for(auto itr : queryMap)
   {
      auto &vec = itr.value;
      vec.clear();
      AssertFatal(!vec.size(), "" );
   }
   queryMap.clear();
}

template<class TYPE>
inline void GFXProfiler<TYPE>::enterDebugEvent(ColorI color, const char *_name)
{
   if(!enable_Profiler)
      return;

   ++timers;
   StringTableEntry nameSte = StringTable->insert(_name);
  
   TYPE timer = getQueryTimer(GFX, nameSte);

   //check stack
   if(timerStack.size())
   {
      timerStack.last().end();
   }

   timer.mName = nameSte;
   timer.begin();   

   activeTimers.push_back_unique(nameSte);
   timerStack.push_back(timer);
}

template<class TYPE>
inline void GFXProfiler<TYPE>::leaveDebugEvent()
{
   if(!enable_Profiler)
      return;

   --timers;

   timerStack.last().end();
   AssertFatal(timerStack.size(), "");
   timerStack.pop_back();

   //check stack
   if(timerStack.size())
   {      
      timerStack.last().begin();
   }
}

#endif