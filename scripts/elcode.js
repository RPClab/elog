function getSelection(text)
{
   if (typeof text == 'undefined')
      return "";
   if (browser == 'MSIE') {
      sel = document.selection;
      rng = sel.createRange();
      rng.colapse;
      return rng.text; 
   } else {
      if (text.selectionEnd > 0 && text.selectionEnd != text.selectionStart && 
          text.value.charAt(text.selectionEnd-1) == ' ')
         return text.value.substring(text.selectionStart, text.selectionEnd-1);
      else
         return text.value.substring(text.selectionStart, text.selectionEnd);
   }
}

function replaceSelection(doc, text, newSelection, cursorPos)
{
   if (browser == 'MSIE') {
      text.focus();
      sel = doc.selection;
      rng = sel.createRange();
      rng.colapse;
      is_sel = rng.text.length > 0;
      rng.text = newSelection;
      if (!is_sel) {
         rng.moveStart('character', -(newSelection.length-cursorPos));
         rng.moveEnd('character', -(newSelection.length-cursorPos));
         rng.select();
      }
   } else {
      start = text.selectionStart;
      stop  = text.selectionEnd;
      if (text.selectionEnd > 0 && text.selectionStart != text.selectionEnd &&
          text.value.charAt(text.selectionEnd-1) == ' ')
        stop--;
      end   = text.textLength;
      endtext = text.value.substring(stop, end);
      starttext = text.value.substring(0, start);
      oldTop = text.scrollTop;
      text.value = starttext + newSelection + endtext;
      if (start != stop) {
         text.selectionStart = start;
         text.selectionEnd   = start + newSelection.length;
      } else {
         text.selectionStart = start +	cursorPos;
         text.selectionEnd   = text.selectionStart;
     }
     text.scrollTop = oldTop;
   }
}

function elcode(text, tag, value)
{
   elcode1(text, tag, value, '');
}

function elcode1(text, tag, value, selection)
{
   if (selection == '')
      selection = getSelection(text);

   if (tag == '')
      str = selection + value;
   else if (tag == 'LIST')
      str = '[LIST]\r\n[*] ' + selection + '\r\n[/LIST]';
   else if (tag == 'TABLE')
      str = '[TABLE border="1"]\r\nA|B\r\n|-\r\nC|D\r\n[/TABLE]';
   else if (tag == 'LINE')
      str = selection + '[LINE]';
   else if (tag == '*')
      str = '\r\n[*] ';   
   else if (value == '')
      str = '['+tag+']' + selection + '[/'+tag+']';
   else
      str = '['+tag+'='+value+']' + selection + '[/'+tag+']';

   if (tag == '')
      pos = value.length;
   else if (tag == 'LIST')
      pos = 11;
   else if (tag == 'TABLE')
      pos = 19;
   else if (tag == '*')
      pos = 5;   
   else if (value == '')
      pos = tag.length + 2;
   else
      pos = tag.length + value.length + 3;
   replaceSelection(document, text, str, pos);
   text.focus();
}

function elcode2(doc, text, tag, value)
{
   str = '['+tag+']' + value + '[/'+tag+']';

   pos = str.length;
   replaceSelection(doc, text, str, pos);
   text.focus();
}

function queryURL(text)
{
   selection =	getSelection(text);
   linkText = prompt(linkText_prompt, selection);
   linkURL = prompt(linkURL_prompt, 'http://');
   elcode1(text, 'URL',	linkURL, linkText);
}

function queryHeading(text)
{
   selection =	getSelection(text);
   heading = prompt(linkHeading_prompt, '');
   tag = 'H' + heading;
   elcode1(text, tag, '', selection);
}

function insertTime(text)
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
     if(xmlHttp.readyState == 4)
       {
       selection =	getSelection(text);
       elcode1(text, '', xmlHttp.responseText, selection);
       }
  }
  
  xmlHttp.open("GET","?cmd=gettimedate",true);
  xmlHttp.send(null);
}

function elKeyInit()
{
   document.onkeypress = elKeyPress;
}

function elKeyPress(evt)
{
   evt = (evt) ? evt : window.event;
   var unicode = evt.charCode ? evt.charCode : evt.keyCode;
   var actualkey = String.fromCharCode(unicode);

   if (evt.ctrlKey && !evt.shiftKey && !evt.altKey) {

      if (browser == 'MSIE' || browser == 'Safari') {
         if (unicode == 10)
            unicode = 13;
         else   
            unicode += 96;
         actualkey = String.fromCharCode(unicode);
      }

      if (actualkey == "b") {
         elcode(document.form1.Text, 'B','');
         return false;
      }
      if (actualkey == "i") {
         elcode(document.form1.Text, 'I','');
         return false;
      }
      if (actualkey == "u") {
         elcode(document.form1.Text, 'U','');
         return false;
      }
      if (actualkey == "o") {
         elcode(document.form1.Text, 'CODE','');
         return false;
      }
      if (actualkey == "l") {
         elcode(document.form1.Text, 'LIST','');
         return false;
      }
      if (actualkey == "n") {
         elcode(document.form1.Text, '*','');
         return false;
      }
      if (actualkey == "h") {
         queryHeading(document.form1.Text);
         return false;
      }
      if (actualkey == "m") {
         window.open('upload.html','','top=280,left=350,width=500,height=120,dependent=yes,menubar=no,status=no,scrollbars=no,location=no,resizable=yes');
         return false;
      }
      if (actualkey == "p") {
         document.form1.jcmd.value = "Preview";
         chkform();
         cond_submit();
         return false;
      }
      
      if (unicode == 13) { // return
         document.form1.jcmd.value = "Submit";
         chkform();
         cond_submit();
         return false;
      }
   }
   
   return true;
}

function browse(evt)
{
   evt = (evt) ? evt : window.event;
   var unicode = evt.charCode ? evt.charCode : evt.keyCode;
   var actualkey = String.fromCharCode(unicode);

   if (evt.ctrlKey && !evt.altKey) {

      if (browser == 'MSIE') {
         if (unicode == 10)
            unicode = 13;
         else   
            unicode += 96;
         actualkey = String.fromCharCode(unicode);
      }

      if (actualkey == "$") {
         // home
         window.location.href = "?cmd_first.x=1";
         return false;
      }
      if (actualkey == "#") {
         // end
         window.location.href = "?cmd_last.x=1";
         return false;
      }
      if (actualkey == "!") {
         // page up
         window.location.href = "?cmd_previous.x=1";
         return false;
      }
      if (actualkey == "\"") {
         // page down
         window.location.href = "?cmd_next.x=1";
         return false;
      }
   }
   
   return true;
}
