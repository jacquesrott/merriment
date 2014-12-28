#include <math.h>

#include "almath.h"


// Vec2

vec2* v2_p_v2(vec2* out, const vec2* a, const vec2* b) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    return out;
}


vec2* v2_m_v2(vec2* out, const vec2* a, const vec2* b) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    return out;
}


vec2* v2_x_f(vec2* out, const vec2* v, float f) {
    out->x = v->x * f;
    out->y = v->y * f;
    return out;
}


vec2* v2_d_f(vec2* out, const vec2* v, float f) {
    out->x = v->x / f;
    out->y = v->y / f;
    return out;
}


vec2* v2_dot_v2(vec2* out, const vec2* a, const vec2* b) {
    out->x = a->x * b->x + a->y * b->x;
    out->y = a->x * b->y + a->y * b->y;
    return out;
}


// Vec3


vec3* v3_p_v3(vec3* out, const vec3* a, const vec3* b) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
    return out;
}


vec3* v3_m_v3(vec3* out, const vec3* a, const vec3* b) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
    return out;
}


vec3* v3_x_f(vec3* out, const vec3* v, float f) {
    out->x = v->x * f;
    out->y = v->y * f;
    out->z = v->z * f;
    return out;
}


vec3* v3_d_f(vec3* out, const vec3* v, float f) {
    out->x = v->x / f;
    out->y = v->y / f;
    out->z = v->z / f;
    return out;
}


vec3* v3_dot_v3(vec3* out, const vec3* a, const vec3* b) {
    out->x = a->x * b->x + a->y * b->x + a->z * b->x;
    out->y = a->x * b->y + a->y * b->y + a->z * b->y;
    out->z = a->x * b->z + a->y * b->z + a->z * b->z;
    return out;
}


vec4 v3_to_v4(const vec3* v) {
    vec4 out = {
        .x=v->x,
        .y=v->y,
        .z=v->z,
        .w=1.0
    };
    return out;
}



// Vec4

vec4* v4_p_v4(vec4* out, const vec4* a, const vec4* b) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
    out->w = a->w + b->w;
    return out;
}


vec4* v4_m_v4(vec4* out, const vec4* a, const vec4* b) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
    out->w = a->w - b->w;
    return out;
}


vec4* v4_x_f(vec4* out, const vec4* v, float f) {
    out->x = v->x * f;
    out->y = v->y * f;
    out->z = v->z * f;
    out->w = v->w * f;
    return out;
}


vec4* v4_d_f(vec4* out, const vec4* v, float f) {
    out->x = v->x / f;
    out->y = v->y / f;
    out->z = v->z / f;
    out->w = v->w / f;
    return out;
}


vec4* v4_dot_v4(vec4* out, const vec4* a, const vec4* b) {
    out->x = a->x * b->x + a->y * b->x + a->z * b->x + a->w * b->x;
    out->y = a->x * b->y + a->y * b->y + a->z * b->y + a->w * b->y;
    out->z = a->x * b->z + a->y * b->z + a->z * b->z + a->w * b->z;
    out->w = a->x * b->w + a->y * b->w + a->z * b->w + a->w * b->w;
    return out;
}


// Mat4


mat4 m4_identity() {
    mat4 m = {
        {
            {1.0, 0, 0, 0},
            {0, 1.0, 0, 0},
            {0, 0, 1.0, 0},
            {0, 0, 0, 1.0}
        }
    };
    return m;
}


mat4 m4_scalef(float i) {
    mat4 m = {
        {
            {i, 0, 0, 0},
            {0, i, 0, 0},
            {0, 0, i, 0},
            {0, 0, 0, 1.0}
        }
    };
    return m;
}


mat4 m4_scale(const vec3* v) {
    mat4 m = {
        {
            {v->x, 0, 0, 0},
            {0, v->y, 0, 0},
            {0, 0, v->z, 0},
            {0, 0, 0, 1.0}
        }
    };
    return m;
}


mat4 m4_translate(const vec3* v) {
    mat4 m = {
        {
            {1, 0, 0, v->x},
            {0, 1, 0, v->y},
            {0, 0, 1, v->z},
            {0, 0, 0, 1}
        }
    };
    return m;
}


