#include "mine.h"

Mine::Mine(): id{ 0 }, type{ WOOD }{

}

Mine::Mine(int id, int type) : id{ id }, type{ type } {
    this->wood = 0;
    this->stone = 0;
    this->iron = 0;
}
