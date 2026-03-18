#include "pch.h"
#include "Utils/Config.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;


namespace winrt::StarlightGUI::implementation
{
    App::App()
    {

        UnhandledException([](winrt::Windows::Foundation::IInspectable const&,
            winrt::Microsoft::UI::Xaml::UnhandledExceptionEventArgs const& e)
            {
                LOG_ERROR(L"App", L"===== Unhandled exception detected! =====");
                LOG_ERROR(L"App", L"Type: 'winrt::hresult_error'");
                LOG_ERROR(L"App", L"Code: %d", e.Exception().value);
                LOG_ERROR(L"App", L"Message: %s", e.Message().c_str());
                LOG_ERROR(L"App", L"=========================================");
                e.Handled(true);
            });
    }

    void App::OnLaunched(LaunchActivatedEventArgs const&)
    {
        InitializeConfig();
        InitializeLogger();
        if (elevated_run) {
            if (ReadConfig("elevated_run_tried", true)) {
                SaveConfig("elevated_run_tried", false);
                LOG_INFO(L"", L"Running as TrustedInstaller!");
            }
            else {
                SaveConfig("elevated_run_tried", true);
                if (CreateProcessElevated(GetExecutablePath(), true)) {
                    Exit();
                    return;
                }
                else {
                    LOG_ERROR(L"", L"Failed to run as TrustedInstaller! See log for more information.");
                }
            }
        }
        window = make<MainWindow>();
        window.Activate();
    }

    void App::InitializeLogger() {
        LOGGER_INIT();
        LOG_INFO(L"", L"Launching Starlight GUI...");
    }
}
