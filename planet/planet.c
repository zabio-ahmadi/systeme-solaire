#include "planet.h"
#include <stdlib.h>
#include <stdio.h>
#include "../gfx/gfx.h"
#include <math.h>


// TODO : magic

/**
 * @brief Create a planet object
 * 
 * @param mass 
 * @param rayon 
 * @param excentricity 
 * @param perihelie 
 * @param color 
 * @return planet_t 
 */
planet_t create_planet(double mass,double rayon, double excentricity, double perihelie, uint32_t color){

  planet_t planet;
  planet.mass = mass;
  planet.rayon = rayon;
  planet.pos = vec2_create(perihelie * (1 - excentricity), 0); 
  planet.prec_pos =  vec2_create_zero();
  planet.planet_excentricity = excentricity;
  planet.perihelie = perihelie;
  planet.color = color;

  return planet;

}

/**
 * @brief Create a system object
 * 
 * @param nb_planets 
 * @return system_t 
 */
system_t create_system(int nb_planets) {

  system_t system;
  system.nb_planets = nb_planets;
  system.star = create_planet(M_SOLEIL,10,0,0, COLOR_YELLOW);
  system.star.pos = vec2_create_zero();
  return system; 

}

/**
 * @brief affiche les planètes sur notre écran 1000 x 1000
 * 
 * @param ctxt 
 * @param system 
 */
void show_system(struct gfx_context_t *ctxt, system_t *system) {

  // affiche le soleil 
  coordinates sun_cord = vec2_to_coordinates(system->star.pos,SCREEN_WIDTH,SCREEN_HEIGHT);
  draw_full_circle(ctxt,sun_cord.column, sun_cord.row, system->star.rayon, system->star.color);
 

  // affiche les planètes
  for (uint32_t i = 0; i < system->nb_planets; i++){
     
    // calcule la coef de proportion 
    long coef = system->planets[system->nb_planets-1].perihelie;
    double scalar = 1.0/coef;

    // coord de centre de la planète
    vec2 center = vec2_mul(scalar, system->planets[i].pos);
    // rayon de la planète
    double rayon = (system->planets[i].rayon /coef  * 100000) * 7;

    coordinates screen_pos = vec2_to_coordinates(center, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    draw_full_circle(ctxt, screen_pos.column, screen_pos.row, rayon,system->planets[i].color);

  }

}

/**
 * @brief calcule le vecteur p 
 * 
 * @param planet 
 * @param system 
 * @return vec2 
 */
vec2 calcul_de_vp(planet_t planet, system_t *system) {

  vec2 vector_normal = vec2_create(-planet.pos.y, planet.pos.x);
  double scalar = sqrt((G * system->star.mass * (1 + planet.planet_excentricity)) / (planet.perihelie * (1 - planet.planet_excentricity)));
  vec2 v_unitaire_vp = vec2_normalize(vector_normal);
  vec2 vp = vec2_mul(scalar, v_unitaire_vp);
  return vp;

}

/**
 * @brief cacul la position initiale en terme de delta_t 
 * 
 * @param planet 
 * @param delta_t 
 * @param system 
 * @return vec2 
 */
vec2 intial_position(planet_t planet, double delta_t, system_t *system) {

  vec2 vector_p = calcul_de_vp(planet, system);
  vec2 acceleration = planet_acceleration(planet, system);
  vec2 position = vec2_add(vec2_add(planet.pos, vec2_mul(delta_t, vector_p)), vec2_mul(pow(delta_t, 2) / 2, acceleration));
  return position;

}



/**
 * @brief : calcul force gravitationelle
 * 
 * @param planet a 
 * @param planet b 
 * @return vec2 
 */
vec2 force_gravitationelle_planet(planet_t a, planet_t b) {
  vec2 r_a_b = vec2_sub(b.pos, a.pos);
  vec2 m_f = vec2_mul(G * ((a.mass * b.mass) / pow(vec2_norm(r_a_b), 3)), r_a_b); // calcule de la force de reaction entre deux planet 

  return m_f;
}


/**
 * @brief cacul les forces resultants des planètes sur une planète
 * 
 * @param system 
 * @param planet 
 * @return vec2 
 */
vec2 planet_resultant_force(system_t *system, planet_t planet) {
    
  vec2 resulting_force = vec2_create_zero();

  //la force gravitationelle entre soleil et la planète
  vec2 force_g = force_gravitationelle_planet(planet, system->star);
  resulting_force = vec2_add(resulting_force, force_g);

  // force resultantes des planètes sur l'un l'autre
  for (uint8_t i = 0; i < system->nb_planets; i++) {
      
    // annule la force resultante sur elle-meme 
    if (planet.mass == system->planets[i].mass) 
        continue;

    vec2 f_g = force_gravitationelle_planet(planet, system->planets[i]);
    resulting_force = vec2_add(resulting_force, f_g);
  }

  return resulting_force;
}

/**
 * @brief calcul acceleration 
 * 
 * @param planet 
 * @param system 
 * @return vec2 
 */
vec2 planet_acceleration(planet_t planet, system_t *system) {

  vec2 force_resultant = planet_resultant_force(system, planet);
  //a = 1/m * f 
  return vec2_mul(1 / planet.mass, force_resultant);
}


vec2 next_position(planet_t planet, double delta_t, system_t *system){

  vec2 accelleration = planet_acceleration(planet, system);

  //xp (t + delta_t)
  vec2 next_pos = vec2_add(vec2_sub(vec2_mul(2, planet.pos), planet.prec_pos), vec2_mul(pow(delta_t, 2), accelleration));

  return next_pos;

}

  
void update_system(system_t *system, double delta_t) {

  for (uint32_t i = 0; i < system->nb_planets; i++) {
      
    vec2 prec_pos = system->planets[i].pos;
    system->planets[i].pos = next_position(system->planets[i], delta_t, system);
    system->planets[i].prec_pos = prec_pos;
  }

}
void free_system(system_t *system) {
  free(system->planets);
}