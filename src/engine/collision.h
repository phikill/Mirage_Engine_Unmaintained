#ifndef COLLISION_H
#define COLLISION_H

typedef enum collision_layer {
	COLLISION_LAYER_PLAYER = 1,
	COLLISION_LAYER_ENEMY = 1 << 1,
	COLLISION_LAYER_TERRAIN = 1 << 2,
	COLLISION_LAYER_ENEMY_PASSTHROUGH = 1 << 3,
    COLLISION_LAYER_PROJECTILE = 1 << 4,
    COLLISION_LAYER_HOUSE = 1 << 5,

} Collision_Layer;

#endif