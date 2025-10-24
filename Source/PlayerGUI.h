#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

// ==================================================
// PlayerGUI: مسؤول عن واجهة المستخدم (الأزرار، السلايدر)
// يتواصل مع PlayerAudio فقط لتشغيل الصوت
// ==================================================
class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void resized() override;  // تحديد أماكن الأزرار والسلايدر

    // واجهات تشغيل الصوت
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

private:
    PlayerAudio playerAudio; // عنصر الصوت

    // عناصر الواجهة
    juce::TextButton loadButton{ "Load File" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton muteButton{ "Mute" };
    juce::TextButton loopButton{ "Loop" };
    juce::Slider volumeSlider;

    std::unique_ptr<juce::FileChooser> fileChooser;

    // التعامل مع الأزرار والسلايدر
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

    bool isMuted = false;
    float lastGain = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
