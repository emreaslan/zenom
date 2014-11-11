#-------------------------------------------------
#
# Prepares qtcreator wizard files
#
#-------------------------------------------------
TEMPLATE = subdirs

include( ../../zenom.pri )

WIZARD_FILE = $$system(cp project.pro.template zenom/project.pro)
WIZARD_FILE = $$system(replace "%XENOMAI_HEADERS%" $${XENOMAI_HEADERS} -- zenom/project.pro)
WIZARD_FILE = $$system(replace "%XENOMAI_LIBS%" $${XENOMAI_LIBS} -- zenom/project.pro)
WIZARD_FILE = $$system(replace "%ZENOM_INSTALL_HEADERS%" $${ZENOM_INSTALL_HEADERS} -- zenom/project.pro)
WIZARD_FILE = $$system(replace "%ZENOM_INSTALL_LIBS%" $${ZENOM_INSTALL_LIBS} -- zenom/project.pro)


wizard.files  += zenom/logo.png
wizard.files  += zenom/main.cpp
wizard.files  += zenom/project.pro
wizard.files  += zenom/project.znm
wizard.files  += zenom/wizard.xml
wizard.path   = $${QTCREATOR_WIZARDS_PATH}/zenom
INSTALLS += wizard
