/*
 * ELOG specific FCKedit configuration
 */

FCKConfig.PluginsPath = FCKConfig.BasePath.substr(0, FCKConfig.BasePath.length - 7) + 'editor/plugins/';
FCKConfig.Plugins.Add('elog', null);

FCKConfig.FirefoxSpellChecker	= true ;

FCKConfig.Plugins.Add('dragresizetable');

FCKConfig.ProtectedSource.Add( /<script[\s\S]*?<\/script>/gi ) ; // <SCRIPT> tags
FCKConfig.ProtectedSource.Add( /<(.*?)javascript\:(.*?)/gi ) ; // javascript: tags
FCKConfig.ProtectedSource.Add( /<(.*?)(?:on(blur|c(hange|lick)|dblclick|focus|keypress|(key|mouse)(down|up)|(un)?load|mouse(move|o(ut|ver))|reset|s(elect|ubmit)))=(.*?)(\s*?)(.*?)>/gi ) ; // events

FCKToolbarItems.RegisterItem('SourceSimple', new FCKToolbarButton( 'Source', window.top.ELOGSource, null, FCK_TOOLBARITEM_ONLYICON, true, true, 1));

FCKConfig.ToolbarSets["Default"] = [
	['SourceSimple','FitWindow','ShowBlocks','-','ELOGSubmit','Preview'],
	['Cut','Copy','Paste','PasteText','PasteWord','-','Print','SpellCheck'],
	['Undo','Redo','-','Find','Replace','-','SelectAll','RemoveFormat'],
	['Bold','Italic','Underline','StrikeThrough','-','Subscript','Superscript'],
	['OrderedList','UnorderedList','-','Outdent','Indent'],
	['JustifyLeft','JustifyCenter','JustifyRight','JustifyFull'],
	['InsertLink','Unlink','Anchor'],
	['ELOGImage','Table','Rule','Smiley','SpecialChar','InsertTime'],
	['Style','FontFormat','FontName','FontSize'],
	['TextColor','BGColor'],
	['About']
] ;

FCKConfig.Keystrokes = [
	[ CTRL + 65 /*A*/, true ],
	[ CTRL + 67 /*C*/, true ],
	[ CTRL + 70 /*F*/, true ],
	[ CTRL + 88 /*X*/, true ],
	[ CTRL + 86 /*V*/, 'Paste' ],
	[ SHIFT + 45 /*INS*/, 'Paste' ],
	[ CTRL + 90 /*Z*/, 'Undo' ],
	[ CTRL + 89 /*Y*/, 'Redo' ],
	[ CTRL + SHIFT + 90 /*Z*/, 'Redo' ],
	[ CTRL + 76 /*L*/, 'Link' ],
	[ CTRL + 66 /*B*/, 'Bold' ],
	[ CTRL + 73 /*I*/, 'Italic' ],
	[ CTRL + 85 /*U*/, 'Underline' ],
	[ CTRL + 83 /*S*/, 'Save' ],
	[ CTRL + ALT + 13 /*ENTER*/, 'FitWindow' ],
	[ CTRL + 13 /*ENTER*/, 'ELOGSubmit' ],
	[ CTRL + 9 /*TAB*/, 'Source' ]
] ;

FCKConfig.ContextMenu = ['Generic','Link','Anchor','Image','BulletedList','NumberedList','Table'];
