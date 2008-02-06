/********************************************************************\

   Name:         md.js
   Created by:   Stefan Ritt

   Contents:     JavaScript code for ImageMagic interface inside ELOG

   $Id$

\********************************************************************/

var dummy = 0;

function im(id, thumb, image, cmd)
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
         if (xmlHttp.responseText != "" &&
             xmlHttp.responseText.search(/Fonts/) == -1)
            alert(xmlHttp.responseText);
         o = document.getElementById(id);
         if (o)
            o.src = thumb+'?'+dummy;
         for (i=0 ; i<8 ; i++) {
            o = document.getElementById(id+'_'+i);
            if (o)
               o.src = thumb+'-'+i+'.png'+'?'+dummy;
         }   
      dummy++;
      }
   }
  
   xmlHttp.open("GET","?cmd=im&req="+cmd+"&img="+image, true);
   xmlHttp.send(null);
}
