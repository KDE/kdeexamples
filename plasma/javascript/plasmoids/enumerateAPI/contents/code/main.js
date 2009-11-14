classNames = new Array()
classNames.push('BusyWidget')
classNames.push('CheckBox')
classNames.push('ComboBox')
classNames.push('FlashingLabel')
classNames.push('Frame')
classNames.push('GroupBox')
classNames.push('IconWidget')
classNames.push('ItemBackground')
classNames.push('Label')
classNames.push('LineEdit')
classNames.push('Meter')
classNames.push('PushButton')
classNames.push('RadioButton')
classNames.push('ScrollBar')
classNames.push('ScrollWidget')
classNames.push('Separator')
classNames.push('SignalPlotter')
classNames.push('Slider')
classNames.push('SpinBox')
classNames.push('SvgWidget')
classNames.push('TabBar')
classNames.push('TextEdit')
classNames.push('ToolButton')
classNames.push('TreeView')
classNames.push('VideoWidget')
classNames.push('WebView')

// ScrollWidget

var commonProperties = new Array
commonProperties.push("objectName" )
commonProperties.push("parent" )
commonProperties.push("id" )
commonProperties.push("opacity" )
commonProperties.push("enabled" )
commonProperties.push("visible" )
commonProperties.push("pos" )
commonProperties.push("x" )
commonProperties.push("y" )
commonProperties.push("z" )
commonProperties.push("rotation" )
commonProperties.push("scale" )
commonProperties.push("transformOriginPoint" )
commonProperties.push("palette" )
commonProperties.push("font" )
commonProperties.push("layoutDirection" )
commonProperties.push("size" )
commonProperties.push("focusPolicy" )
commonProperties.push("windowFlags" )
commonProperties.push("windowTitle" )
commonProperties.push("geometry" )
commonProperties.push("parentWidget" )
commonProperties.push("stylesheet" )
commonProperties.push("nativeWidget" )
commonProperties.push("destroyed(QObject*)" )
commonProperties.push("destroyed()" )
commonProperties.push("deleteLater()" )
commonProperties.push("parentChanged()" )
commonProperties.push("opacityChanged()" )
commonProperties.push("visibleChanged()" )
commonProperties.push("enabledChanged()" )
commonProperties.push("xChanged()" )
commonProperties.push("yChanged()" )
commonProperties.push("zChanged()" )
commonProperties.push("rotationChanged()" )
commonProperties.push("scaleChanged()" )
commonProperties.push("close()" )
commonProperties.push("newProxyWidget(const QWidget*)" )
commonProperties.push("styleSheet()")
commonProperties.push("timerEvent(QTimerEvent*)")

var apihtml = ''
var apitext = ''
for (index in classNames) {
    apihtml += '<p><b>' + classNames[index] + "</b><ul>\n";
    apitext += classNames[index] + '\n';
    widget = new this[classNames[index]]
    for (i in widget) {
        if (commonProperties.indexOf(i) == -1) {
            apihtml += '<li>'
            apitext += '  * '
            if (i.substr(i.length - 1, 1) != ')') {
                detail = typeof widget[i] + " " + i
                apihtml += detail
                apitext += detail + '\n'
            } else {
                openbracket = i.lastIndexOf('(')
                objname = i.substr(0, openbracket)
                //print(typeof widget[objname]['connect'] + ' <-------- see? ' + classNames[index] + '::' + i)
                /*
                print("checking " + objname)
                for (j in widget[objname]) {
                    print("is " + j)
                }
                if (typeof widget[objname]['connect'] == "function") {
                    apihtml += "<i>signal</i> " + i
                    apitext += 'signal ' + i + '\n'
                } else {
                */
                    apihtml += "<i>function</i> " + i
                    apitext += 'function ' + i + '\n'
                //}
            }
            apihtml += "</li>\n"
        }
    }
    apihtml += "</ul>"
    apitext += '\n'
    widget.deleteLater()
}

layout = new LinearLayout
tabbar = new TabBar
display = new TextEdit
display.readOnly = true
display.text = apihtml
tabbar.addTab(i18n("HTML"), display)

bg = new ItemBackground
display = new TextEdit
display.readOnly = true
display.text = apitext
tabbar.addTab(i18n("Text"), display)
layout.addItem(tabbar)

