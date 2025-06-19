#include "NomalBox.h"

namespace collision
{
    void NomalBox::ColliderWith(RectCollision& _main, RectCollision& _box, int8_t _boxFlag)
    {
        //í èÌBoxÇÃîªíËÇé¿é{
        _main.CalcDiff(_box);
        _main.ExclDiff((_boxFlag & LEFT), (_boxFlag & RIGHT), (_boxFlag & TOP), (_boxFlag & BOTTOM));
        _main.PushBack();
    }
}
