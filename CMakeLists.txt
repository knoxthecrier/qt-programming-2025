cmake_minimum_required(VERSION 3.28)
project(qt_programming_2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_programming_2024 src/main.cpp
        src/MyGame.cpp
        src/MyGame.h
        src/Items/Item.cpp
        src/Items/Item.h
        src/Scenes/Scene.cpp
        src/Scenes/Scene.h
        src/Scenes/BattleScene.cpp
        src/Scenes/BattleScene.h
        assets/assets.qrc
        src/Items/Maps/Map.cpp
        src/Items/Maps/Map.h
        src/Items/Maps/Battlefield.cpp
        src/Items/Maps/Battlefield.h
        src/Items/Characters/SimpleCharacter.h
        src/Items/Characters/SimpleCharacter.cpp
        src/Items/Platform.h
        src/Items/Platform.cpp
        src/Items/DropItem.h
        src/Items/DropItem.cpp
        src/Items/Weapon.h
        src/Items/Weapons/Ball.h
        src/Items/Weapons/Fist.h
        src/Items/Weapons/Knife.h
        src/Items/Weapons/Rifle.h
        src/Items/Weapons/Sniper.h
        src/Items/Consumable.h
        src/Items/Consumables/Bandage.h
        src/Items/Consumables/Medkit.h
        src/Items/Consumables/Adrenaline.h
        src/Items/Armor.h
        src/Items/Armors/LightArmor.h
        src/Items/Armors/HeavyArmor.h
        src/Items/WeaponType.h
        src/Items/WeaponFactory.h
        src/Items/ConsumableType.h
        src/Items/ArmorType.h
        src/Items/ConsumableFactory.h
        src/Items/ArmorFactory.h
    )
target_link_libraries(qt_programming_2024
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

