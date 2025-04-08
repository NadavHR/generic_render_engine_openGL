#ifndef RENDER_TARGET_GROUP_HPP
#define RENDER_TARGET_GROUP_HPP
#include <vector>
#include <memory>
#include <stack>
#include <functional>
#include "irender_object.hpp"
#include "render_shader.hpp"

/** this class groups together multiple render objects that are supposed to be rendered with the same shader and parameters
 * 
 */
class RenderTargetGroup 
{
private:
    std::function<void(RenderShader&, const RenderParams&)> mSetRenderSettings; 
    std::function<void(RenderShader&, const RenderParams&)> mPostRender; 
    RenderShader &mShader;
    void drawAll();
    std::vector<std::shared_ptr<IRenderObject>> mRenderObjects;
    std::stack<size_t> mAvailableIndices;
    
public:
    /**adds a render object to the group 
     * @returns the unique index of the render object in the group
     */
    size_t addRenderObject(std::shared_ptr<IRenderObject> renderObject);

    /**pops a render object out of the group emptying its index
     * @returns pointer to the render object
     */
    std::shared_ptr<IRenderObject> popRenderObject(size_t index);

    /**gets the render object in the specified index
     * @returns pointer to the render object
     */
    std::shared_ptr<IRenderObject> getRenderObject(size_t index);

    /**renders all render objects in the group
     * 
     */
    void render(RenderParams const &params);

    RenderShader& getShader();

    /** constructs render target group
     *  @param shader the shader all render objects will be drawn with
     *  @param setRenderSettings lambda expression that runs before rendering every frame, used to set uniforms and such
     *  @param postRender lambda expression that runs after finishing rendering, used to set back settings that changed in `setRenderSettings` (if needed)
     */
    RenderTargetGroup(RenderShader &shader, 
        std::function<void(RenderShader&, const RenderParams&)> setRenderSettings = [] (RenderShader& shader, const RenderParams& params) {},
         std::function<void(RenderShader&, const RenderParams&)> postRender = [] (RenderShader& shader, const RenderParams& params) {} );
    ~RenderTargetGroup();
};



#endif /* RENDER_TARGET_GROUP_HPP */
