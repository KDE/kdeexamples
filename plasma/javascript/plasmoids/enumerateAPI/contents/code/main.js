var text = true

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

var commonProperties = new Array
commonProperties.push("objectName")
commonProperties.push("parent")
commonProperties.push("id")
commonProperties.push("opacity")
commonProperties.push("enabled")
commonProperties.push("visible")
commonProperties.push("pos")
commonProperties.push("x")
commonProperties.push("y")
commonProperties.push("z")
commonProperties.push("rotation")
commonProperties.push("scale")
commonProperties.push("transformOriginPoint")
commonProperties.push("palette")
commonProperties.push("font")
commonProperties.push("layoutDirection")
commonProperties.push("size")
commonProperties.push("focusPolicy")
commonProperties.push("windowFlags")
commonProperties.push("windowTitle")
commonProperties.push("geometry")
commonProperties.push("parentWidget")
commonProperties.push("stylesheet")
commonProperties.push("nativeWidget")
commonProperties.push("destroyed(QObject*)")
commonProperties.push("destroyed()")
commonProperties.push("deleteLater()")
commonProperties.push("parentChanged()")
commonProperties.push("opacityChanged()")
commonProperties.push("visibleChanged()")
commonProperties.push("enabledChanged()")
commonProperties.push("xChanged()")
commonProperties.push("yChanged()")
commonProperties.push("zChanged()")
commonProperties.push("rotationChanged()")
commonProperties.push("scaleChanged()")
commonProperties.push("close()")
commonProperties.push("newProxyWidget(const QWidget*)")
commonProperties.push("styleSheet()")
commonProperties.push("timerEvent(QTimerEvent*)")

function enumerateObject(name, obj, excludeCommon)
{
    var rv
    if (text) {
        rv = name + '\n';
    } else {
        rv = '<p><b>' + name + "</b><ul>\n";
    }

    for (i in obj) {
        if (excludeCommon && commonProperties.indexOf(i) != -1) {
            continue;
        }

        if (text) {
            rv += '  * '
        } else {
            rv += '<li>'
        }

        if (i.substr(i.length - 1, 1) != ')') {
            rv += typeof obj[i] + " " + i
            if (text) {
                rv += "\n"
            }
        } else {
            openbracket = i.lastIndexOf('(')
            objname = i.substr(0, openbracket)
            if (text) {
                rv += 'function ' + i + '\n'
            } else {
                rv += "<i>function</i> " + i
            }
        }

        if (!text) {
            rv += "</li>\n"
        }
    }

    if (text) {
        rv += "\n"
    } else {
        rv += "</ul>"
    }

    return rv
}

// WIDGET API
var widgetApi = ''
for (index in classNames) {
    var widgetName = classNames[index]
    var widget = new this[widgetName]
    widgetApi += enumerateObject(widgetName, widget, true)
    widget.deleteLater()
}

layout = new LinearLayout
tabbar = new TabBar
display = new TextEdit
display.readOnly = true
display.text = widgetApi
tabbar.addTab(i18n("Widgets"), display)

// LAYOUTS API
var layoutApi = ''
layoutApi += enumerateObject("LinearLayout", layout, true)
var q = new PushButton
print('*****************************************************************************')
var gl = new GridLayout(q)
layoutApi += enumerateObject("GridLayout", layout, true)
q.deleteLater()
print('*****************************************************************************')
var p = new PushButton
var l = new AnchorLayout(p)
layoutApi += enumerateObject("AnchorLayout", l, true)
p.deleteLater()
l = 0

display = new TextEdit
display.readOnly = true
display.text = layoutApi
tabbar.addTab(i18n("Layouts"), display)

// IMAGE API
fsvg = new FrameSvg('panel-background')
var imageApi = enumerateObject('FrameSvg', fsvg, false)
svg = new Svg('panel-background')
imageApi += enumerateObject('Svg', svg, false)
pixmap = new QPixmap
imageApi += enumerateObject('QPixmap', pixmap, false)

display = new TextEdit
display.readOnly = true
display.text = imageApi
tabbar.addTab(i18n("Images"), display)

// PAINTING API
var paintingApi = ''
var p = new QColor
paintingApi += enumerateObject('QColor', p, false)
p = new QFont
paintingApi += enumerateObject('QFont', p, false)
p = new QPoint
paintingApi = enumerateObject('QPainter', p, false)
p = new QPainter
paintingApi += enumerateObject('QPainter', p, false)
p = new QPen
paintingApi += enumerateObject('QPen', p, false)
p = new QPoint
paintingApi += enumerateObject('QPoint', p, false)
p = new QRectF
paintingApi += enumerateObject('QRectF', p, false)
p = new QSizeF(2,2)
paintingApi += enumerateObject('QSizeF', p, false)
p = 0

display = new TextEdit
display.readOnly = true
display.text = paintingApi
tabbar.addTab(i18n("Painting"), display)

// DATAENGINE API
var dataApi = ''
var d = dataEngine("time")
dataApi += enumerateObject("DataEngine", d, false)
var d = dataEngine("time").serviceForSource("Local")
var d = service("time", "Local")
dataApi += enumerateObject("Service", d, false)
d = 0

display = new TextEdit
display.readOnly = true
display.text = dataApi
tabbar.addTab(i18n("DataEngine"), display)

tabbar.adjustSize()
layout.addItem(tabbar)

plasmoid.gc()
