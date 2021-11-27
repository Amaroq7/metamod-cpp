/*
 *  Copyright (C) 2020-2021 Anubis Development Team
 *
 *  This file is part of Anubis.
 *
 *  Anubis is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  Anubis is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with Anubis.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "BasePlayer.hpp"

#include <extdll.h>
#include <tier0/platform.h>
#include <util.h>
#include <cbase.h>
#include <player.h>

namespace Anubis::Game::Valve
{
    BasePlayer::BasePlayer(nstd::observer_ptr<Engine::IEdict> edict) : BaseMonster(edict) {}

    BasePlayer::operator CBasePlayer *() const
    {
        return reinterpret_cast<CBasePlayer *>(m_entity);
    }

    void BasePlayer::makeVIP()
    { /* CStrike only */
    }
    void BasePlayer::giveShield(bool deploy [[maybe_unused]])
    { /* CStrike only */
    }
    void BasePlayer::removeShield()
    { /* CStrike only */
    }
    void BasePlayer::dropShield(bool deploy [[maybe_unused]])
    { /* CStrike only */
    }
    bool BasePlayer::hasShield() const
    {
        /* CStrike only */
        return false;
    }

} // namespace Anubis::Game::Valve
