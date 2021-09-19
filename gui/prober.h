#ifndef PROBER_H
#define PROBER_H

class DrawnPlug;

// Something that can probe a plug
class Prober
{
public:
    Prober();
    virtual void setProbe(DrawnPlug *plug) = 0;
};

#endif // PROBER_H
