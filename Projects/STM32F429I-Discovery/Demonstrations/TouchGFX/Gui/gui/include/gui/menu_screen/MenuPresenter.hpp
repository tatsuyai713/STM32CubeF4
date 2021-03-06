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
  


#ifndef MENU_PRESENTER_HPP
#define MENU_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <gui/model/Model.hpp>

using namespace touchgfx;

class MenuView;

class MenuPresenter : public Presenter, public ModelListener
{
public:
    MenuPresenter(MenuView& v);
    virtual ~MenuPresenter();

    virtual void activate();
    virtual void deactivate();

private:
    MenuPresenter();

    MenuView& view;
};

#endif // MENU_PRESENTER_HPP
