#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Creamos un ID único global para encontrar nuestro texto fácilmente
#define TEXT_ID "mi-texto-global"_spr

// Función que se ejecutará en cada frame del juego
void actualizarTextoGlobal(float dt) {
    // Obtenemos la escena que se está mostrando actualmente en el juego
    auto runningScene = CCDirector::sharedDirector()->getRunningScene();
    if (!runningScene) return;

    // Buscamos si nuestro texto ya existe en la escena actual
    auto textoExistente = runningScene->getChildByID(TEXT_ID);

    if (!textoExistente) {
        // Si no existe en esta pantalla, lo creamos desde cero
        auto miTexto = CCLabelBMFont::create("Texto Global en todo GD", "chatFont.fnt");
        
        // Lo posicionamos (por ejemplo, abajo a la izquierda con un pequeño margen)
        miTexto->setPosition({ 15, 15 });
        miTexto->setAnchorPoint({ 0.0f, 0.0f }); // Anclaje en la esquina inferior izquierda
        miTexto->setScale(0.5f);
        miTexto->setID(TEXT_ID);

        // ZOrder muy alto (9999) para asegurarnos de que se dibuje por encima de los menús
        runningScene->addChild(miTexto, 9999);
    }
}

// Geode ejecuta $execute cuando el mod se carga por primera vez al abrir el juego
$execute {
    // Registramos una función repetitiva (scheduler) que corre en cada fotograma
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(
        schedule_selector(actualizarTextoGlobal), 
        CCDirector::sharedDirector(), 
        0.0f, // 0.0f significa que se ejecuta en cada frame posible
        false
    );
}
