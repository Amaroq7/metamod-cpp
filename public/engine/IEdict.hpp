/*
 *  Copyright (C) 2020 Metamod++ Development Team
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

#include <cinttypes>
#include <cstddef>

namespace Metamod::Entities
{
    class IBasePlayer;
    class IBaseEntity;
}

namespace Metamod::Engine
{
    class IEntVars;

    class IEdict
    {
    public:
        virtual ~IEdict() = default;

        /**
         * @brief Returns edict's index.
         *
         * @return Edict's index.
         */
        virtual std::uint32_t getIndex() const = 0;

        /**
         * @brief Returns edict's index.
         *
         * @return Edict's index.
         */
        virtual std::uint32_t getSerialNumber() const = 0;

        /**
         * @brief Checks if edict is freed.
         *
         * @return True if edict is freed, false otherwise.
         */
        virtual bool isValid() const = 0;

        /**
         * @brief Returns entity.
         *
         * @return Edict's base entity representation.
         */
        virtual Entities::IBaseEntity *getBaseEntity() = 0;

        /**
         * @brief Returns player entity.
         *
         * @return Edict's player entity representation.
         */
        virtual Entities::IBasePlayer *getBasePlayer() = 0;

        /**
         * @brief Returns entity's variables.
         *
         * @return Enitity's variables.
         */
        virtual IEntVars *getEntVars() const = 0;
    };
}