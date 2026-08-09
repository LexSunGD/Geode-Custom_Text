#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

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

        // 4. Crear el botón usando el handler oficial de Geode
        // Esto soluciona el error de compilación por completo
        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            clicked_handler(MyPauseLayer::onGlobedButton)
        );
        if (!button) return true;

        // 5. Buscar el contenedor izquierdo del menú de pausa
        auto menu = this->getChildByID("left-button-menu");
        if (!menu) return true; 

        // 6. Inyectar el botón de forma limpia con su ID correspondiente
        menu->addChild(button);
        button->setID("globed-pause-button"_spr);
        menu->updateLayout();

        return true;
    }

    // Esta es la función que se ejecutará de forma segura al presionar el botón
    void onGlobedButton(CCObject* sender) {
        // Enviar la notificación nativa para que Globed reaccione y abra su menú
        CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
    }
};
