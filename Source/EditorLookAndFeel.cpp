#include "EditorLookAndFeel.hpp"

EditorLookAndFeel::EditorLookAndFeel()
{
    setDefaultSansSerifTypeface (getCustomFont());
        
    setColour(TextEditor::backgroundColourId, Colours::white);
    setColour(TextEditor::textColourId,       Colours::black);
}

const Typeface::Ptr EditorLookAndFeel::getCustomFont()
{
    static auto customTypeface =
        Typeface::createSystemTypefaceFor (BinaryData::ShareTechMonoRegular_ttf,
                                           BinaryData::ShareTechMonoRegular_ttfSize);
    
    return customTypeface;
}

Typeface::Ptr EditorLookAndFeel::getTypefaceForFont (const Font&)
{
    return getCustomFont();
}
