#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    //Animation () : frameStart(0), frameEnd(0), frameTime(0.0f) {}
    Animation (int frameStart, int frameEnd, float frameTime);
    int frameStart;
    int frameEnd;
    float frameTime;
};

#endif // ANIMATION_H
