#ifndef SCREEN_RENDER_OBJECT_HPP
#define SCREEN_RENDER_OBJECT_HPP
#include "irender_object.hpp"

const float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

class ScreenRenderObject : public IRenderObject {
    private:
        static unsigned int quadVAO, quadVBO;
        static void drawSquare();
    
    public:
        void render(RenderShader &shader) override;
        ScreenRenderObject();

};

#endif /* SCREEN_RENDER_OBJECT_HPP */
