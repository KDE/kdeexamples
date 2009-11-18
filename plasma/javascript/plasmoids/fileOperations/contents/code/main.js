function showOpenFileDialog()
{
    print("opening a file?")
    var dialog = new OpenFileDialog
    dialog.accepted.connect(openFileDialogAccepted)
    dialog.finished.connect(openFileDialogFinished)
    dialog.show()
}

function openFileDialogAccepted(dialog)
{
    var url = dialog.url
    print("open this file! " + url.protocol + ' ' + url.host + ' ' + url.path)
}

function openFileDialogFinished(dialog)
{
    dialog.accepted.disconnect(openFileDialogAccepted)
    dialog.finished.disconnect(openFileDialogFinished)
    plasmoid.gc()
}

function showSaveFileDialog()
{
    print("saving a file?")
    var dialog = new SaveFileDialog
    dialog.accepted.connect(saveFileDialogAccepted)
    dialog.finished.connect(saveFileDialogFinished)
    dialog.show()
}

function saveFileDialogAccepted(dialog)
{
    print("save to this file! " + dialog.files)
}

function saveFileDialogFinished(dialog)
{
    dialog.accepted.disconnect(saveFileDialogAccepted)
    dialog.finished.disconnect(saveFileDialogFinished)
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

