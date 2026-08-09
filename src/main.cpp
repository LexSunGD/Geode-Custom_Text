#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

// ==========================================
// 1. INTERFAZ DE GLOBED (ENLACE INTER-MOD)
// ==========================================
// Declaramos la clase original de Globed para que tu mod pueda llamarla directamente.
// No necesitas programarla, solo decirle a C++ que existe en la memoria del juego.
class GlobedMenuPopup : public FLAlertLayer {
public:
    static GlobedMenuPopup* create() {
        // Buscamos la dirección en la memoria del mod instalado
        return reinterpret_cast<GlobedMenuPopup*(*)(bool)>(
            geode::addresser::getNonVirtual(
                geode::modifier::Resolve<bool>::func(&GlobedMenuPopup::create)
            )
        )(false);
    }
    void show();
};

// ==========================================
// 2. MODIFICACIÓN DEL MENÚ DE PAUSA
// ==========================================
class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        // Buscamos el menú izquierdo (Lógica que ya aprobó el compilador)
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
    
    // Esta es la nueva acción que abre la ventana flotante de tu imagen
    void onGlobedButton(CCObject* sender) {
        // Llamamos directamente a la ventana emergente de Globed
        if (auto popup = GlobedMenuPopup::create()) {
            popup->show();
        }
    }
};
