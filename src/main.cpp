#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    // Función estática: No requiere instancias ni clases extra, directo al grano
    static void onGlobedClick(CCObject* sender) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
    }

    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        // 1. Crear el aspecto del botón
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        
        // 2. Crear el botón apuntando directamente a nuestra función estática
        auto button = CCMenuItemSpriteExtra::create(spr, nullptr, menu_selector(MyPauseLayer::onGlobedClick));

        // 3. Buscar el menú izquierdo directamente por su ID nativo de Geode
        if (auto menu = this->getChildByID("left-button-menu")) {
            menu->addChild(button);
            menu->updateLayout(); // Organiza el botón en la fila automáticamente
        }

        return true;
    }
};
