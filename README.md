# Arcane Rise
Arcane Rise es un juego 2D desarrollado en C++ utilizando Visual Studio y Raylib. 
El juego implementa un sistema de menús (Main Menu, Pausa, Submenús para Instrucciones, Créditos, etc.), manejo de recursos
(texturas y sonidos), animaciones básicas y colisiones entre el jugador, obstáculos, enemigos y power-ups.

# Características
* Menú Principal: Navegación entre opciones como "Start Game", "Options", "Instructions", "Credits" y "Exit", con fondos personalizados para cada pantalla.
* Estado del Juego: Implementa estados como GAMEPLAY, PAUSE, GAME OVER, e incluso un submenú para instrucciones y créditos.

* Recursos: Gestión centralizada de texturas y sonidos a través de un Resource Manager.
# Animaciones y Sonidos:
* Animación de caminata del jugador mediante dos texturas y espejado según la dirección.
* Sonidos para colisiones (escudo, power up, etc.) y para acciones del menú (selección).
* Música de fondo variable: una para el menú, otra para el juego, una para la pausa y un sonido de Game Over que se reproduce una sola vez.
# Colisiones y Efectos:
* Colisiones entre el jugador y obstáculos, enemigos y power-ups.
Incremento progresivo de la dificultad mediante cambios en la velocidad de los obstáculos y enemigos en función del puntaje.
# Requisitos:
* Visual Studio 2019/2022 o cualquier IDE compatible con C++.

* Raylib: Asegurate de tener Raylib instalado y configurado 
para tu proyecto (incluyendo los headers y bibliotecas correspondientes).

* Librerías estándar de C++: No se usan librerías externas adicionales.
# Instalación y Compilación
1. Copiar el link del repositorio
2. En el cmd usar git clone (https://github.com/LeonardoBrizuela99/1982.git) para clonar el repositorio en el lugar deseado
3. Abrir el proyecto
4. Abrí el archivo de solución (.sln) en Visual Studio.
5. Asegurate de que Raylib esté correctamente referenciado en las propiedades del proyecto (incluyendo directorios de include y lib).
6. Compilar
7. Seleccioná la configuración (Debug/Release) y compilá el proyecto.
# Estructura del Proyecto
## game_manager/
* Contiene la lógica central del juego:
* game.h y game.cpp: Inicialización, actualización y renderizado del juego, manejo de estados (GAMEPLAY, PAUSE, GAME OVER, etc.), y procesamiento de colisiones.
## screen_manager/
* Maneja los menús y submenús del juego:
* menu.h y menu.cpp: Definen y renderizan el Main Menu, Pausa, Submenús (Instrucciones, Créditos, etc.), y sus interacciones con el mouse.
## resource_manager/
* Encargado de cargar y liberar recursos (texturas, sonidos y música):
* resource_manager.h y resource_manager.cpp: Declaraciones y definiciones de las variables globales de recursos y funciones LoadResources() y UnloadResources().
## game_elements/
* Contiene la lógica de los elementos del juego (jugador, obstáculos, power-ups, enemigos, etc.).
# Controles
* Movimiento del Jugador:
- Flechas o las teclas A (izquierda) y D (derecha).
## Acciones:
* ESC: Pausa el juego.
* P: Pausa/Resumir el juego.
# Menús:
* Seleccioná opciones haciendo clic con el mouse.
# Uso
* Ejecutá el juego.
* Navegá por el menú principal y seleccioná "Start Game" para iniciar el juego.
* Durante el juego, usá las teclas de dirección para mover el jugador y evita los obstáculos, enemigos y power-ups según la mecánica implementada.
* Al perder (Game Over), se reproducirá una canción específica y se mostrarán opciones para reiniciar o volver al menú principal.
* Créditos
* Dev/animador/arte(menu principal, menu de pausa, creditos, instrucciones, gameover, peronsaje, enemigos, power ups, etc ) por Leonardo Brizuela.
## Musica
* Por Mrthenoronha.
  - (https://freesound.org/people/Mrthenoronha/sounds/521656/) 
  - (https://freesound.org/people/Mrthenoronha/sounds/653436/)
  - (https://freesound.org/people/Mrthenoronha/sounds/512379/)
  - (https://freesound.org/people/Mrthenoronha/sounds/528717/)
## Game background
* Por ansimuz.
  - (https://opengameart.org/content/country-side-platform-tiles)
## Sonidos
* Por LittleRobotSoundFactory, MATRIXX_ and ryusa
  - (https://freesound.org/people/LittleRobotSoundFactory/sounds/270537/)
  - (https://freesound.org/people/ryusa/sounds/531176/)
  - (https://freesound.org//people/MATRIXXX_/sounds/506546/)

## Versión del juego: v1.0

# Bugs
* Música en bucle en el game over
* Desaparición repentina del side enemy cuando sale por primera vez
* Reinicio de música del menu principal, juego y menú de pausa cada vez que se ingresa.

# Futuro Update
* Implementar opciones, ya que en esta opción no se muestra nada.



