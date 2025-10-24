#pragma once

#include <JuceHeader.h>
#include "PlayerGUI.h"

// MainComponent class
// مسؤول عن عرض PlayerGUI وتشغيل الصوت
class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    PlayerGUI playerGUI; // واجهة جديدة مع كل الأزرار والميزات

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
