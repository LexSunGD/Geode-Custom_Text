#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        if (!PauseLayer::init(unfocused)) return false;

        // 1. Verificación de seguridad
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 2. Crear el sprite del botón
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        // 3. Crear el botón TOTALMENTE LIMPIO (sin selectores ni funciones extra)
        auto button = CCMenuItemSpriteExtra::create(spr, this, nullptr);
        if (!button) return true;

        // 4. Esta es la forma nativa y moderna de Geode para Android. ¡Cero errores!
        button->setCallback([](CCObject*) {
            CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
        });

        // 5. Inyectar usando node-ids de forma segura
        auto menu = this->getChildByID("left-button-menu");
        if (!menu) return true; 

        menu->addChild(button);
        button->setID("globed-pause-button"_spr);
        menu->updateLayout();

        return true;
    }
};
