/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TITANIC_SEASONAL_ADJUSTMENT_H
#define TITANIC_SEASONAL_ADJUSTMENT_H

#include "titanic/core/background.h"

namespace Titanic {

class CSeasonalAdjustment : public CBackground {
	DECLARE_MESSAGE_MAP;
	bool StatusChangeMsg(CStatusChangeMsg *msg);
	bool MouseButtonDownMsg(CMouseButtonDownMsg *msg);
	bool MouseButtonUpMsg(CMouseButtonUpMsg *msg);
	bool MovieEndMsg(CMovieEndMsg *msg);
	bool TurnOn(CTurnOn *msg);
	bool TurnOff(CTurnOff *msg);
	bool ActMsg(CActMsg *msg);
private:
	bool _switching;
	bool _enabled;
public:
	CLASSDEF;
	CSeasonalAdjustment() : CBackground(), _switching(false), _enabled(false) {}

	/**
	 * Save the data for the class to file
	 */
	void save(SimpleFile *file, int indent) override;

	/**
	 * Load the data for the class from file
	 */
	void load(SimpleFile *file) override;
};

} // End of namespace Titanic

#endif /* TITANIC_SEASONAL_ADJUSTMENT_H */
