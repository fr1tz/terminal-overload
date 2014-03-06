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

   bool mEnableProfiler;

   typedef Map<StringTableEntry, Vector<TYPE> > TimerMap;  

   GFXProfiler() : mPrintTimes(false), mTimers(0), mEnableProfiler(false) {}

   void printTimes() { mPrintTimes = true; }
protected:
   bool mPrintTimes;
   TYPE getQueryTimer(GFXDevice* d, const StringTableEntry name);   

   Vector<TYPE> mTimeQueries;
   Vector<TYPE> mFreetimeQueries;
   TimerMap mQueryMap;
   
   Vector<TYPE> mTimerStack;
   Vector<StringTableEntry> mActiveTimers;
   S32 mTimers;
   typename TYPE::DataType mData;

   Map<StringTableEntry, F64> mCampturesTimes;
   U32 mCapturedFrames;
};


template<class TYPE>
inline TYPE GFXProfiler<TYPE>::getQueryTimer(GFXDevice* d, const StringTableEntry name)
{
   if(!mFreetimeQueries.size())
   {
      const int size = 100;
      mTimeQueries.reserve( mTimeQueries.capacity() + size );
      mFreetimeQueries.reserve( mFreetimeQueries.capacity() + size );
      for(int i = 0; i < size; ++i)
      {
         TYPE timer(GFX, mData);
         mTimeQueries.push_back(timer);
         mFreetimeQueries.push_back(timer);
      }
   }

   TimerMap::Iterator itr;
   itr = mQueryMap.find(name);
   if(itr == mQueryMap.end())
      mQueryMap[name] = Vector<TYPE>();

   TYPE queryID = mFreetimeQueries.last();
   mFreetimeQueries.pop_back();
   mQueryMap[name].push_back(queryID);

   return queryID;
}

template<class TYPE>
inline F64 GFXProfiler<TYPE>::getQueryTime(StringTableEntry name)
{
   F64 timeTotal = 0.0;
   TimerMap::Iterator itr = mQueryMap.find(name);
   if(itr != mQueryMap.end())
   {
      Vector<TYPE> &vec = itr->value;
      for(int i = 0; i < vec.size(); ++i)
      {            
         timeTotal += vec[i].getTime();
      }      
   }

   return timeTotal;
}

template<class TYPE>
inline void GFXProfiler<TYPE>::PrintQueriesTimes()
{
   Con::printf("");
   F64 allTimers = 0;
   for(int i = 0; i < mActiveTimers.size(); ++i)
   {
      StringTableEntry name = mActiveTimers[i];
      F64 time = mCampturesTimes[name]/mCapturedFrames;

      if(time >= 0.1f)
         Con::printf("%s : %f", name, time);
      allTimers += time;      
   }

   Con::printf("All mTimers Total : %f\n", allTimers);
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
      if(mPrintTimes && !mEnableProfiler)
         mEnableProfiler = true;
         
      if(!mEnableProfiler)
         return;

      mData.onBeginFrame();
      GFXDEBUGEVENT_START(RENDER_FRAME, ColorI::RED); //CanvasPreRender
      return;
   }

   if(!mEnableProfiler)
      return;

   AssertFatal(mTimerStack.size() == 1, avar("GFXDEBUGEVENT not ended :%s", mTimerStack[1].mName) );
   AssertFatal(mTimerStack[0].mName == StringTable->insert("RENDER_FRAME"), avar("GFXDEBUGEVENT not ended :%s", mTimerStack[0].mName));
   GFXDEBUGEVENT_END(); //RENDER_FRAME
   mData.onEndFrame();

   AssertFatal(mTimerStack.size() == 0, "");
   AssertFatal(mTimers == 0, "");


   ++mCapturedFrames;
   for(int i = 0; i<mActiveTimers.size(); ++i )
   {
      StringTableEntry name = mActiveTimers[i];
      F64 totalTime = mCampturesTimes[name];
      mCampturesTimes[name] = totalTime + getQueryTime(name);
   }

   if(mPrintTimes && mCapturedFrames == 30)
   {      
      PrintQueriesTimes();      
      reset();

      mPrintTimes = false;
      mEnableProfiler = false;
   }
   mActiveTimers.clear();
   mFreetimeQueries = mTimeQueries;
   for(TimerMap::Iterator itr = mQueryMap.begin(); itr != mQueryMap.end(); ++itr)
   {
      Vector<TYPE> &vec = itr->value;
      vec.clear();
      AssertFatal(!vec.size(), "" );
   }
   mQueryMap.clear();
}

template<class TYPE>
inline void GFXProfiler<TYPE>::enterDebugEvent(ColorI color, const char *_name)
{
   if(!mEnableProfiler)
      return;

   ++mTimers;
   StringTableEntry nameSte = StringTable->insert(_name);
  
   TYPE timer = getQueryTimer(GFX, nameSte);

   //check stack
   if(mTimerStack.size())
   {
      mTimerStack.last().end();
   }

   timer.mName = nameSte;
   timer.begin();   

   mActiveTimers.push_back_unique(nameSte);
   mTimerStack.push_back(timer);
}

template<class TYPE>
inline void GFXProfiler<TYPE>::leaveDebugEvent()
{
   if(!mEnableProfiler)
      return;

   --mTimers;

   mTimerStack.last().end();
   AssertFatal(mTimerStack.size(), "");
   mTimerStack.pop_back();

   //check stack
   if(mTimerStack.size())
   {      
      mTimerStack.last().begin();
   }
}

#endif