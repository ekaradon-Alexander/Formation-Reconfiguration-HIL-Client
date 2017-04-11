#include "uav.h"

UAV::UAV()
{

}

UAVModel1::UAVModel1(int ID,
                     float x, float y, float z, float dt,
                     float psi, float v, float U, float A)
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->z = z;
    this->dt = dt;
    this->psi = psi;
    this->v = v;
    this->U = U;
    this->A = A;
}
