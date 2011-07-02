var content  = '<p></p>';
$(document).ready(function() {
    deleteCkeditors();
    CKEDITOR.replace('editor1',
            {
                fullPage : true,
                extraPlugins : 'syntaxhighlight,tableresize',
                width: '75%',
                height: '100%',
                toolbar:
                [
                    ['Source','-','NewPage','-','Templates'],
                    ['Cut','Copy','Paste','PasteText','PasteFromWord','-','SpellChecker', 'Scayt'],
                    ['Undo','Redo','-','Find','Replace','-','SelectAll','RemoveFormat'],
                    ['BidiLtr', 'BidiRtl'],
		    ['Bold','Italic','Underline','Strike','-','Subscript','Superscript'],'/',
                    ['NumberedList','BulletedList','-','Outdent','Indent','Blockquote','CreateDiv'],
                    ['JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock'],
                    ['Link','Unlink','Anchor','Table'],
		    ['TextColor','BGColor','Code','SpecialChar', 'ShowBlocks'],'/',
                    ['Styles','Format','Font','FontSize']
                ]
            });//'Maximize'
    CKEDITOR.on('instanceReady',
      function( evt )
      {
         var editor = evt.editor;
         editor.execCommand('maximize');
	 editor.insertHtml(content);
      });
});

function deleteCkeditors() {
    for (prop in CKEDITOR.instances) {
        var instance = CKEDITOR.instances[prop];
        if (instance) {
            CKEDITOR.remove(instance);
        }
    }
}
function setContent(html) {
    content = html;
}
function insertHTML(html)
{
	var oEditor = CKEDITOR.instances.editor1;
	if ( oEditor.mode == 'wysiwyg' )
	{
		oEditor.insertHtml( html );
	}
	content = html;
}
function getContents()
{
	var oEditor = CKEDITOR.instances.editor1;
	return oEditor.getData();
}