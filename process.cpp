#include "process.h"

process::process()
{
    address=0;
    size =0;
    Id=0;
}
process::process(double x,double y,int f)
{
    address =x;
    size =y;
    Id =f;
}
void process ::setId(int x)
{
    Id = x;
}

void process :: setAdd(double x)
{
    address =x;
}

void process ::setSize(double x)
{
    size =x;
}

double process ::getSize()
{
    return size;
}

double process :: getAdd()
{
    return address;
}

int process ::getId()
{
    return Id;
}
