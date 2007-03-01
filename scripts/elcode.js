function getSelection(text)
{
   if (browser == 'MSIE') {
      sel = document.selection;
      rng = sel.createRange();
      rng.colapse;
      return rng.text; 
   } else if (browser == 'Mozilla')
      if (text.selectionEnd > 0 && text.value.charAt(text.selectionEnd-1) == ' ')
         return text.value.substring(text.selectionStart, text.selectionEnd-1);
      else
         return text.value.substring(text.selectionStart, text.selectionEnd);
   else 
      return "";
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
   } else if (browser == 'Mozilla') {
      start = text.selectionStart;
      stop  = text.selectionEnd;
      if (text.selectionEnd > 0 && text.value.charAt(text.selectionEnd-1) == ' ')
        stop--;
      end   = text.textLength;
      endtext = text.value.substring(stop, end);
      starttext = text.value.substring(0,	start);
      text.value = starttext + newSelection + endtext;
      if (start != stop) {
         text.selectionStart = start;
         text.selectionEnd   = start + newSelection.length;
      } else {
         text.selectionStart = start +	cursorPos;
         text.selectionEnd   = text.selectionStart;
      }
   } else
      text.value += newSelection;
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
   else if (value == '')
      str = '['+tag+']' + selection + '[/'+tag+']';
   else
      str = '['+tag+'='+value+']' + selection + '[/'+tag+']';

   if	(tag == '')
      pos = value.length;
   else if (tag == 'LIST')
      pos = 11;
   else if (tag == 'TABLE')
      pos = 19;
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
