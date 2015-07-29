// This function takes a string that should be translated
// and asks the server for the translation to the server's locale.
// Translation of the string is returned.
//
// NOTE: This function works SYNCRHONOUSLY
function localize(str) {
    var URL = "?cmd=loc&value=" + str;

    return $.ajax({
        type: "GET",
        url: URL,
        async: false
    }).responseText;
}

// After the page has loaded, load the Ckeditor and the attachment dropbox
$(document).ready(function() {

	$('textarea').addClass("ckeditor");

	// Need to wait for the ckeditor instance to finish initialization
    // because CKEDITOR.instances.editor.commands is an empty object
    // if you try to use it immediately after CKEDITOR.replace('editor');
    CKEDITOR.on('instanceReady', function (ev) {

        var editor = ev.editor;

        // Make the editor bigger (at least 500px high and 80% of the viewport otherwise)
        //var width = Math.max(500, 0.7 * $(window).height() );
        //editor.resize("100%", new String(width));
        init_resize();

        // Create a new command with the desired exec function
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
                // This code will open the Upload tab.
                this.selectPage('Upload');
                // replace the submit function with something useless
                dialogObj.getContentElement( 'Upload', 'upload' ).submit = function() {
                    return false;
                };
            });
        }
    });

    // Replace the textarea with the CKeditor
    CKEDITOR.replace('Text', { language: CKEditorLang });

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
});