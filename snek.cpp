#include <stdio.h>
#include "snek.h"

Snek::Snek(int x, int y)
{
    m_head = new SnekNode { x, y, nullptr, nullptr};

    m_tail = m_head;
    m_size = 1;
}

Snek::~Snek()
{
    SnekNode* tail = m_tail;

    while(tail)
    {
        SnekNode* prev = tail->prev;
        delete tail;

        tail = prev;
    }
}

void Snek::addSegment(int x, int y)
{
    SnekNode * n = new SnekNode{x,y,nullptr,nullptr};

    m_tail->next = n;
    n->prev = m_tail;
    
    m_tail = n;    
    m_size++;

}

void Snek::updatePositions()
{
    SnekNode* n_node = m_tail;
    while(n_node != m_head)
    {
        n_node->x = n_node->prev->x;
        n_node->y = n_node->prev->y;
        
        n_node = n_node->prev;
    }
 
    m_head->next->x = last_head_loc_x;
    m_head->next->y = last_head_loc_y;
}

void Snek::move(int dir)
{
    last_head_loc_x = m_head->x;
    last_head_loc_y = m_head->y;
    switch(dir)
    {
        case DIR_RIGHT:
            m_head->x += 1;
            break;
        case DIR_LEFT:
            m_head->x -= 1;
            break;
        case DIR_UP:
            m_head->y -= 1;
            break;
        case DIR_DOWN:
            m_head->y += 1;
            break;
        default:
            break;
    }
}

bool Snek::checkCollision(int x, int y)
{
    SnekNode* node = m_head->next;

    while(node)
    {
        if(node->x == x && node->y == y)
            return true;
        node = node->next;
    }

    return false;
}