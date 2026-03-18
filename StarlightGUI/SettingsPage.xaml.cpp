#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

#include "Utils/Config.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::Windows::Storage::Pickers;

namespace winrt::StarlightGUI::implementation
{
    static bool loaded;

    SettingsPage::SettingsPage()
    {
        InitializeComponent();
        InitializeOptions();
    }

    void SettingsPage::InitializeOptions() {
        if (enum_file_mode == "ENUM_FILE_IRP") {
            EnumFileModeComboBox().SelectedIndex(1);
        }
        else if (enum_file_mode == "ENUM_FILE_NTFSPARSER") {
            EnumFileModeComboBox().SelectedIndex(2);
        }
        else {
            EnumFileModeComboBox().SelectedIndex(0);
        }

        if (background_type == "Mica") {
            BackgroundComboBox().SelectedIndex(1);
        }
        else if (background_type == "Acrylic") {
            BackgroundComboBox().SelectedIndex(2);
        }
        else {
            BackgroundComboBox().SelectedIndex(0);
        }

        if (navigation_style == "Left") {
            NavigationComboBox().SelectedIndex(1);
        }
        else if (navigation_style == "Top") {
            NavigationComboBox().SelectedIndex(2);
        }
        else {
            NavigationComboBox().SelectedIndex(0);
        }

        if (mica_type == "Base") {
            MicaTypeComboBox().SelectedIndex(1);
        }
        else {
            MicaTypeComboBox().SelectedIndex(0);
        }

        if (acrylic_type == "Base") {
            AcrylicTypeComboBox().SelectedIndex(1);
        }
        else if (acrylic_type == "Thin") {
            AcrylicTypeComboBox().SelectedIndex(2);
        }
        else {
            AcrylicTypeComboBox().SelectedIndex(0);
        }

        if (image_stretch == "None") {
            ImageStretchComboBox().SelectedIndex(0);
        }
        else if (image_stretch == "Fill") {
            ImageStretchComboBox().SelectedIndex(1);
        }
        else if (image_stretch == "Uniform") {
            ImageStretchComboBox().SelectedIndex(2);
        } 
        else {
            ImageStretchComboBox().SelectedIndex(3);
        }

        EnumStrengthenButton().IsOn(enum_strengthen);
        PDHFirstButton().IsOn(pdh_first);
		ListRevealFocusButton().IsOn(list_revealfocus);
		ElevatedRunButton().IsOn(elevated_run);
        DangerousConfirmButton().IsOn(dangerous_confirm);
        CheckUpdateButton().IsOn(check_update);

        ImagePathText().Text(to_hstring(background_image));
        ImageOpacitySlider().Value(image_opacity);
		DisasmCountSlider().Value(disasm_count);
    }

    void SettingsPage::EnumFileModeComboBox_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        if (slg::CheckIllegalComboBoxAction(sender, e)) return;

