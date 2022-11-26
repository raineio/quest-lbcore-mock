#include "main.hpp"
#include "custom-types/shared/register.hpp"
#include "logger.h"
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

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void load();

namespace Wasureta {

    class CustomLeaderboard {

        CustomLeaderboard::CustomLeaderboard(const ModInfo& modInfo) : modInfo(modInfo) {
            get_instance().Add(this);
        }


    public:
        Wasureta::CustomLeaderboard* Get(const ModInfo& modInfo = { MOD_ID, VERSION }) {
            auto lbreg = new Wasureta::CustomLeaderboard(modInfo);
            return lbreg;
        }   

        std::string pluginId;
    };

    class CustomLeaderboardManager {

        static CustomLeaderboardManager instance;
        std::set<Wasureta::CustomLeaderboard*> _customLeaderboards;

        std::unordered_map<std::string, Wasureta::CustomLeaderboard> _customLeaderbordsById; 
        
        /// @brief Registers a Custom Leaderboard to the manager.
        /// @param modInfo Your mod info, not required 
        void Register(const ModInfo& modInfo = { MOD_ID, VERSION }) {
            // TODO: Register the board, damn it

            
        }

        /// @brief Removes a Custom Leaderboard from the manager.
        /// @param customLeaderboard 
        void Unregister(const ModInfo& modInfo = { MOD_ID, VERSION }) {
            // TODO: Unregister the board, damn it

            if (customLeaderboard->pluginId == null) {

            }
        }

        void Add(CustomLeaderboard* customLeaderboard) {
            DEBUG("Registered Leaderboard for {} v{}.", customLeaderboard->modInfo.id, customLeaderboard->modInfo.version);
            _customLeadeboards.emplace(customLeaderboard);
        }

    private:
        void OnLeaderboardsChanged() {
            for (auto notifyCustomLeaderboardsChange : _customLeaderboardById) {
                notifyCustomLeaderboardsChange->OnLeaderboardsChanged(_customLeaderboardsById.Value);
            }
        }

        CustomLeaderboardManager& CustomLeaderboardManager::get_instance() {
            return instance;
        }
    };
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