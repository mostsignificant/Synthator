#include "Knob.hpp"

Knob::Knob(String label, String unit) : label(label), unit(unit)
{
    setSliderStyle(Slider::SliderStyle::Rotary);
}

String Knob::getLabel() const
{
    return label;
}

String Knob::getUnit() const
{
    return unit;
}

void Knob::setLabel(String label)
{
    this->label = label;
}

void Knob::setUnit(String unit)
{
    this->unit = unit;
}
