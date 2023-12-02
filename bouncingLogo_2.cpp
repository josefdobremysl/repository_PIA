#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>
#include "filters.h"


#include "findLCM.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main() {
    // Inicializace Allegro
    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return 1;
    }

    // Inicializace modulu pro vykreslov�n�
    if (!al_init_primitives_addon()) {
        std::cerr << "Failed to initialize primitives addon!" << std::endl;
        return 1;
    }

    // Inicializace modulu pro na��t�n� obr�zk�
    if (!al_init_image_addon()) {
        std::cerr << "Failed to initialize image addon!" << std::endl;
        return 1;
    }

    // Vytvo�en� okna
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        return 1;
    }

    // Na�ten� obr�zk�
    ALLEGRO_BITMAP* logo1 = al_load_bitmap("C:\\Users\\josef\\Downloads\\logo.jpg");
    
    //  //  //  Změna ZAČÁTEK
    // Načtení obrázku pomocí OpenCV
    cv::Mat inputImage = cv::imread("C:\\Users\\josef\\Downloads\\logo.jpg");

    if (inputImage.empty()) {
        std::cerr << "Nelze načíst obrázek!" << std::endl;
        return -1;
    }

    // Aplikace jednotlivých filtrů
    cv::Mat sepiaImage = applySepiaFilter(inputImage);
    cv::Mat invertImage = applyInvertFilter(inputImage);
    cv::Mat detailEnhancedImage = applyDetailEnhancement(inputImage);
    cv::Mat oliveColorImage = applyOliveColorFilter(inputImage);

    cv::imwrite("C:\\Users\\josef\\Downloads\\logo2.jpg", sepiaImage);
    cv::imwrite("C:\\Users\\josef\\Downloads\\logo3.jpg", invertImage);
    cv::imwrite("C:\\Users\\josef\\Downloads\\logo4.jpg", detailEnhancedImage);
    cv::imwrite("C:\\Users\\josef\\Downloads\\logo5.jpg", oliveColorImage);

    //  //  //  Změna KONEC

    ALLEGRO_BITMAP* logo2 = al_load_bitmap("C:\\Users\\josef\\Downloads\\logo2.jpg");

    if (!logo1 || !logo2) {
        std::cerr << "Failed to load images!" << std::endl;
        al_destroy_display(display);
        return 1;
    }

    // Po��te�n� pozice a sm�r pohybu
    float x = 0; // SCREEN_WIDTH / 2.0 - al_get_bitmap_width(logo1) / 2.0 + 50;
    float y = 0; // SCREEN_HEIGHT / 2.0 - al_get_bitmap_height(logo1) / 2.0;
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
        // Nastaven� barvy pozad� okna
        al_clear_to_color(al_map_rgb(255, 255, 255));

        // Pohyb logo
        x += speedX;
        y += speedY;

        // Kolize s okraji obrazovky
        if (x < 0 || x > SCREEN_WIDTH - al_get_bitmap_width(logo1)) {
            speedX = -speedX; // Obrat sm�r na ose X
        }

        if (y < 0 || y > SCREEN_HEIGHT - al_get_bitmap_height(logo1)) {
            speedY = -speedY; // Obrat sm�r na ose Y
        }

        // Detekce, zda se logo dostalo do rohu
        if (!logoChanged && ((x < 20 && y < 20) || (x == SCREEN_WIDTH - al_get_bitmap_width(logo1) && y == 0) ||
            (x == 0 && y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)) ||
            (x == SCREEN_WIDTH - al_get_bitmap_width(logo1) && y == SCREEN_HEIGHT - al_get_bitmap_height(logo1)))) {
            logoChanged = true;
        }
        if (logoChanged == true) {
            al_draw_bitmap(logo2, x, y, 0); // druh� obr�zek
        }
        else {
            al_draw_bitmap(logo1, x, y, 0); // prvn� obr�zek
        }

        // Vymaz�n� obsahu okna
        al_flip_display();
    }

    // Uvoln�n� pam�ti
    al_destroy_bitmap(logo1);
    al_destroy_bitmap(logo2);
    al_destroy_display(display);

    return 0;
}
