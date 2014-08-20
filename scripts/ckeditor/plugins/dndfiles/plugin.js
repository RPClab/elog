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

						    	console.log("start");

						        iframeHTML.css('box-shadow', 'inset 0px 0px 10px 1px #999998');

						        return false;
						    },
						    'dndHoverEnd': function(event) {
						        event.stopPropagation();
						        event.preventDefault();

						        iframeHTML.css('box-shadow', '0px 0px 0px 0px #999999');

						        console.log("end");
						        return false;
						    },
						    'drop' : function(e) {
						    	e.preventDefault();

						    	console.log("drop");

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

				// This function is called when the upload of files succedes. Displays uploaded images
				// into img tags and everything else as an <a href> tag
				function uploadSuccess(data) {
					// End the progress bar
                	progressJs().end();

                	console.log(data);

				    var html = '';
				    for(var idx = 0; idx < data.attachments.length; idx++) {
				    	var att = data.attachments[idx];
				    	var name = att.fullName;

				    	// this is an image and it has a thumbnail
				    	if(att.thumbName) {
				    		html += '<img src = "' + name + '">';
				    	} else {	// this is not an image
				    		html += "<a href = " + name + '>' + name + '</a>';
				    	}
				    }

				    editor.insertHtml(html);
				}

				// Upload dropped files using FormData
				function upload(files) {
				    // debugger;

				    var formData = tests.formdata ? new FormData() : null;
				    formData.append('drop-count', files.length);		// number of files dropped that should be sent
				    for (var i = 0; i < files.length; i++) {
				    	if (tests.formdata) {
				    		formData.append('next_attachment', parent.next_attachment);
				    		formData.append('encoding', "HTML");
				    		formData.append('attfile', files[i]);
				    		formData.append('acmd', "Upload");			// Command for server to recognize this as an ajax upload
				    		parent.next_attachment += 1;
				    	}
				    }

				    // now post a new XHR request
				    if (tests.formdata) {
				    	var URL = '/' + parent.logbook + '/upload.html?next_attachment=' + parent.next_attachment;

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
						  success: uploadSuccess,
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

