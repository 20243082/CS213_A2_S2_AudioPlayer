#pragma once

#include <JuceHeader.h>
#include <vector>

// MainComponent class
// مسؤول عن إدارة الصوت والواجهة معاً
class MainComponent : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    MainComponent();   // Constructor
    ~MainComponent() override; // Destructor

    // دوال الصوت
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // دوال الواجهة
    void paint(juce::Graphics& g) override;
    void resized() override;

    // دوال التعامل مع الأحداث
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // إدارة الصوت
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    // عناصر الواجهة
    juce::TextButton loadButton{ "Load Files" };      // زر تحميل الملف
    juce::TextButton restartButton{ "Restart" };      // زر إعادة التشغيل
    juce::TextButton stopButton{ "Stop" };            // زر الإيقاف
    juce::Slider volumeSlider;                          // شريط الصوت

    std::unique_ptr<juce::FileChooser> fileChooser;    // لاختيار الملفات

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
