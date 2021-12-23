#include "../gfx/gfx.h"
#include "../vec2/vec2.h"

#ifndef _PLANET_H_
#define _PLANET_H_


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define NB_PLANET 6
#define DELTA_T NB_PLANET * 2021 


#define G 6.67e-11

// mass en kg 
#define M_SOLEIL 1.989e30
#define M_MERCURE 3.285e23
#define M_VENUS 4.867e24
#define M_TERRE 5.972e24 
#define M_MARS 6.39e23 
#define M_JUPITER  1.898e27 
#define M_SATURNE 5.6834e26

// rayon en mètre
#define R_SOLEIL 6.9e47
#define R_MERCURE 2.4e6
#define R_VENUS 6.05e6 
#define R_TERRE 6.371e6  
#define R_MARS 6.33895e6 
#define R_JUPITER 6.99e7 
#define R_SATURNE 5.8232e7


// demi grande axe en mètre
#define DEMI_G_AXE_MERCURE 5.7909050e10  
#define DEMI_G_AXE_VENUS 1.08209e11
#define DEMI_G_AXE_TERRE 1.49596e11
#define DEMI_G_AXE_MARS 2.27923e11
#define DEMI_G_AXE_JUPITER 7.78570e11
#define DEMI_G_AXE_SATURNE 1.433529e12

//EXCENTRICITE
#define EXCENTRICITE_MERCURE 0.2056
#define EXCENTRICITE_VENUS 0.0067
#define EXCENTRICITE_TERRE 0.0167
#define EXCENTRICITE_MARS 0.0935
#define EXCENTRICITE_JUPITER 0.0489
#define EXCENTRICITE_SATURNE 0.0565


// colors 
#define COLOR_MERCURE 0x908a8a
#define COLOR_VENUS 0xe7e7e5
#define COLOR_TERRE 0x545b78
#define COLOR_MARS 0xf27c5c
#define COLOR_JUPITER 0xc8c2ad
#define COLOR_SATURNE 0xbea175




typedef struct _planet {
  double mass;
  double rayon;
  uint32_t color; 
  double planet_excentricity;
  double planet_demi_grand_ax;
  vec2 pos;      // x(t)
  vec2 prec_pos; // x(t - dt)
} planet_t;

typedef struct _system {
  planet_t star;       // ex. The sun
  uint32_t nb_planets; // The number of orbiting planets
  planet_t *planets;   // An array of orbiting planets
} system_t;

// Those function are not mandatory to implement,
// it's rather a hint of what you should have.

planet_t create_planet(double mass,double rayon, double excentricity, double demi_grand_axe, uint32_t color);

system_t create_system(int32_t nb_planets);

vec2 intial_position(planet_t planet, double delta_t, system_t *system);

vec2 force_gravitationelle_planet(planet_t a, planet_t b);

vec2 planet_resultant_force(system_t *system, planet_t planet);

vec2 planet_acceleration(planet_t planet, system_t *system);

vec2 next_position(planet_t planet, double delta_t, system_t *system);

void show_system(struct gfx_context_t *ctxt, system_t *system);

void update_system(system_t *system, double delta_t);

void free_system(system_t *system);

#endif