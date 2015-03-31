/********************************************************************\

   Name:         dnd.js
   Created by:   Stefan Ritt

   Contents:     JavaScript code for Drag & Drop interface

\********************************************************************/

function XMLHttpRequestGeneric()
{
  var request;
  try {
    request = new XMLHttpRequest(); // Firefox, Opera 8.0+, Safari
  }
  catch (e) {
  try {
      request = new ActiveXObject('Msxml2.XMLHTTP'); // Internet Explorer
    }
    catch (e) {
      try {
        request = new ActiveXObject('Microsoft.XMLHTTP');
      }
      catch (e) {
        alert('Your browser does not support AJAX!');
        return undefined;
      }
    }
  }
  return request;
}
