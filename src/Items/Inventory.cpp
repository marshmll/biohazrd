#include "stdafx.h"
#include "Inventory.h"

/* PRIVATE FUNCTIONS =========================================================================================== */

void Inventory::initialize(const short unsigned capacity)
{
    this->capacity = capacity;
    numOfItems = 0;
    itemArray = new Item *[capacity];

    nullify();
}

void Inventory::nullify(const short unsigned from)
{
    if (from >= capacity)
        ErrorHandler::throwErr("INVENTORY::NULLIFY::ERR_TRYING_TO_NULLIFY_FROM_INDEX_OUT_OF_BOUNDS\n");

    for (short unsigned i = from; i < capacity; i++)
        itemArray[i] = nullptr;
}

void Inventory::free()
{
    for (short unsigned i = 0; i < numOfItems; i++)
    {
        delete itemArray[i];
    }

    delete[] itemArray;
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Inventory::Inventory(const short unsigned capacity)
{
    initialize(capacity);
}

Inventory::~Inventory()
{
    free();
}

/* FUNCTIONS ==================================================================================================== */

void Inventory::clear()
{
    for (short unsigned i = 0; i < numOfItems; i++)
    {
        delete itemArray[i];
    }

    numOfItems = 0;

    nullify();
}

Item *Inventory::at(const short unsigned index)
{
    if (size() > 0 && index >= 0 && index < capacity)
    {
        return itemArray[index];
    }

    ErrorHandler::throwErr("INVENTORY::AT::ERR_INDEX_OUT_OF_BOUNDS");

    return nullptr;
}

const bool Inventory::add(Item *item)
{
    if (!full())
    {
        for (unsigned short i = 0; i < capacity; ++i)
        {
            if (itemArray[i] == nullptr)
            {
                itemArray[i] = item->clone();
                ++numOfItems;

                break;
            }
        }

        return true;
    }

    return false;
}

const bool Inventory::remove(const short unsigned index)
{
    if (size() > 0 && index >= 0 && index < capacity)
    {
        delete itemArray[index];

        itemArray[index] = nullptr;

        numOfItems--;

        return true;
    }

    return false;
}

const bool Inventory::loadFromFile(const std::string file_path)
{
    return false;
}

const bool Inventory::saveToFile(const std::string file_path)
{
    return false;
}

/* ACCESSORS ==================================================================================================== */

const short unsigned &Inventory::size() const
{
    return numOfItems;
}

const short unsigned &Inventory::maxSize() const
{
    return capacity;
}

const bool Inventory::empty() const
{
    return numOfItems == 0;
}

const bool Inventory::full() const
{
    return numOfItems == capacity;
}

/* MODIFIERS ==================================================================================================== */
