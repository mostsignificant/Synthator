#pragma once

#include <JuceHeader.h>

class EditorLookAndFeel : public LookAndFeel_V4
{
public:
    EditorLookAndFeel();

    static const Typeface::Ptr getMainFont();
    static const Typeface::Ptr getValueRegularFont();
    static const Typeface::Ptr getValueMonospaceFont();

    Label *createSliderTextBox(Slider &slider) override;

    void drawButtonBackground(Graphics &gfx, Button &button, const Colour &backgroundColour,
                              bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawGroupComponentOutline(Graphics &gfx, int width, int height, const String &text,
                                   const Justification &justification, GroupComponent &canvasroupComponent) override;
    void drawLabel(Graphics &gfx, Label &label) override;
    void drawRotarySlider(Graphics &gfx, int x, int y, int width, int height, float sliderPosProportional,
                          float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override;

    BorderSize<int> getLabelBorderSize(Label &label) override;
    Font getLabelFont(Label &label) override;
    Font getTextButtonFont(TextButton &textButton, int buttonHeight) override;
    Slider::SliderLayout getSliderLayout(Slider &slider) override;

private:
    Typeface::Ptr getTypefaceForFont(const Font &f) override;
};
