#pragma once

#include <JuceHeader.h>

class Knob : public Slider
{
public:
    Knob(String label = "", String unit = "");

    String getLabel() const;
    String getUnit() const;
    void setLabel(String label);
    void setUnit(String unit);

private:
    String label;
    String unit;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};
