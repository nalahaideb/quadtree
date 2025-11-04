#ifndef TREE_CPP
#define TREE_CPP
#include "tree.h"
template < typename T >
void TreeNodev< T >::kill_children()
{
    for (int i = 0; i < child_.size(); ++i)
    {
        if (child_[i] != NULL)
        {
            child_[i]->kill_children();
            delete child_[i];
            child_[i] = NULL;
        }
    }
    child_.clear();
}

template < typename T >
T max(const T x, const T y)
{
    return (x > y ? x : y); 
}

template < typename T >
int TreeNodev< T >::height(TreeNodev< T > * n)
{
    if (n == NULL)
    {
        return -1;
    }
    else
    {
        int max = -1;
        for (int i = 0; i < n->num_child(); ++i)
        {
            if (n->child(i) != NULL)
            {
                int x = 1 + height(n->child(i));
                max = (x > max ? x : max);
            }
        }
        return max;
    }
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::right()
{
    if (child_.size() > 0)
    {
        return child_[num_child() - 1];
    }
    else
    {
        return NULL;
    }
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::left()
{
    if (child_.size() > 0)
    {
        return child_[0];
    }
    else
    {
        return NULL;
    }
}

template < typename T >
int TreeNodev< T >::size()
{
    //change to pointers
    int sizzle = 0;
    std::queue< TreeNodev< T > > q;
    q.push(*this);
    while (!q.empty())
    {
        TreeNodev< T > * p = &q.front();
        for (int i = 0; i < p->num_child(); ++i)
        {
            if (p->child(i) != NULL)
            {
                q.push(*p->child(i));
            }
        }
        q.pop();
        ++sizzle;
    }
    return sizzle;
}

template < typename T >
int TreeNodev< T >::depth()
{
    int depf = -1;
    TreeNodev< T > * p = this; 
    while (p->parent() != NULL)
    {
        ++depf;
        p = p->parent();
    }
    return depf;
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::leftmost()
{
    if (child_.size() <= 0)
    {return this;}
    TreeNodev< T > * p = child_[0];
    while (p != NULL)
    {
        if (p->num_child() > 0)
        {
            p = p->child(0);
        }
        else
        {
            break;
        }
    }
    return p;
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::rightmost()
{
    if (child_.size() <= 0)
    {return this;}
    TreeNodev< T > * p = child_[num_child() - 1];
    while (p != NULL)
    {
        if (p->num_child() > 0)
        {
            p = p->child(p->num_child() - 1);
        }
        else
        {
            break;
        }
    }
    return p;
}

template < typename T >
bool TreeNodev< T >::is_nonleaf()
{//this doesnt work that well ackshually
    if (child_.size() > 0)
    {
        bool children = false;
        for (int i = 0; i < child_.size(); ++i)
        {
            if (child_[i] != NULL) {children = true; break;}
        }
        return children;
    }
    else
    {
        return false;
    }
}

template < typename T >
T TreeNodev< T >::key() 
{
    return key_;
}

template < typename T >
void TreeNodev< T >::insert(const int i, TreeNodev< T > * t)
{
    try
    {   
        if (i < 0)
        {
            ValueError e;
            throw e;
        }
        if (child_.size() > i)
        {
            if (child_[i] != NULL)
            {
                TreeNodev< T > * p = new TreeNodev< T >(t);
                p->insert_parent(this);
                child_[i] = p;
                //child_[i]->insert_parent(this);
            }
            else
            {
                std::cout << "CHILD NOT NULL, child_[i]: " << child_[i] << ' ';
                ValueError e;
                throw e;
            }
        }
        else
        {
            while (child_.size() < i)
            {
                child_.push_back(NULL);
            }
            TreeNodev< T > * p = new TreeNodev< T >(t);
            p->insert_parent(this);
            child_.push_back(p);
            //child_[i]->insert_parent(this);
        }
    }
    catch (ValueError & e)
    {
        std::cout << "INSERT ERROR: INDEX NOT-NULL OR \"i\" OUT OF RANGE" << std::endl;
    }
}

template < typename T >
void TreeNodev< T >::insert(const int i, const T n)
{
    try
    {   
        if (i < 0)
        {
            ValueError e;
            throw e;
        }
        if (child_.size() > i)
        {
            if (child_[i] != NULL)
            {
                child_[i] = new TreeNodev< T >(n, this);
            }
            else
            {
                ValueError e;
                throw e;
            }
        }
        else
        {
            while (child_.size() < i)
            {
                child_.push_back(NULL);
            }
            child_.push_back(new TreeNodev< T >(n, this));
        }
    }
    catch (ValueError & e)
    {
        std::cout << "INSERT ERROR: INDEX NOT-NULL OR \"i\" OUT OF RANGE" << std::endl;
    }
}

template < typename T >
void TreeNodev< T >::insert_parent(const T n)
{
    TreeNodev< T > * p = new TreeNodev< T >(n);
    parent = p;
}

template < typename T >
void TreeNodev< T >::insert_left(const T n)
{
    TreeNodev< T > * p = new TreeNodev< T >(n, this);
    child_.push_front(p);
}

template < typename T >
void TreeNodev< T >::insert_right(const T n)
{
    TreeNodev< T > * p = new TreeNodev< T >(n, this);
    child_.push_back(p);
}

template < typename T >
void TreeNodev< T >::remove(const int i)
{
    try
    {
        if (i < 0 || i >= child_.size() || child_[i] == NULL)
        {
            ValueError e;
            throw e;
        }
        else
        {
            delete child_[i];
            child_[i] = NULL;
        }
    }
    catch (ValueError e)
    {
        std::cout << "REMOVE ERROR" << std::endl;
    }
}

template < typename T >
void TreeNodev< T >::remove_left()
{
    if (child_[0] != NULL)
    {
        delete child_[0];
    }
    child_.erase(child_.begin());

}

template < typename T >
void TreeNodev< T >::remove_right()
{
    if (child_[child_.size() - 1] != NULL)
    {
        delete child_[child_.size() - 1];
        child_.pop_back();
    }
    //child_.erase(child_.size());
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::next()
{
    try
    {
        if (parent_ == NULL)
        {
            ValueError e;
            throw e;
        }
        int i = 0;
        while (parent_->child_[i] != this && i < parent_->num_child())
        {
            ++i;
        }
        if (i + 1 > parent_->num_child() - 1)
        {
            ValueError e;
            throw e;
        }
        return parent_->child_[++i];
    }
    catch (ValueError & e)
    {
        std::cout << "NEXT ERROR: OUT OF BOUNDS\n";
        return NULL;
    }
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::prev()
{
    try
    {
        if (parent_ == NULL)
        {
            ValueError e;
            throw e;
        }
        int i = parent_->num_child();
        while (parent_->child_[i] != this && i > 0)
        {
            --i;
        }
        if (i - 1 < 0)
        {
            ValueError e;
            throw e;
        }
        return parent_->child_[--i];
    }
    catch (ValueError & e)
    {
        std::cout << "PREV ERROR: OUT OF BOUNDS\n";
        return NULL;
    }
}
template < typename T >
int TreeNodev< T >::num_child() const
{
    return child_.size();
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::firstborn()
{
    return child_[0];
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::lastborn()
{
    return child_[child_.size() - 1];
}

template < typename T >
void TreeNodev< T >::insert_parent(TreeNodev< T > * p)
{
    parent_ = p;
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::child(const int i)
{
    if (i > child_.size())
    {return NULL;}
    else
    {return child_[i];}
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::root() const
{
    TreeNodev< T > * p = this;
    while (true)
    {
        if (p->parent() == NULL)
        {break;}
        else
        {p = p->parent();}
    }
    return p;
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::parent()
{
    return parent_;
}

template < typename T >
TreeNodev< T > * TreeNodev< T >::root()
{
    TreeNodev< T > * p = this;
    while (true)
    {
        if (p->parent() == NULL)
        {break;}
        else
        {p = p->parent();}
    }
    return p;
}

template < typename T >
bool TreeNodev< T >::is_leaf()
{
    if (child_.size() <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif

