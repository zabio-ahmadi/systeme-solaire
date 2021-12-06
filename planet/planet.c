#include "planet.h"
#include <stdlib.h>

#define G 6.67e-11
#define M_SOLEIL 1.989e30

// TODO : magic

planet_t create_planet(double mass, vec2 pos) {
  planet_t p;
  p.mass = mass;
  p.pos = pos;
  vec2 v;
  v.x = pos.x - 0;
  v.y = pos.y - 0;
  p.prec_pos = v;
  return p;
}
system_t create_system(double delta_t) {
    system_t s;
}
void show_system(struct gfx_context_t *ctxt, system_t *system) {}
void update_system(system_t *system, double delta_t) {}
void free_system(system_t *system) {}