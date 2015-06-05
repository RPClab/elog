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

// asend does an AJAX call to send current form data to server
function asend() {
   var f = document.form1;
   var r = XMLHttpRequestGeneric();
   r.onreadystatechange = function()
     {
       if (r.readyState==4)
          in_asend = false;
     
       // after successful completion ...
       if (r.readyState==4 && r.status==200) {
          // restore original title
          document.title = page_title;
       
          // set "saved" message
          d = new Date();
          e1 = document.getElementById('saved1');
          e1.style.display = 'inline';
          s = e1.innerHTML.substring(0, e1.innerHTML.length-8);
          e1.innerHTML = s+d.toTimeString().substring(0, 8);
          e2 = document.getElementById('saved2');
          e2.innerHTML = e1.innerHTML;
          e2.style.display = 'inline';
          
          // append edit_id (to prevent creation of new messages)
          if (r.responseText.substring(0,2) == 'OK') {
             if (document.getElementById('edit_id') == null) {
                var id = r.responseText.substring(3);
                var input = document.createElement('input');
                input.type  = 'hidden';
                input.name  = 'edit_id';
                input.id    = 'edit_id';
                input.value = parseInt(id);
                document.form1.appendChild(input);
             }
          }
       }
     }

   r.open("Post", ".");
   
   // get all form fields
   var f = new FormData(document.form1);
   var t;

   // append text for CKEDITOR and textarea, respectively
   if (typeof f.delete == 'function') // not avalable in all browsers
      f.delete("Text");
   if (typeof(CKEDITOR) != 'undefined')
      t = CKEDITOR.instances.Text.getData();
   else if (document.form1.Text != undefined)
      t = document.form1.Text.value;
   
   if (t != undefined)
      f.append("Text", t);
   
   // add jcmd
   f.append("jcmd", "Save");
   in_asend = true;
   r.send(f);
}

// getElementById
function $id(id) {
   return document.getElementById(id);
}

var uploading_dropped_files = false;

// upload file(s) after thei have been dropped
function upload(files) {
   var formData = (!!window.FormData) ? new FormData() : null;
   
   // add all the other attachments that were previously added
   $( "input[name^='attachment']" ).each(function(idx, el) {
                                         formData.append($(el).attr('name'), $(el).attr('value'));
                                         });
   
   formData.append('drop-count', files.length);        // number of files dropped that should be sent
   for (var i = 0; i < files.length; i++) {
      if (!!window.FormData) {
         formData.append('next_attachment', parent.next_attachment);
         formData.append('encoding', "HTML");
         formData.append('attfile', files[i]);
         
         parent.next_attachment += 1;
      }
   }
   
   formData.append('cmd', "Upload");          // Command for server to recognize this as an file upload
   
   if (!!window.FormData) {
      var URL = 'upload.html?next_attachment=' + parent.next_attachment;
      
      // set the flag so the chkupload validator doesn't trigger
      uploading_dropped_files = true;
      
      var submiter = $("input[value='Upload']");
      var fileinput = $("input[type='File']");
      
      // If we are uploading drag&drop files then ignore the validator
      submiter.on("click", function(e) {
                  if(uploading_dropped_files == false) {
                  return chkupload();
                  }
                  return true;
                  });
      
      // We have finished uploading drag&drop files
      uploading_dropped_files = false;
      
      $.ajax({
             xhr: function()
             {
             var xhr = new window.XMLHttpRequest();
             
             // Start the progress bar
             progressJs().start();
             
             //Upload progress
             xhr.upload.addEventListener("progress", function(evt){
                                         if (evt.lengthComputable) {
                                         var percentComplete = evt.loaded / evt.total;
                                         //Update the progress bar
                                         progressJs().set(percentComplete);
                                         }
                                         }, false);
             
             return xhr;
             },
             contentType: false,
             processData: false,
             type: 'POST',
             url: URL,
             data: formData,
             success: function(data) {
             // End the progress bar
             progressJs().end();
             
             var attch = $(".attachment", $(data));
             var attch_upload = $("#attachment_upload", $(data));
             
             // add the new attachments to the current page
             $("#attachment_upload").before(attch.slice(-files.length));
             
             // replace the attachment upload section
             $("#attachment_upload").replaceWith(attch_upload);
             },
             fail: function() {
             // End the progress bar
             progressJs().end();
             console.log("Error uploading files...");
             }
             });
   }
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
}

function dragleave(e)
{
   e.stopPropagation();
   e.preventDefault();
   $id('holder').style.border = '6px dashed #ccc';
}

function drop(e)
{
   e.stopPropagation();
   e.preventDefault();
   $id('holder').style.border = '6px dashed #ccc';
   upload(e.dataTransfer.files);
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
   d.addEventListener('dragover', dragover);
   d.addEventListener('dragenter', dragenter);
   d.addEventListener('dragleave', dragleave);
   d.addEventListener('drop', drop);
}
