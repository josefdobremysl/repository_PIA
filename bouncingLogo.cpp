#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>

#include "findLCM.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main() {
    // Inicializace Allegro
    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return 1;
    }

    // Inicializace modulu pro vykreslování
    if (!al_init_primitives_addon()) {
        std::cerr << "Failed to initialize primitives addon!" << std::endl;
        return 1;
    }

    // Inicializace modulu pro naèítání obrázkù
    if (!al_init_image_addon()) {
        std::cerr << "Failed to initialize image addon!" << std::endl;
        return 1;
    }

    // Vytvoøení okna
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        return 1;
    }

    // Naètení obrázkù
    ALLEGRO_BITMAP* logo1 = al_load_bitmap("C:\\CVUT\\pomoc.png");
    ALLEGRO_BITMAP* logo2 = al_load_bitmap("C:\\CVUT\\pomoc.png");

    if (!logo1 || !logo2) {
        std::cerr << "Failed to load images!" << std::endl;
        al_destroy_display(display);
        return 1;
    }

    // Poèáteèní pozice a smìr pohybu
    float x = SCREEN_WIDTH / 2.0 - al_get_bitmap_width(logo1) / 2.0 - 50;
    float y = SCREEN_HEIGHT / 2.0 - al_get_bitmap_height(logo1) / 2.0;
    float speedX = 0.05;
    float speedY = 0.05;

    bool logoChanged = false;

    int diffScreenLogoH = SCREEN_HEIGHT - al_get_bitmap_height(logo1); //calculate height difference of screen and logo
    int diffScreenLogoW = SCREEN_WIDTH - al_get_bitmap_width(logo1); //calculate width difference of screen and logo

    std::cout << diffScreenLogoH << std::endl;
    std::cout << diffScreenLogoW << std::endl;

    int numberOfSteps = FindLCM::calculateLCM(diffScreenLogoH, diffScreenLogoW); //Find Least Common Multiple
    int cas = numberOfSteps / speedX; //time needed to hit corner (work in progress)

    std::cout << numberOfSteps << std::endl;
    std::cout << cas << std::endl;

    while (true) {
        // Nastavení barvy pozadí okna
        al_clear_to_color(al_map_rgb(255, 255, 255));

        // Pohyb logo
        x += speedX;
        y += speedY;

        // Kolize s okraji obrazovky
        if (x < 0 || x > SCREEN_WIDTH - al_get_bitmap_width(logo1)) {
            speedX = -speedX; // Obrat smìr na ose X
        }

        if (y < 0 || y > SCREEN_HEIGHT - al_get_bitmap_height(logo1)) {
            speedY = -speedY; // Obrat smìr na ose Y
        }

        // Detekce, zda se logo dostalo do rohu
        if (!logoChanged && ((x < 20 && y < 20) || (x == SCREEN_WIDTH - al_get_bitmap_width(logo1) && y == 0) ||
            (x == 0 && y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)) ||
            (x == SCREEN_WIDTH - al_get_bitmap_width(logo1) && y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)))) {
            logoChanged = true;
        }
        if (logoChanged == true) {
            al_draw_bitmap(logo2, x, y, 0); // druhý obrázek
        }
        else {
            al_draw_bitmap(logo1, x, y, 0); // první obrázek
        }

        // Vymazání obsahu okna
        al_flip_display();
    }

    // Uvolnìní pamìti
    al_destroy_bitmap(logo1);
    al_destroy_bitmap(logo2);
    al_destroy_display(display);

    return 0;
}
