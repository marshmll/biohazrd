target_sources(BIOHAZRD PRIVATE
  main.cpp
  AnimationComponent.cpp
  EditorState.cpp
  Entity.cpp
  Game.cpp
  GameState.cpp
  GraphicsSettings.cpp
  GUI.cpp
  HitboxComponent.cpp
  MainMenuState.cpp
  MovementComponent.cpp
  Player.cpp
  SettingsState.cpp
  State.cpp
  Tile.cpp
  TileMap.cpp
)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Config DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Fonts DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Maps DESTINATION ${CMAKE_BINARY_DIR}/bin)