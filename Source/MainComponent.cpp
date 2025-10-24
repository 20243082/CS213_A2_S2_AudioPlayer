#include "MainComponent.h"

// Constructor
MainComponent::MainComponent()
{
    // إضافة PlayerGUI للنافذة
    addAndMakeVisible(playerGUI);

    // إعداد حجم النافذة وقنوات الصوت
    setSize(600, 300);
    setAudioChannels(0, 2); // 0 input, 2 output
}

// Destructor
MainComponent::~MainComponent()
{
    shutdownAudio(); // تنظيف الموارد الصوتية
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerGUI.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerGUI.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    playerGUI.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    // PlayerGUI يغطي كل مساحة النافذة
    playerGUI.setBounds(getLocalBounds());
}
