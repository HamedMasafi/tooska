#ifndef TREE_H
#define TREE_H

#include "../global.h"

#include <bits/stdc++.h>
#include <functional>
#include <vector>

TOOSKA_BEGIN_NAMESPACE(core)

template<class T>
class node_t
{
public:
    typedef node_t<T> node_type;
    typedef node_t<T> *node_type_ptr;

protected:
    T *_parent;
    std::vector<T*> _childs;

public:
    node_t(T *parent = nullptr)
    {
        if (parent)
            parent->add_child(static_cast<T *>(this));
    }
    ~node_t()
    {
        std::for_each(_childs.begin(), _childs.end(), [](T *t){
            delete t;
        });
    }

    T *parent() const
    {
        return _parent;
    }

    void add_child(T *child)
    {
        child->_parent = static_cast<T*>(this);
        if (std::find(_childs.begin(), _childs.end(), child) == _childs.end())
            _childs.push_back(child);
    }

    void remove_child(T *child)
    {
        child->set_parent(nullptr);
        //        _childs.erase(
        std::remove(_childs.begin(), _childs.end(), child);
        //                      _childs.end());
    }

    std::vector<T*> childs() const
    {
        return _childs;
    }

    std::vector<T *> find(const std::function<bool(T *)> &callback)
    {
        std::vector<T *> ret;
        find_internal(callback, ret);
        return ret;
    }

private:
    void find_internal(const std::function<bool(T *)> &callback, std::vector<T*> &ret)
    {
        if (callback(this))
            ret.push_back(this);

        for (auto ch: _childs)
            ch->find_internal(callback, ret);
    }
};

//depreacted
class tree_node
{
//public:
//    typedef tree_node<T> node_type;
//    typedef tree_node<T>* node_type_ptr;

protected:
    tree_node *_parent;
    std::vector<tree_node*> _childs;

public:
    tree_node(tree_node *parent = nullptr)
    {
        set_parent(parent);
    }

    tree_node *parent() const
    {
        return _parent;
    }

    void set_parent(tree_node *parent)
    {
        _parent = parent;
    }

    void add_child(tree_node *child)
    {
        child->set_parent(this);
        _childs.push_back(child);
    }

    void remove_child(tree_node *child)
    {
        child->set_parent(nullptr);
//        _childs.erase(
        std::remove(_childs.begin(), _childs.end(), child);
//                      _childs.end());
    }

    std::vector<tree_node*> childs() const
    {
        return _childs;
    }

    std::vector<tree_node *> find(const std::function<bool(tree_node *)> &callback)
    {
        std::vector<tree_node *> ret;
        find_internal(callback, ret);
        return ret;
    }

private:
    void find_internal(const std::function<bool(tree_node *)> &callback, std::vector<tree_node*> &ret)
    {
        if (callback(this))
            ret.push_back(this);

        for (auto ch: _childs)
            ch->find_internal(callback, ret);
    }
};

//depreacted
template<class T>
class tree
{
public:
    class node{
        T *_data;
        node *_parent;
        std::vector<tree_node*> _childs;
    public:
        T *operator ->() {
            return _data;
        }

        node(node *parent = nullptr)
        {
            set_parent(parent);
        }
        node(T *data, node *parent = nullptr) : _data(data)
        {
            set_parent(parent);
        }

        node *parent() const
        {
            return _parent;
        }

        void set_parent(node *parent)
        {
            _parent = parent;
        }

        void add_child(T *child)
        {
            child->set_parent(this);
            _childs.push_back(child);
        }

        void remove_child(T *child)
        {
            child->set_parent(nullptr);
//            _childs.erase(
            std::remove(_childs.begin(), _childs.end(), child);
//                          _childs.end());
        }

        std::vector<T*> childs() const
        {
            return _childs;
        }
        operator T*() {
            return _data;
        }

        friend class tree;
    };

    node *root;

    tree() : root(nullptr)
    {}

    node *operator =(T *data) {
        root = new node(data);
        return root;
    }
    bool operator !() {
        return root != nullptr;
    }
    operator bool() {
        return root != nullptr;
    }
    T *operator ->() {
        if (!root)
            return nullptr;
        return root->_data;
    }
};

TOOSKA_END_NAMESPACE

#endif // TREE_H
