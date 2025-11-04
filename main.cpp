#include "project.h"
//﷽﷽﷽
//the testing shall be good and the bugs destroyed inshallah
//﷽﷽﷽
Event event;
KeyPressed kp;
//TreeNodev< int > tree(0, W - W, H - H, W, H);
std::vector< Orb * > orb_vector;
int start, end, dt;
int RATE = 1000 / 60;
bool toggle = false;
void collision_check(const std::vector< Orb * > & orbs);
void debug_circle();
void tree_collision();
void squared_collision();
void controls(KeyPressed & kp);
int main()
{
    srand((unsigned int) time(NULL));
    std::cout << "n : "; int n = 0; std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        orb_vector.push_back(new Orb(10 + rand() % W,
                                     10 + rand() % H, 3, rand() % 3 - 2, rand() % 3 - 2));
    }
    while (true)
    {
        kp = get_keypressed();
        start = getTicks();
        if (kp[TAB]) {break;}
        if (event.poll() && event.type() == QUIT) {break;}
        controls(kp);
        drawAfterMe();
        if (toggle)
        {
            tree_collision();
        }
        else 
        {
            squared_collision();
        }
        drawBeforeMe();
        end = getTicks();
        dt = RATE - end + start;
        if (dt > 0) delay(dt);
    }
    for (int i = 0; i < orb_vector.size(); ++i)
    {
        delete orb_vector[i];
    }
    return 0;
}
void squared_collision()
{
    while (true)
    {
        kp = get_keypressed();
        start = getTicks();
    
        if (event.poll() && event.type() == QUIT) {break;}
        if (kp[TAB]) {break;}
        controls(kp);
        
        if (toggle == true)
        {
            return;
        }
        drawAfterMe();
        collision_check(orb_vector);
        drawBeforeMe();
        end = getTicks();
        dt = RATE - end + start;
        if (dt > 0) delay(dt);
    }
}
void tree_collision()
{
    while (true)
    {
        TreeNodev< int > tree(0, 0, 0, W, H);
        tree.orbs = orb_vector;
        kp = get_keypressed();
        start = getTicks();
        if (kp[TAB]) {break;}
        controls(kp);
      
        if (toggle == false)
        {return;}
        if (event.poll() && event.type() == QUIT) {break;}
        drawAfterMe();
        tree.run();
        drawBeforeMe();
        end = getTicks();
        dt = RATE - end + start;
        if (dt > 0) delay(dt);
        tree.kill_children();
    }
}
void collision_check(const std::vector< Orb * > & orbs)
{
    for (int i = 0; i < orbs.size(); ++i)
    {
        for (int j = 0; j < orbs.size(); ++j)
        {
            if (orbs[j]->touched(orbs[i]) &&
                orbs[i] != orbs[j] && !orbs[i]->checked && !orbs[j]->checked)
            {
                int t = orbs[j]->vx;
                orbs[j]->vx = orbs[i]->vx,
                    orbs[i]->vx = t;
                t = orbs[j]->vy;
                orbs[j]->vy = orbs[i]->vy,
                    orbs[i]->vy = t;
                orbs[i]->checked = true;
                orbs[j]->checked = true;
            }
                orbs[i]->checked = false;
            orbs[j]->checked = false;       
        }
            orbs[i]->run();
    }
}
void debug_circle()
{
    sf.put_circle(20, 20, 10, GRAY);
    sf.put_pixel(20, 20, GREEN);
    sf.put_pixel(10, 20, GREEN);
    sf.put_pixel(20, 10, GREEN);
    sf.put_pixel(20, 30, GREEN);
    sf.put_pixel(30, 20, GREEN);
    sf.put_pixel(30, 30, GREEN);
    sf.put_pixel(10, 10, GREEN);
    sf.put_pixel(10, 30, GREEN);
    sf.put_pixel(30, 10, GREEN);
}
void controls(KeyPressed & kp)
{
    if (kp[DOWNARROW] && !orb_vector.empty())
    {
        orb_vector.erase(orb_vector.end() - 1);
        std::cout << "ORBS: " << orb_vector.size() << std::endl;
    }
    if (kp[UPARROW])
    {
        orb_vector.push_back(new Orb(10 + rand() % W,
                                     10 + rand() % H, 3, rand() % 3 - 2, rand() % 3 - 2));
        std::cout << "ORBS: " << orb_vector.size() << std::endl;
    }
    if (kp[RIGHTARROW])
    {toggle = !toggle;}
}
