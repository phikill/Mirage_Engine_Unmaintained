#ifndef PHYSICS_H
#define PHYSICS_H

#include <linmath\linmath.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdbool.h>
#include "../types.h"
#include "../renderer/render.h"
#include "../array_list/array_list.h"

typedef struct hit Hit;
typedef struct body Body;
typedef struct static_body Static_Body;

typedef void (*On_Hit)(Body *self, Body *other, Hit hit);
typedef void (*On_Hit_Static)(Body *self, Static_Body *other, Hit hit);

typedef struct aabb 
{
	vec3 position;
	vec3 init_position;
	vec3 half_size;
	
} AABB;

struct body 
{
	AABB aabb;
	vec3 velocity;
	vec3 acceleration;
	On_Hit on_hit;
	On_Hit_Static on_hit_static;
    usize entity_id;
	u8 collision_layer;
	u8 collision_mask;
	bool is_kinematic;
	bool is_active;
	int a;                
	int l;   
    int sector;
    int index_trigger;
	bool is_trigger;

};

struct static_body 
{
	AABB aabb;
	u8 collision_layer;
};

struct ray_cast_trace 
{
	AABB aabb;
	u8 collision_layer;
};

struct hit 
{
	usize other_id;
	f32 time;
	vec3 position;
	vec2 normal;
	bool is_hit;
	bool trigger;
};

void physics_init(void);
void physics_update(void);
usize physics_body_create(vec3 position, 
						  vec3 size, 
						  vec3 velocity, 
						  u8 collision_layer, 
						  u8 collision_mask, 
						  bool is_kinematic, 
						  On_Hit on_hit, 
						  On_Hit_Static on_hit_static, 
						  usize entity_id, 
						  int index_trigger, 
						  int a,                
						  int l);

usize physics_trigger_create(vec3 position, 
							 vec3 size, 
							 u8 collision_layer, 
							 u8 collision_mask, 
							 On_Hit on_hit);

Body *physics_body_get(usize index);
Static_Body *physics_static_body_get(usize index);
Array_List *physics_static_body_list_array_get();
Array_List *physics_body_list_array_get();

Hit ray_intersect_aabb(vec3 pos, vec3 magnitude, AABB aabb);
bool ray_cast_line_bool(Body * P, vec3 position, vec3 D, u8 dist);

void physics_static_body_destroy_from_memory(usize body_id);
usize physics_static_body_count();
usize physics_static_body_create(vec3 position, 
								 vec3 size, 
								 u8 collision_layer);

bool physics_point_intersect_aabb(vec3 point, AABB aabb);
bool physics_aabb_intersect_aabb(AABB a, AABB b);
AABB aabb_minkowski_difference(AABB a, AABB b);
void aabb_penetration_vector(vec3 r, AABB aabb);
void aabb_min_max(vec3 min, vec3 max, AABB aabb);
Hit ray_intersect_aabb(vec3 position, vec3 magnitude, AABB aabb);
void physics_reset();
Static_Body *ray_cast_line(vec3 position, vec3 D, u8 dist);
Static_Body *ray_cast_line_static(Body  *body, 
								  vec3 position,
								  vec3 D, 
								  u8 dist);

Static_Body *static_body_physics_body_get(usize physics_id);
void physics_static_body_destroy_from_memory(usize body_id);
Array_List *physics_static_body_list_array_get();

void physics_body_destroy(usize body_id);
void static_physics_body_destroy(usize body_id);
void static_physics_body_destroy_from_memory(usize body_id);
void physics_body_destroy_from_memory(usize body_id);
void physics_static_reset(void);

#endif /* PHYSICS_H */

