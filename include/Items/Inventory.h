#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Items.h"

class Inventory
{
private:
    /* VARIABLES ================================================================================================= */

    Item **itemArray;

    short unsigned numOfItems;
    short unsigned capacity;

    /* PRIVATE FUNCTIONS ========================================================================================= */

    void initialize(const short unsigned capacity);

    void nullify(const short unsigned from = 0);

    void free();

public:
    /* CONSTRUCTOR AND DESTRUCTOR =============================================================================== */

    Inventory(const short unsigned capacity);

    virtual ~Inventory();

    /* FUNCTIONS ================================================================================================ */

    void clear();

    Item *at(const short unsigned index);

    const bool add(Item *item);

    const bool remove(const short unsigned index);

    const bool loadFromFile(const std::string file_path);

    const bool saveToFile(const std::string file_path);

    /* ACCESSORS ================================================================================================ */

    const short unsigned &size() const;

    const short unsigned &maxSize() const;

    const bool empty() const;

    const bool full() const;

    /* MODIFIERS ================================================================================================ */
};

#endif /* INVENTORY_H_ */