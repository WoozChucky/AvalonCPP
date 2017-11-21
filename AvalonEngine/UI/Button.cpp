#include "Button.hpp"

av::ui::Button::Button()
{

}

void av::ui::Button::setOnClick(void(* callback)()) {

    // This executes something, I guess
    callback();
}