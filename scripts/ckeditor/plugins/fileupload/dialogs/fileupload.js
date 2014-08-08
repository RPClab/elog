/**
 * The abbr dialog definition.
 *
 * Created out of the CKEditor Plugin SDK:
 * http://docs.ckeditor.com/#!/guide/plugin_sdk_sample_1
 */

// Our dialog definition.
CKEDITOR.dialog.add( 'fileuploadDialog', function( editor ) {

	var lang = editor.lang.image2;
	console.log(editor.lang);
	console.log(lang.btnUpload);

	return {

		// Basic properties of the dialog window: title, minimum size.
		title: 'Upload file',
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
            					var formData = new FormData();
            					formData.append('drop-count', files.length);		// number of files being uploaded
            					formData.append('acmd', "Upload");			// Command for the server to recognize this as an ajax upload
							    for (var i = 0; i < files.length; i++) {
						    		formData.append('next_attachment', parent.next_attachment);
						    		formData.append('encoding', "HTML");
						    		formData.append('attfile', files[i]);

						    		// Remember the original name of the file in a hidden text field
						    		dialog.getContentElement( 'Upload', 'name' ).setValue( files[i].name );
				    			}

				    			var URL = '/' + parent.logbook + '/upload.html?next_attachment=' + parent.next_attachment;

								$.ajax({
								  xhr: function()
								  {
								    var xhr = new window.XMLHttpRequest();

								    //Upload progress
								    xhr.upload.addEventListener("progress", function(evt){
								      if (evt.lengthComputable) {
								        var percentComplete = evt.loaded / evt.total;
								        //Do something with upload progress
								        // console.log(percentComplete);
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
            						dialog.getContentElement( 'Upload', 'src' ).setValue( data.attachments[0].fullName );
								  },
								  fail: function() {
								  	console.log("error");
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
						label: "URL",

						// Validation checking whether the field is not empty.
						validate: CKEDITOR.dialog.validate.notEmpty( "URL cannot be empty!" )
					},
					{
						// Original name of the file, this field is hidden and only used to
						// capture and display the original filename in the editor
						type: 'text',
						id: 'name',
						hidden: true
					}
				]
			}
		],

		// This method is invoked once a user clicks the OK button, confirming the dialog.
		onOk: function() {
            var dialog = this;

            console.log(dialog.getValueOf( 'Upload', 'src' ));
            console.log(dialog.getValueOf( 'Upload', 'name' ));

            var file = editor.document.createElement( 'a' );
            file.setAttribute( 'href', dialog.getValueOf( 'Upload', 'src' ) );
            file.setText( dialog.getValueOf( 'Upload', 'name' ) );

            editor.insertElement( file );
		}
	};
});