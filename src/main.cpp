#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    bool init(bool unfocused) {
        // 1. Inicialización original de RobTop
        if (!PauseLayer::init(unfocused)) return false;

        // 2. Verificación de seguridad de Globed
        if (!Loader::get()->isModLoaded("dankmeme.globed2")) {
            return true; 
        }

        // 3. Crear el sprite del botón
        auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
        if (!spr) return true; 

        // 4. Crear el botón usando la API de Geode basada en Lambdas
        // Esto es 100% seguro en Android y PC porque no usa vtables ni menu_selector
        auto button = CCMenuItemSpriteExtra::create(
            spr,
            this,
            nullptr // No asignamos selector antiguo aquí
        );
        if (!button) return true;

        // Asignamos la acción de forma segura con el sistema de Geode
        button->setCallback([](CCObject* sender) {
            // Enviamos la notificación nativa a Globed
            CCNotificationCenter::sharedNotificationCenter()->postNotification("dankmeme.globed2/open-menu", nullptr);
        });
        
        // 5. Buscar el contenedor izquierdo
        auto menu = this->getChildByID("left-button-menu");
        if (!menu) return true; 

        // 6. Inyectar el botón y actualizar el diseño
        menu->addChild(button);
        button->setID("globed-pause-button"_spr);
        menu->updateLayout();

        return true;
    }
};
