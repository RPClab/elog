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

    CKEDITOR.replace('Text');
});