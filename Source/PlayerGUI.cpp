#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    addAndMakeVisible(loadButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(restartButton);
    addAndMakeVisible(muteButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(volumeSlider);

    loadButton.addListener(this);
    playButton.addListener(this);
    stopButton.addListener(this);
    restartButton.addListener(this);
    muteButton.addListener(this);
    loopButton.addListener(this);
    volumeSlider.addListener(this);

    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(1.0);
}

PlayerGUI::~PlayerGUI() {}

void PlayerGUI::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto buttonHeight = 30;
    loadButton.setBounds(area.removeFromTop(buttonHeight));
    playButton.setBounds(area.removeFromTop(buttonHeight));
    stopButton.setBounds(area.removeFromTop(buttonHeight));
    restartButton.setBounds(area.removeFromTop(buttonHeight));
    muteButton.setBounds(area.removeFromTop(buttonHeight));
    loopButton.setBounds(area.removeFromTop(buttonHeight));
    volumeSlider.setBounds(area.removeFromTop(buttonHeight));
}

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>("Select an audio file...");
        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& chooser)
            {
                auto result = chooser.getResult();
                if (result.existsAsFile())
                    playerAudio.loadFile(result);
            });
    }
    else if (button == &playButton)
    {
        playerAudio.play();
    }
    else if (button == &stopButton)
    {
        playerAudio.stop();
    }
    else if (button == &restartButton)
    {
        playerAudio.setPosition(0.0);
        playerAudio.play();
    }
    else if (button == &muteButton)
    {
        if (!isMuted)
        {
            lastGain = volumeSlider.getValue();
            playerAudio.setGain(0.0f);
            isMuted = true;
        }
        else
        {
            playerAudio.setGain(lastGain);
            isMuted = false;
        }
    }
    else if (button == &loopButton)
    {
        loopActive = !loopActive;
        playerAudio.setLoop(loopActive);
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain(static_cast<float>(slider->getValue()));
}
