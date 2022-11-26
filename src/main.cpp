#include "main.hpp"
#include "custom-types/shared/register.hpp"
#include "logger.hpp"
#include "hooking.h"

#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include <vector>
#include <unordered_map>

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

    void CustomLeaderboardManager::OnLeaderboardsChange() {
        // FIXME: make auto const& or auto& instead 
        for (auto lb : _notifyCustomLeaderboardsChanges) {
            INFO("Size of _notifyCustomLeaderboardsChanges vector: {}", _notifyCustomLeaderboardsChanges.capacity());
            INFO("lb ptr: {}", fmt::ptr(lb));
            lb->OnLeaderboardsChanged(_notifyCustomLeaderboardsChanges.get);
        };
    }

    void CustomLeaderboardManager::Register(const ModInfo &modInfo) {

    }

    void CustomLeaderboardManager::Unregister(const ModInfo &modInfo) {

    }

    void CustomLeaderboard::Show() {

    }

    void CustomLeaderboard::Hide() {

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