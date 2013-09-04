panel = panelById(panelIds[0])
panel.length = screenGeometry(panel.screen).width / 2
panel.alignment = "center"
sleep(1000)
panel.alignment = "left"
panel.offset = screenGeometry(panel.screen).width / 5
panel.height = 32
sleep(1000)
panel.offset = 0
panel.length = screenGeometry(panel.screen).width
panel.height = 24
