#include "avdl_physics.h"
#include "dd_math.h"
#include "avdl_collider.h"
#include "avdl_collider_aabb.h"
#include "avdl_collider_sphere.h"

struct manifold {
	int collide;
	struct dd_vec3 normal;
	float penetration;
};

void avdl_physics_create(struct avdl_physics *o) {
	o->object_count = 0;
	avdl_physics_clearConstantForce(o);

	o->update = avdl_physics_update;
	o->addObject = avdl_physics_addObject;

	o->addConstantForcef = avdl_physics_addConstantForcef;
	o->clearConstantForce = avdl_physics_clearConstantForce;
}

void avdl_physics_collision_aabbVSaabb(struct manifold *m, struct avdl_rigidbody *a, struct avdl_rigidbody *b) {
}

void avdl_physics_collision_aabbVSsphere(struct manifold *m, struct avdl_rigidbody *a, struct avdl_rigidbody *b) {

	/*
	dd_log("aabb vs sphere CHECK");
	dd_log("~~~~~~~~~~~~~~~~");
	*/

	struct avdl_collider_aabb *a_col = a->collider;
	struct avdl_collider_sphere *b_col = b->collider;

	/*
	dd_log("a: %f - %f - %f",
		a->position.x,
		a->position.y,
		a->position.z
	);
	dd_log("b: %f - %f - %f",
		b->position.x,
		b->position.y,
		b->position.z
	);
	*/

	// vector from obj A to obj B
	struct dd_vec3 diff;
	dd_vec3_setf(&diff,
		b->position.x -a->position.x,
		b->position.y -a->position.y,
		b->position.z -a->position.z
	);
	//dd_log("diff: %f - %f - %f", diff.x, diff.y, diff.z);

	/*
	dd_log("a min: %f - %f - %f", a_col->min.x, a_col->min.y, a_col->min.z);
	dd_log("a max: %f - %f - %f", a_col->max.x, a_col->max.y, a_col->max.z);
	*/

	// find closest point on aabb
	struct dd_vec3 closest;
	dd_vec3_setf(&closest,
		dd_math_clamp(a->position.x -a_col->max.x, a->position.x +a_col->max.x, a->position.x +diff.x),
		dd_math_clamp(a->position.y -a_col->max.y, a->position.y +a_col->max.y, a->position.y +diff.y),
		dd_math_clamp(a->position.z -a_col->max.z, a->position.z +a_col->max.z, a->position.z +diff.z)
	);
	//dd_log("closest: %f - %f - %f", closest.x, closest.y, closest.z);

	struct dd_vec3 normal;
	dd_vec3_setf(&normal,
		//diff.x -closest.x,
		//diff.y -closest.y,
		//diff.z -closest.z
		b->position.x -closest.x,
		b->position.y -closest.y,
		b->position.z -closest.z
	);
	//dd_log("normal: %f - %f - %f", normal.x, normal.y, normal.z);

	float r = b_col->radius;
	//dd_log("radius: %f", b_col->radius);
	float d = dd_vec3_magnitude(&normal);
	//dd_log("magnit: %f", d);

	if ( r < d) {
		m->collide = 0;
	}
	else {
		m->collide = 1;
		dd_vec3_set(&m->normal, &normal);
		dd_vec3_normalise(&m->normal);
		m->penetration = r -d;
		//dd_log("m->normal: %f - %f - %f", m->normal.x, m->normal.y, m->normal.z);
	}
}

