#include "GraphicsWrapper.h"
#include <rtos.h>

CGraphicsWrapper::CGraphicsWrapper(direction_t *joypadDirection) : mJoypadDirection(joypadDirection)
{
    mForegroundColor=White;
    mBackgroundColor=Black;
    mOrienttation=0;

    mDisplay->set_orientation(mOrienttation);
    mDisplay->foreground(mForegroundColor);
    mDisplay->background(mBackgroundColor);
    mDisplay->cls(); 
    mDisplay->locate(0,0);
}

void CGraphicsWrapper::CheckIfDirectionChanged(direction_t &directionInfo)
{
   mUpdateDirection = false;
   mUpdateText = false;
   directionInfo.dataReady = false;
   if(mJoypadDirection->dataReady == true)
   {
      if((directionInfo.direction != mJoypadDirection->direction) && (mUpdateDirection))
      {
         mUpdateDirection = true;
         directionInfo.direction = mJoypadDirection-> direction;
      }
      if (directionInfo.buttonPress != mJoypadDirection->buttonPress)
      {
         directionInfo.buttonPress = true;
      }
      if ((directionInfo.xAxisAnalog != mJoypadDirection->xAxisAnalog) && 
         (directionInfo.yAxisAnalog != mJoypadDirection->yAxisAnalog) &&
         (mUpdateText))
      {
         directionInfo.xAxisAnalog = mJoypadDirection->xAxisAnalog;
         directionInfo.yAxisAnalog = mJoypadDirection->yAxisAnalog;
      }
      if((directionInfo.buttonPress == true) || (mUpdateDirection == true) || (mUpdateText == true))
      {
         directionInfo.buttonPress = true;
      }
   }

}

void CGraphicsWrapper::DirectionDisplayUI()
{
   direction_t oldDirection_data = {};
   direction_t updatedDirection_data = {};

   while(mKeepRunning == true)
   {
      CheckIfDirectionChanged(updatedDirection_data);
      if(updatedDirection_data.dataReady == true)
      {
         if(mUpdateLayout == true)
         {
               drawLayout();
         }
         if(mUpdateDirection ==  true)
         {
            drawDirection(oldDirection_data, Black);
            drawDirection(updatedDirection_data, DarkGreen);
         }
         if(mUpdateText == true)
         {
            updateText(oldDirection_data, Black);
            updateText(updatedDirection_data, DarkGreen);
         }
         if(updatedDirection_data.buttonPress == true)
         {
            updateText(oldDirection_data, Black);
            updateText(updatedDirection_data, DarkGreen);
         }
         updatedDirection_data.dataReady = false;
         memcpy(&updatedDirection_data,&oldDirection_data,sizeof(oldDirection_data));
         mJoypadDirection->dataReady = false;
         mUpdateLayout = false;
         mUpdateDirection = false;
         mUpdateText = false;
         ThisThread::sleep_for(20ms);
      }
      else
      {
         ThisThread::sleep_for(100ms);
      }
      
   }
}

void CGraphicsWrapper::GraphicsDidsplayThreadHelper()
{

    return;
}

void CGraphicsWrapper::Start()
{
    mKeepRunning = true;
    mUpdateDirection = true;
    mUpdateText = true;
    mUpdateLayout = true;
}

void CGraphicsWrapper::Stop()
{
    return;
}

void CGraphicsWrapper::drawDirection(direction_t& directionInfo, unsigned short shapeColor, int orientation)
{

}
void CGraphicsWrapper::drawLayout(){}
void CGraphicsWrapper::drawButtonPress(direction_t& directionInfo, unsigned short shapeColor){}
void CGraphicsWrapper::updateText(direction_t& directionInfo, unsigned short textColor){}