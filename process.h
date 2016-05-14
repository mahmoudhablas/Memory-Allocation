#ifndef PROCESS_H
#define PROCESS_H

class process
{
private:
    double address;
    double size;
    int Id;
public:
    process();
    process(double x,double y,int f=0);
    void setId(int x);
    void setAdd(double x);
    void setSize(double x);
    double getSize();
    double getAdd();
    int getId();
};

#endif // PROCESS_H