        if (EnumFileModeComboBox().SelectedIndex() == 1)
        {
            enum_file_mode = "ENUM_FILE_IRP";
        }
        else if (EnumFileModeComboBox().SelectedIndex() == 2)
        {
            enum_file_mode = "ENUM_FILE_NTFSPARSER";
        }
        else
        {
            enum_file_mode = "ENUM_FILE_NTAPI";
        }
        SaveConfig("enum_file_mode", enum_file_mode);
    }

    void SettingsPage::EnumStrengthenButton_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (!IsLoaded()) return;
		enum_strengthen = EnumStrengthenButton().IsOn();
        SaveConfig("enum_strengthen", enum_strengthen);
    }

    void SettingsPage::PDHFirstButton_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (!IsLoaded()) return;
        pdh_first = PDHFirstButton().IsOn();
        SaveConfig("pdh_first", pdh_first);
    }

    void SettingsPage::BackgroundComboBox_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        if (slg::CheckIllegalComboBoxAction(sender, e)) return;

        if (BackgroundComboBox().SelectedIndex() == 1)
        {
            background_type = "Mica";
        }
        else if (BackgroundComboBox().SelectedIndex() == 2)
        {
            background_type = "Acrylic";
        }
        else 
        {
            background_type = "Static";
        }
        SaveConfig("background_type", background_type);

        g_mainWindowInstance->LoadBackdrop();

        Console::GetInstance().SetBackdropByConfig();
    }

    void SettingsPage::MicaTypeComboBox_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        if (slg::CheckIllegalComboBoxAction(sender, e)) return;

        if (MicaTypeComboBox().SelectedIndex() == 0)
        {
            mica_type = "Base";
        }
        else
        {
            mica_type = "BaseAlt";
        }

        SaveConfig("mica_type", mica_type);

        g_mainWindowInstance->LoadBackdrop();
    }

    void SettingsPage::AcrylicTypeComboBox_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        if (slg::CheckIllegalComboBoxAction(sender, e)) return;

        if (AcrylicTypeComboBox().SelectedIndex() == 1)
        {
            acrylic_type = "Base";
        }
        else if (AcrylicTypeComboBox().SelectedIndex() == 2) 
        {
            acrylic_type = "Thin";
        }
        else
        {
            acrylic_type = "Default";
        }

        SaveConfig("acrylic_type", acrylic_type);

        g_mainWindowInstance->LoadBackdrop();
    }
    
    void SettingsPage::NavigationComboBox_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        if (slg::CheckIllegalComboBoxAction(sender, e)) return;

        if (NavigationComboBox().SelectedIndex() == 1)
        {
            navigation_style = "Left";
        }
        else if (NavigationComboBox().SelectedIndex() == 2)
        {
            navigation_style = "Top";
        }
        else 
        {
            navigation_style = "LeftCompact";
        }
        SaveConfig("navigation_style", navigation_style);

        g_mainWindowInstance->LoadNavigation();
    }

    void SettingsPage::ListRevealFocusButton_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        list_revealfocus = ListRevealFocusButton().IsOn();
        SaveConfig("list_revealfocus", list_revealfocus);
    }

    void SettingsPage::ElevatedRunButton_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        slg::CreateInfoBarAndDisplay(L"提示", L"该设置需要重启以生效!", InfoBarSeverity::Informational, g_mainWindowInstance);
        elevated_run = ElevatedRunButton().IsOn();
        SaveConfig("elevated_run", elevated_run);
    }

    void SettingsPage::DangerousConfirmButton_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        dangerous_confirm = DangerousConfirmButton().IsOn();
        SaveConfig("dangerous_confirm", dangerous_confirm);
    }

    void SettingsPage::CheckUpdateButton_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (!IsLoaded()) return;
		slg::CreateInfoBarAndDisplay(L"提示", L"该设置需要重启以生效!", InfoBarSeverity::Informational, g_mainWindowInstance);
        check_update = CheckUpdateButton().IsOn();
        SaveConfig("check_update", check_update);
    }

    void SettingsPage::ClearImageButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (!IsLoaded()) return;
        SaveConfig("background_image", "");
        ImagePathText().Text(L"");

        g_mainWindowInstance->LoadBackground();
    }

    slg::coroutine SettingsPage::SetImageButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (!IsLoaded()) co_return;
        HWND hWnd = g_mainWindowInstance->GetWindowHandle();

        FileOpenPicker picker = FileOpenPicker(winrt::Microsoft::UI::GetWindowIdFromWindow(hWnd));

        picker.SuggestedStartLocation(PickerLocationId::ComputerFolder);
        picker.FileTypeFilter().Append(L".png");
        picker.FileTypeFilter().Append(L".jpg");
        picker.FileTypeFilter().Append(L".bmp");
        picker.FileTypeFilter().Append(L".jpeg");

        auto result = co_await picker.PickSingleFileAsync();

        if (!result) co_return;

        try {
            auto file = co_await StorageFile::GetFileFromPathAsync(result.Path());

            if (file && file.IsAvailable() && (file.FileType() == L".png" || file.FileType() == L".jpg" || file.FileType() == L".bmp" || file.FileType() == L".jpeg")) {
                std::string path = WideStringToString(file.Path().c_str());
                SaveConfig("background_image", path);
                ImagePathText().Text(to_hstring(background_image));

                g_mainWindowInstance->LoadBackground();
            }
        }
        catch (hresult_error) {

        }
    }


    void SettingsPage::RefreshOpacityButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (!IsLoaded()) return;
        g_mainWindowInstance->LoadBackground();
    }

    void SettingsPage::ImageStretchComboBox_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        if (slg::CheckIllegalComboBoxAction(sender, e)) return;

        if (ImageStretchComboBox().SelectedIndex() == 0)
        {
            image_stretch = "None";
        }
        else if (ImageStretchComboBox().SelectedIndex() == 1)
        {
            image_stretch = "Fill";
        }
        else if (ImageStretchComboBox().SelectedIndex() == 2)
        {
            image_stretch = "Uniform";
        }
        else
        {
            image_stretch = "UniformToFill";
        }
        SaveConfig("image_stretch", image_stretch);

        g_mainWindowInstance->LoadBackground();
    }

    void SettingsPage::LogButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        LOGGER_TOGGLE();
    }

    void SettingsPage::FixButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        slg::CreateInfoBarAndDisplay(L"提示", L"该设置需要重启以生效!", InfoBarSeverity::Informational, g_mainWindowInstance);
        DriverUtils::FixServices();
    }

    void SettingsPage::ImageOpacitySlider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        SaveConfig("image_opacity", ImageOpacitySlider().Value());
    }

    void SettingsPage::DisasmCountSlider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
    {
        if (!IsLoaded()) return;
        SaveConfig("disasm_count", DisasmCountSlider().Value());
    }
}
