#include "pch.h"
#include "Config.h"

namespace winrt::StarlightGUI::implementation {

    void InitializeConfig() {
        enum_file_mode = ReadConfig("enum_file_mode", "ENUM_FILE_NTAPI");
        enum_strengthen = ReadConfig("enum_strengthen", false);
        pdh_first = ReadConfig("pdh_first", true);
        background_type = ReadConfig("background_type", "Static");
        mica_type = ReadConfig("mica_type", "BaseAlt");
        acrylic_type = ReadConfig("acrylic_type", "Default");
		list_revealfocus = ReadConfig("list_revealfocus", true);
        elevated_run = ReadConfig("elevated_run", false);
        dangerous_confirm = ReadConfig("dangerous_confirm", true);
        check_update = ReadConfig("check_update", true);
        navigation_style = ReadConfig("navigation_style", "LeftCompact");
        background_image = ReadConfig("background_image", "");
        image_opacity = ReadConfig("image_opacity", 20);
        image_stretch = ReadConfig("image_stretch", "UniformToFill");
		disasm_count = ReadConfig("disasm_count", 16);
    }
}