mat4 m4_rotate(const vec3* v) {
    mat4 m = {
        {
            {cos(v->y)*cos(v->z), cos(v->z)*sin(v->x)*sin(v->y) - cos(v->x)*sin(v->z), cos(v->x)*cos(v->z)*sin(v->y) + sin(v->x)*sin(v->z), 0},
            {cos(v->y)*sin(v->z), cos(v->x)*cos(v->z) + sin(v->x)*sin(v->y)*sin(v->z), -cos(v->z)*sin(v->x) + cos(v->x)*sin(v->y)*sin(v->z), 0},
            {-sin(v->y), cos(v->y)*sin(v->x), cos(v->x)*cos(v->y), 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}


mat4 m4_rotatex(float x) {
    mat4 m = {
        {
            {1, 0, 0, 0},
            {0, cos(x), -sin(x), 0},
            {0, sin(x), cos(x), 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}


mat4 m4_rotatey(float y) {
    mat4 m = {
        {
            {cos(y), 0, sin(y), 0},
            {0, 1, 0, 0},
            {-sin(y), 0, cos(y), 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}



mat4 m4_rotatez(float z) {
    mat4 m = {
        {
            {cos(z), -sin(z), 0, 0},
            {sin(z), cos(z), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}


vec3* m4_x_v3(vec3* out, const mat4* m, const vec3* v) {
    out->x = m->rows[0].x * v->x + m->rows[0].y * v->y + m->rows[0].z * v->z + m->rows[0].w;
    out->y = m->rows[1].x * v->x + m->rows[1].y * v->y + m->rows[1].z * v->z + m->rows[1].w;
    out->z = m->rows[2].x * v->x + m->rows[2].y * v->y + m->rows[2].z * v->z + m->rows[2].w;
    return out;
}


vec4* m4_x_v4(vec4* out, const mat4* m, const vec4* v) {
    out->x = m->rows[0].x * v->x + m->rows[0].y * v->y + m->rows[0].z * v->z + m->rows[0].w * v->w;
    out->y = m->rows[1].x * v->x + m->rows[1].y * v->y + m->rows[1].z * v->z + m->rows[1].w * v->w;
    out->z = m->rows[2].x * v->x + m->rows[2].y * v->y + m->rows[2].z * v->z + m->rows[2].w * v->w;
    out->w = m->rows[3].x * v->x + m->rows[3].y * v->y + m->rows[3].z * v->z + m->rows[3].w * v->w;
    return out;
}


mat4* m4_x_m4(mat4* out, const mat4* a, const mat4* b) {
    out->rows[0].x = a->rows[0].x*b->rows[0].x + a->rows[0].y*b->rows[1].x + a->rows[0].z*b->rows[2].x + a->rows[0].w*b->rows[3].x;
    out->rows[0].y = a->rows[0].x*b->rows[0].y + a->rows[0].y*b->rows[1].y + a->rows[0].z*b->rows[2].y + a->rows[0].w*b->rows[3].y;
    out->rows[0].z = a->rows[0].x*b->rows[0].z + a->rows[0].y*b->rows[1].z + a->rows[0].z*b->rows[2].z + a->rows[0].w*b->rows[3].z;
    out->rows[0].w = a->rows[0].x*b->rows[0].w + a->rows[0].y*b->rows[1].w + a->rows[0].z*b->rows[2].w + a->rows[0].w*b->rows[3].w;


    out->rows[1].x = a->rows[1].x*b->rows[0].x + a->rows[1].y*b->rows[1].x + a->rows[1].z*b->rows[2].x + a->rows[1].w*b->rows[3].x;
    out->rows[1].y = a->rows[1].x*b->rows[0].y + a->rows[1].y*b->rows[1].y + a->rows[1].z*b->rows[2].y + a->rows[1].w*b->rows[3].y;
    out->rows[1].z = a->rows[1].x*b->rows[0].z + a->rows[1].y*b->rows[1].z + a->rows[1].z*b->rows[2].z + a->rows[1].w*b->rows[3].z;
    out->rows[1].w = a->rows[1].x*b->rows[0].w + a->rows[1].y*b->rows[1].w + a->rows[1].z*b->rows[2].w + a->rows[1].w*b->rows[3].w;


    out->rows[2].x = a->rows[2].x*b->rows[0].x + a->rows[2].y*b->rows[1].x + a->rows[2].z*b->rows[2].x + a->rows[2].w*b->rows[3].x;
    out->rows[2].y = a->rows[2].x*b->rows[0].y + a->rows[2].y*b->rows[1].y + a->rows[2].z*b->rows[2].y + a->rows[2].w*b->rows[3].y;
    out->rows[2].z = a->rows[2].x*b->rows[0].z + a->rows[2].y*b->rows[1].z + a->rows[2].z*b->rows[2].z + a->rows[2].w*b->rows[3].z;
    out->rows[2].w = a->rows[2].x*b->rows[0].w + a->rows[2].y*b->rows[1].w + a->rows[2].z*b->rows[2].w + a->rows[2].w*b->rows[3].w;


    out->rows[3].x = a->rows[3].x*b->rows[0].x + a->rows[3].y*b->rows[1].x + a->rows[3].z*b->rows[2].x + a->rows[3].w*b->rows[3].x;
    out->rows[3].y = a->rows[3].x*b->rows[0].y + a->rows[3].y*b->rows[1].y + a->rows[3].z*b->rows[2].y + a->rows[3].w*b->rows[3].y;
    out->rows[3].z = a->rows[3].x*b->rows[0].z + a->rows[3].y*b->rows[1].z + a->rows[3].z*b->rows[2].z + a->rows[3].w*b->rows[3].z;
    out->rows[3].w = a->rows[3].x*b->rows[0].w + a->rows[3].y*b->rows[1].w + a->rows[3].z*b->rows[2].w + a->rows[3].w*b->rows[3].w;

    return out;
}
