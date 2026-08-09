#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    // 1. Usamos customSetup en lugar de init para máxima estabilidad en Android
    void customSetup() {
        PauseLayer::customSetup();

        // 2. Buscamos el menú izquierdo directamente usando Node-IDs
        auto targetMenu = static_cast<CCMenu*>(this->getChildByID("left-button-menu"));

        // 3. Si el menú existe, inyectamos el botón de forma directa
        if (targetMenu) {
            // El sprite del chat
            auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
            
            // Creamos el botón usando menu_selector de la forma tradicional que ya demostró funcionar
            auto btn = CCMenuItemSpriteExtra::create(
                spr, 
                this, 
                menu_selector(MyPauseLayer::onGlobedButton)
            );
            
            // Añadimos al menú y actualizamos el layout automático
            targetMenu->addChild(btn);
            btn->setID("globed-pause-button"_spr);
            targetMenu->updateLayout();
        }
    }
    
    // 4. La función que se ejecuta al presionar el botón (siguiendo la firma exacta del ejemplo)
    void onGlobedButton(CCObject* sender) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(
            "dankmeme.globed2/open-menu", 
            nullptr
        );
    }
};
