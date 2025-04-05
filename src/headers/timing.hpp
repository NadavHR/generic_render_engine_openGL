#ifndef TIMING_HPP
#define TIMING_HPP
// implemented in main because that is where we process time
/** Gives the exact deltaTime (in seconds) between the last 2 frames without any processing
 *
 * great for timing effects that always need to update at the same rate (like for example UI elements)
*/
float getDeltaTimeRawSec();


/** Gives a deltaTime (by default in seconds) that is scaled by some "time scalar", this allows for speeding up or slowing down time   
 * 
 * we can use this to mess with time in a way that only affects gameplay objects, like freezing the world to enter a camera mode, slowing down or speeding up simulations, and so on
 */
float getDeltaTime() {  
    return getDeltaTimeRawSec() * timeScalar;
}
float timeScalar = 1.0; // TODO: make this private so it could be only accessed with getters and setters that limit its range according to settings


#endif /* TIMING_HPP */
