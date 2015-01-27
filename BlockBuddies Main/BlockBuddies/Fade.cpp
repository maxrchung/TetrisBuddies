#include "Fade.hpp"

Fade::Fade()
{
}

// Fade only updates if it is currently fading in or
// fading out. Set the Fade's state from outside and 
// fade will start updating on its own. Grab the Fade's
// value while it's updating and use it to change the
// opacity of objects.
//
// Right now, the update merely ++'s or --'s respectively,
// and if we want it more complicated, we can pass in
// duration values or whatnot.
//
// Once the fade is finished fading, check the state to see
// if it is FADED_IN or FADED_OUT accordingly and act on it
void Fade::update()
{
    // Raises opacity until it hits 255
    if(state == FadeStates::FADING_IN)
    {
        value += 16;
        if(value >= 255)
        {
            value = 255; // For safety
            state = FadeStates::FADED_IN;
        }
    }
    // Lowers opacity until it hits 0
    else if(state == FadeStates::FADING_OUT)
    {
        value -= 16;
        if(value <= 0)
        {
            value = 0;
            state = FadeStates::FADED_OUT;
        }
    }
}