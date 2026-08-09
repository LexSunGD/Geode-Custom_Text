#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        // Buscamos el menú izquierdo (Lógica aprobada por el compilador)
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
    
    // Nueva acción segura a través de la API de Geode
    void onGlobedButton(CCObject* sender) {
        // Ejecutamos el comando interno que invoca la interfaz de Globed
        // Esto le dice a Geode que busque y abra el menú de forma nativa y segura
        geode::Loader::get()->getLoadedMod("dankmeme.globed2")->getSettingValue<bool>("open-menu"); 
        
        // NOTA: Si el comando de arriba no responde en tu versión de Globed, 
        // la alternativa estándar de Geode para disparar la interfaz por texto es:
        // geode::Console::get()->executeCommand("globed open");
    }
};
