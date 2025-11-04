#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include "orb.h"
class ValueError {};
template < typename T > class TreeNodev;
template < typename T > class Data;
template < typename T >
bool is_root(const TreeNodev< T > * p)
{return (p->parent() == NULL);}
template < typename T>
std::ostream & operator<<(std::ostream & cout, std::vector< T > & v)
{
    if (!v.empty())
    {
        for (int i = 0; i < v.size(); ++i)
        {
            cout << v[i];
        }
    }
    else
    {
        cout << "<NULL>";
    }
    return cout;
   
}
template < typename T >
class TreeNodev
{
  public:
    //root node ctor
    TreeNodev(const T & key, const int x, const int y, const int w, const int h, TreeNodev * parent=NULL)
        :key_(key), parent_(parent), threshold(5), ps(&sf)
    {
        rect.x = x, rect.y = y, rect.w = w, rect.h = h;
    }
    TreeNodev(TreeNodev * parent)
        :key_(parent->key()), parent_(parent), rect(parent->rect), threshold(5), ps(&sf), orbs(parent->orbs)
    {

    }
    //we like to have fun here
    ~TreeNodev()
    {
        //std::cout << child_.size() << std::endl;
        kill_children();
    }
    const TreeNodev< T > * const parent() const
    {
        return parent_;
    }
    bool is_root() const//??
    {
        return ::is_root(this);
    }
    //go go gadget subdivide children
    void subdivide()
    {
        //change variable names -please God

        std::vector< Orb * > vtl, vtr, vbl, vbr; 
        for (int i = 0; i < orbs.size(); ++i)
        {
            //top left
            if (orbs[i]->x >= x() && orbs[i]->x <= x() + w() / 2 && orbs[i]->y >= y() && orbs[i]->y <= y() + h() / 2)
            {
                vtl.push_back(orbs[i]);
            }
            //top right
            if (orbs[i]->x >= x() + w() / 2 && orbs[i]->x <= x() + w() && orbs[i]->y >= y() && orbs[i]->y <= y() + h() / 2)
            {
                vtr.push_back(orbs[i]);
            }
            //bottom left
            if (orbs[i]->x >= x() && orbs[i]->x <= x() + w() / 2 && orbs[i]->y >= y() + h() / 2 && orbs[i]->y <= y() + h())
            {
                vbl.push_back(orbs[i]);
            }
            //bottom right
            if (orbs[i]->x >= x() + w() / 2 && orbs[i]->x <= x() + w() && orbs[i]->y >= y() + h() / 2 && orbs[i]->y <= y() + h())
            {
                vbr.push_back(orbs[i]);
            }
        }
        TreeNodev< T > p(key_ + 1, x(), y(), w() / 2, h() / 2);
        p.orbs = vtl;
        insert(0, &p);
        TreeNodev< T > q(key_ + 2, x() + w() / 2, y(), w() / 2, h() / 2);
        q.orbs = vtr;
        insert(1, &q);
        TreeNodev< T > r(key_ + 3, x(), y() + h() / 2, w() / 2, h() / 2);
        r.orbs = vbl;                
        insert(2, &r);
        TreeNodev< T > s(key_ + 4, x() + w() / 2, y() + h() / 2, w() / 2, h() / 2);
        s.orbs = vbr;               
        insert(3, &s);
    }
    void draw_border()
    {
        ps->put_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, 1, GREEN);
        ps->put_line(rect.x + 1, rect.y + 1, rect.x + rect.w - 1, rect.y + 1, YELLOW);
        ps->put_line(rect.x + 1, rect.y+rect.h - 1, rect.x + rect.w - 1, rect.y + rect.h - 1, YELLOW);
        ps->put_line(rect.x + 1, rect.y + 1, rect.x + 1, rect.y + rect.h - 1, YELLOW);
        ps->put_line(rect.x + rect.w - 1, rect.y + 1, rect.x +rect.w - 1, rect.y + rect.h - 1, YELLOW);
    }
    void run()
    {
        if (orbs.size() > threshold)
        {
            subdivide();
        }
        draw_border();
        if (child_.size() <= 0)
        {
            collision_check();        
        }
        else
        {
            for (int i = 0; i < child_.size(); ++i)
            {
                if (child_[i] != NULL)
                {
                    child_[i]->collision_check();
                    child_[i]->run();
                }
            }
        }
    }
    void collision_check()
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
    //done
    T key();
    bool is_leaf();
    bool is_nonleaf();
    void insert(const int i, const T n);
    void insert(const int i, TreeNodev< T > * t);
    void insert_parent(const T n);
    void insert_parent(TreeNodev< T > * p);
    void insert_left(const T  n);
    void insert_right(const T  n);
    int height(TreeNodev< T > * n);
    int num_child() const;
    TreeNodev< T > * root() const;
    TreeNodev< T > * root();
    TreeNodev< T > * parent();
    TreeNodev< T > * firstborn();
    TreeNodev< T > * lastborn();
    TreeNodev< T > * child(const int i); //returns 'i-th' child from vector
    TreeNodev< T > * leftmost(); //leftmost of entire tree from given node
    TreeNodev< T > * rightmost(); //rightmost of entire tree from given node
    int depth();
    int size();
    TreeNodev< T > * next();
    TreeNodev< T > * prev();
    //only for binary tree ******
    TreeNodev< T > * left();//***
    TreeNodev< T > * right();//**
    //only for binary tree ******
    //probably also wanna make this take TreeNodev *   
    void remove(const int i);
    void remove_left();
    void remove_right();
    //todo
    void kill_children();
    Rect rect;
    int x() const
    {return rect.x;}
    int y() const
    {return rect.y;}
    int w() const
    {return rect.w;}
    int h() const
    {return rect.h;}
    void set_threshold(const int n)
    {
        threshold = n;
    }
    std::vector< Orb * > orbs;
private:
    Surface * ps;
    int threshold;
    T key_;
    TreeNodev< T > * parent_;
    std::vector< TreeNodev< T > * > child_;
};

template < typename T >
void gen_gviz(TreeNodev< T > & t)
{
    std::ofstream f;
    f.open("graph.dot");
    f << "digraph G\n{\n";
    std::queue< TreeNodev< T > > q;
    q.push(t);
    while (!q.empty())
    {
        TreeNodev< T > * p = &q.front();
        //std::cout << q.front().key() << std::endl;
        for (int i = 0; i < p->num_child(); ++i)
        {
            if (p->child(i) != NULL)
            {// b [label="hello\nworld"];
                f << "\t\"" << p->p_vec() << "--" << p->a_vec()  
                  << "\"->\"" << p->child(i)->p_vec() << "00" << p->child(i)->a_vec()
                  << "\";" << std::endl; 
                q.push(*p->child(i));
            }
        }
        q.pop();
    }    
    f << "}\n";
    f.close();
}

#endif
/*
     TreeNodev< T > * p = new TreeNodev< T >(key_, a, b, c, d);
        
        child_.push_back(p);
        for (int i = 0; i < child_.size(); ++i)
        {
            if (child_[i] != NULL)
            {
                child_[i]->subdivide();
            }
        }
 */
