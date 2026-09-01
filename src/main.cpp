#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fstream>
#include <sstream>

using namespace geode::prelude;

struct DifficultyStep {
    float percentage;
    std::string spriteName;
};

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        CCSprite* m_customDifficultyMeter = nullptr;
        std::vector<DifficultyStep> m_loadedRecipe;
    };

    void loadJsonRecipe() {
        auto safeFields = m_fields.self();
        safeFields->m_loadedRecipe.clear();

        auto configDir = Mod::get()->getConfigDir();
        auto jsonPath = configDir / "recipe.json";

        // Si el archivo no existe en la carpeta config, lo creamos de forma automática
        if (!ghc::filesystem::exists(jsonPath)) {
            matjson::Value defaultJson = matjson::Array({
                matjson::Object({{"percentage", 0.0}, {"sprite", "NA_dif.png"}}),
                matjson::Object({{"percentage", 8.33}, {"sprite", "Auto_dif.png"}}),
                matjson::Object({{"percentage", 16.66}, {"sprite", "Easy_dif.png"}}),
                matjson::Object({{"percentage", 25.0}, {"sprite", "Normal_dif.png"}}),
                matjson::Object({{"percentage", 33.33}, {"sprite", "Hard_dif.png"}}),
                matjson::Object({{"percentage", 41.66}, {"sprite", "Harder_dif.png"}}),
                matjson::Object({{"percentage", 50.0}, {"sprite", "Insane_dif.png"}}),
                matjson::Object({{"percentage", 66.66}, {"sprite", "EasyDemon_dif.png"}}),
                matjson::Object({{"percentage", 75.0}, {"sprite", "MediumDemon_dif.png"}}),
                matjson::Object({{"percentage", 83.33}, {"sprite", "HardDemon_dif.png"}}),
                matjson::Object({{"percentage", 91.66}, {"sprite", "InsaneDemon_dif.png"}}),
                matjson::Object({{"percentage", 100.0}, {"sprite", "ExtremeDemon_dif.png"}})
            });

            std::ofstream file(jsonPath);
            file << defaultJson.dump(matjson::FormatOptions { .indent = 4 });
            file.close();
        }

        // Leer el archivo JSON de forma segura usando la nueva API matjson de Geode
        std::ifstream file(jsonPath);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            // Usamos matjson::Value::from_str para procesar el string del archivo
            auto jsonResult = matjson::Value::from_str(buffer.str());
            if (jsonResult.is_ok()) {
                auto json = jsonResult.unwrap();
                if (json.is_array()) {
                    for (const auto& item : json.as_array()) {
                        if (item.contains("percentage") && item.contains("sprite")) {
                            float percent = static_cast<float>(item["percentage"].as_double());
                            std::string sprite = item["sprite"].as_string();
                            safeFields->m_loadedRecipe.push_back({ percent, sprite });
                        }
                    }
                }
            }
        }

        if (safeFields->m_loadedRecipe.empty()) {
            safeFields->m_loadedRecipe.push_back({ 0.0f, "NA_dif.png" });
        }
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        if (level->isPlatformer()) return true;

        this->loadJsonRecipe();

        m_fields->m_customDifficultyMeter = CCSprite::create("NA_dif.png"_spr);
        
        if (m_fields->m_customDifficultyMeter) {
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            
            float offsetX = static_cast<float>(Mod::get()->getSettingValue<int64_t>("meter-pos-x"));
            float offsetY = static_cast<float>(Mod::get()->getSettingValue<int64_t>("meter-pos-y"));
            m_fields->m_customDifficultyMeter->setPosition({ (winSize.width / 2) + offsetX, (winSize.height / 2) + offsetY });
            
            float scale = static_cast<float>(Mod::get()->getSettingValue<double>("meter-scale"));
            m_fields->m_customDifficultyMeter->setScale(scale); 

            int64_t opacityPercent = Mod::get()->getSettingValue<int64_t>("meter-opacity");
            GLubyte alphaValue = static_cast<GLubyte>((opacityPercent * 255) / 100);
            m_fields->m_customDifficultyMeter->setOpacity(alphaValue);

            m_fields->m_customDifficultyMeter->setID("custom-difficulty-meter"_spr);

            if (m_uiLayer) {
                m_uiLayer->addChild(m_fields->m_customDifficultyMeter);
            }
        }

        return true;
    }
    
    void updateProgressbar() {
        PlayLayer::updateProgressbar(); 

        if (!m_fields->m_customDifficultyMeter) return;

        float percentage = this->getCurrentPercent();

        if (percentage > 100.0f) percentage = 100.0f;
        if (percentage < 0.0f) percentage = 0.0f;

        std::string spriteName = "NA_dif.png"; 

        for (const auto& step : m_fields->m_loadedRecipe) {
            if (percentage >= step.percentage) {
                spriteName = step.spriteName; 
            } else {
                break; 
            }
        }

        auto textureCache = CCTextureCache::sharedTextureCache();
        std::string fullPath = Mod::get()->getID() + "/" + spriteName;
        auto newTexture = textureCache->addImage(fullPath.c_str(), false);
        
        if (newTexture) {
            m_fields->m_customDifficultyMeter->setTexture(newTexture);
            
            CCRect rect = CCRectZero;
            rect.size = newTexture->getContentSize();
            m_fields->m_customDifficultyMeter->setTextureRect(rect);
            
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            float offsetX = static_cast<float>(Mod::get()->getSettingValue<int64_t>("meter-pos-x"));
            float offsetY = static_cast<float>(Mod::get()->getSettingValue<int64_t>("meter-pos-y"));
            m_fields->m_customDifficultyMeter->setPosition({ (winSize.width / 2) + offsetX, (winSize.height / 2) + offsetY });
            
            float scale = static_cast<float>(Mod::get()->getSettingValue<double>("meter-scale"));
            m_fields->m_customDifficultyMeter->setScale(scale);

            int64_t opacityPercent = Mod::get()->getSettingValue<int64_t>("meter-opacity");
            GLubyte alphaValue = static_cast<GLubyte>((opacityPercent * 255) / 100);
            m_fields->m_customDifficultyMeter->setOpacity(alphaValue);
        }
    }
};
