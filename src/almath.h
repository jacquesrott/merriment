#ifndef DW_MATH_H
#define DW_MATH_H


typedef struct {
    float x;
    float y;
} vec2;


typedef struct {
    float x;
    float y;
    float z;
} vec3;


typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4;


typedef struct {
    vec4 rows[4];
} mat4;


typedef vec4 quat;


vec2* v2_p_v2(vec2* out, const vec2* a, const vec2* b);
vec2* v2_m_v2(vec2* out, const vec2* a, const vec2* b);
vec2* v2_x_f(vec2* out, const vec2* v, float f);
vec2* v2_d_f(vec2* out, const vec2* v, float f);
vec2* v2_dot_v2(vec2* out, const vec2* a, const vec2* b);
vec2* v2_scale(vec2* out, const vec2* a, const vec2* b);
float v2_length(const vec2* v);
void v2_print(const vec2* v);

vec3* v3_p_v3(vec3* out, const vec3* a, const vec3* b);
vec3* v3_m_v3(vec3* out, const vec3* a, const vec3* b);
vec3* v3_x_f(vec3* out, const vec3* v, float f);
vec3* v3_d_f(vec3* out, const vec3* v, float f);
vec3* v3_dot_v3(vec3* out, const vec3* a, const vec3* b);
vec3* v3_scale(vec3* out, const vec3* a, const vec3* b);
void v3_print(const vec3* v);
float v3_length(const vec3* v);
vec4 v3_to_v4(const vec3* v);

vec4* v4_p_v4(vec4* out, const vec4* a, const vec4* b);
vec4* v4_m_v4(vec4* out, const vec4* a, const vec4* b);
vec4* v4_x_f(vec4* out, const vec4* v, float f);
vec4* v4_d_f(vec4* out, const vec4* v, float f);
vec4* v4_dot_v4(vec4* out, const vec4* a, const vec4* b);
vec4* v4_scale(vec4* out, const vec4* a, const vec4* b);
void v4_print(const vec4* v);
float v4_length(const vec4* v);

mat4 m4_identity();
mat4 m4_scalef(float i);
mat4 m4_scale(const vec3* v);
mat4 m4_translate(const vec3* v);
mat4 m4_ortho3d(float near, float far, float top, float bottom, float left, float right);
mat4 m4_ortho2d(float top, float bottom, float left, float right);

mat4 m4_rotate(const vec3* v);
mat4 m4_rotatex(float x);
mat4 m4_rotatey(float y);
mat4 m4_rotatez(float z);

vec3* m4_x_v3(vec3* out, const mat4* m, const vec3* v);
vec4* m4_x_v4(vec4* out, const mat4* m, const vec4* v);
mat4* m4_x_m4(mat4* out, const mat4* a, const mat4* b);
void m4_print(const mat4* m);

#endif
