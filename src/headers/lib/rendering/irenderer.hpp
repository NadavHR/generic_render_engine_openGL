#ifndef IRENDERER_HPP
#define IRENDERER_HPP
// this class is an interface only used to make it so renderers will be more easily interchangable 
class IRenderer
{
public:
    // renders to whatever the output is 
    virtual void render() {}
};

#endif /* IRENDERER_HPP */
