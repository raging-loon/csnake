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


// Linked list of SnekNodes
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

    /**
     * Update each element based on the element previous element
     * Does not update the head element 
     * m_head->next is updated based on last_head_loc_*
     * So when m_head is updated, head->next can be updated based
     * on where m_head was
    */
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

    // Used when the head moves, keeps its last location
    // so head->next can be accurately updated
    int last_head_loc_x;
    int last_head_loc_y;

};




#endif // SNEK_H_