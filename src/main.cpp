#include "main.hpp"
#include "custom-types/shared/register.hpp"
#include "logger.h"
#include "hooking.h"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include <vector>
#include <unordered_map>
#include <fmt/format.h>

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}


namespace Wasureta {

    std::vector<Wasureta::INotifyCustomLeaderboardsChange *> _notifyCustomLeaderboardsChanges;
    std::unordered_map<std::string, Wasureta::CustomLeaderboard *> _customLeaderboardsById;

    CustomLeaderboardManager::CustomLeaderboardManager() = default;

    CustomLeaderboardManager::~CustomLeaderboardManager() = default;

    void CustomLeaderboardManager::OnLeaderboardsChanged() {

        std::vector<CustomLeaderboard*> valueVec;
        valueVec.reserve(_customLeaderboardsById.size());
        for (const auto& [key, value] : _customLeaderboardsById) {
            valueVec.emplace_back(value);
        }

        for (const auto& lb : _notifyCustomLeaderboardsChanges) {
            INFO("lb ptr: {}", fmt::ptr(lb));
            lb->OnLeaderboardsChanged(valueVec, _customLeaderboardsById);
        }
    }

    void CustomLeaderboardManager::Register(const ModInfo &modInfo) {

    }

    void CustomLeaderboardManager::Unregister(const ModInfo &modInfo) {

    }

    void CustomLeaderboard::Show() {

    }

    void CustomLeaderboard::Hide() {

    }

    void INotifyCustomLeaderboardsChange::OnLeaderboardsChanged(std::span<CustomLeaderboard *> orderedCustomLeaderboards,
                                                                std::unordered_map<std::string, CustomLeaderboard *> customLeaderboardsById) {

    }
}



// MAKE_AUTO_HOOK_MATCH(PlatformLeaderboardViewController_LeaderboardSetData, 
//     &GlobalNamespace::PlatformLeaderboardViewController::SetData, 
//     void, GlobalNamespace::PlatformLeaderboardViewController* self, 
//     GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap) {
//     PlatformLeaderboardViewController_LeaderboardSetData(self, difficultyBeatmap);

//     std::vector<INotifyLeaderboardSet*> _leaderboards;



//     for (auto& leaderboard : _leaderboards) {
//         leaderboard->OnLeaderboardSet(difficultyBeatmap);
//     }
// }

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) { 
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    INFO("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    custom_types::Register::AutoRegister();
    // Wasureta::Register(this);
}