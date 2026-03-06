#pragma once

#include <pch.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <string>
#include <locale>
#include <codecvt>

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace winrt::StarlightGUI::implementation {
    void InitializeConfig();

    template<typename T>
    void SaveConfig(std::string key, T s_value) {
        static char* value = NULL;
        size_t len = 0;
        try
        {
            // 获取用户文件夹路径
            if (value == NULL) _dupenv_s(&value, &len, "USERPROFILE");

            auto userFolder = fs::path(value);
            auto configFilePath = userFolder / "StarlightGUI.json";
            json configData;

            if (fs::exists(configFilePath))
            {
                std::ifstream configFile(configFilePath);
                configFile >> configData;
            }

            configData[key] = s_value;

            std::ofstream configFile(configFilePath);
            configFile << configData.dump(4);
        }
        catch (...)
        {
        }
        InitializeConfig();
    }

    template<typename T>
    auto ReadConfig(std::string key, T defaultValue) {
        static char* value = NULL;
        size_t len = 0;
        try
        {
            // 获取用户文件夹路径
            if (value == NULL) _dupenv_s(&value, &len, "USERPROFILE");

            auto userFolder = fs::path(value);
            auto configFilePath = userFolder / "StarlightGUI.json";

            if (fs::exists(configFilePath))
            {
                std::ifstream configFile(configFilePath);
                json configData;
                configFile >> configData;

                if (configData.contains(key))
                {
                    return configData[key];
                }
            }
        }
        catch (...)
        {
            SaveConfig(key, defaultValue);
            return ReadConfig(key, defaultValue);
        }

        SaveConfig(key, defaultValue);
        return ReadConfig(key, defaultValue);
    }
}