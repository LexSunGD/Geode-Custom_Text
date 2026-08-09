#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto targetMenu = static_cast<CCMenu*>(this->getChildByID("left-button-menu"));

        if (targetMenu) {
            auto spr = CCSprite::createWithSpriteFrameName("GJ_chatBtn_001.png");
            
            auto btn = CCMenuItemSpriteExtra::create(
                spr, 
                this, 
                menu_selector(MyPauseLayer::onGlobedButton)
            );
            
            targetMenu->addChild(btn);
            btn->setID("globed-pause-button"_spr);
            targetMenu->updateLayout();
        }
    }
    
    void onGlobedButton(CCObject* sender) {
        this->scheduleOnce(schedule_selector(MyPauseLayer::triggerGlobedMenu), 0.0f);
    }

    void triggerGlobedMenu(float dt) {
        // Enviamos las 3 variantes de nombres que Globed usa en sus diferentes versiones.
        // Las que no existan serán ignoradas por el juego, pero la correcta activará el menú.
        
        // Variante 1: La clásica de Geode
        CCNotificationCenter::sharedNotificationCenter()->postNotification(
            "dankmeme.globed2/open-menu", nullptr
        );

        // Variante 2: La ruta directa de la interfaz de Globed
        CCNotificationCenter::sharedNotificationCenter()->postNotification(
            "globed/open-menu", nullptr
        );

        // Variante 3: El trigger de la capa flotante (Popup)
        CCNotificationCenter::sharedNotificationCenter()->postNotification(
            "dankmeme.globed2/open-popup", nullptr
        );
    }
};
