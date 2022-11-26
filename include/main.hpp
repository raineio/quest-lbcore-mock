#pragma once

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "modloader/shared/modloader.hpp"

// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

// Define these functions here so that we can easily read configuration and log information from other files
Configuration& getConfig();

namespace Wasureta {
    class CustomLeaderboardManager {
        CustomLeaderboardManager();
        ~CustomLeaderboardManager();

        static void OnLeaderboardsChange();

        void Register(const ModInfo &modInfo = {MOD_ID, VERSION});

        void Unregister(const ModInfo &modInfo = {MOD_ID, VERSION});
    };

    class CustomLeaderboard {
        void Show();

        void Hide();
    };

    class INotifyCustomLeaderboardsChange {
    public:
        void OnLeaderboardsChanged(std::span<CustomLeaderboard *> orderedCustomLeaderboards,
                                   std::unordered_map<std::string, CustomLeaderboard>);
    };
}
