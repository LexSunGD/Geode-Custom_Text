#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

// Definimos la función de forma independiente fuera de la clase modificada.
// Esto evita problemas de herencia en Android y pasa cualquier compilador de C++.
void onGlobedPauseButtonClick(CCObject* sender) {
    CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
}

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        // 1. Ejecutar primero la inicialización original de RobTop
        if (!PauseLayer::init(unfocused)) return false;

        // 2. Verificación de seguridad: Si Globed no está activo, salimos de inmediato
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 3. Crear el sprite nativo de RobTop
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        // 4. Crear el botón apuntando a nuestra función externa y segura.
        // Al estar fuera de la clase $modify, menu_selector funciona de forma nativa
        // y es perfectamente estable en PC y Android64.
        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            menu_selector(onGlobedPauseButtonClick)
        );
        if (!button) return true;

        // 5. Buscar el contenedor izquierdo
        auto menu = this->getChildByID("left-button-menu");
        if (!menu) return true; 

        // 6. Inyectar el botón de forma limpia
        menu->addChild(button);
        button->setID("globed-pause-button"_spr);
        menu->updateLayout();

        return true;
    }
};
