#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Variable global o estática para saber a quién seguir (false = Jugador 1, true = Jugador 2)
bool g_followPlayer2 = false;

class $modify(MyPlayLayer, PlayLayer) {
    
    // 1. Hook para detectar cuando se presiona la tecla o botón
    void update(float dt) {
        PlayLayer::update(dt);

        // Ejemplo usando una tecla física (por ejemplo, la tecla 'C')
        // En una implementación real, es mejor usar el 'CCKeyboardDispatcher' de Cocos2d-x o un botón en la UI
        if (CCKeyboardDispatcher::get()->getAsyncKeyState(enumKeyCodes::KEY_C)) {
            // Alternar entre Jugador 1 y Jugador 2
            g_followPlayer2 = !g_followPlayer2;
            
            // Mostrar un pequeño mensaje en pantalla para confirmar el cambio
            Notification::create(
                g_followPlayer2 ? "Siguiendo a Jugador 2" : "Siguiendo a Jugador 1", 
                NotificationIcon::Info
            )->show();
        }

        // 2. Modificar el objetivo de la cámara en el modo Plataforma
        // PlayLayer maneja la cámara del modo plataforma a través de punteros internos o llamando al método nativo
        if (m_levelSettings->m_platformerMode) {
            // Hack directo: Intercambiamos temporalmente los punteros antes de que la cámara actualice
            // O modificamos la función nativa 'cameraMoveToPlayer' si es necesario.
            if (g_followPlayer2 && m_player2) {
                // Forzamos a la cámara a centrarse en el Jugador 2
                this->cameraMoveToPlayer(m_player2); 
            } else {
                this->cameraMoveToPlayer(m_player1);
            }
        }
    }
};
