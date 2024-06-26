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

#ifndef LASTEXPRESS_RESOURCE_H
#define LASTEXPRESS_RESOURCE_H

#include "lastexpress/data/archive.h"
#include "lastexpress/shared.h"

#include "common/array.h"

namespace LastExpress {

class Background;
class Cursor;
class Font;

class ResourceManager : public Common::Archive {
public:
	ResourceManager(bool demo);
	~ResourceManager() override;

	// Loading
	bool loadArchive(ArchiveIndex type);
	bool isArchivePresent(ArchiveIndex type);
	Common::SeekableReadStream *getFileStream(const Common::String &name) const;

	// Archive functions
	bool hasFile(const Common::Path &path) const override;
	int listMembers(Common::ArchiveMemberList &list) const override;
	const Common::ArchiveMemberPtr getMember(const Common::Path &path) const override;
	Common::SeekableReadStream *createReadStreamForMember(const Common::Path &path) const override;

	// Resource loading
	Background *loadBackground(const Common::String &name) const;
	Cursor *loadCursor() const;
	Font *loadFont() const;

private:
	bool _isDemo;

	bool loadArchive(const Common::Path &name);
	void reset();

	Common::Array<HPFArchive *> _archives;

	friend class Debugger;
};

} // End of namespace LastExpress

#endif // LASTEXPRESS_RESOURCE_H
