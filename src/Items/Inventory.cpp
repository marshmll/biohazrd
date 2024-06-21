#include "stdafx.h"
#include "Inventory.h"

/* PRIVATE FUNCTIONS =========================================================================================== */

void Inventory::initialize(const short unsigned capacity)
{
    this->capacity = capacity;
    this->numOfItems = 0;
    this->itemArray = new Item *[this->capacity];

    this->nullify();
}

void Inventory::nullify(const short unsigned from)
{
    if (from >= this->capacity)
        ErrorHandler::throwErr("INVENTORY::NULLIFY::ERR_TRYING_TO_NULLIFY_FROM_INDEX_OUT_OF_BOUNDS\n");

    for (short unsigned i = from; i < this->capacity; i++)
        this->itemArray[i] = nullptr;
}

void Inventory::free()
{
    for (short unsigned i = 0; i < this->numOfItems; i++)
    {
        delete this->itemArray[i];
    }

    delete[] this->itemArray;
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Inventory::Inventory(const short unsigned capacity)
{
    this->initialize(capacity);
}

Inventory::~Inventory()
{
    this->free();
}

/* FUNCTIONS ==================================================================================================== */

void Inventory::clear()
{
    for (short unsigned i = 0; i < this->numOfItems; i++)
    {
        delete this->itemArray[i];
    }

    this->numOfItems = 0;

    this->nullify();
}

void Inventory::add(Item *item)
{
}

void Inventory::remove(const short unsigned index)
{
}

void Inventory::loadFromFile(const std::string file_path)
{
}

void Inventory::saveToFile(const std::string file_path)
{
}

/* ACCESSORS ==================================================================================================== */

const short unsigned &Inventory::size() const
{
    return this->numOfItems;
}

const short unsigned &Inventory::maxSize() const
{
    return this->capacity;
}

const bool Inventory::empty() const
{
    return this->size() == 0;
}

/* MODIFIERS ==================================================================================================== */
