/*
 *  Copyright (C) 2020-2021 Metamod++ Development Team
 *
 *  This file is part of Metamod++.
 *
 *  Metamod++ is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  Metamod++ is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with Metamod++.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "Common.hpp"
#include "IHelpers.hpp"
#include "IPlugin.hpp"
#include "IHookChains.hpp"
#include "engine/IEngine.hpp"
#include "gamelib/IGameLib.hpp"

namespace Metamod
{
    enum class GameType : std::uint8_t
    {
        Valve = 0,
        CStrike,
        CZero,
    };

    enum class LogLevel : std::uint8_t
    {
        Debug = 0,
        Info,
        Warning,
        Error
    };

    enum class LogDest : std::uint8_t
    {
        Console = (1 << 0),
        File = (1 << 1)
    };

    class IMetamod
    {
    public:
        static constexpr std::uint16_t MAJOR_VERSION = 0;
        static constexpr std::uint16_t MINOR_VERSION = 0;
        static constexpr std::uint32_t VERSION = (MAJOR_VERSION << 16 | MINOR_VERSION);

    public:
        struct RegMsg
        {
            std::string_view name;
            std::int16_t size;
            std::uint8_t id = -1;
        };

        virtual ~IMetamod() = default;

        virtual std::uint32_t getInterfaceVersion() const = 0;
        virtual Engine::IEngine *getEngine() const = 0;
        virtual GameLib::IGameLib *getGameLib() const = 0;
        virtual GameType getGameType() const = 0;
        virtual const RegMsg *getMsgInfo(std::string_view name) const = 0;
        virtual void logMsg(IPlugin *plugin, LogLevel level, LogDest dest, std::string_view msg) = 0;
    };

    using fnMetaQuery = IPlugin *(*)();
    C_DLLEXPORT IPlugin *MetaQuery();

    using fnMetaInit = bool (*)(IMetamod *api);
    C_DLLEXPORT bool MetaInit(IMetamod *api);
}
