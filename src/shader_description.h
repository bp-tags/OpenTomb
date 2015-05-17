#ifndef __OpenTomb__shader_description__
#define __OpenTomb__shader_description__

#include <SDL2/SDL_platform.h>
#include <SDL2/SDL_opengl.h>
#include "gl_util.h"

/*!
 * A shader description consists of a program, code to load the
 * program, and the indices of the various uniform values. Each
 * shader or set of related shaders will have its own subclass
 * of shader_description. We assume (for now) that every shader
 * has a texture.
 */
struct shader_description
{
    GLhandleARB program;
    GLint sampler;
    
    shader_description(const char *vertexFilename, const char *fragmentFilename);
    shader_description(const char *vertexFilename, GLhandleARB fragmentShader);
    ~shader_description();
    
private:
    /*! Called by constructor to load data. */
    void load(GLhandleARB vertex, GLhandleARB fragment);
};

/*!
 * A shader description type that contains transform information. This comes in the form of a model view projection matrix.
 */
struct unlit_shader_description : public shader_description
{
    GLint model_view_projection;
    
    unlit_shader_description(const char *vertexFilename, const char *fragmentFilename);
    unlit_shader_description(const char *vertexFilename, GLhandleARB fragmentShader);
};

/*!
 * A shader description type that is suitable for lit objects. Also
 * contains a model view matrix and information about the current
 * light situation
 */
struct lit_shader_description : public unlit_shader_description
{
    GLint model_view;
    GLint number_of_lights;
    GLint light_position;
    GLint light_color;
    GLint light_falloff;
    GLint light_ambient;
    
    lit_shader_description(const char *vertexFilename, const char *fragmentFilename);
};

struct unlit_tinted_shader_description : public unlit_shader_description
{
    GLint current_tick;
    GLint tint_mult;
    
    unlit_tinted_shader_description(const char *vertexFilename, const char *fragmentFilename);
    unlit_tinted_shader_description(const char *vertexFilename, GLhandleARB fragmentShader);
};

#endif /* defined(__OpenTomb__shader_description__) */