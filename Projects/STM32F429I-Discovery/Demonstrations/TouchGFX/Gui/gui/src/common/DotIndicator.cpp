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
  


#include <gui/common/DotIndicator.hpp>
#include <BitmapDatabase.hpp>
#include <assert.h>


DotIndicator::DotIndicator() :
    unselectedDots(EAST),
    numberOfDots(0),
    currentDot(0)
{
    unselectedDots.setXY(0, 0);
    dotHighlighted.setXY(0, 0);

    add(unselectedDots);
    add(dotHighlighted);
}

DotIndicator::~DotIndicator()
{
}

void DotIndicator::setNumberOfDots(uint8_t size)
{
    numberOfDots = size;

    assert(numberOfDots > 0 && "At least one dot is needed");
    assert(numberOfDots <= MAX_SIZE && "Above maximum number of dots");

    unselectedDots.removeAll();
    for (int i = 0; i < numberOfDots; i++)
    {
        unselectedDots.add(dotNormal[i]);
    }
    // adjust size of container according to the actual bitmaps
    setWidth(unselectedDots.getWidth());
    setHeight(unselectedDots.getHeight());
    setHighlightPosition(currentDot = 0);
}

void DotIndicator::setBitmaps(const Bitmap& unselected, const Bitmap& selected)
{
    dotHighlighted.setBitmap(selected);
    for (int i = 0; i < MAX_SIZE - 1; i++)
    {
        dotNormal[i].setBitmap(unselected);
    }
    if (numberOfDots > 0)
    {
        setNumberOfDots(numberOfDots);
    }
}

void DotIndicator::goRight()
{
    setHighlightPosition(currentDot = (currentDot + 1) % numberOfDots);
}

void DotIndicator::goLeft()
{
    setHighlightPosition(currentDot = (currentDot + numberOfDots - 1) % numberOfDots);
}

void DotIndicator::setHighlightPosition(uint8_t index)
{
    // note that index is unsigned
    if (index < numberOfDots)
    {
        dotHighlighted.setX(index * dotNormal[0].getWidth());
    }
    invalidate();
}
