target_sources(BIOHAZRD PRIVATE
    Components/AnimationComponent.cpp
    Components/AttributeComponent.cpp
    Components/HitboxComponent.cpp
    Components/MovementComponent.cpp
    Components/SkillComponent.cpp

    Engine/Game.cpp

    Entities/Enemy.cpp
    Entities/Entity.cpp
    Entities/Player.cpp

    GUI/GUI.cpp
    GUI/PlayerGUI.cpp

    Items/MeleeWeapons/MeleeWeapon.cpp
    Items/MeleeWeapons/Sword.cpp
    Items/RangedWeapons/RangedWeapon.cpp
    Items/RangedWeapons/Bow.cpp
    Items/Item.cpp

    States/EditorModes/DefaultEditorMode.cpp
    States/EditorModes/EditorMode.cpp
    States/EditorState.cpp
    States/GameState.cpp
    States/MainMenuState.cpp
    States/SettingsState.cpp
    States/State.cpp

    TileMap/TileMap.cpp

    Tiles/EnemySpawner.cpp
    Tiles/Tile.cpp

    Utils/ErrorHandler.cpp
    Utils/GraphicsSettings.cpp

    main.cpp
)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Config DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Fonts DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Maps DESTINATION ${CMAKE_BINARY_DIR}/bin)