void avdl_physics_collision_sphereVSsphere(struct manifold *m, struct avdl_rigidbody *a, struct avdl_rigidbody *b) {

	/*
	dd_log("aabb vs sphere CHECK");
	dd_log("~~~~~~~~~~~~~~~~");
	*/

	struct avdl_collider_sphere *a_col = a->collider;
	struct avdl_collider_sphere *b_col = b->collider;

	/*
	dd_log("a: %f - %f - %f",
		a->position.x,
		a->position.y,
		a->position.z
	);
	dd_log("b: %f - %f - %f",
		b->position.x,
		b->position.y,
		b->position.z
	);
	*/

	// vector from obj A to obj B
	struct dd_vec3 diff;
	dd_vec3_setf(&diff,
		b->position.x -a->position.x,
		b->position.y -a->position.y,
		b->position.z -a->position.z
	);
	//dd_log("diff: %f - %f - %f", diff.x, diff.y, diff.z);

	float distance = dd_vec3_magnitude(&diff);

	/*
	*/
	// find closest point on aabb
	struct dd_vec3 contact;
	dd_vec3_setf(&contact,
		a->position.x +(diff.x /2),
		a->position.y +(diff.y /2),
		a->position.z +(diff.z /2)
	);
	//dd_log("closest: %f - %f - %f", closest.x, closest.y, closest.z);

	struct dd_vec3 normal;
	dd_vec3_setf(&normal,
		b->position.x -contact.x,
		b->position.y -contact.y,
		b->position.z -contact.z
	);
	//dd_log("normal: %f - %f - %f", normal.x, normal.y, normal.z);

	// collision!
	if (distance < a_col->radius +b_col->radius) {
		m->collide = 1;
		dd_vec3_set(&m->normal, &normal);
		dd_vec3_normalise(&m->normal);
		m->penetration = distance -( a_col->radius + b_col->radius );
	}
	// no collision
	else {
		m->collide = 0;
	}

}

