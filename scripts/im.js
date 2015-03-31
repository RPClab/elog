/********************************************************************\

   Name:         md.js
   Created by:   Stefan Ritt

   Contents:     JavaScript code for ImageMagic interface inside ELOG

   $Id$

\********************************************************************/

var dummy = 0;
var imReq;
var elName;
var thumbName;

function im(name, thumb, image, cmd)
{
   imReq = XMLHttpRequestGeneric();
   elName = name;
   thumbName = thumb;
   imReq.onreadystatechange = onReady;
   imReq.open("GET","?cmd=im&req="+cmd+"&img="+image, true);
   imReq.send(null);
}

function onReady()
{
   if (imReq.readyState == 4) {
      if (imReq.responseText != "" &&
          imReq.responseText.search(/Fonts/) == -1)
         alert(imReq.responseText);
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
   delete imReq;
}

function deleteAtt(idx)
{
   submitted = true;
   document.form1.smcmd.value='delatt'+idx;
   document.form1.submit();
}