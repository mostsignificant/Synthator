#pragma once

#include <JuceHeader.h>

class EditorLookAndFeel : public LookAndFeel_V4
{
public:
    EditorLookAndFeel();
    
    static const Typeface::Ptr getCustomFont();
    
private:
    Typeface::Ptr getTypefaceForFont (const Font& f) override;
};
