#include "stdafx.h"
#include "Tab.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

Tab::Tab(const float width, const float height,
         const Color bg_color, const Color text_color,
         VideoMode &vm, Font &font)

    : vm(vm), font(font)
{
    bg.setFillColor(bg_color);
    bg.setSize(Vector2f(width, height));

    hidden = true;
}

Tab::~Tab() {}

/* ACCESSORS ===================================================================================================== */

const bool &Tab::isHidden() const
{
    return hidden;
}

const bool Tab::isOpen() const
{
    return !hidden;
}

/* MODIFIERS ===================================================================================================== */

void Tab::hideToggle()
{
    hidden = !hidden;
}

void Tab::show()
{
    hidden = false;
}

void Tab::hide()
{
    hidden = true;
}
