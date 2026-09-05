#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

#define TEXT_ID "mi-texto-global"_spr

class $modify(MyCCDirector, CCDirector) {

    void drawScene() {
        CCDirector::drawScene();

        auto runningScene = this->getRunningScene();
        if (!runningScene) return;

        // Buscamos si el texto ya existe en la escena activa
        auto textoExistente = runningScene->getChildByID(TEXT_ID);

        if (!textoExistente) {
            // "bigFont.fnt" es la fuente Pusab real y limpia de Geometry Dash
            auto miTexto = CCLabelBMFont::create("TU MARCA DE AGUA", "bigFont.fnt");
            
            // Color blanco puro
            miTexto->setColor({ 255, 255, 255 });

            // Opacidad de marca de agua (150 es un buen balance)
            miTexto->setOpacity(150); 
            
            // Posicionamiento en la esquina inferior izquierda
            miTexto->setPosition({ 15, 15 });
            miTexto->setAnchorPoint({ 0.0f, 0.0f });
            
            // Pusab es gruesa, bajamos la escala a 0.35f para que se vea fina
            miTexto->setScale(0.35f); 
            miTexto->setID(TEXT_ID);

            // Lo agregamos al frente de la escena actual
            runningScene->addChild(miTexto, 9999);
        }
    }
};
