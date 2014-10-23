/**
 * The abbr dialog definition.
 *
 * Created out of the CKEditor Plugin SDK:
 * http://docs.ckeditor.com/#!/guide/plugin_sdk_sample_1
 */

// Our dialog definition.
CKEDITOR.dialog.add( 'fileuploadDialog', function( editor ) {

	var lang = editor.lang.image2;
	var	commonLang = editor.lang.common

	return {

		// Basic properties of the dialog window: title, minimum size.
		title: commonLang.upload + ' file',
		minWidth: 200,
		minHeight: 150,

		// Dialog window contents definition.
		contents: [
			{
				// Definition of the Upload Settings dialog tab (page).
				id: 'Upload',
				label: lang.uploadTab,

				// The tab contents.
				elements: [
					{
						// File browser for selecting a file
						type: 'file',
						id: 'upload',
						label: lang.btnUpload,
						style: 'height:40px',
					},
					{
						// Button for uploading the file.
						type: 'fileButton',
						id: 'uploadButton',
						label: lang.btnUpload,
					    onLoad: function( a ) {
					        CKEDITOR.document.getById( this.domId ).on( 'click', function() {

					        	// grab the file(s) from the file input tag and upload it using AJAX
				            	var dialog = this.getDialog();
            					var files = dialog.getContentElement("Upload", "upload").getInputElement().$.files;

            					// no files were selected
            					if(files.length == 0) {
            						alert("Please select a file!");
            						return false;
            					}

            					// Create the form data object for uploading with POST
            					var formData = new FormData();

						        // add all the other attachments that were previously added
						        $( "input[name^='attachment']" ).each(function(idx, el) {
						            formData.append($(el).attr('name'), $(el).attr('value'));
						        });


            					formData.append('drop-count', files.length);		// number of files being uploaded
							    for (var i = 0; i < files.length; i++) {
						    		formData.append('next_attachment', parent.next_attachment);
						    		formData.append('encoding', "HTML");
						    		formData.append('attfile', files[i]);
						    		parent.next_attachment += 1;

						    		// Remember the original name of the file in a hidden text field
						    		dialog.getContentElement( 'Upload', 'name' ).setValue( files[i].name );
				    			}
				    			formData.append('cmd', "Upload");          // Command for server to recognize this as an file upload

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
								  success: function(data) {

		                			// Extract the last attachment section of the returned page
							        var attch = $(".attachment", $(data)).last();

							        // Create a new attachment section that will replace the current one
							        var attch_upload = $("#attachment_upload", $(data));

							        // Extract the url
							        var src = $("input", attch)[0].value;

								  	if(src) {	// check if we have the correct response
								  		dialog.getContentElement( 'Upload', 'src' ).setValue( src );
								  	} else {
								  		console.log("Data returned is not json...");
								  	}

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
								  	console.log("Error while uploading file...");
								  }
								});

								// Do not call the built-in click command
								return false;
					        }, this );
					    },
						'for': [ 'Upload', 'upload' ]
					},
					{
						// URL of the file
						type: 'text',
						id: 'src',
						label: commonLang.url,

						// Validation checking whether the field is not empty.
						validate: CKEDITOR.dialog.validate.notEmpty( "URL cannot be empty!" )
					},
					{
						// Original name of the file
						type: 'text',
						id: 'name',
						label: commonLang.name,
						validate: CKEDITOR.dialog.validate.notEmpty( "Name cannot be empty!" )
					}
				]
			}
		],

		// This method is invoked once a user clicks the OK button, confirming the dialog.
		onOk: function() {
            var dialog = this;

            var file = editor.document.createElement( 'a' );
            file.setAttribute( 'href', dialog.getValueOf( 'Upload', 'src' ) );
            file.setText( dialog.getValueOf( 'Upload', 'name' ) );

            editor.insertElement( file );
		}
	};
});