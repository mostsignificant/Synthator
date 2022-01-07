#pragma once

#include <JuceHeader.h>

class EditorLookAndFeel : public LookAndFeel_V4
{
public:
    EditorLookAndFeel();

    static const Typeface::Ptr getLabelFont();
    static const Typeface::Ptr getValueRegularFont();
    static const Typeface::Ptr getValueMonospaceFont();

    void drawRotarySlider(Graphics &gfx, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          Slider &slider) override;

private:
    Typeface::Ptr getTypefaceForFont(const Font &f) override;
};
