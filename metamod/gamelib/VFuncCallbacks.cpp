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

#include "VFuncCallbacks.hpp"

#include <Metamod.hpp>
#include "GameLib.hpp"
#include "VFuncHelpers.hpp"

namespace
{
    using namespace Metamod;
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<GameLib::Entities::IBaseEntity, T>>>
    T *instanceToType(void *instance)
    {
        static GameLib::GameLib *gameLib = gMetaGlobal->getGameLib();
        static Engine::Engine *engine = gMetaGlobal->getEngine();
        static std::uint32_t offset = gameLib->getPevOffset();

        edict_t *ed = ENT(*reinterpret_cast<entvars_t **>(reinterpret_cast<std::intptr_t *>(instance) + offset));
        if constexpr (std::is_same_v<T, GameLib::Entities::IBasePlayer>)
        {
            return gameLib->getBasePlayer(engine->getEdict(ed));
        }
    }
    /* virtual void	Spawn( void ) { return; } */
    void vSpawnHook(
#if defined __linux__
        void *instance
#endif
    )
    {
#if defined SP_WINDOWS
        void *instance;
        __asm
        {
            mov [instance], ecx
        }
#endif
        static GameLib::BasePlayerSpawnHookRegistry *hookchain = gMetaGlobal->getGameLib()->getCBasePlayerHooks()->spawn();

        hookchain->callChain([instance](GameLib::Entities::IBasePlayer *plr) {
            GameLib::VFuncHelpers::execOriginalFunc<>(gMetaGlobal->getGameLib()->getOriginalVFunc(0), instance);
        }, instanceToType<GameLib::Entities::IBasePlayer>(instance));
    }

    /*int TakeDamage( entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType); */
    std::int32_t vTakeDamageHook(
#if defined SP_POSIX
        void *instance,
#endif
        entvars_t *pevInflictor,
        entvars_t *pevAttacker,
        float flDamage,
        std::int32_t bitsDamageType [[maybe_unused]])
    {
#if defined SP_WINDOWS
        void *instance;
        __asm
        {
            mov [instance], ecx
        }
#endif

        return 0;
    }

    /*void TraceAttack( entvars_t *pevAttacker, float flDamage, Vector vecDir, TraceResult *ptr, int
     * bitsDamageType); */
    void vTraceAttack(
#if defined SP_POSIX
        void *instance,
#endif
        entvars_t *pevAttacker,
        float flDamage,
        Vector vecDir,
        ::TraceResult *ptr,
        std::int32_t bitsDamageType)
    {
#if defined SP_WINDOWS
        void *instance;
        __asm
        {
            mov [instance], ecx
        }
#endif
    }

} // namespace