#ifndef SNEK_H_
#define SNEK_H_

#include <cassert>
#include <vector>

struct SnekNode
{
    int             x = 0;
    int             y = 0;

    SnekNode*       next;
    SnekNode*       prev;
};

class Snek
{
public:

    enum 
    {
        DIR_RIGHT,
        DIR_UP,
        DIR_DOWN,
        DIR_LEFT
    };

    Snek(int x = 0, int y = 0);
    ~Snek();

    void            addSegment(int x = 0, int y = 0);

    void            updatePositions();

    SnekNode* const getHead() const { return m_head; }
    SnekNode* const getTail() const { return m_tail; }

    // Move actions
    void            move(int dir);

    unsigned int    getSize() { return m_size-5; }

    bool            checkCollision(int x, int y);

private:
    SnekNode*       m_head;
    SnekNode*       m_tail;
    unsigned int    m_size;

    // simply datastructure to store our segments
    std::vector<SnekNode> m_segmentList;

    // Used when the head moves, keeps its last location
    // so head->next can be accurately updated
    int last_head_loc_x;
    int last_head_loc_y;

};




#endif // SNEK_H_