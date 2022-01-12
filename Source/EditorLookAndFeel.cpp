#include "EditorLookAndFeel.hpp"
#include "EditorColours.hpp"
#include "FormulaButton.hpp"
#include "Knob.hpp"

namespace
{

const auto CornerSize = 10.0F;
const auto LineThickness = 3.0F;
const auto margin = 10.0F;

} // namespace

EditorLookAndFeel::EditorLookAndFeel()
{
    setDefaultSansSerifTypeface(getMainFont());

    setColour(TextEditor::backgroundColourId, Colours::white);
    setColour(TextEditor::textColourId, Colours::black);
}

const Typeface::Ptr EditorLookAndFeel::getMainFont()
{
    static auto typeface =
        Typeface::createSystemTypefaceFor(BinaryData::RubikRegular_ttf, BinaryData::RubikRegular_ttfSize);

    return typeface;
}

const Typeface::Ptr EditorLookAndFeel::getValueRegularFont()
{
    static auto typeface =
        Typeface::createSystemTypefaceFor(BinaryData::ShareRegular_ttf, BinaryData::ShareRegular_ttfSize);

    return typeface;
}

const Typeface::Ptr EditorLookAndFeel::getValueMonospaceFont()
{
    static auto typeface = Typeface::createSystemTypefaceFor(BinaryData::ShareTechMonoRegular_ttf,
                                                             BinaryData::ShareTechMonoRegular_ttfSize);

    return typeface;
}

Typeface::Ptr EditorLookAndFeel::getTypefaceForFont(const Font &)
{
    return getMainFont();
}

void EditorLookAndFeel::drawRotarySlider(Graphics &gfx, int x, int y, int width, int height,
                                         float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                                         Slider &slider)
{
    const auto margin = 5.0F;

    // rotary angles and positions

    const auto rotaryOffset = 0.25F;
    rotaryStartAngle = (1.0F + rotaryOffset) * MathConstants<float>::pi;
    rotaryEndAngle = (3.0F - rotaryOffset) * MathConstants<float>::pi;

    const auto rotaryRange = rotaryEndAngle - rotaryStartAngle;
    const auto sliderPos = rotaryStartAngle + rotaryRange * sliderPosProportional;

    // rotary geometry

    const auto radius = jmin(width / 2, height / 2);
    const auto centreX = x + width * 0.5F;
    const auto centreY = y + height * 0.5F;
    const auto rx = centreX - radius;
    const auto ry = centreY - radius;
    const auto rw = radius * 2.0F;

    // value slider

    auto valueSliderStart = rotaryStartAngle;
    auto valueSliderEnd = sliderPos;

    if (slider.getMinimum() < 0.0 && slider.getMaximum() > 0.0)
    {
        valueSliderStart = slider.getValue() < 0.0 ? sliderPos : MathConstants<float>::twoPi;
        valueSliderEnd = slider.getValue() < 0.0 ? MathConstants<float>::twoPi : sliderPos;
    }

    Path completeArc;
    completeArc.addArc(rx + margin, ry + margin, rw - 2 * margin, rw - 2 * margin, rotaryStartAngle, rotaryEndAngle,
                       true);

    gfx.setColour(EditorColours::RaisinBlack);
    gfx.strokePath(completeArc, PathStrokeType(LineThickness, PathStrokeType::JointStyle::curved,
                                               PathStrokeType::EndCapStyle::rounded));

    Path sliderArc;
    sliderArc.addArc(rx + margin, ry + margin, rw - 2 * margin, rw - 2 * margin, valueSliderStart, valueSliderEnd,
                     true);

    gfx.setColour(EditorColours::ViridianGreen);
    gfx.strokePath(sliderArc, PathStrokeType(LineThickness, PathStrokeType::JointStyle::curved,
                                             PathStrokeType::EndCapStyle::rounded));

    // draw inner knob

    const auto knobX = rx + margin * 2.0;
    const auto knobY = ry + margin * 2.0;
    const auto knobSize = rw - 4.0 * margin;

    const ColourGradient knobGradient(EditorColours::RaisinBlack, knobX, knobY, EditorColours::BlackCoffee, knobSize,
                                      knobSize, true);

    gfx.setGradientFill(knobGradient);
    gfx.fillEllipse(knobX, knobY, knobSize, knobSize);

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawEllipse(knobX, knobY, knobSize, knobSize, LineThickness);

    // draw indicator

    const auto indicatorLength = radius - 3.0F * margin;

    const auto sliderX =
        cos(sliderPos + rotaryStartAngle + rotaryOffset * MathConstants<float>::pi) * indicatorLength + centreX;
    const auto sliderY =
        sin(sliderPos + rotaryStartAngle + rotaryOffset * MathConstants<float>::pi) * indicatorLength + centreY;

    Path indicator;
    indicator.startNewSubPath(centreX, centreY);
    indicator.lineTo(sliderX, sliderY);

    const ColourGradient indicatorGradient(EditorColours::ViridianGreen.brighter(), centreX, centreY,
                                           EditorColours::ViridianGreen, sliderX, sliderY, true);

    gfx.setGradientFill(indicatorGradient);
    gfx.strokePath(indicator, PathStrokeType(LineThickness, PathStrokeType::JointStyle::curved,
                                             PathStrokeType::EndCapStyle::rounded));

    // draw label if set

    if (const auto *knob = dynamic_cast<const Knob *>(&slider))
    {
        const String label = knob->getLabel();
        if (!label.isEmpty())
        {
            gfx.setFont(getMainFont());
            gfx.setFont(12.0F);
            gfx.setColour(EditorColours::ParadisePink);

            gfx.drawFittedText(label, 0, 0, width, height, Justification::centredBottom, 1);
        }
    }
}

