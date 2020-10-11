#include "GraphicsWrapper.h"
#include <rtos.h>
#include <GraphicsDisplay.h>

ILI9341 mDisplay(SPI_16, 12000000, PB_5,PB_4, PB_3, PA_10, PA_8, PB_10,"myLCD");  // Spi 16bit, 12MHz, mosi, miso, sclk, cs, reset, dc

CGraphicsWrapper::CGraphicsWrapper(direction_t *joypadDirection) : mJoypadDirection(joypadDirection)
{
    mForegroundColor=Black;
    mBackgroundColor=White;
    mOrienttation=1;
}

void CGraphicsWrapper::CheckIfDirectionChanged(direction_t &directionInfo)
{
   // mUpdateDirection = false;
   // mUpdateText = false;
   // directionInfo.dataReady = false;
   // if(mJoypadDirection->dataReady == true)
   // {
   //    if((directionInfo.direction != mJoypadDirection->direction) && (mUpdateDirection))
   //    {
   //       mUpdateDirection = true;
   //       directionInfo.direction = mJoypadDirection-> direction;
   //    }
   //    if (directionInfo.buttonPress != mJoypadDirection->buttonPress)
   //    {
   //       directionInfo.buttonPress = true;
   //    }
   //    if ((directionInfo.xAxisAnalog != mJoypadDirection->xAxisAnalog) && 
   //       (directionInfo.yAxisAnalog != mJoypadDirection->yAxisAnalog) &&
   //       (mUpdateText))
   //    {
   //       directionInfo.xAxisAnalog = mJoypadDirection->xAxisAnalog;
   //       directionInfo.yAxisAnalog = mJoypadDirection->yAxisAnalog;
   //    }
   //    if((directionInfo.buttonPress == true) || (mUpdateDirection == true) || (mUpdateText == true))
   //    {
   //       directionInfo.buttonPress = true;
   //    }
   // }

}

void CGraphicsWrapper::DirectionDisplayUI()
{
   // direction_t oldDirection_data = {};
   // direction_t updatedDirection_data = {};

   // while(mKeepRunning == true)
   // {
   //    CheckIfDirectionChanged(updatedDirection_data);
   //    if(updatedDirection_data.dataReady == true)
   //    {
   //       if(mUpdateLayout == true)
   //       {
   //             drawLayout();
   //       }
   //       if(mUpdateDirection ==  true)
   //       {
   //          drawDirection(oldDirection_data, Black, 0);
   //          drawDirection(updatedDirection_data, DarkGreen, 0);
   //       }
   //       if(mUpdateText == true)
   //       {
   //          updateText(oldDirection_data, Black);
   //          updateText(updatedDirection_data, DarkGreen);
   //       }
   //       if(updatedDirection_data.buttonPress == true)
   //       {
   //          drawButtonPress(oldDirection_data, Black);
   //          drawButtonPress(updatedDirection_data, DarkGreen);
   //       }
         
   //       updatedDirection_data.dataReady = false;
   //       oldDirection_data.buttonPress = updatedDirection_data.buttonPress?true:false;
   //       oldDirection_data.direction = updatedDirection_data.direction;
   //       oldDirection_data.xAxisAnalog = updatedDirection_data.xAxisAnalog;
   //       oldDirection_data.yAxisAnalog = updatedDirection_data.yAxisAnalog;
   //       mJoypadDirection->dataReady = false;
   //       mUpdateLayout = false;
   //       mUpdateDirection = false;
   //       mUpdateText = false;
   //       ThisThread::sleep_for(1ms);
   //    }
   //    else
   //    {
   //       ThisThread::sleep_for(100ms);
   //    }
      
   // }
   int y = 50;
   int oldy = 50;
   mDisplay.set_orientation(0);
   mDisplay.locate(0,20);
   mDisplay.set_font((unsigned char*) Terminal6x8);
   mDisplay.printf("Display Test");
   while(true)
   {
      mDisplay.locate(120,y);
      mDisplay.fillcircle(120,y,50, Red);
      //wait_us(10);
      if(y >= 270)
      {
         oldy=y;
         y = 50;
      }
      else
      {
         oldy=y;
         y+=10;
      }
      mDisplay.fillcircle(120,oldy,50, Black);
   }

}

void CGraphicsWrapper::GraphicsDidsplayThreadHelper(void* graphicsWrapper)
{
   static_cast<CGraphicsWrapper*>(graphicsWrapper)->DirectionDisplayUI();
}

void CGraphicsWrapper::Start()
{
   mKeepRunning = true;
   mUpdateDirection = true;
   mUpdateText = true;
   mUpdateLayout = true;
   mDisplay.set_orientation(2);
   mDisplay.foreground(White);
   mDisplay.background(Black);
   mDisplay.cls();
   mDisplay.set_font((unsigned char*) Terminal6x8);
   printf("Thread Running!");

   mControllerDirectionUI.start(Callback<void()>(CGraphicsWrapper::GraphicsDidsplayThreadHelper,this));  // callback using member function

}

void CGraphicsWrapper::Stop()
{
   mKeepRunning = false;
   mDisplay.cls();
   mControllerDirectionUI.join();
}

void CGraphicsWrapper::drawDirection(direction_t& directionInfo, unsigned short shapeColor, int orientation)
{
   // int x0,y0,x1,y1,x2,y2;
   // switch(directionInfo.direction)
   // {
   //    case Direction_e::UP:
   //       mDisplay.locate(100,160);
   //       x0=100; y0=160;
   //       x1=120; y1=180;
   //       x2=140; y2=160;
   //       break;
   //    case Direction_e::RIGHT:
   //       break;
   //    case Direction_e::DOWN:
   //       break;
   //    case Direction_e::LEFT:
   //       break;
   //    case Direction_e::NONE:
   //    default:
   //       break;
   // }
   // mDisplay.fillTriangle(x0,y0,x1,y1,x2,y2, shapeColor);
}

CGraphicsWrapper::~CGraphicsWrapper()
{
   Stop();
}
void CGraphicsWrapper::drawLayout(){}
void CGraphicsWrapper::drawButtonPress(direction_t& directionInfo, unsigned short shapeColor){}
void CGraphicsWrapper::updateText(direction_t& directionInfo, unsigned short textColor){}