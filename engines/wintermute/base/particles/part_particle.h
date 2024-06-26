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

/*
 * This file is based on WME Lite.
 * http://dead-code.org/redir.php?target=wmelite
 * Copyright (c) 2011 Jan Nedoma
 */

#ifndef WINTERMUTE_PARTPARTICLE_H
#define WINTERMUTE_PARTPARTICLE_H


#include "engines/wintermute/base/base.h"
#include "engines/wintermute/math/rect32.h"
#include "engines/wintermute/math/vector2.h"

namespace Wintermute {

class PartEmitter;
class BaseSprite;
class BasePersistenceManager;

class PartParticle : public BaseClass {
public:
	enum TParticleState {
	    PARTICLE_NORMAL, PARTICLE_FADEIN, PARTICLE_FADEOUT
	};

	PartParticle(BaseGame *inGame);
	~PartParticle() override;

	float _growthRate;
	bool _exponentialGrowth;

	float _rotation;
	float _angVelocity;

	int32 _alpha1;
	int32 _alpha2;

	Rect32 _border;
	Vector2 _pos;
	float _posZ;
	Vector2 _velocity;
	float _scale;
	BaseSprite *_sprite;
	uint32 _creationTime;
	int32 _lifeTime;
	bool _isDead;
	TParticleState _state;

	bool update(PartEmitter *emitter, uint32 currentTime, uint32 timerDelta);
	bool display(PartEmitter *emitter);

	bool setSprite(const Common::String &filename);

	bool fadeIn(uint32 currentTime, int fadeTime);
	bool fadeOut(uint32 currentTime, int fadeTime);

	bool persist(BasePersistenceManager *PersistMgr) override;
private:
	uint32 _fadeStart;
	int32 _fadeTime;
	int32 _currentAlpha;
	int32 _fadeStartAlpha;
};

} // End of namespace Wintermute

#endif
