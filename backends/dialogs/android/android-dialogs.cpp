/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

// TODO FORBIDDEN SYMBOLS?
//#define FORBIDDEN_SYMBOL_EXCEPTION_FILE
//#define FORBIDDEN_SYMBOL_EXCEPTION_time_h
//#define FORBIDDEN_SYMBOL_EXCEPTION_unistd_h
//???
//??? Disable symbol overrides so that we can use system headers
//#define FORBIDDEN_SYMBOL_ALLOW_ALL
#define FORBIDDEN_SYMBOL_EXCEPTION_getenv(a)

// Allow use of stuff in <time.h>
#define FORBIDDEN_SYMBOL_EXCEPTION_time_h

// Disable printf override in common/forbidden.h to avoid
// clashes with log.h from the Android SDK.
// That header file uses
//   __attribute__ ((format(printf, 3, 4)))
// which gets messed up by our override mechanism; this could
// be avoided by either changing the Android SDK to use the equally
// legal and valid
//   __attribute__ ((format(printf, 3, 4)))
// or by refining our printf override to use a varadic macro
// (which then wouldn't be portable, though).
// Anyway, for now we just disable the printf override globally
// for the Android port
#define FORBIDDEN_SYMBOL_EXCEPTION_printf

#include "common/scummsys.h"

#if defined(__ANDROID__) && defined(USE_SYSDIALOGS)

#include "backends/platform/android/android.h"
#include "backends/platform/android/jni-android.h"
#include "backends/dialogs/android/android-dialogs.h"

#include "common/config-manager.h"

AndroidDialogManager::AndroidDialogManager() : DialogManager() {
	reset();
}

void AndroidDialogManager::callbackForJavaPickerDlgReturned(Common::U32String uriSelected, int retCode) {
	 _waitForJavaPickerToReturn = false;
	 _uriSelected = uriSelected;
	 _retCode = retCode;
}

void AndroidDialogManager::reset() {
	 _waitForJavaPickerToReturn = false;
	_uriSelected = "";
	_retCode = -1;
}

Common::DialogManager::DialogResult AndroidDialogManager::showFileBrowser(const Common::U32String &title, Common::FSNode &choice, bool isDirBrowser) {
	DialogResult result = kDialogCancel;
	if (_waitForJavaPickerToReturn) {
		// This should never happen (probably)
		return kDialogCancel;
	}

	char pathBuffer[MAXPATHLEN];

	LOGD("AndroidDialogManager::showFileBrowser()");
	// ????
	Common::String newTitle = title.encode(Common::kISO8859_1);
	// TODO Use last path
	// ConfMan.hasKey("browser_lastpath"))  // ConfMan.get("browser_lastpath").c_str()

	// TODO JNI call
	_waitForJavaPickerToReturn = true;
	if (isDirBrowser) {
		JNI::showAndroidFolderPickerForURI("");
	} else {
		JNI::showAndroidFilePickerForURI("");
	}
	// Since the (java side) Android file and folder pickers are non-blocking (startActivityForResult())
	// We need a waiting loop here, the "callback" in the
	while (_waitForJavaPickerToReturn) {
		// processEvents();
		// updateScreen();
		g_system->delayMillis(10);
	}

	LOGD("AndroidDialogManager::showFileBrowser() - return status: %d", _retCode);
	//LOGD("AndroidDialogManager::showFileBrowser() - SELECTED URI: %S", _uriSelected.c_str());
	// TODO update last browser path
	// TODO how do we set the choice as FSNode??
	// TODO if isDirBrowser false (selection of file, eg. SoundFont) then use JNI call for intent ACTION_OPEN_DOCUMENT
	//
	//
	// NEED TO CALL ScummVMActivity.java: selectDirectoryWithNativeUI(Uri uriToLoad)  for folder pick
	//              AND get the result URI as a sting to use it SOMEHOW for FSNode!
    // NEED TO CALL ScummVMActivity.java: selectFileWithNativeUI(Uri uriToLoad) for file pick
	//              AND get the result URI as a sting to use it SOMEHOW for FSNode!
	// TODO HOW DO WE WAIT FOR onActivityResult and how do we get the resulting URI?
	switch (_retCode) {
	case 0:
		result = kDialogCancel;
		break;
	case 1:
		result = kDialogOk;
		break;
	default:
		result = kDialogError;
	}

	g_system->getEventManager()->getEventDispatcher()->clearEvents();
	reset();
	return result;
}

#endif
