#pragma once

#include <string>
#include "Chess.h"

using namespace std;

namespace Factories
{
    class BoardFactory
    {
    public:
        static void CreateBoard(Entities::Chess *game, string whitePieces = "RNBQKBNRpppppppp", string blackPieces = "RNBKQBNRpppppppp");
        static void AddPieces(Entities::Chess *game, string pieces, Player player);
    };
} // namespace Factories