#ifndef FADE_HPP
#define FADE_HPP

// States describing what state the fade currently is
enum FadeStates
{
    FADING_IN,
    FADED_IN,
    FADING_OUT,
    FADED_OUT
};

// Class that handles fading
class Fade
{
public:
    Fade(int limit = 255);

    // Updates the fade value frame by frame depending on its state
    void update();

    // What's the max limit of the fade
    int limit;

    // Start everything as hidden
    int value = 0;
    FadeStates state;
};

#endif//FADE_HPP