#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    struct gfx_context_t *ctxt =
        gfx_create("Planetary system", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    // TODO : create your system
    //créer le system 
    system_t system = create_system(NB_PLANET);
    system.planets = malloc(system.nb_planets * sizeof(planet_t));

    system.planets[0] = create_planet(M_MERCURE,R_MERCURE,EXCENTRICITE_MERCURE,PERIHELIE_MERCURE, COLOR_MERCURE);
    system.planets[1] = create_planet(M_VENUS,R_VENUS,EXCENTRICITE_VENUS,PERIHELIE_VENUS, COLOR_VENUS);
    system.planets[2] = create_planet(M_TERRE,R_TERRE,EXCENTRICITE_TERRE,PERIHELIE_TERRE, COLOR_TERRE);
    system.planets[3] = create_planet(M_MARS,R_MARS,EXCENTRICITE_MARS,PERIHELIE_MARS, COLOR_MARS);  
    system.planets[4] = create_planet(M_JUPITER,R_JUPITER,EXCENTRICITE_JUPITER,PERIHELIE_JUPITER, COLOR_JUPITER);  
    system.planets[5] = create_planet(M_SATURNE,R_SATURNE,EXCENTRICITE_SATURNE,PERIHELIE_SATURNE, COLOR_SATURNE);  
    

    // calcul la position initial à partir de delta_t 
    for (uint8_t i = 0; i < NB_PLANET; i++) {
        system.planets[i].prec_pos = system.planets[i].pos;
        system.planets[i].pos = intial_position(system.planets[i], DELTA_T, &system);
    }

    while (true)
    {
        gfx_clear(ctxt, COLOR_BLACK);
        // TODO : draw the current state of your system
        show_system(ctxt, &system);
        // TODO : update your system
        update_system(&system, DELTA_T);
        
        if (gfx_keypressed() == SDLK_ESCAPE)
        {
            break;
        }
        gfx_present(ctxt);
    }

    //TODO : Free your system
    free_system(&system);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
