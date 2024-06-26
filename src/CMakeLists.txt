target_sources(BIOHAZRD PRIVATE
    Components/AnimationComponent.cpp
    Components/AttributeComponent.cpp
    Components/HitboxComponent.cpp
    Components/MovementComponent.cpp
    Components/SkillComponent.cpp

    Engine/Engine.cpp

    Entities/Enemies/Enemy.cpp
    Entities/Enemies/EnemySystem.cpp
    Entities/Enemies/GreenSlime.cpp

    Entities/Entity.cpp
    Entities/Player.cpp

    GUI/GUI.cpp
    GUI/PlayerGUI.cpp
    GUI/TextTagSystem.cpp

    Items/Weapons/MeleeWeapons/MeleeWeapon.cpp
    Items/Weapons/MeleeWeapons/Sword.cpp
    Items/Weapons/RangedWeapons/RangedWeapon.cpp
    Items/Weapons/RangedWeapons/Bow.cpp
    Items/Weapons/Weapon.cpp
    Items/Inventory.cpp
    Items/Item.cpp

    States/EditorModes/DefaultEditorMode.cpp
    States/EditorModes/EditorMode.cpp
    States/EditorModes/EnemyEditorMode.cpp
    States/EditorState.cpp
    States/GameState.cpp
    States/MainMenuState.cpp
    States/SettingsState.cpp
    States/State.cpp

    TileMap/TileMap.cpp

    Tiles/EnemySpawnerTile.cpp
    Tiles/RegularTile.cpp
    Tiles/Tile.cpp

    Utils/ErrorHandler.cpp
    Utils/GraphicsSettings.cpp
    Utils/IniParser.cpp
    Utils/Logger.cpp

    main.cpp
)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Config DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Fonts DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Maps DESTINATION ${CMAKE_BINARY_DIR}/bin)