Label *EditorLookAndFeel::createSliderTextBox(Slider &slider)
{
    const auto label = new Label();

    label->setJustificationType(Justification::centred);
    label->setKeyboardType(TextInputTarget::decimalKeyboard);
    label->setLookAndFeel(this);

    return label;
}

Slider::SliderLayout EditorLookAndFeel::getSliderLayout(Slider &slider)
{
    juce::Slider::SliderLayout layout = juce::LookAndFeel_V4::getSliderLayout(slider);

    const auto localBounds = slider.getLocalBounds();
    const auto textBoxWidth = layout.textBoxBounds.getWidth();
    const auto textBoxHeight = layout.textBoxBounds.getHeight();

    layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);
    layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);

    return layout;
}

void EditorLookAndFeel::drawButtonBackground(Graphics &gfx, Button &button, const Colour &backgroundColour,
                                             bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    if (const auto *fb = dynamic_cast<FormulaButton *>(&button))
    {
        return; // no background
    }

    LookAndFeel_V4::drawButtonBackground(gfx, button, backgroundColour, shouldDrawButtonAsHighlighted,
                                         shouldDrawButtonAsDown);
}

void EditorLookAndFeel::drawGroupComponentOutline(Graphics &gfx, int width, int height, const String &text,
                                                  const Justification &j, GroupComponent &groupComponent)
{
    const auto rectangle = Rectangle<int>{0, 0, width, height};

    // fill rectangle depending on type
    /* if (const auto *synthatorGroupComponent = dynamic_cast<SynthatorGroupComponent *>(&groupComponent))
     {
         const ColourGradient groupComponentGradient(EditorColours::Steel, 0.0F, 0.0F, EditorColours::Tungsten, 0.0F,
                                                     height, false);
         gfx.setGradientFill(groupComponentGradient);
     }
     else if (const auto *synthatorButtonGroupComponent = dynamic_cast<SynthatorButtonGroupComponent
     *>(&groupComponent))
     {
         gfx.setColour(EditorColours::Steel);
     }
     else
     {
         gfx.setColour(EditorColours::Tungsten);
     }*/

    gfx.fillRect(rectangle);

    // outline rectangle
    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawRect(rectangle, 1.0F);
}

void EditorLookAndFeel::drawLabel(Graphics &gfx, Label &label)
{
    gfx.setColour(EditorColours::Platinum);

    float valueOffsetY = 0.0F;

    if (const auto *knob = dynamic_cast<const Knob *>(label.getParentComponent()))
    {
        const String unit = knob->getUnit();
        if (!unit.isEmpty())
        {
            Font unitFont(getMainFont());
            unitFont.setHeight(10.0F);
            gfx.setFont(unitFont);

            gfx.drawFittedText(unit, 0, 8, label.getWidth(), label.getHeight(), label.getJustificationType(), 1);

            valueOffsetY = -4.0F;
        }
    }

    Font valueFont(getMainFont());
    valueFont.setHeight(12.0F);

    gfx.setFont(valueFont);
    gfx.drawFittedText(label.getText(), 0, valueOffsetY, label.getWidth(), label.getHeight(),
                       label.getJustificationType(), 1);
}

Font EditorLookAndFeel::getLabelFont(Label &label)
{
    return getMainFont();
}

Font EditorLookAndFeel::getTextButtonFont(TextButton &textButton, int buttonHeight)
{
    ignoreUnused(textButton);

    Font buttonFont(getMainFont());
    buttonFont.setHeight(14.0F);

    return buttonFont;
}

BorderSize<int> EditorLookAndFeel::getLabelBorderSize(Label &l)
{
    return LookAndFeel_V4::getLabelBorderSize(l);
}
