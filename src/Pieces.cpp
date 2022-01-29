//
// Created by Krzysiek on 29/01/2022.
//

#include <iostream>
#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Pieces.h"

std::map<PieceType, std::vector<Pair>> pieces = {
		{
				I, {Pair(0, 0), Pair(1, 0), Pair(2, 0), Pair(3, 0)}
		},
		{
				J, {Pair(0, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}
		},
		{
				L, {Pair(3, 0), Pair(1, 1), Pair(2, 1), Pair(3, 1)}
		},
		{
				O, {Pair(1, 0), Pair(2, 0), Pair(1, 1), Pair(2, 1)}
		},
		{
				S, {Pair(1, 0), Pair(2, 0), Pair(0, 1), Pair(1, 1)}
		},
		{
				T, {Pair(1, 0), Pair(0, 1), Pair(1, 1), Pair(2, 1)}
		},
		{
				Z, {Pair(0, 0), Pair(1, 0), Pair(1, 1), Pair(2, 1)}
		},
};