void avdl_physics_update(struct avdl_physics *o) {

	// move objects
	for (int i = 0; i < o->object_count; i++) {
		// calculate this frame's acceleration
		struct dd_vec3 acceleration;
		dd_vec3_setf(&acceleration, 0, 0, 0);

		// constant force
		dd_vec3_addf(&acceleration,
			o->constant_force.x *o->object[i]->mass_inv,
			o->constant_force.y *o->object[i]->mass_inv,
			o->constant_force.z *o->object[i]->mass_inv
		);

		// add acceleration to velocity
		dd_vec3_add(&o->object[i]->velocity, &o->object[i]->velocity, &acceleration);

		// apply velocity to position
		dd_vec3_add(&o->object[i]->position, &o->object[i]->position, &o->object[i]->velocity);
	}

	// collisions
	for (int i = 0; i < o->object_count-1; i++) {
		for (int j = i+1; j < o->object_count; j++) {

			int collision = 0;
			struct manifold m;
			m.collide = 0;
			// aabb
			if (o->object[i]->collider && o->object[i]->collider->type == AVDL_COLLIDER_TYPE_AABB) {
				// vs aabb
				if (o->object[j]->collider && o->object[j]->collider->type == AVDL_COLLIDER_TYPE_AABB) {
					//avdl_physics_collision_aabbVSaabb(&m, o->object[i], o->object[j]);
					//dd_log("aabb vs aabb");
				}
				else
				// vs sphere
				if (o->object[j]->collider && o->object[j]->collider->type == AVDL_COLLIDER_TYPE_SPHERE) {
					avdl_physics_collision_aabbVSsphere(&m, o->object[i], o->object[j]);
					m.normal.x *= -1;
					m.normal.y *= -1;
					m.normal.z *= -1;
					//dd_log("aabb vs sphere");
				}
				else {
					dd_log("aabb vs ???");
				}
			}
			else
			// sphere
			if (o->object[i]->collider && o->object[i]->collider->type == AVDL_COLLIDER_TYPE_SPHERE) {
				// vs aabb
				if (o->object[j]->collider && o->object[j]->collider->type == AVDL_COLLIDER_TYPE_AABB) {
					avdl_physics_collision_aabbVSsphere(&m, o->object[j], o->object[i]);
					//dd_log("sphere vs aabb");
				}
				else
				// vs sphere
				if (o->object[j]->collider && o->object[j]->collider->type == AVDL_COLLIDER_TYPE_SPHERE) {
					avdl_physics_collision_sphereVSsphere(&m, o->object[i], o->object[j]);
					//dd_log("sphere vs sphere");
				}
				else {
					dd_log("sphere vs ???");
				}
			}

			// radius smaller than distance - no collision
			if (m.collide) {
				//dd_log("Collision!");

				// total mass
				float mass_total = o->object[i]->mass +o->object[j]->mass;

				// relative velocity
				struct dd_vec3 rv;
				dd_vec3_setf(&rv,
					o->object[j]->velocity.x -o->object[i]->velocity.x,
					o->object[j]->velocity.y -o->object[i]->velocity.y,
					o->object[j]->velocity.z -o->object[i]->velocity.z
				);
				dd_log("rv: %f - %f - %f", rv.x, rv.y, rv.z);
				dd_log("m.normal: %f - %f - %f", m.normal.x, m.normal.y, m.normal.z);

				// elasticity - lowest of two
				float e = dd_math_min(o->object[i]->restitution, o->object[j]->restitution);
				float velAlongNormal = dd_vec3_dot(&rv, &m.normal);
				float z = -(1 +e) *velAlongNormal;
				z /= o->object[i]->mass_inv +o->object[j]->mass_inv;

				// calculate impulse
				struct dd_vec3 impulse;
				dd_vec3_setf(&impulse,
					m.normal.x *z,
					m.normal.y *z,
					m.normal.z *z
				);
				//dd_log("impulse: %f - %f - %f", impulse.x, impulse.y, impulse.z);

				// apply impulse
				dd_vec3_setf(&o->object[i]->velocity,
					o->object[i]->velocity.x - o->object[i]->mass_inv *impulse.x,
					o->object[i]->velocity.y - o->object[i]->mass_inv *impulse.y,
					o->object[i]->velocity.z - o->object[i]->mass_inv *impulse.z
				);

				dd_vec3_setf(&o->object[j]->velocity,
					o->object[j]->velocity.x + o->object[j]->mass_inv *impulse.x,
					o->object[j]->velocity.y + o->object[j]->mass_inv *impulse.y,
					o->object[j]->velocity.z + o->object[j]->mass_inv *impulse.z
				);

				// correct position so objects don't collide
				struct dd_vec3 correction;
				dd_vec3_setf(&correction,
					m.normal.x *m.penetration,
					m.normal.y *m.penetration,
					m.normal.z *m.penetration
				);
				//dd_log("correction: %f - %f - %f", correction.x, correction.y, correction.z);

				dd_vec3_setf(&o->object[i]->position,
					o->object[i]->position.x + o->object[i]->mass_inv *correction.x,
					o->object[i]->position.y + o->object[i]->mass_inv *correction.y,
					o->object[i]->position.z + o->object[i]->mass_inv *correction.z
				);
				dd_vec3_setf(&o->object[j]->position,
					o->object[j]->position.x - o->object[j]->mass_inv *correction.x,
					o->object[j]->position.y - o->object[j]->mass_inv *correction.y,
					o->object[j]->position.z - o->object[j]->mass_inv *correction.z
				);

//				// friction
//				// Re-calculate relative velocity after normal impulse
//				// is applied (impulse from first article, this code comes
//				// directly thereafter in the same resolve function)
//				//Vec2 rv = VB - VA
//				// relative velocity
//				struct dd_vec3 rv2;
//				dd_vec3_setf(&rv2,
//					o->object[j]->velocity.x -o->object[i]->velocity.x,
//					o->object[j]->velocity.y -o->object[i]->velocity.y,
//					o->object[j]->velocity.z -o->object[i]->velocity.z
//					/*
//					-o->object[j]->velocity.x +o->object[i]->velocity.x,
//					-o->object[j]->velocity.y +o->object[i]->velocity.y,
//					-o->object[j]->velocity.z +o->object[i]->velocity.z
//					*/
//				);
//				dd_log("rv2: %f - %f - %f", rv2.x, rv2.y, rv2.z);
//
//				// Solve for the tangent vector
//				//Vec2 tangent = rv - Dot( rv, normal ) * normal
//				//tangent.Normalize( )
//				struct dd_vec3 tangent2;
//				dd_vec3_setf(&tangent2,
//					rv2.x -dd_vec3_dot(&rv2, &m.normal) *m.normal.x,
//					rv2.y -dd_vec3_dot(&rv2, &m.normal) *m.normal.y,
//					rv2.z -dd_vec3_dot(&rv2, &m.normal) *m.normal.z
//				);
//				dd_log("dot: %f", dd_vec3_dot(&rv2, &m.normal));
//				dd_log("tangent2 pre norm: %f - %f - %f", tangent2.x, tangent2.y, tangent2.z);
//				dd_vec3_normalise(&tangent2);
//				/*
//				if (isnan(tangent2.x)) {
//					dd_vec3_setf(&tangent2,
//						0,
//						-1,
//						0
//					);
//				}
//				*/
//				dd_log("tangent2: %f - %f - %f", tangent2.x, tangent2.y, tangent2.z);
//
//				// Solve for magnitude to apply along the friction vector
//				//float jt = -Dot( rv, t )
//				//jt = jt / (1 / MassA + 1 / MassB)
//				float jt = -dd_vec3_dot( &rv2, &tangent2 );
//				jt /= o->object[i]->mass_inv +o->object[j]->mass_inv;
//				//dd_log("jt: %f", jt);
//
//				// PythagoreanSolve = A^2 + B^2 = C^2, solving for C given A and B
//				// Use to approximate mu given friction coefficients of each body
//				//float mu = PythagoreanSolve( A->staticFriction, B->staticFriction )
//				float mu = dd_math_sqrt(dd_math_pow(0.5, 2) +dd_math_pow(0.5, 2));
//				//dd_log("mu: %f", mu);
//
//				// Clamp magnitude of friction and create impulse vector
//				//Vec2 frictionImpulse
//				struct dd_vec3 frictionImpulse;
//				if( dd_math_abs( jt ) < z * mu )
//					dd_vec3_setf(&frictionImpulse,
//						jt * tangent2.x,
//						jt * tangent2.y,
//						jt * tangent2.z
//					);
//				else {
//					//float dynamicFriction = PythagoreanSolve( A->dynamicFriction, B->dynamicFriction )
//					//frictionImpulse = -j * t * dynamicFriction
//					//float dynamicFriction = 1;
//					float dynamicFriction = dd_math_sqrt(dd_math_pow(0.5, 2) +dd_math_pow(0.5, 2));
//					dd_vec3_setf(&frictionImpulse,
//						-z *tangent2.x *dynamicFriction,
//						-z *tangent2.y *dynamicFriction,
//						-z *tangent2.z *dynamicFriction
//					);
//				}
//				//dd_log("frictionImpulse: %f - %f - %f", frictionImpulse.x, frictionImpulse.y, frictionImpulse.z);
//				/*
//
//				// Apply
//				A->velocity -= (1 / A->mass) * frictionImpulse
//				B->velocity += (1 / B->mass) * frictionImpulse
//				*/
//				// apply friction impulse
//				dd_vec3_setf(&o->object[i]->velocity,
//					o->object[i]->velocity.x - o->object[i]->mass_inv *frictionImpulse.x,
//					o->object[i]->velocity.y - o->object[i]->mass_inv *frictionImpulse.y,
//					o->object[i]->velocity.z - o->object[i]->mass_inv *frictionImpulse.z
//				);
//
//				dd_vec3_setf(&o->object[j]->velocity,
//					o->object[j]->velocity.x + o->object[j]->mass_inv *frictionImpulse.x,
//					o->object[j]->velocity.y + o->object[j]->mass_inv *frictionImpulse.y,
//					o->object[j]->velocity.z + o->object[j]->mass_inv *frictionImpulse.z
//				);
//				//dd_log("new vel1: %f - %f - %f", o->object[i]->velocity.x, o->object[i]->velocity.y, o->object[i]->velocity.z);
//				//dd_log("new vel2: %f - %f - %f", o->object[j]->velocity.x, o->object[j]->velocity.y, o->object[j]->velocity.z);
			}
		}
	}
}

void avdl_physics_clean(struct avdl_physics *o) {
}

void avdl_physics_addObject(struct avdl_physics *o, struct avdl_rigidbody *obj) {
	if (o->object_count == 10) {
		dd_log("avdl error: physics engine: can't add more than 10 objects");
		return;
	}

	o->object[o->object_count] = obj;
	o->object_count++;
}

void avdl_physics_addConstantForcef(struct avdl_physics *o, float x, float y, float z) {
	dd_vec3_addf(&o->constant_force, x, y, z);
}

void avdl_physics_clearConstantForce(struct avdl_physics *o) {
	dd_vec3_setf(&o->constant_force, 0, 0, 0);
}
