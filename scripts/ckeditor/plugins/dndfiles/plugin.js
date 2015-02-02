/**
 * Basic sample plugin inserting current date and time into CKEditor editing area.
 */

// Register the plugin within the editor.
CKEDITOR.plugins.add( 'dndfiles', {

	icons: 'dndfiles',

	// The plugin initialization logic goes inside this method.
	init: function( editor ) {

		// Define an editor command that inserts a timestamp.
		editor.addCommand( 'dragndrop', {

			// Define the function that will be fired when the command is executed.
			exec: function( editor ) {

				// stores the names of all the files that are uploaded
				var filename = [];
				var iframe = document.getElementsByTagName('iframe')[0];
				var iframeHTML = $(iframe).contents().find("html");

				var holder = $(document.getElementsByTagName('iframe')[0].contentDocument),
				    tests = {
				      filereader: typeof FileReader != 'undefined',
				      dnd: 'draggable' in document.createElement('span'),
				      formdata: !!window.FormData,
				      progress: "upload" in new XMLHttpRequest
				    }

				// Function that initializes all relevant listeners for the drag and drop events
				function init() {

					if(tests.dnd) { // Drag and drop is enabled

						// Handle drag and drop events
						holder.dndhover().on({
						    'dndHoverStart': function(event) {
						        event.stopPropagation();
						        event.preventDefault();

						        iframeHTML.css('box-shadow', 'inset 0px 0px 10px 1px #999998');

						        return false;
						    },
						    'dndHoverEnd': function(event) {
						        event.stopPropagation();
						        event.preventDefault();

						        iframeHTML.css('box-shadow', '0px 0px 0px 0px #999999');

						        return false;
						    },
						    'drop' : function(e) {
						    	e.preventDefault();

						    	iframeHTML.css('box-shadow', '0px 0px 0px 0px #999999');

						    	// Upload dropped files
						    	upload(e.originalEvent.dataTransfer.files);
						    }
						});
					} else {
						console.log("Drag and drop functionality not available...");
					  fileupload.querySelector('input').onchange = function () {
					    upload(this.files);
					  };
					}
				}

				// Upload dropped files using FormData
				function upload(files) {
				    // debugger;

				    var formData = tests.formdata ? new FormData() : null;

			        // add all the other attachments that were previously added
			        $( "input[name^='attachment']" ).each(function(idx, el) {
			            formData.append($(el).attr('name'), $(el).attr('value'));
			        });

				    formData.append('drop-count', files.length);		// number of files dropped that should be sent
				    for (var i = 0; i < files.length; i++) {
				    	if (tests.formdata) {
				    		formData.append('next_attachment', parent.next_attachment);
				    		formData.append('encoding', "HTML");
				    		formData.append('attfile', files[i]);
				    		formData.append('cmd', "Upload");			// Command for server to recognize this as an file upload
				    		parent.next_attachment += 1;
				    	}
				    }

				    // now post a new XHR request
				    if (tests.formdata) {
				    	var URL = 'upload.html?next_attachment=' + parent.next_attachment;

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

						// This function is called when the upload of files succedes. Displays uploaded images
						// into img tags and everything else as an <a href> tag
						  success: function(data) {
	  					    var html = '';

		        			// Extract the last attachment section of the returned page
					        var attch = $(".attachment", $(data)).slice(-files.length);

					        // Create a new attachment section that will replace the current one
					        var attch_upload = $("#attachment_upload", $(data));

					        $("input", attch).each(function() {

					        	// Extract the url of the file
                        var src = $(this)[0].defaultValue;
                        var thumb = $(this)[0].alt;

					        	// Ignore inputs that have this value as it is not needed
					        	if(src === "Delete")
					        		return;

						    	if(src.indexOf(".png") >= 0 || src.indexOf(".jpg") >= 0 || src.indexOf(".jpeg") >= 0
                           || src.indexOf(".gif") >= 0 || src.indexOf(".svg") >= 0) { // This is an image
						    		html += '<a href = ' + src + '><img src = "' + thumb + '">' + '</a>';
						    	} else {	// this is not an image
						    		// Server appends 14 characters in front of the name so we should remove them
						    		var server_suffix = 14;
						    		html += "<a href = " + src + '>' + src.slice(server_suffix) + '</a>';
						    	}
					        });

						    // Insert files into the editor
						    editor.insertHtml(html);

			                // add the new attachments to the current page
			                $("#attachment_upload").before(attch.slice(-files.length));

			                // replace the attachment upload section
			                $("#attachment_upload").replaceWith(attch_upload);

							// End the progress bar
		                	progressJs().end();
						  },
						  fail: function() {
						  	// End the progress bar
                			progressJs().end();
						  	console.log("Error uploading files...");
						  }
						});
				    }
				}

				init();
			}
		});
	}
});

// Load all of the plugin data so the user can use it immediately on load
CKEDITOR.on( 'instanceReady', function( evt ) {
	var editor = CKEDITOR.instances.Text;
	editor.execCommand("dragndrop");
} );

