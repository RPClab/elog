/*
 * FCKeditor - The text editor for Internet - http://www.fckeditor.net
 * Copyright (C) 2003-2007 Frederico Caldeira Knabben
 *
 * == BEGIN LICENSE ==
 *
 * Licensed under the terms of any of the following licenses at your
 * choice:
 *
 *  - GNU General Public License Version 2 or later (the "GPL")
 *    http://www.gnu.org/licenses/gpl.html
 *
 *  - GNU Lesser General Public License Version 2.1 or later (the "LGPL")
 *    http://www.gnu.org/licenses/lgpl.html
 *
 *  - Mozilla Public License Version 1.1 or later (the "MPL")
 *    http://www.mozilla.org/MPL/MPL-1.1.html
 *
 * == END LICENSE ==
 *
 * This plugin registers ELOG specific Toolbar items
 */

// Register toolbar button
var oELOGSubmitItem = new FCKToolbarButton('ELOGSubmit', 'Submit Entry', null, null, true, null, 3);
FCKToolbarItems.RegisterItem('ELOGSubmit', oELOGSubmitItem);

// Register command
var oELOGSubmitCommand = new Object() ;
oELOGSubmitCommand.Name = 'ELOGSubmit' ;

oELOGSubmitCommand.Execute = function()
{
   window.top.document.form1.jcmd.value = "Submit";
   if(window.top.chkform())
      window.top.cond_submit();
}

oELOGSubmitCommand.GetState = function()
{
	// This function is always enabled.
	return FCK_TRISTATE_OFF ;
}

FCKCommands.RegisterCommand('ELOGSubmit', oELOGSubmitCommand);

