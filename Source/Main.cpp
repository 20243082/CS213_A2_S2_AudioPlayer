#include <JuceHeader.h>
#include "MainComponent.h"

// Our application class
class SimpleAudioPlayer : public juce::JUCEApplication
{
public:
    // اسم البرنامج وإصداره
    const juce::String getApplicationName() override { return "Simple Audio Player"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    // دالة البداية: إنشاء واظهار النافذة الرئيسية
    void initialise(const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    // دالة إنهاء البرنامج
    void shutdown() override
    {
        mainWindow = nullptr; // تنظيف الموارد
    }

private:
    // النافذة الرئيسية للتطبيق
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name)
            : DocumentWindow(name,
                juce::Colours::lightgrey,
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true); // MainComponent = الواجهة + المنطق
            centreWithSize(400, 200);                     // وضع النافذة في منتصف الشاشة
            setVisible(true);
        }

        // دالة عند الضغط على زر الإغلاق
        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

    std::unique_ptr<MainWindow> mainWindow; // مؤشر للنافذة
};

// هذا الماكرو يقوم بتشغيل البرنامج
START_JUCE_APPLICATION(SimpleAudioPlayer)
