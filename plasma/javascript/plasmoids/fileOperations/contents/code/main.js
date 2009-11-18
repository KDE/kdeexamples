function showOpenFileDialog()
{
    print("opening a file?")
    var dialog = new OpenFileDialog
    dialog.finished.connect(openFileDialogFinished)
    dialog.show()
}

function openFileDialogFinished(dialog)
{
    var url = dialog.url
    print("open this file! " + url.protocol + ' ' + url.host + ' ' + url.path)
    dialog.finished.disconnect(openFileDialogFinished)
    plasmoid.gc()
}

function showSaveFileDialog()
{
    print("saving a file?")
    dialog = new OpenFileDialog
    var dialog = new SaveFileDialog
    dialog.show()
    dialog.finished.connect(saveFileDialogFinished)
}

function saveFileDialogFinished(dialog)
{
    print("save to this file! " + dialog.files)
    dialog.finished.disconnect(openFileDialogFinished)
    plasmoid.gc()
}

open = new PushButton
open.text = i18n("Open File")
open.clicked.connect(showOpenFileDialog)

save = new PushButton
save.text = i18n("Save File")
save.clicked.connect(showSaveFileDialog)

layout = new LinearLayout
layout.setOrientation(QtVertical)
layout.addItem(open)
layout.addItem(save)

