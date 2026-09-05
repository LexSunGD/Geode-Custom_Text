#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

// ID único para identificar el texto en la escena
#define TEXT_ID "mi-texto-global"_spr

// Hacemos un hook a CCDirector, que maneja las escenas de Geometry Dash
class $modify(MyCCDirector, CCDirector) {

    // Sobrescribimos el método drawScene, que se ejecuta en cada maldito frame del juego
    void drawScene() {
        // Ejecutamos primero el comportamiento original del juego para que renderice todo normalmente
        CCDirector::drawScene();

        // Obtenemos la escena que se está mostrando actualmente
        auto runningScene = this->getRunningScene();
        if (!runningScene) return;

        // Buscamos si nuestro texto ya existe en la pantalla actual
        auto textoExistente = runningScene->getChildByID(TEXT_ID);

        if (!textoExistente) {
            // Si no existe en esta escena, lo creamos
            auto miTexto = CCLabelBMFont::create("Texto Global en todo GD", "chatFont.fnt");
            
            // Lo posicionamos (abajo a la izquierda)
            miTexto->setPosition({ 15, 15 });
            miTexto->setAnchorPoint({ 0.0f, 0.0f });
            miTexto->setScale(0.5f);
            miTexto->setID(TEXT_ID);

            // ZOrder de 9999 para que siempre quede pintado al frente de todo
            runningScene->addChild(miTexto, 9999);
        }
    }
};
