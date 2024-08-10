
#ifndef PROJECT_3_VISUAL_H
#define PROJECT_3_VISUAL_H

class Visual {

public:
    virtual void draw(RenderWindow& screen) = 0;
    virtual ~Visual()= default;
};

#endif
