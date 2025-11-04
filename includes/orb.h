#include "project.h"
#ifndef ORB_H
#define ORB_H
class Orb
{
  public:
    Orb(const int x_pos = W / 2, const int y_pos = H / 2, const int rad = 3, const int v_y = 5, const int v_x = 5)
        :ps(&sf), x(x_pos), y(y_pos), r(rad), vx(v_x), vy(v_y), color(BLUE)
    {}
    void run();
    void draw();
    void flash();
    void move();
    bool touched(Orb * orb1);
    void touching_wall();
    int x, y, r, vx, vy;
    Color color;
    Surface * ps;
    bool checked;
  private:
};
void Orb::touching_wall()
{
    //add something funny where when they touch
    //the wall they reset their speed but touching
    //another orb increments their speed each time
    if (y - r <= 0 || y + r >= H)
    {
        vy *= -1;
    }
    if (x + r >= W || x - r <= 0)
    {
        vx *= -1;
    }
}
void Orb::run()
{
    move();
    draw();
    touching_wall();
    //if (vx + vy > 30) {vx %= 3, vy %= 3;}
    //color = BLUE;
}
void Orb::move()
{
    x += vx;
    y += vy;
}
void Orb::draw()
{
    ps->put_circle(x, y, r, color);
}
void Orb::flash()
{
    ps->put_circle(x, y, r, RED);
}
bool Orb::touched(Orb * orb)
{
    if (abs(orb->x - x) <= r + r / 2 &&
        abs(orb->y - y) <= r + r / 2)
    {
        //std::cout << ">>>>>>>>>>touching\n";
        // orb->vx *= 2, orb->vy *= 2, vy *= 2, vx *= 2;
        return true;      
    }
    else
    {return false;}
}

#endif 
