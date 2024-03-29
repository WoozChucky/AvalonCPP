#include <Common/Utilities/SmartEnum.h>
#include <Common/Logging/AppenderConsole.h>

#include <stdexcept>

namespace Avalon::Impl::EnumUtilsImpl
{

    /********************************************************************\
    |* data for enum 'ColorTypes' in 'AppenderConsole.h' auto-generated *|
    \********************************************************************/
    template <>
    EnumText EnumUtils<ColorTypes>::ToString(ColorTypes value)
    {
        switch (value)
        {
            case BLACK: return { "BLACK", "BLACK", "" };
            case RED: return { "RED", "RED", "" };
            case GREEN: return { "GREEN", "GREEN", "" };
            case BROWN: return { "BROWN", "BROWN", "" };
            case BLUE: return { "BLUE", "BLUE", "" };
            case MAGENTA: return { "MAGENTA", "MAGENTA", "" };
            case CYAN: return { "CYAN", "CYAN", "" };
            case GREY: return { "GREY", "GREY", "" };
            case YELLOW: return { "YELLOW", "YELLOW", "" };
            case LRED: return { "LRED", "LRED", "" };
            case LGREEN: return { "LGREEN", "LGREEN", "" };
            case LBLUE: return { "LBLUE", "LBLUE", "" };
            case LMAGENTA: return { "LMAGENTA", "LMAGENTA", "" };
            case LCYAN: return { "LCYAN", "LCYAN", "" };
            case WHITE: return { "WHITE", "WHITE", "" };
            default: throw std::out_of_range("value");
        }
    }

    template <>
    size_t EnumUtils<ColorTypes>::Count() { return 15; }

    template <>
    ColorTypes EnumUtils<ColorTypes>::FromIndex(size_t index)
    {
        switch (index)
        {
            case 0: return BLACK;
            case 1: return RED;
            case 2: return GREEN;
            case 3: return BROWN;
            case 4: return BLUE;
            case 5: return MAGENTA;
            case 6: return CYAN;
            case 7: return GREY;
            case 8: return YELLOW;
            case 9: return LRED;
            case 10: return LGREEN;
            case 11: return LBLUE;
            case 12: return LMAGENTA;
            case 13: return LCYAN;
            case 14: return WHITE;
            default: throw std::out_of_range("index");
        }
    }

    template <>
    size_t EnumUtils<ColorTypes>::ToIndex(ColorTypes value)
    {
        switch (value)
        {
            case BLACK: return 0;
            case RED: return 1;
            case GREEN: return 2;
            case BROWN: return 3;
            case BLUE: return 4;
            case MAGENTA: return 5;
            case CYAN: return 6;
            case GREY: return 7;
            case YELLOW: return 8;
            case LRED: return 9;
            case LGREEN: return 10;
            case LBLUE: return 11;
            case LMAGENTA: return 12;
            case LCYAN: return 13;
            case WHITE: return 14;
            default: throw std::out_of_range("value");
        }
    }
}
