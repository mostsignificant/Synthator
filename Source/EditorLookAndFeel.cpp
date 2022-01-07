#include "EditorLookAndFeel.hpp"
#include "Knob.hpp"

EditorLookAndFeel::EditorLookAndFeel()
{
    setDefaultSansSerifTypeface(getLabelFont());

    setColour(TextEditor::backgroundColourId, Colours::white);
    setColour(TextEditor::textColourId, Colours::black);
}

const Typeface::Ptr EditorLookAndFeel::getLabelFont()
{
    static auto typeface = Typeface::createSystemTypefaceFor(BinaryData::RubikRegular_ttf,
                                                             BinaryData::RubikRegular_ttfSize);

    return typeface;
}

const Typeface::Ptr EditorLookAndFeel::getValueRegularFont()
{
    static auto typeface = Typeface::createSystemTypefaceFor(BinaryData::ShareRegular_ttf,
                                                             BinaryData::ShareRegular_ttfSize);

    return typeface;
}

const Typeface::Ptr EditorLookAndFeel::getValueMonospaceFont()
{
    static auto typeface = Typeface::createSystemTypefaceFor(
        BinaryData::ShareTechMonoRegular_ttf, BinaryData::ShareTechMonoRegular_ttfSize);

    return typeface;
}

Typeface::Ptr EditorLookAndFeel::getTypefaceForFont(const Font &)
{
    return getLabelFont();
}

void EditorLookAndFeel::drawRotarySlider(Graphics &gfx, int x, int y, int width, int height,
                                         float sliderPosProportional, float rotaryStartAngle,
                                         float rotaryEndAngle, Slider &slider)
{
    // rotary angles and positions

    rotaryStartAngle = 1.15 * MathConstants<float>::pi;
    rotaryEndAngle = 2.85 * MathConstants<float>::pi;

    const auto rotaryRange = rotaryEndAngle - rotaryStartAngle;
    const auto sliderPos = rotaryStartAngle + rotaryRange * sliderPosProportional;

    // rotary geometry

    const auto radius = jmin(width / 2, height / 2);
    const auto centreX = x + width * 0.5F;
    const auto centreY = y + height * 0.5F;
    const auto rx = centreX - radius;
    const auto ry = centreY - radius;
    const auto rw = radius * 2.0F;
    const auto angle = rotaryStartAngle + sliderPosProportional * rotaryRange;
}