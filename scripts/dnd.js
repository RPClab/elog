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

// getElementById
function $id(id) {
   return document.getElementById(id);
}

function drag(e)
{
   console.log('drag');
}

function dragover(e)
{
   e.dataTransfer.dropEffect = 'copy';
   e.preventDefault();
}

function dragenter(e)
{
   e.stopPropagation();
   e.preventDefault();
   $id('holder').style.border = '6px dashed #0c0';
   console.log('dragenter');
}

function dragleave(e)
{
   e.stopPropagation();
   e.preventDefault();
   $id('holder').style.border = '6px dashed #ccc';
   console.log('dragleave');
}

function drop(e)
{
   e.stopPropagation();
   e.preventDefault();
   console.log('drop');
}

function dndInit()
{
   document.body.addEventListener('dragover', function(e) {
                                  e.preventDefault();
                                  });
   document.body.addEventListener('drop', function(e) {
                                  e.preventDefault();
                                  });
   
   d = $id('holder');
   d.addEventListener('drag', drag);
   d.addEventListener('dragover', dragover);
   d.addEventListener('dragenter', dragenter);
   d.addEventListener('dragleave', dragleave);
   d.addEventListener('drop', drop);
}
