#ifndef UAV_H
#define UAV_H


class UAV
{
public:
    UAV();

protected:
    float x;
    float y;
    float z;
    float dt;
    int ID;
};

class UAVModel1 : public UAV
{
public:
    UAVModel1(int ID,
              float x, float y, float z,
              float dt, float psi, float v, float U, float A);

public:
    static int nState;
    static int nControl;

    float psi;
    float v;

private:
    float U;
    float A;

public:
    void updateState(float u, float a);
};

int UAVModel1::nState = 5;
int UAVModel1::nControl = 2;

#endif // UAV_H
