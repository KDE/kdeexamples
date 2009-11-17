function showOpenFileDialog()
{
    print("opening a file?")
    dialog = new OpenFileDialog
    dialog.finished.connect(openFileDialogFinished)
    dialog.show()
}

function openFileDialogFinished(a)
{
    url = a.url
    print("open this file! " + url.protocol + ' ' + url.host + ' ' + url.path)
    delete a
}

function saveFileDialogFinished(a)
{
    print("save to this file! " + a.files)
    delete a
}

function showSaveFileDialog()
{
    dialog = new SaveFileDialog
    dialog.show()
    dialog.finished.connect(saveFileDialogFinished)
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

