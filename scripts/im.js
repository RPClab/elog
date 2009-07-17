/********************************************************************\

   Name:         md.js
   Created by:   Stefan Ritt

   Contents:     JavaScript code for ImageMagic interface inside ELOG

   $Id$

\********************************************************************/

var dummy = 0;
var httpReq;
var elName;
var thumbName;

function im(name, thumb, image, cmd)
{
   try {
      httpReq = new XMLHttpRequest(); // Firefox, Opera 8.0+, Safari
   }
   catch (e) {
      try {
         httpReq = new ActiveXObject("Msxml2.XMLHTTP"); // Internet Explorer
      }
      catch (e) {
         try {
            httpReq = new ActiveXObject("Microsoft.XMLHTTP");
         } 
         catch (e) {
            alert("Your browser does not support AJAX!");
            return false;
         }
      }
   }
  
   elName = name;
   thumbName = thumb;
   httpReq.onreadystatechange = onReady;
   httpReq.open("GET","?cmd=im&req="+cmd+"&img="+image, true);
   httpReq.send(null);
}

function onReady()
{
   if (httpReq.readyState == 4) {
      if (httpReq.responseText != "" &&
          httpReq.responseText.search(/Fonts/) == -1)
         alert(httpReq.responseText);
      o = document.getElementsByName(elName);
      if (o[0])
         o[0].src = thumbName+'?'+dummy;
      if (o[1])
         o[1].src = thumbName+'?'+dummy;
      for (i=0 ; i<8 ; i++) {
         o = document.getElementsByName(elName+'_'+i);
         if (o[0])
            o[0].src = thumbName+'-'+i+'.png'+'?'+dummy;
         if (o[1])
            o[1].src = thumbName+'-'+i+'.png'+'?'+dummy;
      }
      dummy++;
   }
   delete httpReq;
}

function deleteAtt(idx)
{
   document.form1.smcmd.value='delatt'+idx;
   document.form1.submit();
}