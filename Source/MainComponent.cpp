#include "MainComponent.h"

// Constructor
MainComponent::MainComponent()
{
    // تسجيل صيغ الملفات الصوتية الأساسية (WAV, MP3, إلخ)
    formatManager.registerBasicFormats();

    // إضافة الأزرار إلى الواجهة وربط الأحداث
    for (auto* btn : { &loadButton, &restartButton , &stopButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // إعداد شريط الصوت (Volume)
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // إعداد حجم النافذة وقنوات الصوت
    setSize(500, 250);
    setAudioChannels(0, 2); // 0 input, 2 output
}

// Destructor
MainComponent::~MainComponent()
{
    shutdownAudio(); // تنظيف الموارد الصوتية
}

// إعدادات التشغيل قبل بدء الصوت
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

// تحديث بيانات الصوت في كل إطار
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    transportSource.getNextAudioBlock(bufferToFill);
}

// تحرير الموارد عند إغلاق البرنامج
void MainComponent::releaseResources()
{
    transportSource.releaseResources();
}

// رسم الواجهة
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

// ضبط موقع وحجم عناصر الواجهة عند تغيير حجم النافذة
void MainComponent::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 40);
    restartButton.setBounds(140, y, 80, 40);
    stopButton.setBounds(240, y, 80, 40);

    volumeSlider.setBounds(20, 100, getWidth() - 40, 30);
}

// التعامل مع ضغط الأزرار
void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file.existsAsFile())
                {
                    if (auto* reader = formatManager.createReaderFor(file))
                    {
                        // فصل المصدر القديم أولاً
                        transportSource.stop();
                        transportSource.setSource(nullptr);
                        readerSource.reset();

                        // إنشاء مصدر قارئ جديد
                        readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

                        // ربطه مع مشغل الصوت
                        transportSource.setSource(readerSource.get(),
                            0,
                            nullptr,
                            reader->sampleRate);
                        transportSource.start();
                    }
                }
            });
    }

    if (button == &restartButton)
    {
        transportSource.start();
    }

    if (button == &stopButton)
    {
        transportSource.stop();
        transportSource.setPosition(0.0);
    }
}

// التعامل مع تغييرات شريط الصوت
void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        transportSource.setGain((float)slider->getValue());
}
