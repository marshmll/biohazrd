#include "stdafx.h"
#include "Engine.h"

int main()
{
    Engine engine;

    engine.run();

    engine.~Engine();

    exit(EXIT_SUCCESS);
}