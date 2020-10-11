#ifndef GRAPHICS_WRAPPER_H
#define GRAPHICS_WRAPPER_H
#include <cstdio>
#include <cstring>
#include <string.h>
#include <atomic>

#include <mbed.h>
#include <Arial12x12.h>
#include <Arial24x23.h>
#include <Arial43x48_numb.h>
#include <ILI9341.h>
#include <data_framework.h>

/**
 * @brief A Wrapper API to start a separate thread and draw UI on
 * the TFT screen.
 * 
 */
class CGraphicsWrapper
{
   private:
      std::atomic_bool mKeepRunning;
      std::atomic_bool mUpdateDirection;
      std::atomic_bool mUpdateText;
      std::atomic_bool mUpdateLayout;
      unsigned short mBackgroundColor;
      unsigned short mForegroundColor;
      direction_t *mJoypadDirection;
      int mOrienttation;
      Thread mControllerDirectionUI;

      void DirectionDisplayUI();
      static void GraphicsDidsplayThreadHelper(void* graphicsWrapper);
      void CheckIfDirectionChanged(direction_t& directionInfo);
      void drawDirection(direction_t& directionInfo, unsigned short shapeColor, int orientation);
      void drawLayout();
      void drawButtonPress(direction_t& directionInfo, unsigned short shapeColor);
      void updateText(direction_t& directionInfo, unsigned short textColor);

   public:
      void Start();
      void Stop();
      CGraphicsWrapper(direction_t *joypadDirection);
      CGraphicsWrapper(){};
      ~CGraphicsWrapper();
};
#endif
