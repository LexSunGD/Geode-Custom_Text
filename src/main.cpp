#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

#define TEXT_ID "mi-texto-global"_spr

class $modify(MyCCDirector, CCDirector) {

    void drawScene() {
        CCDirector::drawScene();

        auto runningScene = this->getRunningScene();
        if (!runningScene) return;

        auto textoExistente = runningScene->getChildByID(TEXT_ID);

        if (!textoExistente) {
            // Cambiamos "chatFont.fnt" por "gjFont09.fnt" (Pusab limpia)
            auto miTexto = CCLabelBMFont::create("TU MARCA DE AGUA", "gjFont09.fnt");
            
            // Forzamos el color a Blanco Puro (R: 255, G: 255, B: 255)
            miTexto->setColor({ 255, 255, 255 });

            // OPCIONAL: Añade opacidad para efecto marca de agua (0 transparente, 255 sólido)
            // 150 es un buen balance para que sea visible pero traslúcido
            miTexto->setOpacity(150); 
            
            // Posicionamiento y escala
            miTexto->setPosition({ 15, 15 });
            miTexto->setAnchorPoint({ 0.0f, 0.0f });
            miTexto->setScale(0.4f); // Pusab suele verse más grande, bajamos la escala a 0.4f
            miTexto->setID(TEXT_ID);

            runningScene->addChild(miTexto, 9999);
        }
    }
};
