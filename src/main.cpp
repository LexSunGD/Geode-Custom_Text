#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

#define TEXT_ID "mi-texto-global"_spr

class $modify(MyCCDirector, CCDirector) {

    void drawScene() {
        CCDirector::drawScene();

        auto runningScene = this->getRunningScene();
        if (!runningScene) return;

        // Leemos las configuraciones de Geode en tiempo real
        std::string configuracionTexto = Mod::get()->getSettingValue<std::string>("texto-marca");
        float posX = Mod::get()->getSettingValue<double>("posicion-x");
        float posY = Mod::get()->getSettingValue<double>("posicion-y");
        int opacidad = Mod::get()->getSettingValue<int64_t>("opacidad-marca");
        float escala = Mod::get()->getSettingValue<double>("escala-marca");

        // Buscamos si el texto ya existe en la pantalla actual
        auto textoExistente = static_cast<CCLabelBMFont*>(runningScene->getChildByID(TEXT_ID));

        if (!textoExistente) {
            // Si no existe, lo creamos con la fuente Pusab real
            auto miTexto = CCLabelBMFont::create(configuracionTexto.c_str(), "bigFont.fnt");
            miTexto->setColor({ 255, 255, 255 });
            miTexto->setAnchorPoint({ 0.0f, 0.0f });
            miTexto->setID(TEXT_ID);
            
            // Aplicamos los valores dinámicos
            miTexto->setPosition({ posX, posY });
            miTexto->setOpacity(static_cast<GLubyte>(opacidad));
            miTexto->setScale(escala);

            runningScene->addChild(miTexto, 9999);
        } else {
            // Si el texto ya existe, actualizamos constantemente sus propiedades.
            // Esto permite cambiar los ajustes en el menú de Geode sin reiniciar el juego.
            textoExistente->setString(configuracionTexto.c_str());
            textoExistente->setPosition({ posX, posY });
            textoExistente->setOpacity(static_cast<GLubyte>(opacidad));
            textoExistente->setScale(escala);
        }
    }
};
