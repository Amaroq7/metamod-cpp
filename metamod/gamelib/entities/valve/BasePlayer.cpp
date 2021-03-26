/*
 *  Copyright (C) 2020 SPMod Development Team
 *
 *  This file is part of SPMod.
 *
 *  SPMod is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SPMod is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SPMod.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "BasePlayer.hpp"
#include <osconfig.h>
#include <util.h>
#include <cbase.h>
#include <player.h>

#include <gamelib/EntitiesHooks.hpp>
#include <gamelib/VFuncHelpers.hpp>

namespace Metamod::GameLib::Entities::Valve
{
    BasePlayer::BasePlayer(const Engine::Edict *edict,
                           BasePlayerHooks *m_hooks,
                           const std::unordered_map<std::uint16_t, std::intptr_t> &originalVFuncs)
        : BaseMonster(edict), m_hooks(m_hooks), m_originalVFuncs(originalVFuncs)
    {}

    BasePlayer::operator CBasePlayer *() const
    {
        return reinterpret_cast<CBasePlayer *>(GET_PRIVATE(*m_edict));
    }

    void BasePlayer::makeVIP() { /* CStrike only */ }

    int BasePlayer::takeDamage(Engine::IEntVars *pevInflictor,
                               Engine::IEntVars *pevAttacker,
                               float flDamage,
                               int bitsDamageType)
    {

        bool hasHooks = m_hooks->takeDamage()->hasHooks();

        // VFunc is hooked so call the original
        if (hasHooks && !m_callHooks)
        {
            return VFuncHelpers::execOriginalFunc<std::int32_t, entvars_t *, entvars_t *, float, std::int32_t>(
                m_originalVFuncs.at(static_cast<std::uint16_t>(vFuncType::TakeDamage)),
                                 operator CBasePlayer *(), *static_cast<Engine::EntVars *>(pevInflictor),
                                 *static_cast<Engine::EntVars *>(pevAttacker), flDamage, bitsDamageType);
        }

        return operator CBasePlayer *()->TakeDamage(
            *dynamic_cast<Engine::EntVars *>(pevInflictor),
            *dynamic_cast<Engine::EntVars *>(pevAttacker),
            flDamage,
            bitsDamageType
        );
    }
} // namespace Valve
