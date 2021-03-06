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
  


#ifndef HOME_AUTOMATION_PRESENTER_HPP
#define HOME_AUTOMATION_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HomeAutomationView;

class HomeAutomationPresenter : public Presenter, public ModelListener
{
public:
    HomeAutomationPresenter(HomeAutomationView& v);
    virtual ~HomeAutomationPresenter();

    virtual void activate();
    virtual void deactivate();

    void roomSelected(uint8_t roomId);
    void newRoomTemperature(int16_t temperature);

    virtual void roomUpdated(RoomTemperatureInfo& room);
    void newScheduleAccepted();
    void getNewSchedule(RoomTemperatureInfo& room);
    void exitScreen();

    RoomTemperatureInfo& getSelectedRoom();

private:
    HomeAutomationPresenter();

    HomeAutomationView& view;
};

#endif // HOME_AUTOMATION_PRESENTER_HPP
