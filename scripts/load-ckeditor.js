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
    CKEDITOR.on('dialogDefinition', function (ev) {
        // Take the dialog name and its definition from the event data.
        var dialogName = ev.data.name;
        var dialogDefinition = ev.data.definition;

        // Check if the definition is from the dialog we're
        // interested in (the 'image2' and 'fileupload' dialog).
        if ( dialogName == 'image2' || dialogName == 'fileupload') {

            var dialogObj = dialogDefinition.dialog;
            dialogObj.on("show", function() {
                // replace the submit function with something useless
                dialogObj.getContentElement( 'Upload', 'upload' ).submit = function() {
                    return false;
                };
            });
        }
    });

    CKEDITOR.replace('Text');
});