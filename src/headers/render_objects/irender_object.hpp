#ifndef IRENDER_OBJECT_HPP
#define IRENDER_OBJECT_HPP
#include "render_shader.hpp"

class IRenderObject {
    public:
        // this bool determines if this render object will be rendered in the current iteration  
        bool visible = true;

        /** the render function holds everything needed to render the object 
         * it assumes the correct shader is already in use
        */
        virtual void render(RenderShader &shader) {};
        virtual ~IRenderObject() = default;
};

#endif /* IRENDER_OBJECT_HPP */
