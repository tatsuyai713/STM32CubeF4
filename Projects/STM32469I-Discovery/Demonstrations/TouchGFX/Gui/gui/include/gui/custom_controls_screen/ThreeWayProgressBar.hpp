/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.10.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  

#ifndef THREE_WAY_PROGRESS_BAR_HPP
#define THREE_WAY_PROGRESS_BAR_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <gui/custom_controls_screen/ThreeWayProgressBarCircle.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#include <touchgfx/EasingEquations.hpp>

using namespace touchgfx;

class ThreeWayProgressBar : public Container
{
public:
    ThreeWayProgressBar();
    virtual ~ThreeWayProgressBar();

    void reset();
    void stopAnimation();

    void setBarPercentage(int barIndex, int percentage);

    void setActive(bool active);

    void setButtonClickedCallback(touchgfx::GenericCallback<const ThreeWayProgressBar&>& callback) { buttonClickedAction = &callback; }

private:
    static const int NUMBER_OF_BARS = 3;

    GenericCallback<const ThreeWayProgressBar&>* buttonClickedAction;  

    int radius;

    Image background;
    ButtonWithLabel centerButton;

    MoveAnimator<ThreeWayProgressBarCircle> circles[NUMBER_OF_BARS];

    Circle bars[NUMBER_OF_BARS];
    PainterRGB565Bitmap bitmapPainter;

    Callback<ThreeWayProgressBar, const AbstractButton& > buttonPressedCallback;
    void buttonPressedHandler(const AbstractButton& button);


};

#endif /* THREE_WAY_PROGRESS_BAR_HPP */
