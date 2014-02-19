/*
 * Copyright 2010-2013 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "DeleteGameState.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Game.h"
#include "../Engine/Language.h"
#include "../Engine/Palette.h"
#include "../Interface/Text.h"
#include "../Interface/Window.h"
#include "../Interface/TextButton.h"
#include "../Resource/ResourcePack.h"
#include "SavedGameState.h"
#include "../Engine/Options.h"
#include "../Engine/Exception.h"
#include "ErrorMessageState.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Confirmation screen.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 * @param save Name of the save file to delete.
 */
DeleteGameState::DeleteGameState(Game *game, OptionsOrigin origin, const std::wstring &save) : State(game), _origin(origin)
{
	std::string file = Language::wstrToFs(save);
	_filename = Options::getUserFolder() + file + ".sav";
	_screen = false;

	// Create objects
	_window = new Window(this, 256, 120, 32, 40, POPUP_BOTH);
	_btnYes = new TextButton(60, 18, 90, 112);
	_btnNo = new TextButton(60, 18, 170, 112);
	_txtMessage = new Text(246, 32, 37, 70);

	// Set palette
	if (_origin != OPT_BATTLESCAPE)
	{
		_game->setPalette(_game->getResourcePack()->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(6)), Palette::backPos, 16);
	}

	add(_window);
	add(_btnYes);
	add(_btnNo);
	add(_txtMessage);

	centerAllSurfaces();

	// Set up objects
	_window->setColor(Palette::blockOffset(8)+10);
	_window->setBackground(game->getResourcePack()->getSurface("BACK01.SCR"));

	_btnYes->setColor(Palette::blockOffset(8)+10);
	_btnYes->setText(tr("STR_YES"));
	_btnYes->onMouseClick((ActionHandler)&DeleteGameState::btnYesClick);
	_btnYes->onKeyboardPress((ActionHandler)&DeleteGameState::btnYesClick, (SDL_Keycode)Options::getInt("keyOk"));

	_btnNo->setColor(Palette::blockOffset(8)+10);
	_btnNo->setText(tr("STR_NO"));
	_btnNo->onMouseClick((ActionHandler)&DeleteGameState::btnNoClick);
	_btnNo->onKeyboardPress((ActionHandler)&DeleteGameState::btnNoClick, (SDL_Keycode)Options::getInt("keyCancel"));

	_txtMessage->setColor(Palette::blockOffset(8)+10);
	_txtMessage->setAlign(ALIGN_CENTER);
	_txtMessage->setBig();
	_txtMessage->setWordWrap(true);
	_txtMessage->setText(tr("STR_IS_IT_OK_TO_DELETE_THE_SAVED_GAME"));

	if (_origin == OPT_BATTLESCAPE)
	{
		applyBattlescapeTheme();
	}
}

/**
 *
 */
DeleteGameState::~DeleteGameState()
{

}

void DeleteGameState::btnNoClick(Action *)
{
	_game->popState();
}

void DeleteGameState::btnYesClick(Action *)
{
	_game->popState();
	if (!CrossPlatform::deleteFile(_filename))
	{
		std::wstring error = tr("STR_DELETE_UNSUCCESSFUL");
		if (_origin != OPT_BATTLESCAPE)
			_game->pushState(new ErrorMessageState(_game, error, Palette::blockOffset(8)+10, "BACK01.SCR", 6));
		else
			_game->pushState(new ErrorMessageState(_game, error, Palette::blockOffset(0), "TAC00.SCR", -1));
	}
}

}
