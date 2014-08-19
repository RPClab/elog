$(document).ready(function() {

	$('textarea').addClass("ckeditor");

	// Need to wait for the ckeditor instance to finish initialization
    // because CKEDITOR.instances.editor.commands is an empty object
    // if you try to use it immediately after CKEDITOR.replace('editor');
    CKEDITOR.on('instanceReady', function (ev) {

        // Create a new command with the desired exec function
        var editor = ev.editor;
        var overridecmd = new CKEDITOR.command(editor, {
            exec: function(editor){
	        	// Replace this with your desired save button code
	        	// alert(editor.document.getBody().getHtml());
			   window.top.document.form1.jcmd.value = "Submit";
			   if(window.top.chkform())
			      window.top.cond_submit();
            }
        });

        // Replace the old save's exec function with the new one
        ev.editor.commands.save.exec = overridecmd.exec;
    });

    // There is a default listener on the submit button that we
    // need to get rid off in order to get custom upload working
    // without also firing an empty POST request
    CKEDITOR.on('dialogDefinition', function (ev) {
        // Take the dialog name and its definition from the event data.
        var dialogName = ev.data.name;
        var dialogDefinition = ev.data.definition;

        // Check if the definition is from the dialog we're
        // interested in (the 'image2' and 'fileuploadDialog' dialog).
        if ( dialogName == 'image2' || dialogName == 'fileuploadDialog') {

            var dialogObj = dialogDefinition.dialog;
            dialogObj.on("show", function() {
                // replace the submit function with something useless
                dialogObj.getContentElement( 'Upload', 'upload' ).submit = function() {
                    return false;
                };
            });
        }
    });

    // Replace the textarea with the CKeditor
    CKEDITOR.replace('Text');

    // Workaround function for the drag and drop events, it disallows
    // dragstart and dragend events firing for each child elements of a specific elements.
    // In other words, events are only going to fire when an element is dragged over an element
    // and its children and when the item is dragged away from the element and its children
    $.fn.dndhover = function(options) {

        return this.each(function() {

            var self = $(this);
            var collection = $();

            self.on('dragenter', function(event) {
                if (collection.size() === 0) {
                    self.trigger('dndHoverStart');
                }
                collection = collection.add(event.target);
            });

            self.on('dragleave', function(event) {
                /*
                 * Firefox 3.6 fires the dragleave event on the previous element
                 * before firing dragenter on the next one so we introduce a delay
                 */
                setTimeout(function() {
                    collection = collection.not(event.target);
                    if (collection.size() === 0) {
                        self.trigger('dndHoverEnd');
                    }
                }, 1);
            });

            self.on('drop', function(event) {
                collection = $();
                self.trigger('dndHoverEnd');
            });
        });
    };

    var uploading_dropped_files = false;

    // We should check if the browser supports these events
    var tests = {
        filereader: typeof FileReader != 'undefined',
        dnd: 'draggable' in document.createElement('span'),
        formdata: !!window.FormData,
        progress: "upload" in new XMLHttpRequest
    }

    function upload(files) {
        // debugger;

        var formData = tests.formdata ? new FormData() : null;

        // add all the other attachments that were previously added
        $( "input[name^='attachment']" ).each(function(idx, el) {
            formData.append($(el).attr('name'), $(el).attr('value'));
            // console.log(el);
        });

        formData.append('drop-count', files.length);        // number of files dropped that should be sent
        for (var i = 0; i < files.length; i++) {
            if (tests.formdata) {
                formData.append('next_attachment', parent.next_attachment);
                formData.append('encoding', "HTML");
                formData.append('attfile', files[i]);

                parent.next_attachment += 1;
            }
        }


        formData.append('cmd', "Upload");          // Command for server to recognize this as an file upload

        if (tests.formdata) {
            var URL = '/' + parent.logbook + '/upload.html?next_attachment=' + parent.next_attachment;

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

            // Start the POST request with dropped files
            // submiter.click();

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

    var holder = $("#holder");
    holder.dndhover().on({
        'dndHoverStart' : function(event) {
            event.stopPropagation();
            event.preventDefault();
            console.log("holder-enter")
            holder.css("border", "10px dashed #0c0");
            return false;
        },
        'dragover' : function(event) {
            event.stopPropagation();
            event.preventDefault();
            return false;
        },
        'dndHoverEnd' : function(event) {
            event.stopPropagation();
            event.preventDefault();
            console.log("holder-leave");
            holder.css("border", "10px dashed #ccc");
            return false;
        },
        'drop' : function(e) {
            e.preventDefault();

            console.log("holder-drop");
            holder.css("border", "10px dashed #ccc");

            upload(e.originalEvent.dataTransfer.files);
        }
    });
});