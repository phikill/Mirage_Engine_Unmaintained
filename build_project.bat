@echo off

rem 
rem @gcc -Wall -Wextra -ISRC/include -o mango.exe ^
rem	SRC/mirage_engine/common.c ^
rem	SRC/mirage_engine/global.c ^
rem	SRC/mirage_engine/math_util.c ^
rem	SRC/mirage_engine/util.c ^
rem    SRC/mirage_engine/animation/animation.c ^
rem    SRC/mirage_engine/array_list/array_list.c ^
rem    SRC/mirage_engine/audio/audio.c ^
rem    SRC/mirage_engine/config/config.c ^
rem    SRC/mirage_engine/entity/entity.c ^
rem    SRC/mirage_engine/entity/item.c ^
rem    SRC/mirage_engine/input/input_internal.c ^
rem    SRC/mirage_engine/io/io.c ^
rem    SRC/mirage_engine/NPC/mind_npc.c ^
rem    SRC/mirage_engine/NPC/npc_utils.c ^
rem    SRC/mirage_engine/physics/physics.c ^
rem    SRC/mirage_engine/renderer/character_renderer.c ^
rem    SRC/mirage_engine/renderer/load.c ^
rem    SRC/mirage_engine/renderer/render.c ^
rem    SRC/mirage_engine/renderer/render_internal.c ^
rem    SRC/mirage_engine/time/time.c ^
rem    SRC/mirage_engine/time/turn_manager.c ^
rem    SRC/mirage_engine/ui/button.c

@wcc386 /6r -i="SRC/include" "SRC/mirage_engine/common.c"
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/global.c" 
echo.
echo.
@wcc386 /6r -i="SRC/include" "SRC/mirage_engine/math_util.c"
echo.
echo.
@wcc386 /6r -i="SRC/include" "SRC/mirage_engine/util.c"
echo.
echo.
@wcc386 /6r -i="SRC/include" "SRC/mirage_engine/animation/animation.c"
echo.
echo.
echo.
@wcc386 /6r -i="SRC/include" "SRC/mirage_engine/array_list/array_list.c"
echo.
echo.
echo.
@wcc386 /6r -i="SRC/include" "SRC/mirage_engine/audio/audio.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/config/config.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/entity/entity.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/entity/item.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/input/input_internal.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/io/io.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/NPC/mind_npc.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/NPC/npc_utils.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/physics/physics.c"
echo.
echo.
echo.
@wcc386 /6r -e999 -i="SRC/include" "SRC/mirage_engine/renderer/character_renderer.c"
echo.



pause
