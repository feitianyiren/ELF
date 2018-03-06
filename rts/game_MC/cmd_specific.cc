/**
* Copyright (c) 2017-present, Facebook, Inc.
* All rights reserved.
*
* This source code is licensed under the BSD-style license found in the
* LICENSE file in the root directory of this source tree. An additional grant
* of patent rights can be found in the PATENTS file in the same directory.
*/

#include "engine/cmd.h"
#include "engine/game_env.h"
#include "engine/cmd_receiver.h"

// Derived class. Note that the definition is automatically generated by a python file.
#include "engine/cmd.gen.h"
#include "engine/cmd_specific.gen.h"
#include "cmd_specific.gen.h"
#include "lua/cpp_interface.h"

bool CmdGenerateMap::run(GameEnv *env, CmdReceiver*) {
    RTSMapGenerator::GenerateRandom(env->GetMap(), env->GetNumOfPlayers(), _seed);
    // create fog for each player
    for (int player_id = 0; player_id < env->GetNumOfPlayers(); ++player_id) {
        env->GetPlayer(player_id).CreateFog();
    }

    return true;
}

#define _CREATE(...) receiver->SendCmd(CmdIPtr(new CmdCreate(INVALID, __VA_ARGS__)))
#define _CHANGE_RES(...) receiver->SendCmd(CmdIPtr(new CmdChangePlayerResource(INVALID, __VA_ARGS__)))


bool CmdGameStartSpecific::run(GameEnv*, CmdReceiver*) {
    return true;
}

bool CmdGenerateUnit::run(GameEnv *env, CmdReceiver *receiver) {
    RTSUnitGenerator::Generate(&env->GetMap(), env->GetNumOfPlayers(), _seed, receiver);
    return true;
}

#undef _CHANGE_RES
#undef _CREATE
