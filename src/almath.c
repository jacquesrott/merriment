#include <stdio.h>

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


vec2* v2_scale(vec2* out, const vec2* a, const vec2* b) {
    out->x = a->x * b->x;
    out->y = a->y * b->y;
    return out;
}


void v2_print(const vec2* v) {
    printf("[ %f\t%f ]\n", v->x, v->y);
    printf("\n");
}


float v2_length(const vec2* v) {
    float l = v->x*v->x + v->y*v->y;
    return sqrt(l);
}


vec2* v2_polar(vec2* out, float length, float angle) {
    out->x = fabs(length) * cos(angle);
    out->y = fabs(length) * sin(angle);
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


vec3* v3_scale(vec3* out, const vec3* a, const vec3* b) {
    out->x = a->x * b->x;
    out->y = a->y * b->y;
    out->z = a->z * b->z;
    return out;
}


void v3_print(const vec3* v) {
    printf("[ %f\t%f\t%f ]\n", v->x, v->y, v->z);
    printf("\n");
}


float v3_length(const vec3* v) {
    float l = v->x*v->x + v->y*v->y + v->z*v->z;
    return sqrt(l);
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


vec4* v4_scale(vec4* out, const vec4* a, const vec4* b) {
    out->x = a->x * b->x;
    out->y = a->y * b->y;
    out->z = a->z * b->z;
    out->w = a->w * b->w;
    return out;
}


void v4_print(const vec4* v) {
    printf("[ %f\t%f\t%f\t%f ]\n", v->x, v->y, v->z, v->w);
    printf("\n");
}


float v4_length(const vec4* v) {
    float l = v->x*v->x + v->y*v->y + v->z*v->z + v->w*v->w;
    return sqrt(l);
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


mat4 m4_ortho3d(float near, float far, float top, float bottom, float left, float right) {
    mat4 m = {
        {
            {2.0 / (right-left), 0, 0, -((right+left) / (right-left))},
            {0, 2.0 / (bottom-top), 0, -((bottom+top) / (bottom-top))},
            {0, 0, -2.0 / (far-near), -((far+near) / (far-near))},
            {0, 0, 0, 1.0}
        }
    };
    return m;
}


mat4 m4_ortho2d(float top, float bottom, float left, float right) {
    mat4 m = {
        {
            {2.0 / (right-left), 0, 0, -((right+left) / (right-left))},
            {0, 2.0 / (bottom-top), 0, -((bottom+top) / (bottom-top))},
            {0, 0, -1.0, 0},
            {0, 0, 0, 1.0}
        }
    };
    return m;
}


mat4 m4_rotate(const vec3* v) {
    float cx = cos(v->x);
    float sx = sin(v->x);
    float cy = cos(v->y);
    float sy = sin(v->y);
    float cz = cos(v->z);
    float sz = sin(v->z);
    mat4 m = {
        {
            {cy*cz, cz*sx*sy - cx*sz, cx*cz*sy + sx*sz, 0},
            {cy*sz, cx*cz + sx*sy*sz, -cz*sx + cx*sy*sz, 0},
            {-sy, cy*sx, cx*cy, 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}


mat4 m4_rotatex(float x) {
    float cx = cos(x);
    float sx = sin(x);
    mat4 m = {
        {
            {1, 0, 0, 0},
            {0, cx, -sx, 0},
            {0, sx, cx, 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}


mat4 m4_rotatey(float y) {
    float cy = cos(y);
    float sy = sin(y);
    mat4 m = {
        {
            {cy, 0, sy, 0},
            {0, 1, 0, 0},
            {-sy, 0, cy, 0},
            {0, 0, 0, 1}
        }
    };
    return m;
}



mat4 m4_rotatez(float z) {
    float cz = cos(z);
    float sz = sin(z);
    mat4 m = {
        {
            {cz, -sz, 0, 0},
            {sz, cz, 0, 0},
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
    out->rows[0].x = b->rows[0].x*a->rows[0].x + b->rows[0].y*a->rows[1].x + b->rows[0].z*a->rows[2].x + b->rows[0].w*a->rows[3].x;
    out->rows[0].y = b->rows[0].x*a->rows[0].y + b->rows[0].y*a->rows[1].y + b->rows[0].z*a->rows[2].y + b->rows[0].w*a->rows[3].y;
    out->rows[0].z = b->rows[0].x*a->rows[0].z + b->rows[0].y*a->rows[1].z + b->rows[0].z*a->rows[2].z + b->rows[0].w*a->rows[3].z;
    out->rows[0].w = b->rows[0].x*a->rows[0].w + b->rows[0].y*a->rows[1].w + b->rows[0].z*a->rows[2].w + b->rows[0].w*a->rows[3].w;


    out->rows[1].x = b->rows[1].x*a->rows[0].x + b->rows[1].y*a->rows[1].x + b->rows[1].z*a->rows[2].x + b->rows[1].w*a->rows[3].x;
    out->rows[1].y = b->rows[1].x*a->rows[0].y + b->rows[1].y*a->rows[1].y + b->rows[1].z*a->rows[2].y + b->rows[1].w*a->rows[3].y;
    out->rows[1].z = b->rows[1].x*a->rows[0].z + b->rows[1].y*a->rows[1].z + b->rows[1].z*a->rows[2].z + b->rows[1].w*a->rows[3].z;
    out->rows[1].w = b->rows[1].x*a->rows[0].w + b->rows[1].y*a->rows[1].w + b->rows[1].z*a->rows[2].w + b->rows[1].w*a->rows[3].w;


    out->rows[2].x = b->rows[2].x*a->rows[0].x + b->rows[2].y*a->rows[1].x + b->rows[2].z*a->rows[2].x + b->rows[2].w*a->rows[3].x;
    out->rows[2].y = b->rows[2].x*a->rows[0].y + b->rows[2].y*a->rows[1].y + b->rows[2].z*a->rows[2].y + b->rows[2].w*a->rows[3].y;
    out->rows[2].z = b->rows[2].x*a->rows[0].z + b->rows[2].y*a->rows[1].z + b->rows[2].z*a->rows[2].z + b->rows[2].w*a->rows[3].z;
    out->rows[2].w = b->rows[2].x*a->rows[0].w + b->rows[2].y*a->rows[1].w + b->rows[2].z*a->rows[2].w + b->rows[2].w*a->rows[3].w;


    out->rows[3].x = b->rows[3].x*a->rows[0].x + b->rows[3].y*a->rows[1].x + b->rows[3].z*a->rows[2].x + b->rows[3].w*a->rows[3].x;
    out->rows[3].y = b->rows[3].x*a->rows[0].y + b->rows[3].y*a->rows[1].y + b->rows[3].z*a->rows[2].y + b->rows[3].w*a->rows[3].y;
    out->rows[3].z = b->rows[3].x*a->rows[0].z + b->rows[3].y*a->rows[1].z + b->rows[3].z*a->rows[2].z + b->rows[3].w*a->rows[3].z;
    out->rows[3].w = b->rows[3].x*a->rows[0].w + b->rows[3].y*a->rows[1].w + b->rows[3].z*a->rows[2].w + b->rows[3].w*a->rows[3].w;

    return out;
}


void m4_print(const mat4* m) {
    int i;
    for(i = 0; i < 4; i++) {
        v4_print(&m->rows[i]);
    }
    printf("\n");
}
