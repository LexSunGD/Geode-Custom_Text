#include <Geode/Geode.hpp>
#include <Geode/modify/NotificationLayer.hpp>

using namespace geode::prelude;

#define TEXT_ID "mi-texto-global"_spr

// Hacemos el hook a la capa de notificaciones globales de Geode
class $modify(MyNotificationLayer, NotificationLayer) {

    // Se ejecuta una sola vez cuando el juego arranca y crea esta capa permanente
    bool init() {
        if (!NotificationLayer::init()) return false;

        // "bigFont.fnt" es la fuente Pusab real y limpia de Geometry Dash
        auto miTexto = CCLabelBMFont::create("TU MARCA DE AGUA", "bigFont.fnt");
        
        // Color blanco puro
        miTexto->setColor({ 255, 255, 255 });

        // Opacidad para efecto marca de agua (ajusta a tu gusto entre 0 y 255)
        miTexto->setOpacity(130); 
        
        // Configuración de posición fina en la esquina inferior izquierda
        miTexto->setPosition({ 15, 15 });
        miTexto->setAnchorPoint({ 0.0f, 0.0f });
        
        // Pusab es una fuente muy gruesa, una escala entre 0.3f y 0.4f es perfecta para marca de agua
        miTexto->setScale(0.35f); 
        miTexto->setID(TEXT_ID);

        // Añadimos el texto a la capa de notificaciones con un ZOrder extremadamente alto.
        // Al estar en esta capa, JAMÁS parpadeará y se renderizará por encima de cualquier ventana emergente.
        this->addChild(miTexto, 99999);

        return true;
    }
};
