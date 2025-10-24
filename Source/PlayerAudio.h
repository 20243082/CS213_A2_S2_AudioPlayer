#pragma once
#include <JuceHeader.h>

// ==================================================
// PlayerAudio: مسؤول عن تشغيل الصوت والتحكم فيه
// لا يحتوي على أي عناصر واجهة (GUI)
// ==================================================
class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    // تحميل ملف صوتي
    bool loadFile(const juce::File& file);

    // التحكم بالتشغيل
    void play();
    void stop();

    // التحكم بالمستوى (Gain) والمكان (Position)
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;

    // دوال JUCE للتعامل مع البلوك الصوتي
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

private:
    juce::AudioFormatManager formatManager;                       // يدير أنواع الملفات الصوتية
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;  // مصدر بيانات الصوت
    juce::AudioTransportSource transportSource;                  // مسؤول عن التشغيل والتحكم
};
