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

/*---- 'Submit' ----------------------------------------------------*/

// Register 'Submit' toolbar button
var oELOGSubmitItem = new FCKToolbarButton('ELOGSubmit', 'Submit Entry', null, null, true, null, 3);
FCKToolbarItems.RegisterItem('ELOGSubmit', oELOGSubmitItem);

// Register 'Submit' command
var oELOGSubmitCommand = new Object();
oELOGSubmitCommand.Name = 'ELOGSubmit';

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

/*---- 'ELOGImage' ------------------------------------------------*/

// Register 'ELOGImage' toolbar button
var oELOGImage = new FCKToolbarButton('ELOGImage', 'Insert Image', null, null, true, null, 37);
FCKToolbarItems.RegisterItem('ELOGImage', oELOGImage);

// Register 'ELOGImage' command
var oELOGImageCommand = new Object();
oELOGImageCommand.Name = 'ELOGImage';

oELOGImageCommand.Execute = function()
{
   window.open('../../'+parent.logbook+'/upload.html?next_attachment='+parent.next_attachment, '',
   'top=280,left=350,width=500,height=120,dependent=yes,menubar=no,status=no,scrollbars=no,location=no,resizable=yes');
}

oELOGImageCommand.GetState = function()
{
 	 // This function is always enabled.
   return FCK_TRISTATE_OFF ;
}

FCKCommands.RegisterCommand('ELOGImage', oELOGImageCommand);

/*---- 'InsertTime' ------------------------------------------------*/

// Create 'InsertTime' toolbar button
var oInsertTimeItem = new FCKToolbarButton('InsertTime', 'Insert Date/Time', null, null, true, null, 4);
oInsertTimeItem.IconPath = FCKConfig.PluginsPath + 'elog/inserttime.gif' ; 
FCKToolbarItems.RegisterItem('InsertTime', oInsertTimeItem);

// Register 'InsertTime' command
var oInsertTimeCommand = new Object();
oInsertTimeCommand.Name = 'InsertTime';

oInsertTimeCommand.Execute = function()
{
   var xmlHttp;
   
   try {
      xmlHttp = new XMLHttpRequest(); // Firefox, Opera 8.0+, Safari
   }
   catch (e) {
      try {
         xmlHttp=new ActiveXObject("Msxml2.XMLHTTP"); // Internet Explorer
      }
   catch (e) {
      try {
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      catch (e) {
        alert("Your browser does not support AJAX!");
        return false;
      }
    }
  }
  
  xmlHttp.onreadystatechange = function()
  {
    if(xmlHttp.readyState == 4) {
      // Get the editor instance that we want to interact with.
      var oEditor = FCKeditorAPI.GetInstance('Text') ;

      // Insert the desired HTML.
      oEditor.InsertHtml(xmlHttp.responseText);
      }
  }
  
  xmlHttp.open("GET","../../?cmd=gettimedate",true);
  xmlHttp.send(null);
}

oInsertTimeCommand.GetState = function()
{
   // This function is always enabled.
   return FCK_TRISTATE_OFF ;
}

FCKCommands.RegisterCommand('InsertTime', oInsertTimeCommand);
