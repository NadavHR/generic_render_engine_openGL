#ifndef IRENDER_OBJECT_HPP
#define IRENDER_OBJECT_HPP
#include "render_shader.hpp"

class IRenderObject {
    private:
        // this bool determines if this render object will be rendered in the current iteration   
        bool mVisible = true;
    
    protected:
        // this function should be overriden if there are cases in which the object should not be rendered that need to be checked for every frame
        virtual bool checkIfShouldRender() {return true;}
    public:
        // sets the visibility of the render object (an invisible render object will not attempt to render) 
        void setVisibility(bool visible) { mVisible = visible; }

        // checks if this render object is set to be visible or invisible
        bool isVisible() { return mVisible; }

        // checks if this render object should be rendered based on visibility AND whatever algorithm may be set to determine if it should be rendered
        bool shouldRender() {return (mVisible && checkIfShouldRender()); }

        /** the render function holds everything needed to render the object 
         * it assumes the correct shader is already in use
        */
        virtual void render(RenderShader &shader) {};
        virtual ~IRenderObject() = default;
};

#endif /* IRENDER_OBJECT_HPP */
